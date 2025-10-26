/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartPaintContext.h"
#include "KChartAbstractCoordinatePlane.h"

#include "KChartMath_p.h"

#include <QPainter>

using namespace KChart;

#define d (d_func())

class Q_DECL_HIDDEN PaintContext::Private
{
public:
    QPainter *painter;
    QRectF rect;
    AbstractCoordinatePlane *plane;

    Private()
        : painter(nullptr)
        , plane(nullptr)
    {
    }
};

PaintContext::PaintContext()
    : _d(new Private())
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

void PaintContext::setRectangle(const QRectF &rect)
{
    d->rect = rect;
}

QPainter *PaintContext::painter() const
{
    return d->painter;
}

void PaintContext::setPainter(QPainter *painter)
{
    d->painter = painter;
}

AbstractCoordinatePlane *PaintContext::coordinatePlane() const
{
    return d->plane;
}

void PaintContext::setCoordinatePlane(AbstractCoordinatePlane *plane)
{
    d->plane = plane;
}
