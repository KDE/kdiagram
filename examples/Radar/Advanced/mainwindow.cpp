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
#include <KChartRadarDiagram>
#include <KChartTextAttributes>
#include <KChartDataValueAttributes>
#include <KChartGridAttributes>
#include <KChartMarkerAttributes>
#include <KChartLegend>

#include <QDebug>
#include <QPainter>

using namespace KChart;

MainWindow::MainWindow( QWidget* parent ) :
    QWidget( parent ), m_currentFactor( 0 ), m_currentDirection( 1 ), m_currentSlice( 0 )
{
    setupUi( this );

    // instantiate the KD Chart classes
    initKChartClasses();

    // insert the KChart::Chart into Qt's layout
    QHBoxLayout* chartLayout = new QHBoxLayout( chartFrame );
    m_chart->setGlobalLeadingLeft( 5 );
    m_chart->setGlobalLeadingRight( 5 );
    chartLayout->addWidget( m_chart );

    // wire up the KD Chart classes
    wireUpKChartClasses();

    // initialize the ItemModel and fill in some data
    m_model.insertRows( 0, 40 );
    m_model.insertColumns(  0,  5 );
    setItemModelData();
}


void MainWindow::initKChartClasses()
{
    m_chart      = new Chart();
    m_diagram    = new RadarDiagram();
    m_plane = new RadarCoordinatePlane();
}

void MainWindow::wireUpKChartClasses()
{
    m_chart->replaceCoordinatePlane( m_plane );
    //note: We need to set a valid item model to the diagram,
    //      before we can add it to the coordinate plane.
    m_diagram->setModel( &m_model );
    m_chart->coordinatePlane()->replaceDiagram( m_diagram );
}

void MainWindow::setItemModelData()
{
    // For a change we do not read data from a resource file here,
    // but we just fill in the cells manually
    int value = 0;
    for ( int column = 0; column < m_model.columnCount(); ++column ) {
        for ( int row = 0; row < m_model.rowCount(); ++row ) {
            QModelIndex index = m_model.index( row, column );
            m_model.setData( index, QVariant( value++  ) );
        }
    }
}


void MainWindow::on_startPositionSB_valueChanged( double pos )
{
    const int intValue = static_cast<int>( pos );
    startPositionSL->blockSignals( true );
    startPositionSL->setValue( intValue );
    startPositionSL->blockSignals( false );
    // note: We use the global getter method here, it will fall back
    //       automatically to return the default settings.
    static_cast<RadarCoordinatePlane*>(m_chart->coordinatePlane())->setStartPosition( pos );
    update();
}

void MainWindow::on_startPositionSL_valueChanged( int pos )
{
    qreal qrealValue = static_cast<qreal>( pos );
    startPositionSB->blockSignals( true );
    startPositionSB->setValue( qrealValue  );
    startPositionSB->blockSignals( false );
    // note: We use the global getter method here, it will fall back
    //       automatically to return the default settings.
    static_cast<RadarCoordinatePlane*>(m_chart->coordinatePlane())->setStartPosition( pos );
    update();
}

void MainWindow::on_circularGridCB_toggled( bool toggle )
{
    GridAttributes attrs( m_plane->gridAttributes( true ) );
    attrs.setGridVisible( toggle );
    m_plane->setGridAttributes( true, attrs );
    update();
}
void MainWindow::on_sagittalGridCB_toggled( bool toggle )
{
    GridAttributes attrs( m_plane->gridAttributes( false ) );
    attrs.setGridVisible( toggle );
    m_plane->setGridAttributes( false, attrs );
    update();
}
