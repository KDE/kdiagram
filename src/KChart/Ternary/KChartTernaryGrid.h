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

#ifndef KCHARTTERNARYGRID_H
#define KCHARTTERNARYGRID_H

#include <QList>

#include "KChartAbstractGrid.h"
#include "KChartTextLabelCache.h"

namespace KChart {

    struct TickInfo {
        TickInfo( qreal percentage = 0, int depth = 0 );
        qreal percentage;
        int depth;
    };

    bool operator==(const TickInfo&, const TickInfo& );

    class PaintContext;

    // VERIFY: Grids are not public API, are they?
    class TernaryGrid : public AbstractGrid
    {
    public:
        TernaryGrid();

        virtual ~TernaryGrid();

        void drawGrid( PaintContext* context ) override;
        DataDimensionsList calculateGrid( const DataDimensionsList& rawDataDimensions ) const override;

        /** Returns two QSizeF objects specifying the dimension of the
            margins needed between each corner of the diagram and the
            border of the drawing area. Margins are required because
            the tick marks are placed outside of the trianges
            containing rectangle.
            The margins are returned in <em>diagram coordinates</em>,
            since the grid does not know about widget coordinates.
        */
        QPair<QSizeF, QSizeF> requiredMargins() const;
        /** Return the locations of the grid lines, so that axes can
            draw axis rulers at the correct positions.
            This information is valid after the grid has been
            painted (that is, the axes need to be painted after the
            grid. */
        const QVector<TickInfo>& tickInfo() const;
    private:
        QVector<TickInfo> m_tickInfo;
        // QList<PrerenderedLabel> m_labels;
    };

}

#endif
