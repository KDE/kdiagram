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

#ifndef KCHART_STOCK_DIAGRAM_P_H
#define KCHART_STOCK_DIAGRAM_P_H

#include "KChartStockDiagram.h"
#include "KChartAbstractCartesianDiagram_p.h"
#include "KChartCartesianDiagramDataCompressor_p.h"
#include "KChartPaintContext.h"

namespace KChart {

class Q_DECL_HIDDEN StockDiagram::Private : public AbstractCartesianDiagram::Private
{
    friend class StockDiagram;

public:
    Private();
    Private( const Private& r );
    ~Private();

    Type type;
    StockDiagram* stockDiagram() { return static_cast< StockDiagram* >( diagram ); }

    QBrush upTrendCandlestickBrush;
    QBrush downTrendCandlestickBrush;
    QPen upTrendCandlestickPen;
    QPen downTrendCandlestickPen;

    QMap<int, QBrush> upTrendCandlestickBrushes;
    QMap<int, QBrush> downTrendCandlestickBrushes;
    QMap<int, QPen> upTrendCandlestickPens;
    QMap<int, QPen> downTrendCandlestickPens;

    QPen lowHighLinePen;
    QMap<int, QPen> lowHighLinePens;


    void drawOHLCBar( int dataset, const CartesianDiagramDataCompressor::DataPoint &open,
                      const CartesianDiagramDataCompressor::DataPoint &high,
                      const CartesianDiagramDataCompressor::DataPoint &low,
                      const CartesianDiagramDataCompressor::DataPoint &close,
                      PaintContext *context );
    void drawHLCBar( int dataset, const CartesianDiagramDataCompressor::DataPoint &high,
                     const CartesianDiagramDataCompressor::DataPoint &low,
                     const CartesianDiagramDataCompressor::DataPoint &close,
                     PaintContext *context );
    void drawCandlestick( int dataset, const CartesianDiagramDataCompressor::DataPoint &open,
                          const CartesianDiagramDataCompressor::DataPoint &high,
                          const CartesianDiagramDataCompressor::DataPoint &low,
                          const CartesianDiagramDataCompressor::DataPoint &close,
                          PaintContext *context );

private:
    void drawLine( int dataset, int col, const QPointF &point1, const QPointF &p2, PaintContext *context );
    QPointF projectPoint( PaintContext *context, const QPointF &point ) const;
    QRectF projectCandlestick( PaintContext *context, const QPointF &open, const QPointF &close, qreal width ) const;
    int openValueColumn() const;
    int highValueColumn() const;
    int lowValueColumn() const;
    int closeValueColumn() const;

    class ThreeDPainter;
};

KCHART_IMPL_DERIVED_DIAGRAM( StockDiagram, AbstractCartesianDiagram, CartesianCoordinatePlane )

}

#endif // KCHART_STOCK_DIAGRAM_P_H

