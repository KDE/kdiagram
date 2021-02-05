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

#ifndef CARTESIANCOORDINATETRANSFORMATION_H
#define CARTESIANCOORDINATETRANSFORMATION_H

#include <QList>
#include <QRectF>
#include <QPointF>

#include "KChartZoomParameters.h"

#include <cmath>
#include <limits>

namespace KChart {

    // FIXME: if this struct is used more often, we need to make it a class
    // with proper accessor methods:

    /**
      * \internal
      */
    struct CoordinateTransformation {

        CoordinateTransformation()
            : axesCalcModeY( CartesianCoordinatePlane::Linear ),
              axesCalcModeX( CartesianCoordinatePlane::Linear ),
              isPositiveX( true ),
              isPositiveY( true )
        {}

        CartesianCoordinatePlane::AxesCalcMode axesCalcModeY;
        CartesianCoordinatePlane::AxesCalcMode axesCalcModeX;

        ZoomParameters zoom;

        QTransform transform;
        QTransform backTransform;
        // a logarithmic scale cannot cross zero, so we have to know which side we are on.
        bool isPositiveX;
        bool isPositiveY;

        qreal logTransform( qreal value, bool isPositiveRange ) const
        {
            if ( isPositiveRange ) {
                return log10( value );
            } else  {
                return -log10( -value );
            }
        }

        qreal logTransformBack( qreal value, bool wasPositive ) const
        {
            if ( wasPositive ) {
                return pow( 10.0, value );
            } else {
                return -pow( 10.0, -value );
            }
        }

        void updateTransform( const QRectF& constDataRect, const QRectF& screenRect )
        {
            QRectF dataRect = constDataRect;
            if ( axesCalcModeX == CartesianCoordinatePlane::Logarithmic ) {
                // the data will be scaled by logTransform() later, so scale its bounds as well
                isPositiveX = dataRect.left() >= 0.0;
                dataRect.setLeft( logTransform( dataRect.left(), isPositiveX ) );
                dataRect.setRight( logTransform( dataRect.right(), isPositiveX ) );
            }
            if ( axesCalcModeY == CartesianCoordinatePlane::Logarithmic ) {
                isPositiveY = dataRect.top() >= 0.0;
                dataRect.setTop( logTransform( dataRect.top(), isPositiveY  ) );
                dataRect.setBottom( logTransform( dataRect.bottom(), isPositiveY ) );
            }

            transform.reset();
            // read the following transformation sequence from bottom to top(!)
            transform.translate( screenRect.left(), screenRect.bottom() );
            transform.scale( screenRect.width(), screenRect.height() );

            // TODO: mirror in case of "reverse" axes?

            // transform into screen space
            transform.translate( 0.5, -0.5 );
            transform.scale( zoom.xFactor, zoom.yFactor );
            transform.translate( -zoom.xCenter, 1.0 - zoom.yCenter );
            // zoom
            transform.scale( 1.0 / dataRect.width(), 1.0 / dataRect.height() );
            transform.translate( -dataRect.left(), -dataRect.bottom() );
            // transform into the unit square

            backTransform = transform.inverted();
        }

        // convert data space point to screen point
        inline QPointF translate( const QPointF& dataPoint ) const
        {
            QPointF data = dataPoint;
            if ( axesCalcModeX == CartesianCoordinatePlane::Logarithmic ) {
                data.setX( logTransform( data.x(), isPositiveX  ) );
            }
            if ( axesCalcModeY == CartesianCoordinatePlane::Logarithmic ) {
                data.setY( logTransform( data.y(), isPositiveY ) );
            }

            return transform.map( data );
        }

        // convert screen point to data space point
        inline const QPointF translateBack( const QPointF& screenPoint ) const
        {
            QPointF ret = backTransform.map( screenPoint );
            if ( axesCalcModeX == CartesianCoordinatePlane::Logarithmic ) {
                ret.setX( logTransformBack( ret.x(), isPositiveX ) );
            }
            if ( axesCalcModeY == CartesianCoordinatePlane::Logarithmic ) {
                ret.setY( logTransformBack( ret.y(), isPositiveY ) );
            }
            return ret;
        }
    };

    typedef QList<CoordinateTransformation> CoordinateTransformationList;

}

#endif
