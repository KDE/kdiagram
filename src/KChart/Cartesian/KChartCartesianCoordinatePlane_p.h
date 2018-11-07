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

#ifndef KCHARTCARTESIANCOORDINATEPLANE_P_H
#define KCHARTCARTESIANCOORDINATEPLANE_P_H

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

#include "KChartAbstractCoordinatePlane_p.h"
#include "CartesianCoordinateTransformation.h"
#include "KChartCartesianGrid.h"
#include "KChartZoomParameters.h"

#include "KChartMath_p.h"


namespace KChart {

/**
 * \internal
 */
class Q_DECL_HIDDEN CartesianCoordinatePlane::Private : public AbstractCoordinatePlane::Private
{
    friend class CartesianCoordinatePlane;
public:
    explicit Private();
    virtual ~Private() {  }

    void initialize() Q_DECL_OVERRIDE
    {
        bPaintIsRunning = false;
        coordinateTransformation.axesCalcModeX = Linear;
        coordinateTransformation.axesCalcModeY = Linear;
        grid = new CartesianGrid();
    }

    static Private *get( CartesianCoordinatePlane *plane )
    {
        return static_cast< Private * >( plane->d_func() );
    }

    bool isVisiblePoint( const AbstractCoordinatePlane * plane, const QPointF& point ) const Q_DECL_OVERRIDE
    {
        QPointF p = point;
        const CartesianCoordinatePlane* const ref =
            qobject_cast< const CartesianCoordinatePlane* >(
                              const_cast< AbstractCoordinatePlane* >( plane )->sharedAxisMasterPlane() );
        const CartesianCoordinatePlane* const cartPlane =
            dynamic_cast< const CartesianCoordinatePlane* >( plane );
        if ( ref != nullptr && ref != cartPlane ) {
            const QPointF logical = ref->translateBack( point ) - cartPlane->visibleDataRange().topLeft()
                                                                + ref->visibleDataRange().topLeft();
            p = ref->translate( logical );
        }
        const QRectF geo( plane->geometry() );
        return geo.contains( p );
    }


    // the coordinate plane will calculate the coordinate transformation:
    CoordinateTransformation coordinateTransformation;

    bool bPaintIsRunning;

    // true after setGridAttributes( Qt::Orientation ) was used,
    // false if resetGridAttributes( Qt::Orientation ) was called
    bool hasOwnGridAttributesHorizontal;
    bool hasOwnGridAttributesVertical;

    // true after the first resize event came in
    // bool initialResizeEventReceived;

    // true if the coordinate plane scales isometrically
    // (same scaling ratio from data to screen space for both axes)
    bool isometricScaling;

    GridAttributes gridAttributesHorizontal;
    GridAttributes gridAttributesVertical;

    qreal horizontalMin;
    qreal horizontalMax;
    qreal verticalMin;
    qreal verticalMax;

    // autoAdjustHorizontalRangeToData determines if and how much the horizontal range is adjusted.
    // A value of 100 means that the fixed horizontal range will be used (e.g. set by the user),
    // otherwise the value will be the percentage of the diagram's horizontal range that is to be
    // left empty (i.e., it resembles the 'gap' between the horizontal extrema and the border of the
    // diagram).
    unsigned int autoAdjustHorizontalRangeToData;

    // autoAdjustVerticalRangeToData determines if and how much the vertical range is adjusted.
    // A value of 100 means that the fixed vertical range will be used (e.g. set by the user),
    // otherwise the value will be the percentage of the diagram's vertical range that is to be
    // left empty (i.e., it resembles the 'gap' between the vertical extrema and the border of the
    // diagram).
    unsigned int autoAdjustVerticalRangeToData;
    bool autoAdjustGridToZoom;

    bool fixedDataCoordinateSpaceRelation;
    bool xAxisStartAtZero;
    QSizeF fixedDataCoordinateSpaceRelationPinnedSize;
    ZoomParameters fixedDataCoordinateSpaceRelationPinnedZoom;

    DataDimensionsList dimensions;

    bool reverseVerticalPlane;
    bool reverseHorizontalPlane;
};


KCHART_IMPL_DERIVED_PLANE(CartesianCoordinatePlane, AbstractCoordinatePlane)

}

#endif /* KCHARTBARDIAGRAM_P_H */
