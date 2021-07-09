/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
