/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
