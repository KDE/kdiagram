/*
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

#include "KChartPaintContext.h"
#include "KChartAbstractCoordinatePlane.h"

#include "KChartMath_p.h"

#include <QRectF>
#include <QPainter>

using namespace KChart;

#define d (d_func())

class Q_DECL_HIDDEN PaintContext::Private {

public:
    QPainter* painter;
    QRectF rect;
    AbstractCoordinatePlane* plane;

    Private()
        : painter( nullptr )
        , plane ( nullptr )
    {}
};

PaintContext::PaintContext()
    : _d ( new Private() )
{
}

PaintContext::~PaintContext()
{
    delete _d;
}

const QRectF PaintContext::rectangle() const
{
    return d->rect;
}

void PaintContext::setRectangle ( const QRectF& rect )
{
    d->rect = rect;
}

QPainter* PaintContext::painter() const
{
    return d->painter;
}

void PaintContext::setPainter( QPainter* painter )
{
    d->painter = painter;
}

AbstractCoordinatePlane* PaintContext::coordinatePlane() const
{
    return d->plane;
}

void PaintContext::setCoordinatePlane( AbstractCoordinatePlane* plane)
{
    d->plane = plane;
}
