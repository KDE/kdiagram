/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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

    QHBoxLayout *chartLayout = new QHBoxLayout( chartFrame );
    m_chart = new Chart();
    chartLayout->addWidget( m_chart );

    m_model.loadFromCSV( ":/data" );
    m_model2.loadFromCSV( ":/data2" );

    // Set up the diagram
    m_lines = new LineDiagram();
    m_lines->setModel( &m_model );

    m_lines2 = new LineDiagram();
    m_lines2->setModel( &m_model2 );

    // We call this "plane2" just for remembering, that we use it
    // in addition to the plane, that's built-in by default.
    plane2 = new CartesianCoordinatePlane( m_chart );

    plane2->setReferenceCoordinatePlane( m_chart->coordinatePlane() );

    CartesianAxis *xAxis = new CartesianAxis( m_lines2 );
    CartesianAxis *yAxis = new CartesianAxis( m_lines );
    CartesianAxis *yAxis2 = new CartesianAxis( m_lines2 );

    xAxis->setPosition( KChart::CartesianAxis::Top );
    yAxis->setPosition( KChart::CartesianAxis::Left );
    yAxis2->setPosition( KChart::CartesianAxis::Left );

    m_lines->addAxis( yAxis );

    m_lines2->addAxis( xAxis );
    m_lines2->addAxis( yAxis2 );

    m_chart->coordinatePlane()->replaceDiagram( m_lines );
    plane2->replaceDiagram( m_lines2 );
    m_chart->addCoordinatePlane( plane2/*, 1*/ );
    m_chart->setGlobalLeading( 20, 20, 20, 20 );
    init();
}

void MainWindow::init()
{
    on_displayGrid2CB_toggled( false );
}


void MainWindow::on_displayGrid1CB_toggled( bool checked )
{
    CartesianCoordinatePlane* plane = qobject_cast< CartesianCoordinatePlane * >( m_chart->coordinatePlane() );

    // disable grid for plane
    GridAttributes gv( plane->gridAttributes( Qt::Vertical) );
    gv.setGridVisible( checked );
    plane->setGridAttributes( Qt::Vertical, gv );
    plane->setGridAttributes( Qt::Horizontal, gv );
}

void MainWindow::on_displayGrid2CB_toggled( bool checked )
{
    // disable grid for plane2
    GridAttributes gv( plane2->gridAttributes( Qt::Vertical ) );
    gv.setGridVisible( checked );
    plane2->setGridAttributes( Qt::Vertical, gv );
    plane2->setGridAttributes( Qt::Horizontal, gv );
}
