/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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

        ~TernaryGrid() override;

        void drawGrid( PaintContext* context ) override;
        DataDimensionsList calculateGrid( const DataDimensionsList& rawDataDimensions ) const override;

        /** Returns two QSizeF objects specifying the dimension of the
            margins needed between each corner of the diagram and the
            border of the drawing area. Margins are required because
            the tick marks are placed outside of the triangles
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
