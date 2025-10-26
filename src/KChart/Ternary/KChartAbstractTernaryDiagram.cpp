/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartAbstractTernaryDiagram.h"
#include "KChartAbstractTernaryDiagram_p.h"

#include "KChartTernaryCoordinatePlane.h"

using namespace KChart;

AbstractTernaryDiagram::Private::Private()
    : AbstractDiagram::Private()
{
}

void AbstractTernaryDiagram::init()
{
}

#define d d_func()

AbstractTernaryDiagram::AbstractTernaryDiagram(QWidget *parent, TernaryCoordinatePlane *plane)
    : AbstractDiagram(parent, plane)
{
}

AbstractTernaryDiagram::~AbstractTernaryDiagram()
{
    while (!d->axesList.isEmpty()) {
        TernaryAxis *axis = d->axesList.takeFirst();
        delete axis;
    }
}

void AbstractTernaryDiagram::addAxis(TernaryAxis *axis)
{
    d->axesList.append(axis);
    // FIXME update
}

void AbstractTernaryDiagram::takeAxis(TernaryAxis *axis)
{
    int index = d->axesList.indexOf(axis);
    if (index != -1)
        d->axesList.removeAt(index);
    // FIXME update
}

TernaryAxisList AbstractTernaryDiagram::axes() const
{
    return d->axesList;
}

void AbstractTernaryDiagram::paint(PaintContext *paintContext)
{
    d->paint(paintContext);
}
