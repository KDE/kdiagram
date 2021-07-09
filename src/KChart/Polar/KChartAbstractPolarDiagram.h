/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
