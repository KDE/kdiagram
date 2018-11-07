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

#ifndef KCHARTPOLARCOORDINATEPLANE_P_H
#define KCHARTPOLARCOORDINATEPLANE_P_H

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
#include "KChartZoomParameters.h"
#include "KChartPolarGrid.h"
#include "KChartMath_p.h"


namespace KChart {

/**
 * \internal
 */
struct PolarCoordinatePlane::CoordinateTransformation
{
    // represents the distance of the diagram coordinate origin to the
    // origin of the coordinate plane space:
    QPointF originTranslation;
    qreal radiusUnit;
    qreal angleUnit;
    qreal minValue;

    qreal startPosition;
    ZoomParameters zoom;

    static QPointF polarToCartesian( qreal R, qreal theta )
    {
        // de-inline me
        return QPointF( R * cos( DEGTORAD( theta ) ), R * sin( DEGTORAD( theta ) ) );
    }

    inline const QPointF translate( const QPointF& diagramPoint ) const
    {
        // ### de-inline me
        // calculate the polar coordinates
        const qreal x = (diagramPoint.x() * radiusUnit) - (minValue * radiusUnit);
//qDebug() << x << "=" << diagramPoint.x() << "*" << radiusUnit << "  startPosition: " << startPosition;
        const qreal y = ( diagramPoint.y() * -angleUnit) - 90.0 - startPosition;
        // convert to cartesian coordinates
        QPointF cartesianPoint = polarToCartesian( x, y );
        cartesianPoint.setX( cartesianPoint.x() * zoom.xFactor );
        cartesianPoint.setY( cartesianPoint.y() * zoom.yFactor );

        QPointF newOrigin = originTranslation;
        qreal minOrigin = qMin( newOrigin.x(), newOrigin.y() );
        newOrigin.setX( newOrigin.x() + minOrigin * ( 1 - zoom.xCenter * 2 ) * zoom.xFactor );
        newOrigin.setY( newOrigin.y() + minOrigin * ( 1 - zoom.yCenter * 2 ) * zoom.yFactor );

        return newOrigin + cartesianPoint;
    }

    inline const QPointF translatePolar( const QPointF& diagramPoint ) const
    {
        // ### de-inline me
        return QPointF( diagramPoint.x() * angleUnit, diagramPoint.y() * radiusUnit );
    }
};

class Q_DECL_HIDDEN PolarCoordinatePlane::Private : public AbstractCoordinatePlane::Private
{
    friend class PolarCoordinatePlane;
public:
    explicit Private()
        : currentTransformation(nullptr)
        , initialResizeEventReceived(false )
        , hasOwnGridAttributesCircular ( false )
        , hasOwnGridAttributesSagittal ( false )
    {}

    virtual ~Private() { }

    void initialize() Q_DECL_OVERRIDE
    {
        grid = new PolarGrid();
    }

    static QRectF contentsRect( const PolarCoordinatePlane* plane );

    // the coordinate plane will calculate coordinate transformations for all
    // diagrams and store them here:
    CoordinateTransformationList coordinateTransformations;
    // when painting, this pointer selects the coordinate transformation for
    // the current diagram:
    CoordinateTransformation* currentTransformation;
    // the reactangle occupied by the diagrams, in plane coordinates
    QRectF contentRect;
    // true after the first resize event came in
    bool initialResizeEventReceived;

    // true after setGridAttributes( Qt::Orientation ) was used,
    // false if resetGridAttributes( Qt::Orientation ) was called
    bool hasOwnGridAttributesCircular;
    bool hasOwnGridAttributesSagittal;

    GridAttributes gridAttributesCircular;
    GridAttributes gridAttributesSagittal;

    qreal newZoomX, newZoomY;
};



KCHART_IMPL_DERIVED_PLANE(PolarCoordinatePlane, AbstractCoordinatePlane)

}

#endif /* KCHARTBARDIAGRAM_P_H */
