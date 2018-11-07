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
#include <QListView>

#include <KGanttView>
#include <KGanttConstraintModel>
#include <KGanttDateTimeGrid>
#include <KGanttListViewRowController>

class MyStandardItem : public QStandardItem {
public:
    MyStandardItem( const QVariant& v, int role = Qt::DisplayRole ) : QStandardItem()
    {
        setData( v, role );
    }
    MyStandardItem( const QString& v ) : QStandardItem()
    {
        setData( v, Qt::DisplayRole );
    }
};

class MyListView : public QListView {
public:
  MyListView(QWidget* parent = nullptr) : QListView(parent)
  {
    // Make some space for the header
    setViewportMargins(0, fontMetrics().height()*2+4*frameWidth(), 0, 0);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
  }
};

class MyWidget : public QWidget {
    Q_OBJECT
public:
    MyWidget() : QWidget( nullptr )
    {
        qDebug() << "Building data";
        //proxyModel.setSourceModel( &model );
	for ( int i = 0; i < 10; ++i ) {
	  QStandardItem* item = new MyStandardItem( QString::fromLatin1("Multi Item %1").arg(i) );
	  for ( int j=0; j < 20; j+=3 ) {
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

	  model.appendRow( QList<QStandardItem*>()
			   << item
			   << new MyStandardItem( KGantt::TypeMulti )
			   << new MyStandardItem( QString() )
			   << new MyStandardItem( QString() )
			   << new MyStandardItem( QString() ) );
	}

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
        slider.setRange( 1, 1000 );
        slider.setValue( 100 );
        QVBoxLayout* l = new QVBoxLayout( this );
        l->addWidget( &view );
        l->addWidget( &slider );
        grid.setStartDateTime( QDateTime::currentDateTime().addDays( -3 ) );
        grid.setDayWidth( 100 );
		grid.setFreeDays( QSet<Qt::DayOfWeek>() << Qt::Saturday << Qt::Sunday );
		grid.setFreeDaysBrush( QBrush( Qt::red ) );
	QListView* lv = new MyListView;
	view.setLeftView(lv);
	view.setRowController( new KGantt::ListViewRowController(lv,view.ganttProxyModel()));
        view.setGrid( &grid );
        view.setModel(&model);
        //view.setConstraintModel( &cmodel );
        connect( &slider, SIGNAL(valueChanged(int)),
                 this, SLOT(slotZoom(int)) );
    }

public slots:
    void slotZoom( int z )
    {
        grid.setDayWidth( z );
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

    MyWidget w;
    w.show();

    return app.exec();
}

#include "main.moc"
