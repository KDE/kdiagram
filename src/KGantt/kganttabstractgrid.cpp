/*
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "kganttabstractgrid.h"
#include "kganttabstractgrid_p.h"

#include <QRectF>

using namespace KGantt;


AbstractGrid::AbstractGrid( QObject* parent )
    : QObject( parent ),
      _d( new Private )
{
}

AbstractGrid::~AbstractGrid()
{
    delete _d;
}

#define d d_func()

void AbstractGrid::setModel( QAbstractItemModel* model )
{
    d->model = model;
}

QAbstractItemModel* AbstractGrid::model() const
{
    return d->model;
}

void AbstractGrid::setRootIndex( const QModelIndex& idx )
{
    d->root = idx;
}

QModelIndex AbstractGrid::rootIndex() const
{
    return d->root;
}

bool AbstractGrid::isSatisfiedConstraint( const Constraint& c ) const
{
    // First check if the data is valid,
    // TODO: review if true is the right choice
    if ( !c.startIndex().isValid() || !c.endIndex().isValid() ) return true;

    Span ss = mapToChart( c.startIndex() );
    Span es = mapToChart( c.endIndex() );
    return ( ss.end() <= es.start() );
}

qreal AbstractGrid::mapToChart( const QVariant& value ) const
{
    Q_UNUSED( value );
    return -1.0;
}

QVariant AbstractGrid::mapFromChart( qreal x ) const
{
    Q_UNUSED( x );
    return QVariant();
}

void AbstractGrid::drawBackground(QPainter* paint, const QRectF& rect)
{
    Q_UNUSED(paint);
    Q_UNUSED(rect);
}

void AbstractGrid::drawForeground(QPainter* paint, const QRectF& rect)
{
    Q_UNUSED(paint);
    Q_UNUSED(rect);
}


#include "moc_kganttabstractgrid.cpp"

