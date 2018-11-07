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

#ifndef KCHARTABSTRACTCARTESIANDIAGRAM_H
#define KCHARTABSTRACTCARTESIANDIAGRAM_H

#include "KChartCartesianCoordinatePlane.h"
#include "KChartAbstractDiagram.h"
#include "KChartCartesianAxis.h"

namespace KChart {

    class GridAttributes;

    /**
     * @brief Base class for diagrams based on a cartesian coordianate system.
     *
     * The AbstractCartesianDiagram interface adds those elements that are
     * specific to diagrams based on a cartesian coordinate system to the
     * basic AbstractDiagram interface.
     */
    class KCHART_EXPORT AbstractCartesianDiagram : public AbstractDiagram
    {
        Q_OBJECT
        Q_DISABLE_COPY( AbstractCartesianDiagram )
        KCHART_DECLARE_DERIVED_DIAGRAM( AbstractCartesianDiagram, CartesianCoordinatePlane )

    public:
        explicit AbstractCartesianDiagram( QWidget* parent = nullptr, CartesianCoordinatePlane* plane = nullptr );
        virtual ~AbstractCartesianDiagram();

        /**
         * Returns true if both diagrams have the same settings.
         */
        bool compare( const AbstractCartesianDiagram* other ) const;

#if defined(Q_COMPILER_MANGLES_RETURN_TYPE)
        virtual const int numberOfAbscissaSegments() const = 0;
        virtual const int numberOfOrdinateSegments() const = 0;
#else
        virtual int numberOfAbscissaSegments() const = 0;
        virtual int numberOfOrdinateSegments() const = 0;
#endif
        /**
         * Add the axis to the diagram. The diagram takes ownership of the axis
         * and will delete it.
         *
         * To gain back ownership (e.g. for assigning the axis to another diagram)
         * use the takeAxis method, before calling addAxis on the other diagram.
         *
         * \sa takeAxis
        */
        virtual void addAxis( CartesianAxis * axis );
        /**
         * Removes the axis from the diagram, without deleting it.
         *
         * The diagram no longer owns the axis, so it is
         * the caller's responsibility to delete the axis.
         *
         * \sa addAxis
        */
        virtual void takeAxis( CartesianAxis * axis );
        /**
         * @return a list of all axes added to the diagram
        */
        virtual KChart::CartesianAxisList axes() const;

        /**
          * Triggers layouting of all coordinate planes on the current chart.
          * Normally you don't need to call this method. It's handled automatically for you.
         */
        virtual void layoutPlanes();
        /** \reimpl */
        void setCoordinatePlane( AbstractCoordinatePlane* plane ) Q_DECL_OVERRIDE;

        /**
          * Makes this diagram use another diagram \a diagram as reference diagram with relative offset
          * \a offset.
          * To share cartesian axes between different diagrams there might be cases when you need that.
          * Normally you don't.
          * \sa examples/SharedAbscissa
          */
        virtual void setReferenceDiagram( AbstractCartesianDiagram* diagram, const QPointF& offset = QPointF() );
        /**
          * @return this diagram's reference diagram
          *  \sa setReferenceDiagram
          */
        virtual AbstractCartesianDiagram* referenceDiagram() const;
        /**
          * @return the relative offset of this diagram's reference diagram
          * \sa setReferenceDiagram
          */
        virtual QPointF referenceDiagramOffset() const;

        /* reimpl */
        void setModel( QAbstractItemModel* model ) Q_DECL_OVERRIDE;
        /* reimpl */
        void setRootIndex( const QModelIndex& index ) Q_DECL_OVERRIDE;
        /* reimpl */
        void setAttributesModel( AttributesModel* model ) Q_DECL_OVERRIDE;

    protected Q_SLOTS:
        void connectAttributesModel( AttributesModel* );

    protected:
        /** @return the 3D item depth of the model index \a index */
        virtual qreal threeDItemDepth( const QModelIndex& index ) const = 0;
        /** @return the 3D item depth of the data set \a column */
        virtual qreal threeDItemDepth( int column ) const = 0;
    };
}

#endif
