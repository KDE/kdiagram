/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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

        void addDiagram( AbstractDiagram* diagram ) override;

        LeveyJenningsGridAttributes gridAttributes() const;
        void setGridAttributes( const LeveyJenningsGridAttributes& attr );
   
    protected: 
        const QPointF translateBack( const QPointF& screenPoint ) const;

    private:
        LeveyJenningsGrid* grid() const;
    };

}

#endif
