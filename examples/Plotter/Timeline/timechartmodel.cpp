/**
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KD Chart library.
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "timechartmodel.h"

TimeChartModel::TimeChartModel( QObject* parent )
    : QSortFilterProxyModel( parent )
{
}

QPair< QDateTime, QDateTime > TimeChartModel::visibleRange() const
{
    return range;
}

void TimeChartModel::setVisibleRange( const QDateTime& start, const QDateTime& end )
{
    const QPair< QDateTime, QDateTime > r = qMakePair( start, end );
    if ( r == range )
        return;

    range = r;
    invalidateFilter();
}

void TimeChartModel::setVisibleStart( const QDateTime& start )
{
    setVisibleRange( start, range.second );
}

void TimeChartModel::setVisibleEnd( const QDateTime& end )
{
    setVisibleRange( range.first, end );
}

/*!
 \reimp
 */
QVariant TimeChartModel::data( const QModelIndex& index, int role ) const
{
    const QVariant v = QSortFilterProxyModel::data( index, role );
    if ( index.column() % 2 != 0 || role != Qt::DisplayRole )
        return v;
    else
        return QDateTime::fromSecsSinceEpoch( 0 ).secsTo( v.toDateTime() ) / 3600.0;
}

/*!
 \reimp
 */
bool TimeChartModel::filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const
{
    const QModelIndex index = sourceModel()->index( source_row, 0, source_parent );
    const QDateTime date = index.data().toDateTime();
    return ( date >= range.first || range.first.isNull() ) &&
           ( date <= range.second || range.second.isNull() );
}
