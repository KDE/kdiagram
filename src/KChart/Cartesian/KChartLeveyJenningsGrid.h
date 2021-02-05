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
