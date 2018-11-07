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

#ifndef KCHART_POLAR_COORDINATEPLANE_H
#define KCHART_POLAR_COORDINATEPLANE_H

#include "KChartAbstractCoordinatePlane.h"

namespace KChart {

    class Chart;
    class PaintContext;

    /**
      * @brief Polar coordinate plane
      */
    class KCHART_EXPORT PolarCoordinatePlane : public AbstractCoordinatePlane
    {
        Q_OBJECT

        Q_DISABLE_COPY( PolarCoordinatePlane )
        KCHART_DECLARE_PRIVATE_DERIVED_PARENT( PolarCoordinatePlane, Chart* )

    public:
        struct CoordinateTransformation;
        typedef QList<CoordinateTransformation> CoordinateTransformationList;

        explicit PolarCoordinatePlane ( Chart* parent = nullptr );
        ~PolarCoordinatePlane();

        void addDiagram ( AbstractDiagram* diagram ) Q_DECL_OVERRIDE;

        const QPointF translate ( const QPointF& diagramPoint ) const Q_DECL_OVERRIDE;
        const QPointF translatePolar ( const QPointF& diagramPoint ) const;

        /** \brief Specify the rotation of the coordinate plane.
          *
          * In a pie diagram this indicates the position where the first pie starts,
          * in a polar diagram it specifies the Zero position of the circular axis:
          *
          * \image html polar-plane-start-position.png "Illustration of \"start position\" property"
          *
          * \sa startPosition
          */
        void setStartPosition( qreal degrees );
        /** Retrieve the rotation of the coordinate plane.
          * \sa setStartPosition
          */
        qreal startPosition() const;

        qreal zoomFactorX() const Q_DECL_OVERRIDE;
        qreal zoomFactorY() const Q_DECL_OVERRIDE;

        void setZoomFactors( qreal factorX, qreal factorY ) Q_DECL_OVERRIDE;
        void setZoomFactorX( qreal factor ) Q_DECL_OVERRIDE;
        void setZoomFactorY( qreal factor ) Q_DECL_OVERRIDE;

        QPointF zoomCenter() const Q_DECL_OVERRIDE;

        void setZoomCenter( const QPointF& center ) Q_DECL_OVERRIDE;

        /**
         * Set the attributes to be used for grid lines drawn in circular
         * direction (or in sagittal direction, resp.).
         *
         * To disable circular grid painting, for example, your code should like this:
         * \code
         * GridAttributes ga = plane->gridAttributes( bool );
         * ga.setGridVisible( false );
         * plane-setGridAttributes( bool, ga );
         * \endcode
         *
         * \note setGridAttributes overwrites the global attributes that
         * were set by AbstractCoordinatePlane::setGlobalGridAttributes.
         * To re-activate these global attributes you can call
         * resetGridAttributes.
         *
         * \sa resetGridAttributes, gridAttributes
         * \sa AbstractCoordinatePlane::setGlobalGridAttributes
         * \sa hasOwnGridAttributes
         */
        void setGridAttributes( bool circular, const GridAttributes & );

        /**
         * Reset the attributes to be used for grid lines drawn in circular
         * direction (or in sagittal direction, resp.).
         * By calling this method you specify that the global attributes set by
         * AbstractCoordinatePlane::setGlobalGridAttributes be used.
         *
         * \sa setGridAttributes, gridAttributes
         * \sa AbstractCoordinatePlane::globalGridAttributes
         * \sa hasOwnGridAttributes
         */
        void resetGridAttributes( bool circular );

        /**
         * \return The attributes used for grid lines drawn in circular
         * direction (or in sagittal direction, resp.).
         *
         * \note This function always returns a valid set of grid attributes:
         * If no special grid attributes were set for this direction
         * the global attributes are returned, as returned by
         * AbstractCoordinatePlane::globalGridAttributes.
         *
         * \sa setGridAttributes
         * \sa resetGridAttributes
         * \sa AbstractCoordinatePlane::globalGridAttributes
         * \sa hasOwnGridAttributes
         */
        const GridAttributes gridAttributes( bool circular ) const;

        /**
         * \return Returns whether the grid attributes have been set for the
         * respective direction via setGridAttributes( bool circular ).
         *
         * If false, the grid will use the global attributes set
         * by AbstractCoordinatePlane::globalGridAttributes (or the default
         * attributes, resp.)
         *
         * \sa setGridAttributes
         * \sa resetGridAttributes
         * \sa AbstractCoordinatePlane::globalGridAttributes
         */
        bool hasOwnGridAttributes( bool circular ) const;

        qreal angleUnit() const;
        qreal radiusUnit() const;

        /** reimpl */
        void paint( QPainter* ) Q_DECL_OVERRIDE;

    protected:
        DataDimensionsList getDataDimensionsList() const Q_DECL_OVERRIDE;
        void paintEvent ( QPaintEvent* );
        void resizeEvent ( QResizeEvent* );

        void layoutDiagrams() Q_DECL_OVERRIDE;
    protected Q_SLOTS:
        void slotLayoutChanged( AbstractDiagram* diagram );
        void adjustZoomAndRepaint();

    private:
        void setHasOwnGridAttributes( bool circular, bool on );
    };

}

#endif
