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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TIMECHARTMODEL_H
#define TIMECHARTMODEL_H

#include <QDateTime>
#include <QSortFilterProxyModel>
#include <QPair>

class TimeChartModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TimeChartModel( QObject* parent = nullptr );

    QPair< QDateTime, QDateTime > visibleRange() const;
    
public Q_SLOTS:
    void setVisibleRange( const QDateTime& start, const QDateTime& end );
    void setVisibleStart( const QDateTime& start );
    void setVisibleEnd( const QDateTime& end );

    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const Q_DECL_OVERRIDE;

protected:
    bool filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const Q_DECL_OVERRIDE;

private:
    QPair< QDateTime, QDateTime > range;
};

#endif
