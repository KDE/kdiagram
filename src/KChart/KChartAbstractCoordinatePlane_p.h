/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
    ~Private() override {
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
