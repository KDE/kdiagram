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

#include "KChartStockDiagram.h"
#include "KChartStockDiagram_p.h"

#include "KChartPaintContext.h"
#include "KChartPainterSaver_p.h"

using namespace KChart;

#define d d_func()

StockDiagram::StockDiagram( QWidget *parent, CartesianCoordinatePlane *plane )
    : AbstractCartesianDiagram( new Private(), parent, plane )
{
    init();
}

StockDiagram::~StockDiagram()
{
}

/*
  * Initializes the diagram
  */
void StockDiagram::init()
{
    d->diagram = this;
    d->compressor.setModel( attributesModel() );

    // Set properties to defaults
    d->type = HighLowClose;
    d->upTrendCandlestickBrush = QBrush( Qt::white );
    d->downTrendCandlestickBrush = QBrush( Qt::black );
    d->upTrendCandlestickPen = QPen( Qt::black );
    d->downTrendCandlestickPen = QPen( Qt::black );

    d->lowHighLinePen = QPen( Qt::black );
    setDatasetDimensionInternal( 3 );
    //setDatasetDimension( 3 );

    setPen( QPen( Qt::black ) );
}

void StockDiagram::setType( Type type )
{
    d->type = type;
    Q_EMIT propertiesChanged();
}

StockDiagram::Type StockDiagram::type() const
{
   return d->type;
}

void StockDiagram::setStockBarAttributes( const StockBarAttributes &attr )
{
    attributesModel()->setModelData(
            QVariant::fromValue( attr ),
            StockBarAttributesRole );
    Q_EMIT propertiesChanged();
}

StockBarAttributes StockDiagram::stockBarAttributes() const
{
    return attributesModel()->modelData( StockBarAttributesRole ).value<StockBarAttributes>();
}

void StockDiagram::setStockBarAttributes( int column, const StockBarAttributes &attr )
{
    d->setDatasetAttrs( column, QVariant::fromValue( attr ), StockBarAttributesRole );
    Q_EMIT propertiesChanged();
}

StockBarAttributes StockDiagram::stockBarAttributes( int column ) const
{
    const QVariant attr( d->datasetAttrs( column, StockBarAttributesRole ) );
    if ( attr.isValid() )
        return attr.value<StockBarAttributes>();
    return stockBarAttributes();
}

void StockDiagram::setThreeDBarAttributes( const ThreeDBarAttributes &attr )
{
    attributesModel()->setModelData(
            QVariant::fromValue( attr ),
            ThreeDBarAttributesRole );
    Q_EMIT propertiesChanged();
}

ThreeDBarAttributes StockDiagram::threeDBarAttributes() const
{
	return attributesModel()->modelData( ThreeDBarAttributesRole ).value<ThreeDBarAttributes>();
}

void StockDiagram::setThreeDBarAttributes( int column, const ThreeDBarAttributes &attr )
{
    d->setDatasetAttrs( column, QVariant::fromValue( attr ), StockBarAttributesRole );
    Q_EMIT propertiesChanged();
}

ThreeDBarAttributes StockDiagram::threeDBarAttributes( int column ) const
{
    const QVariant attr( d->datasetAttrs( column, ThreeDBarAttributesRole ) );
    if ( attr.isValid() )
        return attr.value<ThreeDBarAttributes>();
    return threeDBarAttributes();
}


void StockDiagram::setLowHighLinePen( const QPen &pen )
{
    d->lowHighLinePen = pen;
}

QPen StockDiagram::lowHighLinePen() const
{
    return d->lowHighLinePen;
}

void StockDiagram::setLowHighLinePen( int column, const QPen &pen )
{
    d->lowHighLinePens[column] = pen;
}

QPen StockDiagram::lowHighLinePen( int column ) const
{
    if ( d->lowHighLinePens.contains( column ) )
        return d->lowHighLinePens[column];
    return d->lowHighLinePen;
}

void StockDiagram::setUpTrendCandlestickBrush( const QBrush &brush )
{
    d->upTrendCandlestickBrush = brush;
}

QBrush StockDiagram::upTrendCandlestickBrush() const
{
    return d->upTrendCandlestickBrush;
}

void StockDiagram::setDownTrendCandlestickBrush( const QBrush &brush )
{
    d->downTrendCandlestickBrush = brush;
}

QBrush StockDiagram::downTrendCandlestickBrush() const
{
    return d->downTrendCandlestickBrush;
}

void StockDiagram::setUpTrendCandlestickBrush( int column, const QBrush &brush )
{
    d->upTrendCandlestickBrushes[column] = brush;
}

QBrush StockDiagram::upTrendCandlestickBrush( int column ) const
{
    if ( d->upTrendCandlestickBrushes.contains( column ) )
        return d->upTrendCandlestickBrushes[column];
    return d->upTrendCandlestickBrush;
}

void StockDiagram::setDownTrendCandlestickBrush( int column, const QBrush &brush )
{
    d->downTrendCandlestickBrushes[column] = brush;
}

QBrush StockDiagram::downTrendCandlestickBrush( int column ) const
{
    if ( d->downTrendCandlestickBrushes.contains( column ) )
        return d->downTrendCandlestickBrushes[column];
    return d->downTrendCandlestickBrush;
}


void StockDiagram::setUpTrendCandlestickPen( const QPen &pen )
{
    d->upTrendCandlestickPen = pen;
}

QPen StockDiagram::upTrendCandlestickPen() const
{
    return d->upTrendCandlestickPen;
}

