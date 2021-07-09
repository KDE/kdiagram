/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartNormalPlotter_p.h"
#include "KChartPlotter.h"
#include "PaintingHelpers_p.h"

#include <limits>

using namespace KChart;
using namespace std;

NormalPlotter::NormalPlotter( Plotter* d )
    : PlotterType( d )
{
}

Plotter::PlotType NormalPlotter::type() const
{
    return Plotter::Normal;
}

const QPair< QPointF, QPointF > NormalPlotter::calculateDataBoundaries() const
{
    if ( diagram()->useDataCompression() != Plotter::NONE )
        return plotterCompressor().dataBoundaries();
    else
        return compressor().dataBoundaries();
}

void NormalPlotter::paint( PaintContext* ctx )
{
    reverseMapper().clear();

    Q_ASSERT( dynamic_cast< CartesianCoordinatePlane* >( ctx->coordinatePlane() ) );
    const CartesianCoordinatePlane* const plane = static_cast< CartesianCoordinatePlane* >( ctx->coordinatePlane() );
    const int colCount = compressor().modelDataColumns();
    const int rowCount = compressor().modelDataRows();    

    LabelPaintCache lpc;

    if ( diagram()->useDataCompression() != Plotter::NONE )
    {
        for ( int dataset = 0; dataset < plotterCompressor().datasetCount(); ++dataset )
        {
            LineAttributesInfoList lineList;
            PlotterDiagramCompressor::DataPoint lastPoint;
            for ( PlotterDiagramCompressor::Iterator it = plotterCompressor().begin( dataset ); it != plotterCompressor().end( dataset ); ++ it )
            {
                const PlotterDiagramCompressor::DataPoint point = *it;

                const QModelIndex sourceIndex = attributesModel()->mapToSource( point.index );
                LineAttributes laCell = diagram()->lineAttributes( sourceIndex );
                const LineAttributes::MissingValuesPolicy policy = laCell.missingValuesPolicy();

                if ( ISNAN( point.key ) || ISNAN( point.value ) )
                {
                    switch ( policy )
                    {
                    case LineAttributes::MissingValuesAreBridged: // we just bridge both values
                        continue;
                    case LineAttributes::MissingValuesShownAsZero: // fall-through since that attribute makes no sense for the plotter
                    case LineAttributes::MissingValuesHideSegments: // fall-through since they're just hidden
                    default:
                        lastPoint = PlotterDiagramCompressor::DataPoint();
                        continue;
                    }
                }

                // data area painting: a and b are prev / current data points, c and d are on the null line
                const QPointF b( plane->translate( QPointF( point.key, point.value ) ) );

                if ( !point.hidden && PaintingHelpers::isFinite( b )  ) {
                    const QPointF a( plane->translate( QPointF( lastPoint.key, lastPoint.value ) ) );
                    const QPointF c( plane->translate( QPointF( lastPoint.key, 0.0 ) ) );
                    const QPointF d( plane->translate( QPointF( point.key, 0.0 ) ) );

                    // data point label
                    const PositionPoints pts = PositionPoints( b, a, d, c );
                    m_private->addLabel( &lpc, sourceIndex, nullptr, pts, Position::NorthWest,
                                         Position::NorthWest, point.value );

                    const bool lineValid = a.toPoint() != b.toPoint() && PaintingHelpers::isFinite( a );
                    if ( lineValid ) {
                        // data line
                        lineList.append( LineAttributesInfo( sourceIndex, a, b ) );

                        if ( laCell.displayArea() ) {
                            // data area
                            QList<QPolygonF> areas;
                            QPolygonF polygon;
                            polygon << a << b << d << c;
                            areas << polygon;
                            PaintingHelpers::paintAreas( m_private, ctx,
                                                         attributesModel()->mapToSource( lastPoint.index ),
                                                         areas, laCell.transparency() );
                        }
                    }
                }

                lastPoint = point;
            }
            PaintingHelpers::paintElements( m_private, ctx, lpc, lineList );
        }
    }
    else
    {
        if ( colCount == 0 || rowCount == 0 )
            return;
        for ( int column = 0; column < colCount; ++column )
        {
            LineAttributesInfoList lineList;
            CartesianDiagramDataCompressor::DataPoint lastPoint;

            for ( int row = 0; row < rowCount; ++row )
            {
                const CartesianDiagramDataCompressor::CachePosition position( row, column );
                const CartesianDiagramDataCompressor::DataPoint point = compressor().data( position );

                const QModelIndex sourceIndex = attributesModel()->mapToSource( point.index );
                LineAttributes laCell = diagram()->lineAttributes( sourceIndex );
                const LineAttributes::MissingValuesPolicy policy = laCell.missingValuesPolicy();

                if ( ISNAN( point.key ) || ISNAN( point.value ) )
                {
                    switch ( policy )
                    {
                    case LineAttributes::MissingValuesAreBridged: // we just bridge both values
                        continue;
                    case LineAttributes::MissingValuesShownAsZero: // fall-through since that attribute makes no sense for the plotter
                    case LineAttributes::MissingValuesHideSegments: // fall-through since they're just hidden
                    default:
                        lastPoint = CartesianDiagramDataCompressor::DataPoint();
                        continue;
                    }
                }

                // data area painting: a and b are prev / current data points, c and d are on the null line
                const QPointF b( plane->translate( QPointF( point.key, point.value ) ) );

                if ( !point.hidden && PaintingHelpers::isFinite( b )  ) {
                    const QPointF a( plane->translate( QPointF( lastPoint.key, lastPoint.value ) ) );
                    const QPointF c( plane->translate( QPointF( lastPoint.key, 0.0 ) ) );
                    const QPointF d( plane->translate( QPointF( point.key, 0.0 ) ) );

                    // data point label
                    const PositionPoints pts = PositionPoints( b, a, d, c );
                    m_private->addLabel( &lpc, sourceIndex, nullptr, pts, Position::NorthWest,
                                         Position::NorthWest, point.value );

                    const bool lineValid = a.toPoint() != b.toPoint() && PaintingHelpers::isFinite( a );
                    if ( lineValid ) {
                        // data line
                        lineList.append( LineAttributesInfo( sourceIndex, a, b ) );

                        if ( laCell.displayArea() ) {
                            // data area
                            QList<QPolygonF> areas;
                            QPolygonF polygon;
                            polygon << a << b << d << c;
                            areas << polygon;
                            PaintingHelpers::paintAreas( m_private, ctx,
                                                         attributesModel()->mapToSource( lastPoint.index ),
                                                         areas, laCell.transparency() );
                        }
                    }
                }

                lastPoint = point;
            }
            PaintingHelpers::paintElements( m_private, ctx, lpc, lineList );
        }
    }
}
