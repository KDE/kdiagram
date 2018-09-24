/**
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QDateTime>
#include <QStandardItemModel>
#include <QDebug>
#include <QSlider>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include <QPixmapCache>
#include <QPushButton>
#include <QPrinter>
#include <QPrintDialog>
#include <QMenu>

#include <KGanttView>
#include <KGanttGraphicsView>
#include <KGanttConstraintModel>
#include <KGanttDateTimeGrid>

class MyStandardItem : public QStandardItem {
public:
  MyStandardItem( const QVariant& v ) : QStandardItem()
    {
        setData( v, Qt::DisplayRole );
        //setFlags( flags() & ~Qt::ItemIsEditable );
    }
  MyStandardItem( const QString& v ) : QStandardItem()
    {
        setData( v, Qt::DisplayRole );
        //setFlags( flags() & ~Qt::ItemIsEditable );
    }
    MyStandardItem( const QDateTime& dt, int role ) : QStandardItem()
    {
        setData( QVariant::fromValue( dt ), role );
    }
};

class MyWidget : public QWidget {
    Q_OBJECT
public:
    MyWidget() : QWidget( 0 )
    {
        qDebug() << "Building data";
        //proxyModel.setSourceModel( &model );
        for ( int h = 0; h < 20; ++h ) {
	  QStandardItem* topitem = new MyStandardItem( QString::fromLatin1("Top Item %1").arg( h ));
            for ( int i = 0; i < 20; ++i ) {
	      QStandardItem* item = new MyStandardItem( QString::fromLatin1("Multi Item %1").arg( i ));
                for ( int j=0; j < 30; j+=3 ) {
                    item->appendRow( QList<QStandardItem*>()
                                     << new MyStandardItem( QString::fromLatin1( "Item %1" ).arg( j ) )
                                     << new MyStandardItem( KGantt::TypeTask )
                                     << new MyStandardItem( QDateTime::currentDateTime().addDays( j ), KGantt::StartTimeRole )
                                     << new MyStandardItem( QDateTime::currentDateTime().addDays( j+1+i/7 ), KGantt::EndTimeRole )
                                     << new MyStandardItem( 50 ) );
                }
                item->appendRow( QList<QStandardItem*>()
                                 << new MyStandardItem( QString::fromLatin1( "Event" ) )
                                 << new MyStandardItem( KGantt::TypeEvent )
                                 << new MyStandardItem( QDateTime::currentDateTime(), KGantt::StartTimeRole )
                                 << new MyStandardItem( QDateTime(), KGantt::EndTimeRole )
                                 << new MyStandardItem( QString() ) );

                topitem->appendRow( QList<QStandardItem*>()
                                    << item
                                    << new MyStandardItem( KGantt::TypeMulti )
                                    << new MyStandardItem( QString() )
                                    << new MyStandardItem( QString() )
                                    << new MyStandardItem( QString() ) );
            }
            model.appendRow( QList<QStandardItem*>()
                             << topitem
                             << new MyStandardItem(KGantt::TypeMulti/*Summary*/ )
                             << new MyStandardItem(QString())
                             << new MyStandardItem(QString())
                             << new MyStandardItem(QString()) );
        }
        model.appendRow( QList<QStandardItem*>()
                         << new MyStandardItem( QString::fromLatin1( "No data" ) ) );

        //cmodel.addConstraint( KGantt::Constraint( proxyModel.index( 0, 3 ), proxyModel.index( 10, 3 ) ) );
        //cmodel.addConstraint( KGantt::Constraint( proxyModel.index( 10, 3 ), proxyModel.index( 5, 3 ) ) );
        QModelIndex pidx = model.index( 0, 0 );
        pidx = model.index( 0, 0, pidx );
        cmodel.addConstraint( KGantt::Constraint( model.index( 0, 0, pidx), model.index( 1, 0, pidx ) ) );
        cmodel.addConstraint( KGantt::Constraint( model.index( 1, 0, pidx), model.index( 0, 0, pidx ) ) );
        cmodel.addConstraint( KGantt::Constraint( model.index( 1, 0, pidx), model.index( 10, 0, pidx ) ) );
        cmodel.addConstraint( KGantt::Constraint( model.index( 3, 0, pidx), model.index( 5, 0, pidx ) ) );
        cmodel.addConstraint( KGantt::Constraint( model.index( 7, 0, pidx), model.index( 4, 0, pidx ) ) );

        qDebug() << "Creating view";
        slider.setOrientation( Qt::Horizontal );
        slider.setRange( 1, 10000 );
        slider.setValue( 100 );
        QVBoxLayout* l = new QVBoxLayout( this );
        l->addWidget( &view );
        l->addWidget( &slider );
        grid.setStartDateTime( QDateTime::currentDateTime().addDays( -3 ) );
        grid.setDayWidth( 100 );
        //grid.setNoInformationBrush( Qt::NoBrush );
        view.setGrid( &grid );
        view.setModel(&model);
        //view.setConstraintModel( &cmodel );
        connect( &slider, SIGNAL(valueChanged(int)),
                 this, SLOT(slotZoom(int)) );


	QPushButton* pb1 = new QPushButton( tr("Print Preview..."));
	QPushButton* pb2 = new QPushButton( tr("Print..."));
	l->addWidget(pb1);
	l->addWidget(pb2);
	connect(pb1,SIGNAL(clicked()),this,SLOT(slotPrintPreview()));
	connect(pb2,SIGNAL(clicked()),this,SLOT(slotPrint()));

        view.graphicsView()->setHeaderContextMenuPolicy( Qt::CustomContextMenu );
        connect( view.graphicsView(), SIGNAL(headerContextMenuRequested(QPoint)),
                 this, SLOT(slotHeaderMenu(QPoint)) );
    }

public slots:
    void slotZoom( int z )
    {
        grid.setDayWidth( z );
    }

    void slotPrintPreview()
    {
	QPixmap pix(1000,200);
	pix.fill(Qt::white);
	QPainter painter(&pix);
	view.print(&painter, pix.rect());
        painter.end();
	QLabel* label = new QLabel;
	label->setPixmap(pix);
	label->show();
    }
    void slotPrint()
    {
        QPrinter printer( QPrinter::HighResolution );
        QPrintDialog pd( &printer, this );
        if ( pd.exec() == QDialog::Accepted ) {
            /*
            printer.setResolution( 600 );
            QPainter p( &printer );
            QFont f;
            f.setPixelSize( 9 );
            p.setFont( f );
            view.print( &p );
            */
            QRectF r = view.graphicsView()->mapToScene( view.graphicsView()->viewport()->rect() ).boundingRect();
            view.print( &printer, r.left(), r.right() );
        }
    }
    void slotHeaderMenu( const QPoint& pt )
    {
        QMenu menu;
        menu.addAction( tr( "This" ) );
        menu.addAction( tr( "is" ) );
        menu.addAction( tr( "just" ) );
        menu.addAction( tr( "a" ) );
        menu.addAction( tr( "test" ) );
        menu.exec( pt );
    }

private:
    KGantt::View view;
    KGantt::DateTimeGrid grid;
    QSlider slider;
    QStandardItemModel model;
    KGantt::ConstraintModel cmodel;
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );
    QPixmapCache::setCacheLimit( 30*1024 );

    MyWidget w;
    w.show();

    return app.exec();
}

#include "main.moc"
