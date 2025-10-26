/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef PAINTCONTEXT_H
#define PAINTCONTEXT_H

#include "KChartGlobal.h"
#include <QRectF>

QT_BEGIN_NAMESPACE
class QPainter;
QT_END_NAMESPACE

namespace KChart
{

class AbstractCoordinatePlane;

/**
 * @brief Stores information about painting diagrams
 * \internal
 */
class KCHART_EXPORT PaintContext
{
public:
    PaintContext();
    ~PaintContext();

    const QRectF rectangle() const;
    void setRectangle(const QRectF &rect);

    QPainter *painter() const;
    void setPainter(QPainter *painter);

    AbstractCoordinatePlane *coordinatePlane() const;
    void setCoordinatePlane(AbstractCoordinatePlane *plane);

private:
    class Private;
    Private *_d;
    Private *d_func()
    {
        return _d;
    }
    const Private *d_func() const
    {
        return _d;
    }
};

}

#endif /* PAINTCONTEXT_H */
