/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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

