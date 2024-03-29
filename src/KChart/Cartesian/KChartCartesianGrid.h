/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTCARTESIANGRID_H
#define KCHARTCARTESIANGRID_H

#include "KChartCartesianCoordinatePlane.h"
#include "KChartAbstractGrid.h"

namespace KChart {

    class PaintContext;
    class CartesianCoordinatePlane;

    /**
     * \internal
     *
     * \brief Class for the grid in a cartesian plane.
     *
     * The CartesianGrid interface is used
     * for calculating and for drawing
     * the horizontal grid lines, and the vertical grid lines
     * of a cartesian coordinate plane.
     */
    class CartesianGrid : public AbstractGrid
    {
    public:
        CartesianGrid();
        ~CartesianGrid() override;

        int minimalSteps() const;
        void setMinimalSteps(int minsteps);

        int maximalSteps() const;
        void setMaximalSteps(int maxsteps);

        void drawGrid( PaintContext* context ) override;

    private:
        int m_minsteps;
        int m_maxsteps;
        
        DataDimensionsList calculateGrid(
            const DataDimensionsList& rawDataDimensions ) const override;

        /**
         * Helper function called by calculateGrid() to calculate the grid of one dimension.
         *
         * Classes derived from CartesianGrid can overwrite calculateGridXY() if they need
         * a special way of calculating the start or end or step width of their grid lines.
         * 
         * \param adjustLower If true, the function adjusts the start value
         * so it matches the position of a grid line, if false the start value is
         * the raw data dimension start value.
         * \param adjustUpper If true, the function adjusts the end value
         * so it matches the position of a grid line, if false the end value is
         * the raw data dimension end value.
         */
        virtual DataDimension calculateGridXY(
            const DataDimension& rawDataDimension,
            Qt::Orientation orientation,
            bool adjustLower, bool adjustUpper ) const;

        /**
          * Helper function called by calculateGridXY().
          *
          * Classes derived from CartesianGrid can overwrite calculateStepWidth() if they need
          * a way of calculating the step width, based upon given start/end values
          * for their horizontal or vertical grid lines which is different from the default
          * implementation.
          *
          * \note The CartesianGrid class tries to keep the displayed range as close to
          * the raw data range as possible, so in most cases there should be no reason
          * to change the default implementation: Using
          * KChart::GridAttributes::setGridGranularitySequence() should be sufficient.
          *
          * \param start The raw start value of the data range.
          * \param end The raw end value of the data range.
          * \param granularities The list of allowed granularities.
          * \param adjustLower If true, the function adjusts the start value
          * so it matches the position of a grid line, if false the start value is
          * left as it is, in any case the value is adjusted for internal calculation only.
          * \param adjustUpper If true, the function adjusts the end value
          * so it matches the position of a grid line, if false the end value is
          * left as it is, in any case the value is adjusted for internal calculation only.
          *
          * \returns stepWidth: One of the values from the granularities
          * list, optionally multiplied by a positive (or negative, resp.)
          * power of ten. subStepWidth: The matching width for sub-grid lines.
          */
        virtual void calculateStepWidth(
            qreal start, qreal end,
            const QList<qreal>& granularities,
            Qt::Orientation orientation,
            qreal& stepWidth, qreal& subStepWidth,
            bool adjustLower, bool adjustUpper ) const;
    };

}

#endif
