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
#include <KChartBarDiagram>

#include <QDebug>
#include <QPainter>

using namespace KChart;

#define USE_ROOTINDEX 1

MainWindow::MainWindow( QWidget* parent ) :
    QWidget( parent )
{
    setupUi( this );

    QHBoxLayout* chartLayout = new QHBoxLayout( chartFrame );
    m_chart = new Chart();
    chartLayout->addWidget( m_chart );

#if USE_ROOTINDEX
    m_model.insertRows( 0,2, QModelIndex() );
    m_model.insertColumns( 0,1, QModelIndex() );
    QModelIndex idx1 = m_model.index( 0,0,QModelIndex() );
    QModelIndex idx2 = m_model.index( 1,0,QModelIndex() );

    m_model.setData( idx1, 3.14 );
    m_model.setData( idx2, 2*3.14 );

    m_model.insertRows( 0,5, idx1 );
    m_model.insertColumns( 0,5, idx1 );
    
    for ( int i = 0; i < 5; ++i ) {
      for ( int j = 0; j < 5; ++j ) {
	m_model.setData( m_model.index( i,j,idx1), (qreal)i*j );
      }
    }

    m_model.insertRows( 0,2, idx2 );
    m_model.insertColumns( 0,2, idx2 );
    
    for ( int i = 0; i < 2; ++i ) {
      for ( int j = 0; j < 2; ++j ) {
	m_model.setData( m_model.index( i,j,idx2), 10.*(i+1.)/(j+1.) );
      }
    }
#else
    QModelIndex idx1 = QModelIndex();
    m_model.insertRows( 0,5, idx1 );
    m_model.insertColumns( 0,5, idx1 );
    
    for ( int i = 0; i < 5; ++i ) {
      for ( int j = 0; j < 5; ++j ) {
	m_model.setData( m_model.index( i,j,idx1), (qreal)i*j );
      }
    }
    QModelIndex idx2 = idx1;

    m_model2.insertRows( 0,2, idx2 );
    m_model2.insertColumns( 0,2, idx2 );
    
    for ( int i = 0; i < 2; ++i ) {
      for ( int j = 0; j < 2; ++j ) {
	m_model2.setData( m_model2.index( i,j,idx2), 10.*(i+1.)/(j+1.) );
      }
    }
    
#endif

    // Set up the diagram
    m_lines = new LineDiagram();
    m_lines->setModel( &m_model );
#if USE_ROOTINDEX
    m_lines->setRootIndex(idx1);
#endif

    m_bars = new BarDiagram();
#if USE_ROOTINDEX
    m_bars->setModel( &m_model );
    m_bars->setRootIndex(idx2);
#else
    m_bars->setModel( &m_model2 );
#endif

    plane = new CartesianCoordinatePlane( m_chart );

    CartesianAxis *xAxis = new CartesianAxis( m_lines );
    CartesianAxis *yAxis = new CartesianAxis ( m_lines );
    CartesianAxis *yAxis3 = new CartesianAxis ( m_lines );
    xAxis->setPosition ( KChart::CartesianAxis::Bottom );
    yAxis->setPosition ( KChart::CartesianAxis::Left );
    yAxis3->setPosition ( KChart::CartesianAxis::Left );

    CartesianAxis *yAxis2 = new CartesianAxis ( m_bars );
    yAxis2->setPosition ( KChart::CartesianAxis::Right );

    // explicitly add it to the second diagram, we want to share it
    m_bars->addAxis( xAxis );

    m_chart->coordinatePlane()->replaceDiagram( m_lines );
    plane->replaceDiagram( m_bars );
    // We want both planes to use the same space.
    plane->setReferenceCoordinatePlane( m_chart->coordinatePlane() );
    m_chart->addCoordinatePlane( plane/*, 1*/);
}
