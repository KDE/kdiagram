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

#include "KChartPlotter_p.h"
#include "KChartPlotter.h"

#include "KChartPainterSaver_p.h"
#include "KChartValueTrackerAttributes.h"
#include "PaintingHelpers_p.h"

using namespace KChart;

Plotter::Private::Private( const Private& rhs )
    : QObject()
    , AbstractCartesianDiagram::Private( rhs )
    , useCompression( rhs.useCompression )
{
}

void Plotter::Private::init()
{
    AbstractCartesianDiagram::Private::init();
    useCompression = Plotter::NONE;
}

void Plotter::Private::setCompressorResolution(
    const QSizeF& size,
    const AbstractCoordinatePlane* plane )
{
    compressor.setResolution( static_cast<int>( size.width()  * plane->zoomFactorX() ),
                              static_cast<int>( size.height() * plane->zoomFactorY() ) );
}

void Plotter::Private::changedProperties()
{
    if ( CartesianCoordinatePlane* plane = dynamic_cast< CartesianCoordinatePlane* > ( diagram->coordinatePlane() ) )
    {
        QPair< qreal, qreal > verticalRange = plane->verticalRange();
        if ( verticalRange.first != verticalRange.second )
            implementor->plotterCompressor().setForcedDataBoundaries( verticalRange, Qt::Vertical );
        QPair< qreal, qreal > horizontalRange = plane->horizontalRange();
        if ( verticalRange.first != horizontalRange.second )
            implementor->plotterCompressor().setForcedDataBoundaries( horizontalRange, Qt::Horizontal );
    }
}

AttributesModel* Plotter::PlotterType::attributesModel() const
{
    return m_private->attributesModel;
}

ReverseMapper& Plotter::PlotterType::reverseMapper()
{
    return m_private->reverseMapper;
}

Plotter* Plotter::PlotterType::diagram() const
{
    return static_cast< Plotter* >( m_private->diagram );
}

CartesianDiagramDataCompressor& Plotter::PlotterType::compressor() const
{
    return m_private->compressor;
}

PlotterDiagramCompressor& Plotter::PlotterType::plotterCompressor() const
{
    return m_private->plotterCompressor;
}

Plotter::CompressionMode Plotter::PlotterType::useCompression() const
{
    return m_private->useCompression;
}

void Plotter::PlotterType::setUseCompression( Plotter::CompressionMode value )
{
    m_private->useCompression = value;
}
