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

#ifndef KCHARTRADARGrid_H
#define KCHARTRADARGrid_H

//#include "KChartRadarCoordinatePlane.h"
#include "KChartAbstractGrid.h"

namespace KChart {

    class PaintContext;
    class RadarCoordinatePlane;

    /**
     * \internal
     *
     * \brief Class for the grid in a radar plane.
     *
     * The RadarGrid interface is used
     * for calculating and for drawing
     * the grid lines of a radar charts including "axis" 
     * labels.
     */
    class RadarGrid : public AbstractGrid
    {
    public:
        RadarGrid() : AbstractGrid() {}
        virtual ~RadarGrid() {}

        void drawGrid( PaintContext* context ) override;

    private:
        DataDimensionsList calculateGrid(
            const DataDimensionsList& rawDataDimensions ) const override;
    };

}

#endif
