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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"

#include <KChartChart>
#include <KChartAbstractCoordinatePlane>
#include <KChartLineDiagram>
#include <KChartLegend>

#include <QDebug>
#include <QPainter>

using namespace KChart;

MainWindow::MainWindow( QWidget* parent ) :
    QWidget( parent )
{
    setupUi( this );

    QHBoxLayout* chartLayout = new QHBoxLayout( chartFrame );
    m_chart = new Chart();
    m_chart->setGlobalLeadingTop( 10 );
    m_chart->setGlobalLeadingRight( 10 );
    chartLayout->addWidget( m_chart );
    hSBar->setVisible( false );
    vSBar->setVisible( false );

    m_model.loadFromCSV( ":/data" );

    // Set up the diagram
    m_lines = new LineDiagram();
    m_lines->setModel( &m_model );

    CartesianAxis *xAxis = new CartesianAxis( m_lines );
    CartesianAxis *yAxis = new CartesianAxis ( m_lines );
    xAxis->setPosition ( KChart::CartesianAxis::Bottom );
    yAxis->setPosition ( KChart::CartesianAxis::Left );

    xAxis->setTitleText ( "Abscissa axis at the bottom" );
    yAxis->setTitleText ( "Ordinate axis at the left side" );

    m_lines->addAxis( xAxis );
    m_lines->addAxis( yAxis );
    m_chart->coordinatePlane()->replaceDiagram( m_lines );

    connect( m_chart, SIGNAL(propertiesChanged()), SLOT(applyNewZoomParameters()) );

    // Set up the legend
    m_legend = new Legend( m_lines, m_chart );
    m_chart->addLegend( m_legend );
    m_legend->setPosition( KChartEnums::PositionEast );
    m_legend->setAlignment( Qt::AlignTop );
}


void MainWindow::on_zoomFactorSB_valueChanged( double factor )
{
    if ( factor > 1 ) {
        hSBar->setVisible( true );
        vSBar->setVisible( true );
    } else {
        hSBar->setValue( 500 );
        vSBar->setValue( 500 );
        hSBar->setVisible( false );
        vSBar->setVisible( false );
    }
    m_chart->coordinatePlane()->setZoomFactorX( factor );
    m_chart->coordinatePlane()->setZoomFactorY( factor );
    m_chart->update();
}

void MainWindow::on_adjustGridCB_toggled( bool checked )
{
    static_cast <CartesianCoordinatePlane*>( m_chart->coordinatePlane() )
            ->setAutoAdjustGridToZoom( checked );
    m_chart->update();
}

void MainWindow::on_rubberBandZoomCB_toggled( bool checked )
{
    m_chart->coordinatePlane()->setRubberBandZoomingEnabled( checked );
}

void MainWindow::on_hSBar_valueChanged( int hPos )
{
    m_chart->coordinatePlane()->setZoomCenter( QPointF(hPos/1000.0, vSBar->value()/1000.0) );
    m_chart->update();
}

void MainWindow::on_vSBar_valueChanged( int vPos )
{
    m_chart->coordinatePlane()->setZoomCenter( QPointF( hSBar->value()/1000.0, vPos/1000.0) );
    m_chart->update();
}

void MainWindow::applyNewZoomParameters()
{
    hSBar->blockSignals( true );
    vSBar->blockSignals( true );

    hSBar->setValue( qRound( m_chart->coordinatePlane()->zoomCenter().x() * 1000 ) );
    vSBar->setValue( qRound( m_chart->coordinatePlane()->zoomCenter().y() * 1000 ) );
    zoomFactorSB->setValue( m_chart->coordinatePlane()->zoomFactorX() );

    hSBar->blockSignals( false );
    vSBar->blockSignals( false );
}
