/**
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

#include "mainwindow.h"

#include <KChartChart>
#include <KChartAbstractCoordinatePlane>
#include <KChartLineDiagram>
#include <KChartGridAttributes>

#include <QDebug>
#include <QPainter>

using namespace KChart;

MainWindow::MainWindow( QWidget* parent ) :
    QWidget( parent )
{
    setupUi( this );

    QHBoxLayout* chartLayout = new QHBoxLayout( chartFrame );
    m_chart = new Chart();
    chartLayout->addWidget( m_chart );

    // Use the new Layout-system.
    m_chart->setUseNewLayoutSystem(true);

    m_model.loadFromCSV( ":/data" );
    m_model2.loadFromCSV( ":/data2" );

    // Set up the diagram
    m_lines = new LineDiagram();
    m_lines->setModel( &m_model );

    m_lines2 = new LineDiagram();
    m_lines2->setModel( &m_model2 );

    // The by default built-in plane.
    KChart::CartesianCoordinatePlane* plane1 = static_cast< KChart::CartesianCoordinatePlane* >( m_chart->coordinatePlane() );

    // We call this "plane2" just for remembering, that we use it
    // in addition to the plane, that's built-in by default.
    plane2 = new CartesianCoordinatePlane( m_chart );

    CartesianAxis *xAxis = new CartesianAxis( m_lines );
    CartesianAxis *yAxis = new CartesianAxis( m_lines );
    CartesianAxis *yAxis2 = new CartesianAxis( m_lines2 );

    QList<qreal> ticks;
    ticks.append( 5 );
    ticks.append( 10 );
    ticks.append( 15 );
    xAxis->setCustomTicks(ticks);

    QMap< qreal, QString > annotations;
    annotations[ 5 ] = "Five";
    annotations[ 10 ] = "Ten";
    annotations[ 15 ] = "Fifteen";
    xAxis->setAnnotations( annotations );

    xAxis->setPosition( KChart::CartesianAxis::Top );
    yAxis->setPosition( KChart::CartesianAxis::Left );
    yAxis2->setPosition( KChart::CartesianAxis::Right );

    m_lines->addAxis( xAxis ); // shared axis, add to m_lines
    m_lines->addAxis( yAxis );
    m_lines2->addAxis( xAxis ); // and add to m_lines2
    m_lines2->addAxis( yAxis2 );

    m_chart->coordinatePlane()->replaceDiagram( m_lines );
    m_chart->setGlobalLeading( 20, 20, 20, 20 );
    plane2->replaceDiagram( m_lines2 );
    m_chart->addCoordinatePlane( plane2 );

    // Enable the annotations in both planes.
    KChart::GridAttributes grid1 = plane1->gridAttributes( Qt::Horizontal );
    grid1.setLinesOnAnnotations( true );
    plane1->setGridAttributes( Qt::Horizontal, grid1 );
    KChart::GridAttributes grid2 = plane2->gridAttributes( Qt::Horizontal );
    grid2.setLinesOnAnnotations( true );
    plane2->setGridAttributes( Qt::Horizontal, grid2 );
    m_chart->update();
}
