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

#ifndef KCHARTABSTRACTCOORDINATEPLANE_P_H
#define KCHARTABSTRACTCOORDINATEPLANE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the KD Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "KChartAbstractArea_p.h"
#include <KChartAbstractCoordinatePlane.h>
#include <KChartGridAttributes.h>
#include <KChartAbstractGrid.h>
#include <KChartZoomParameters.h>
#include "KChartMath_p.h"

#include <QStack>

QT_BEGIN_NAMESPACE
class QRubberBand;
QT_END_NAMESPACE

namespace KChart {


/**
 * \internal
 */
class Q_DECL_HIDDEN AbstractCoordinatePlane::Private : public AbstractArea::Private
{
    friend class AbstractCoordinatePlane;
protected:
    explicit Private();
    virtual ~Private() {
        delete grid;
    };

    virtual void initialize()
    {
        qDebug("ERROR: Calling AbstractCoordinatePlane::Private::initialize()");
        // can not call the base class: grid = new AbstractGrid();
    }

    virtual bool isVisiblePoint(
        const AbstractCoordinatePlane * plane,
        const QPointF& point ) const
    {
        Q_UNUSED( plane );
        Q_UNUSED( point );
        return true;
    }

    KChart::Chart* parent;
    AbstractGrid* grid;
    QRect geometry;
    AbstractDiagramList diagrams;
    GridAttributes gridAttributes;
    AbstractCoordinatePlane *referenceCoordinatePlane;

    bool enableCornerSpacers;

    bool enableRubberBandZooming;
    QRubberBand* rubberBand;
    QPoint rubberBandOrigin;

    QStack< ZoomParameters > rubberBandZoomConfigHistory;
};


inline AbstractCoordinatePlane::AbstractCoordinatePlane( Private * p, KChart::Chart* parent )
    : AbstractArea( p )
{
    if ( p )
        p->parent = parent;
    init();
}
inline AbstractCoordinatePlane::Private * AbstractCoordinatePlane::d_func()
{
    return static_cast<Private*>( AbstractArea::d_func() );
}
inline const AbstractCoordinatePlane::Private * AbstractCoordinatePlane::d_func() const
{
    return static_cast<const Private*>( AbstractArea::d_func() );
}


}

#endif /* KCHARTABSTRACTCOORDINATEPLANE_P_H*/
