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

#ifndef KCHARTABSTRACTPOLARDIAGRAM_H
#define KCHARTABSTRACTPOLARDIAGRAM_H

#include "KChartPolarCoordinatePlane.h"
#include "KChartAbstractDiagram.h"

namespace KChart {

    class GridAttributes;

    /**
      * @brief Base class for diagrams based on a polar coordinate system.
      */
    class KCHART_EXPORT AbstractPolarDiagram : public AbstractDiagram
    {
        Q_OBJECT
        Q_DISABLE_COPY( AbstractPolarDiagram )
        KCHART_DECLARE_DERIVED_DIAGRAM( AbstractPolarDiagram, PolarCoordinatePlane )

    public:
        explicit AbstractPolarDiagram (
            QWidget* parent = nullptr, PolarCoordinatePlane* plane = nullptr );
        virtual ~AbstractPolarDiagram() {}

        virtual qreal valueTotals () const = 0;
        virtual qreal numberOfValuesPerDataset() const = 0;
        virtual qreal numberOfDatasets() const { return 1; };
        virtual qreal numberOfGridRings() const = 0;

        const PolarCoordinatePlane * polarCoordinatePlane() const;

        int columnCount() const;
        int rowCount() const;
    };

}

#endif
