/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTLEVEYJENNINGSGRID_H
#define KCHARTLEVEYJENNINGSGRID_H

#include "KChartCartesianGrid.h"

namespace KChart {

    class PaintContext;

    /**
     * \internal
     *
     * \brief Class for the grid in a Levey Jennings plane.
     *
     * The LeveyJenningsGrid interface is used
     * for calculating and for drawing
     * the horizonal grid lines, and the vertical grid lines
     * of a Levey Jennings coordinate plane.
     */
    class LeveyJenningsGrid : public CartesianGrid
    {
    public:
        LeveyJenningsGrid() : CartesianGrid() {}
        virtual ~LeveyJenningsGrid() {}

        void drawGrid( PaintContext* context ) override;

    private:
        DataDimensionsList calculateGrid( const DataDimensionsList& rawDataDimensions ) const override;
        DataDimension calculateGridXY( const DataDimension& rawDataDimension, 
                          Qt::Orientation orientation, bool adjustLower, bool adjustUpper ) const override;
        void calculateStepWidth( qreal start_, qreal end_, const QList<qreal>& granularities, Qt::Orientation orientation,
                                 qreal& stepWidth, qreal& subStepWidth, bool adjustLower, bool adjustUpper ) const override;
    };

}

#endif
