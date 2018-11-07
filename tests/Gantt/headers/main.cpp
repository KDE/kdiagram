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
#include <QStandardItemModel>
#include <QPainter>
#include <QHeaderView>
#include <QTreeView>

#include <KGanttView>
#include <KGanttDateTimeGrid>

using namespace KGantt;

/* A custom formatter that displays tabs for every 10 minutes.
 */
class MyDateTimeScaleFormatter : public DateTimeScaleFormatter {
public:
    MyDateTimeScaleFormatter();

    /*reimp*/QDateTime nextRangeBegin( const QDateTime& datetime ) const Q_DECL_OVERRIDE;
    /*reimp*/QDateTime currentRangeBegin( const QDateTime& datetime ) const Q_DECL_OVERRIDE;

    /*reimp*/QString text( const QDateTime& dt ) const Q_DECL_OVERRIDE;
};

MyDateTimeScaleFormatter::MyDateTimeScaleFormatter()
    : DateTimeScaleFormatter( Hour, "hh" )
{
}

QDateTime MyDateTimeScaleFormatter::nextRangeBegin( const QDateTime& datetime ) const
{
    return currentRangeBegin( datetime ).addSecs( 60*10 );
}

QDateTime MyDateTimeScaleFormatter::currentRangeBegin( const QDateTime& datetime ) const
{
    QDateTime dt( datetime );
    dt.setTime( QTime( dt.time().hour(), ( dt.time().minute()/10 ) * 10, 0, 0 ) );
    return dt;
}

QString MyDateTimeScaleFormatter::text( const QDateTime& dt ) const
{
    return QObject::tr( ":%1\nXX" ).arg( dt.time().toString( "mm" ) );
}

/* A custom headerview that is taller than standard
 * so we can fit more lines into it on the graphicsview
 * side.
 */
class MyHeaderView : public QHeaderView {
public:
    explicit MyHeaderView( QWidget* parent = nullptr )
        : QHeaderView( Qt::Horizontal, parent ) {
    }

    /*reimp*/QSize sizeHint() const Q_DECL_OVERRIDE {
        QSize s = QHeaderView::sizeHint(); s.rheight() *= 3; return s;
    }
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    QStandardItemModel model( 1, 1 );
    model.setHeaderData( 0, Qt::Horizontal, QObject::tr( "Task" ) );

    /*** A view with some alternative header labels ***/
    View view1;
    DateTimeGrid grid1;
    grid1.setUserDefinedUpperScale( new DateTimeScaleFormatter( DateTimeScaleFormatter::Year,
                                                                QString::fromLatin1( "yyyy" ),
                                                                QString::fromLatin1( "In the year %1." ),
                                                                Qt::AlignLeft ) );
    grid1.setUserDefinedLowerScale( new DateTimeScaleFormatter( DateTimeScaleFormatter::Month,
                                                                QString::fromLatin1( "MMMM" ),
                                                                QString::fromLatin1( "In the month %1." ),
                                                                Qt::AlignRight ) );
    grid1.setScale( DateTimeGrid::ScaleUserDefined );
    grid1.setDayWidth( 6. );
    view1.setGrid( &grid1 );
    view1.setModel( &model );
    view1.show();

    /*** A view with header and vertical grid lines for every 10 minutes */
    View view2;
    QTreeView* tw = qobject_cast<QTreeView*>( view2.leftView() );
    if ( tw ) tw->setHeader( new MyHeaderView );
    DateTimeGrid grid2;
    grid2.setDayWidth( 5000 );
    grid2.setUserDefinedUpperScale( new DateTimeScaleFormatter( DateTimeScaleFormatter::Hour, QString::fromLatin1( "hh" ) ) );
    grid2.setUserDefinedLowerScale( new MyDateTimeScaleFormatter );
    grid2.setScale( DateTimeGrid::ScaleUserDefined );
    view2.setGrid( &grid2 );
    view2.setModel( &model );
    view2.show();

    return app.exec();
}
