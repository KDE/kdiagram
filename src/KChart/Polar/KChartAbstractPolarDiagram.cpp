/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartAbstractPolarDiagram.h"
#include "KChartAbstractPolarDiagram_p.h"

#include "KChartMath_p.h"

using namespace KChart;

AbstractPolarDiagram::Private::Private()
{
}

AbstractPolarDiagram::Private::~Private()
{
}

void AbstractPolarDiagram::init()
{
}

#define d d_func()

AbstractPolarDiagram::AbstractPolarDiagram(QWidget *parent, PolarCoordinatePlane *plane)
    : AbstractDiagram(new Private(), parent, plane)
{
}

const PolarCoordinatePlane *AbstractPolarDiagram::polarCoordinatePlane() const
{
    return dynamic_cast<const PolarCoordinatePlane *>(coordinatePlane());
}

int AbstractPolarDiagram::columnCount() const
{
    return static_cast<int>(numberOfValuesPerDataset());
}

int AbstractPolarDiagram::rowCount() const
{
    return static_cast<int>(numberOfDatasets());
}
