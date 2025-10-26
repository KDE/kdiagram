/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTPOLARGrid_H
#define KCHARTPOLARGrid_H

#include "KChartAbstractGrid.h"
#include "KChartPolarCoordinatePlane.h"

namespace KChart
{

class PaintContext;
class PolarCoordinatePlane;

/**
 * \internal
 *
 * \brief Class for the grid in a polar plane.
 *
 * The PolarGrid interface is used
 * for calculating and for drawing
 * the sagittal grid lines, and the circular grid lines
 * of a polar coordinate plane.
 */
class PolarGrid : public AbstractGrid
{
public:
    PolarGrid()
        : AbstractGrid()
    {
    }
    ~PolarGrid() override
    {
    }

    void drawGrid(PaintContext *context) override;

private:
    DataDimensionsList calculateGrid(const DataDimensionsList &rawDataDimensions) const override;
};

}

#endif
