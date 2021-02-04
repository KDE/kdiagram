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

#ifndef KCHART_STOCK_DIAGRAM_H
#define KCHART_STOCK_DIAGRAM_H

#include "KChartAbstractCartesianDiagram.h"
#include "KChartCartesianCoordinatePlane.h"
#include "KChartStockBarAttributes.h"
#include "KChartThreeDBarAttributes.h"

namespace KChart {
    class PaintContext;

class KCHART_EXPORT StockDiagram : public AbstractCartesianDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY( StockDiagram )

    KCHART_DECLARE_DERIVED_DIAGRAM( StockDiagram, CartesianCoordinatePlane )

public:
    enum Type {
        HighLowClose,
        OpenHighLowClose,
        Candlestick
    };

    explicit StockDiagram( QWidget *parent = nullptr, CartesianCoordinatePlane *plane = nullptr );
    ~StockDiagram();

 
    /**
      * Switches between the supported types of stock charts,
      * depending on \a type
      */
   void setType( Type type );
 
    /**
      * @return the type of this diagram
      */
   Type type() const;

    void setStockBarAttributes( const StockBarAttributes &attr );
    StockBarAttributes stockBarAttributes() const;

    void setStockBarAttributes( int column, const StockBarAttributes &attr );
    StockBarAttributes stockBarAttributes( int column ) const;

 
    /**
     * Sets the 3D attributes for all bars (i.e. candlesticks)
     *
     * @param attr The 3D attributes to set
     */
 
   /**
    * Sets the 3D attributes for the bar (i.e. candlestick) in certain column
    * of the diagram
    *
    * Note: Every column in a StockDiagram is represented by a row in the model
    *
    * @param column The column to set the 3D bar attributes for
    * @param attr The 3D attributes to set
    */
  void setThreeDBarAttributes( const ThreeDBarAttributes &attr );
 
    /**
     * Returns the 3D attributes for all bars (i.e. candlesticks)
     *
     * @return the 3D bar attributes
     */
    ThreeDBarAttributes threeDBarAttributes() const;

    /**
    * Returns the 3D attributes for a bars (i.e. candlestick) in a certain column
    * of the diagram
    *
    * Note: Every column in a StockDiagram is represented by a row in the model
    *
    * @param column The column to get the 3D bar attributes for
    * @return The 3D attributes for the specified column
    */
    ThreeDBarAttributes threeDBarAttributes( int column ) const;

    void setThreeDBarAttributes( int column, const ThreeDBarAttributes &attr );

    void setLowHighLinePen( const QPen &pen );
    QPen lowHighLinePen() const;

    void setLowHighLinePen( int column, const QPen &pen );
    QPen lowHighLinePen( int column ) const;

    void setUpTrendCandlestickBrush( const QBrush &brush );
    QBrush upTrendCandlestickBrush() const;

    void setDownTrendCandlestickBrush( const QBrush &brush );
    QBrush downTrendCandlestickBrush() const;

    void setUpTrendCandlestickBrush( int column, const QBrush &brush );
    QBrush upTrendCandlestickBrush( int column ) const;

    void setDownTrendCandlestickBrush( int column, const QBrush &brush );
    QBrush downTrendCandlestickBrush( int column ) const;

    void setUpTrendCandlestickPen( const QPen &pen );
    QPen upTrendCandlestickPen() const;

    void setDownTrendCandlestickPen( const QPen &pen );
    QPen downTrendCandlestickPen() const;

    void setUpTrendCandlestickPen( int column, const QPen &pen );
    QPen upTrendCandlestickPen( int column ) const;

    void setDownTrendCandlestickPen( int column, const QPen &pen );
    QPen downTrendCandlestickPen( int column ) const;

#if defined(Q_COMPILER_MANGLES_RETURN_TYPE)
    virtual const int numberOfAbscissaSegments() const;
    virtual const int numberOfOrdinateSegments() const;
#else
    int numberOfAbscissaSegments() const override;
    int numberOfOrdinateSegments() const override;
#endif

    void paint( PaintContext *paintContext ) override;

    void resize( const QSizeF &size ) override;

    qreal threeDItemDepth( int column ) const override;
    qreal threeDItemDepth( const QModelIndex &index ) const override;

protected:
    const QPair<QPointF, QPointF> calculateDataBoundaries() const override;
};

} // namespace KChart

#endif // KCHART_STOCK_DIAGRAM_H

