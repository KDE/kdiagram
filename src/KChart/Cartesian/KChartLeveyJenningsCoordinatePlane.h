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

#ifndef KCHARTLEVEYJENNINGSCOORDINATEPLANE_H
#define KCHARTLEVEYJENNINGSCOORDINATEPLANE_H

#include "KChartCartesianCoordinatePlane.h"

#include "KChartLeveyJenningsGridAttributes.h"

namespace KChart {

    class LeveyJenningsGrid;

    /**
      * @brief Levey Jennings coordinate plane
      * This is actually nothing real more than a plain cartesian
      * coordinate plane. The difference is, that only Levey Jennings
      * Diagrams can be added to it.
      */
    class KCHART_EXPORT LeveyJenningsCoordinatePlane
        : public CartesianCoordinatePlane
    {
        Q_OBJECT
        Q_DISABLE_COPY( LeveyJenningsCoordinatePlane )
        KCHART_DECLARE_PRIVATE_DERIVED_PARENT( LeveyJenningsCoordinatePlane, Chart* )

        friend class LeveyJenningsGrid;

    public:
        explicit LeveyJenningsCoordinatePlane( Chart* parent = nullptr );
        ~LeveyJenningsCoordinatePlane();

        void addDiagram( AbstractDiagram* diagram ) Q_DECL_OVERRIDE;

        LeveyJenningsGridAttributes gridAttributes() const;
        void setGridAttributes( const LeveyJenningsGridAttributes& attr );
   
    protected: 
        const QPointF translateBack( const QPointF& screenPoint ) const;

    private:
        LeveyJenningsGrid* grid() const;
    };

}

#endif
