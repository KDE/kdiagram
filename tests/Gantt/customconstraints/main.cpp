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
#include <QMenu>

#include <KGanttView>
#include <KGanttGraphicsView>
#include <KGanttConstraintModel>
#include <KGanttDateTimeGrid>

class MyGraphicsView : public KGantt::GraphicsView {
    Q_OBJECT
public:
    MyGraphicsView( QWidget* parent=0 ) : KGantt::GraphicsView( parent )
    {
    }

    /*reimp*/void addConstraint( const QModelIndex& from,
                                 const QModelIndex& to,
                                 Qt::KeyboardModifiers modifiers ) Q_DECL_OVERRIDE
    {
        qDebug() << "MyGraphicsView::addConstraint()";
        if ( isReadOnly() ) return;
        KGantt::ConstraintModel* cmodel = constraintModel();
        KGantt::Constraint c( from, to, ( modifiers&Qt::ShiftModifier )?KGantt::Constraint::TypeHard:KGantt::Constraint::TypeSoft );
        c.setData( KGantt::Constraint::ValidConstraintPen, QPen( QColor( Qt::green ), 3, Qt::DashLine ) );
        c.setData( KGantt::Constraint::InvalidConstraintPen, QPen( QColor( Qt::blue ), 3, Qt::DashLine ) );
        if ( cmodel->hasConstraint( c ) ) cmodel->removeConstraint( c );
        else cmodel->addConstraint( c );
    }

};

class MyStandardItem : public QStandardItem {
public:
  MyStandardItem( const QVariant& v ) : QStandardItem()
    {
        setData( v, Qt::DisplayRole );
    }
  MyStandardItem( const QString& v ) : QStandardItem()
    {
        setData( v, Qt::DisplayRole );
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
        view.setGraphicsView( new MyGraphicsView );

        qDebug() << "Building data";
        //proxyModel.setSourceModel( &model );
        for ( int h = 0; h < 2; ++h ) {
            QList<QStandardItem*> items;
            items
                << new MyStandardItem( QString::fromLatin1( "Item %1" ).arg( h ) )
                << new MyStandardItem( KGantt::TypeTask )
                << new MyStandardItem( QDateTime::currentDateTime().addDays( h ), KGantt::StartTimeRole )
                << new MyStandardItem( QDateTime::currentDateTime().addDays( h+1 ), KGantt::EndTimeRole )
                << new MyStandardItem( 50 );
            model.appendRow( items );
        }

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
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );
    //QPixmapCache::setCacheLimit( 30*1024 );

    MyWidget w;
    w.show();

    return app.exec();
}

#include "main.moc"
