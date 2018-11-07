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

#ifndef KCHARTTERNARYCOORDINATEPLANE_H
#define KCHARTTERNARYCOORDINATEPLANE_H

#include "KChartAbstractCoordinatePlane.h"

namespace KChart {

    class TernaryGrid;

    /**
      * @brief Ternary coordinate plane
      */
    class KCHART_EXPORT TernaryCoordinatePlane
        : public AbstractCoordinatePlane
    {
        Q_OBJECT
        Q_DISABLE_COPY( TernaryCoordinatePlane )
        KCHART_DECLARE_PRIVATE_DERIVED_PARENT( TernaryCoordinatePlane, Chart* )

    public:
        explicit TernaryCoordinatePlane( Chart* parent = nullptr );
        ~TernaryCoordinatePlane();

        void addDiagram( AbstractDiagram* diagram ) Q_DECL_OVERRIDE;

        void layoutDiagrams() Q_DECL_OVERRIDE;

        const QPointF translate ( const QPointF& diagramPoint ) const Q_DECL_OVERRIDE;

        void paint( QPainter* ) Q_DECL_OVERRIDE;
        DataDimensionsList getDataDimensionsList() const Q_DECL_OVERRIDE;

        /** \reimpl */
        QSize minimumSizeHint() const;
        /** \reimpl */
        QSizePolicy sizePolicy() const;

    private:
        TernaryGrid* grid() const;
    };

}

#endif