void StockDiagram::setDownTrendCandlestickPen( const QPen &pen )
{
    d->downTrendCandlestickPen = pen;
}

QPen StockDiagram::downTrendCandlestickPen() const
{
    return d->downTrendCandlestickPen;
}

void StockDiagram::setUpTrendCandlestickPen( int column, const QPen &pen )
{
    d->upTrendCandlestickPens[column] = pen;
}

QPen StockDiagram::upTrendCandlestickPen( int column ) const
{
    if ( d->upTrendCandlestickPens.contains( column ) )
        return d->upTrendCandlestickPens[column];
    return d->upTrendCandlestickPen;
}

void StockDiagram::setDownTrendCandlestickPen( int column, const QPen &pen )
{
    d->downTrendCandlestickPens[column] = pen;
}

QPen StockDiagram::downTrendCandlestickPen( int column ) const
{
    if ( d->downTrendCandlestickPens.contains( column ) )
        return d->downTrendCandlestickPens[column];
    return d->downTrendCandlestickPen;
}

#if defined(Q_COMPILER_MANGLES_RETURN_TYPE)
const
#endif
int StockDiagram::numberOfAbscissaSegments() const { return 1; }

#if defined(Q_COMPILER_MANGLES_RETURN_TYPE)
const
#endif
int StockDiagram::numberOfOrdinateSegments() const { return 1; }

void StockDiagram::paint( PaintContext *context )
{
    // Clear old reverse mapping data and create new
    // reverse mapping scene
    d->reverseMapper.clear();

    PainterSaver painterSaver( context->painter() );
    const int rowCount = attributesModel()->rowCount( attributesModelRootIndex() );
    const int divisor = ( d->type == OpenHighLowClose || d->type == Candlestick ) ? 4 : 3;
    const int colCount = attributesModel()->columnCount( attributesModelRootIndex() ) / divisor;
    for ( int col = 0; col < colCount; ++col )
    {
        for ( int row = 0; row < rowCount; row++ ) {
            CartesianDiagramDataCompressor::DataPoint low;
            CartesianDiagramDataCompressor::DataPoint high;
            CartesianDiagramDataCompressor::DataPoint open;
            CartesianDiagramDataCompressor::DataPoint close;
            CartesianDiagramDataCompressor::DataPoint volume;

            if ( d->type == HighLowClose ) {
                const CartesianDiagramDataCompressor::CachePosition highPos( row, col * divisor );
                const CartesianDiagramDataCompressor::CachePosition lowPos( row, col * divisor + 1 );
                const CartesianDiagramDataCompressor::CachePosition closePos( row, col * divisor + 2 );
                low = d->compressor.data( lowPos );
                high = d->compressor.data( highPos );
                close = d->compressor.data( closePos );
            } else if ( d->type == OpenHighLowClose || d->type == Candlestick ) {
                const CartesianDiagramDataCompressor::CachePosition openPos( row, col * divisor );
                const CartesianDiagramDataCompressor::CachePosition highPos( row, col * divisor + 1 );
                const CartesianDiagramDataCompressor::CachePosition lowPos( row, col * divisor + 2 );
                const CartesianDiagramDataCompressor::CachePosition closePos( row, col * divisor + 3 );
                open = d->compressor.data( openPos );
                low = d->compressor.data( lowPos );
                high = d->compressor.data( highPos );
                close = d->compressor.data( closePos );
            }


            switch ( d->type ) {
            case HighLowClose:
                open.hidden = true;
                Q_FALLTHROUGH();
                // Fall-through intended!
            case OpenHighLowClose:
                if ( close.index.isValid() && low.index.isValid() && high.index.isValid() )
                d->drawOHLCBar( col, open, high, low, close, context );
                break;
            case Candlestick:
                d->drawCandlestick( col, open, high, low, close, context );
                break;
            }
        }
    }
}

void StockDiagram::resize( const QSizeF &size )
{
    d->compressor.setResolution( static_cast< int >( size.width() * coordinatePlane()->zoomFactorX() ),
                                 static_cast< int >( size.height() * coordinatePlane()->zoomFactorY() ) );
    setDataBoundariesDirty();
    AbstractCartesianDiagram::resize( size );
}

qreal StockDiagram::threeDItemDepth( int column ) const
{
    Q_UNUSED( column );
    //FIXME: Implement threeD functionality
    return 1.0;
}

qreal StockDiagram::threeDItemDepth( const QModelIndex &index ) const
{
    Q_UNUSED( index );
    //FIXME: Implement threeD functionality
    return 1.0;
}

const QPair<QPointF, QPointF> StockDiagram::calculateDataBoundaries() const
{
    const int rowCount = attributesModel()->rowCount( attributesModelRootIndex() );
    const int colCount = attributesModel()->columnCount( attributesModelRootIndex() );
    qreal xMin = 0.0;
    qreal xMax = rowCount;
    qreal yMin = 0.0;
    qreal yMax = 0.0;
    for ( int row = 0; row < rowCount; row++ ) {
        for ( int col = 0; col < colCount; col++ ) {
            const CartesianDiagramDataCompressor::CachePosition pos( row, col );
            const CartesianDiagramDataCompressor::DataPoint point = d->compressor.data( pos );
            yMax = qMax( yMax, point.value );
            yMin = qMin( yMin, point.value ); // FIXME: Can stock charts really have negative values?
        }
    }
    return QPair<QPointF, QPointF>( QPointF( xMin, yMin ), QPointF( xMax, yMax ) );
}

