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

#include "KChartNormalLyingBarDiagram_p.h"

#include <QModelIndex>

#include "KChartBarDiagram.h"
#include "KChartTextAttributes.h"
#include "KChartAttributesModel.h"
#include "KChartAbstractCartesianDiagram.h"

using namespace KChart;
using namespace std;

NormalLyingBarDiagram::NormalLyingBarDiagram( BarDiagram* d )
    : BarDiagramType( d )
{
}

BarDiagram::BarType NormalLyingBarDiagram::type() const
{
    return BarDiagram::Normal;
}

// TODO there is a lot of duplication between this and the non-lying bar diagram, fix it someday...
const QPair<QPointF, QPointF> NormalLyingBarDiagram::calculateDataBoundaries() const
{
    const int rowCount = compressor().modelDataRows();
    const int colCount = compressor().modelDataColumns();

    const qreal xMin = 0.0;
    const qreal xMax = rowCount;
    qreal yMin = 0.0;
    qreal yMax = 0.0;

    bool isFirst = true;
    for ( int column = 0; column < colCount; ++column ) {
        for ( int row = 0; row < rowCount; ++row ) {
            const CartesianDiagramDataCompressor::CachePosition position( row, column );
            const CartesianDiagramDataCompressor::DataPoint point = compressor().data( position );
            const qreal value = ISNAN( point.value ) ? 0.0 : point.value;
            // this is always true yMin can be 0 in case all values
            // are the same
            // same for yMax it can be zero if all values are negative
            if ( isFirst ) {
                yMin = value;
                yMax = value;
                isFirst = false;
            } else {
                yMin = qMin( yMin, value );
                yMax = qMax( yMax, value );
            }
        }
    }

    // special cases
    if ( yMax == yMin ) {
        if ( yMin == 0.0 ) {
            yMax = 0.1; // we need at least a range
        } else if ( yMax < 0.0 ) {
            yMax = 0.0; // they are the same and negative
        } else if ( yMin > 0.0 ) {
            yMin = 0.0; // they are the same but positive
        }
    }
    const QPointF bottomLeft( QPointF( yMin, xMin ) );
    const QPointF topRight( QPointF( yMax, xMax ) );

    return QPair< QPointF, QPointF >( bottomLeft, topRight );
}

void NormalLyingBarDiagram::paint( PaintContext* ctx )
{
    // FIXME: in all LyingBarDiagram types, the datasets are rendered top to bottom, but the abscissa
    // (in that case Y axis) ticks are still bottom to top. So tick labels are in reverse order.
    reverseMapper().clear();

    const QPair<QPointF,QPointF> boundaries = diagram()->dataBoundaries(); // cached

    const QPointF boundLeft = ctx->coordinatePlane()->translate( boundaries.first ) ;
    const QPointF boundRight = ctx->coordinatePlane()->translate( boundaries.second );

    const int rowCount = attributesModel()->rowCount( attributesModelRootIndex() );
    const int colCount = attributesModel()->columnCount( attributesModelRootIndex() );

    BarAttributes ba = diagram()->barAttributes();
    qreal barWidth = 0;
    qreal maxDepth = 0;
    qreal width = boundLeft.y() - boundRight.y();
    qreal groupWidth = width / rowCount;
    qreal spaceBetweenBars = 0;
    qreal spaceBetweenGroups = 0;

    if ( ba.useFixedBarWidth() ) {

        barWidth = ba.fixedBarWidth();
        groupWidth += barWidth;

        // Pending Michel set a min and max value for the groupWidth
        // related to the area.width
        if ( groupWidth < 0 )
            groupWidth = 0;

        if ( groupWidth * rowCount > width )
            groupWidth = width / rowCount;
    }

    // maxLimit: allow the space between bars to be larger until area.width()
    // is covered by the groups.
    qreal maxLimit = rowCount * ( groupWidth + ( colCount - 1 ) * ba.fixedDataValueGap() );

    //Pending Michel: FixMe
    if ( ba.useFixedDataValueGap() ) {
        if ( width > maxLimit )
            spaceBetweenBars += ba.fixedDataValueGap();
        else
            spaceBetweenBars = ( width / rowCount - groupWidth ) / ( colCount - 1 );
    }

    if ( ba.useFixedValueBlockGap() ) {
        spaceBetweenGroups += ba.fixedValueBlockGap();
    }

    calculateValueAndGapWidths( rowCount, colCount,groupWidth,
                                barWidth, spaceBetweenBars, spaceBetweenGroups );

    LabelPaintCache lpc;

    for ( int row = 0; row < rowCount; row++ ) {
    qreal offset = -groupWidth / 2 + spaceBetweenGroups / 2;

        if ( ba.useFixedDataValueGap() ) {
            if ( spaceBetweenBars > 0 ) {
                if ( width > maxLimit ) {
                    offset -= ba.fixedDataValueGap();
                } else {
                    offset -= ( width / rowCount - groupWidth ) / ( colCount - 1 );
                }
            } else {
                offset += barWidth / 2;
            }
        }

        for ( int column = colCount-1; column >= 0; --column ) {
            // paint one group
            const CartesianDiagramDataCompressor::CachePosition position( row,  column );
            const CartesianDiagramDataCompressor::DataPoint point = compressor().data( position );
            const QModelIndex sourceIndex = attributesModel()->mapToSource( point.index );

            QPointF dataPoint( 0, ( point.key + 0.5 ) );
            const QPointF topLeft = ctx->coordinatePlane()->translate( dataPoint );
            dataPoint.rx() += point.value;
            const QPointF bottomRight = ctx->coordinatePlane()->translate( dataPoint ) +
                                        QPointF( 0, barWidth );

            const QRectF rect = QRectF( topLeft, bottomRight ).translated( 1.0, offset );
            m_private->addLabel( &lpc, sourceIndex, nullptr, PositionPoints( rect ), Position::North,
                                 Position::South, point.value );

            paintBars( ctx, sourceIndex, rect, maxDepth );

            offset += barWidth + spaceBetweenBars;
        }
    }
    m_private->paintDataValueTextsAndMarkers( ctx, lpc, false );
}
