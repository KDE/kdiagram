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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "KChartLeveyJenningsCoordinatePlane.h"
#include "KChartLeveyJenningsCoordinatePlane_p.h"

#include <QtDebug>
#include <QPainter>

#include "KChartPaintContext.h"
#include "KChartPainterSaver_p.h"
#include "KChartCartesianAxis.h"
#include "KChartLeveyJenningsDiagram.h"

using namespace KChart;

#define d d_func()

LeveyJenningsCoordinatePlane::Private::Private()
    : CartesianCoordinatePlane::Private()
{
}

LeveyJenningsCoordinatePlane::LeveyJenningsCoordinatePlane( Chart* parent )
    : CartesianCoordinatePlane( new Private(), parent )
{
}

LeveyJenningsCoordinatePlane::~LeveyJenningsCoordinatePlane()
{
}

void LeveyJenningsCoordinatePlane::init()
{
}

void LeveyJenningsCoordinatePlane::addDiagram( AbstractDiagram* diagram )
{
    Q_ASSERT_X ( dynamic_cast<LeveyJenningsDiagram*>( diagram ),
                 "LeveyJenningsCoordinatePlane::addDiagram", "Only Levey Jennings "
                 "diagrams can be added to a ternary coordinate plane!" );
    CartesianCoordinatePlane::addDiagram ( diagram );
}

LeveyJenningsGrid* LeveyJenningsCoordinatePlane::grid() const
{
    LeveyJenningsGrid* leveyJenningsGrid = static_cast<LeveyJenningsGrid*>( d->grid );
    Q_ASSERT( dynamic_cast<LeveyJenningsGrid*>( d->grid ) );
    return leveyJenningsGrid;
}

LeveyJenningsGridAttributes LeveyJenningsCoordinatePlane::gridAttributes() const
{
    return d->gridAttributes;
}

void LeveyJenningsCoordinatePlane::setGridAttributes( const LeveyJenningsGridAttributes& attr )
{
    d->gridAttributes = attr;
}

const QPointF LeveyJenningsCoordinatePlane::translateBack( const QPointF& screenPoint ) const
{
    return CartesianCoordinatePlane::translateBack( screenPoint );
}

#undef d
