/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartLineDiagram_p.h"
#include "KChartLineDiagram.h"
#include "KChartDataValueAttributes.h"

#include "KChartPainterSaver_p.h"
#include "PaintingHelpers_p.h"

using namespace KChart;
using namespace std;

LineDiagram::Private::Private( const Private& rhs )
    : AbstractCartesianDiagram::Private( rhs )
{
}

AttributesModel* LineDiagram::LineDiagramType::attributesModel() const
{
    return m_private->attributesModel;
}

QModelIndex LineDiagram::LineDiagramType::attributesModelRootIndex() const
{
    return diagram()->attributesModelRootIndex();
}

int LineDiagram::LineDiagramType::datasetDimension() const
{
    return m_private->datasetDimension;
}

ReverseMapper& LineDiagram::LineDiagramType::reverseMapper()
{
    return m_private->reverseMapper;
}

LineDiagram* LineDiagram::LineDiagramType::diagram() const
{
    return static_cast< LineDiagram* >( m_private->diagram );
}

qreal LineDiagram::LineDiagramType::valueForCell( int row, int column ) const
{
    return diagram()->valueForCell( row, column );
}

CartesianDiagramDataCompressor& LineDiagram::LineDiagramType::compressor() const
{
    return m_private->compressor;
}

qreal LineDiagram::LineDiagramType::interpolateMissingValue( const CartesianDiagramDataCompressor::CachePosition& pos ) const
{
    qreal leftValue = std::numeric_limits< qreal >::quiet_NaN();
    qreal rightValue = std::numeric_limits< qreal >::quiet_NaN();
    int missingCount = 1;

    const int column = pos.column;
    const int row = pos.row;
    const int rowCount = compressor().modelDataRows();

    // iterate back and forth to find valid values
    for ( int r1 = row - 1; r1 > 0; --r1 )
    {
        const CartesianDiagramDataCompressor::CachePosition position( r1, column );
        const CartesianDiagramDataCompressor::DataPoint point = compressor().data( position );
        leftValue = point.value;
        if ( !ISNAN( point.value ) )
            break;
        ++missingCount;
    }
    for ( int r2 = row + 1; r2 < rowCount; ++r2 )
    {
        const CartesianDiagramDataCompressor::CachePosition position( r2, column );
        const CartesianDiagramDataCompressor::DataPoint point = compressor().data( position );
        rightValue = point.value;
        if ( !ISNAN( point.value ) )
            break;
        ++missingCount;
    }
    if ( !ISNAN( leftValue ) && !ISNAN( rightValue ) )
        return leftValue + ( rightValue - leftValue ) / ( missingCount + 1 );
    else
        return std::numeric_limits< qreal >::quiet_NaN();
}
