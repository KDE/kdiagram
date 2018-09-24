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

#include "MainWidget.h"

#include "KChartAbstractDiagram_p.h"
#include "KChartChart.h"
#include "KChartPlotter.h"

#include <QHBoxLayout>

#include <cmath>

MainWidget::MainWidget()
   : m_controlsContainer( new QWidget( this ) )
{
    // set up the chart

    QHBoxLayout* topLayout = new QHBoxLayout( this );
    m_controls.setupUi( m_controlsContainer );
    topLayout->addWidget( m_controlsContainer );

    KChart::Chart* chart = new KChart::Chart;
    topLayout->addWidget( chart );

    m_plotter = new KChart::Plotter;
    m_plotter->setModel( &m_model );
    KChart::AbstractDiagram::Private::get( m_plotter )->doDumpPaintTime = true;
    chart->coordinatePlane()->replaceDiagram( m_plotter );

    KChart::CartesianCoordinatePlane* cPlane
        = qobject_cast< KChart::CartesianCoordinatePlane* >( chart->coordinatePlane() );
    Q_ASSERT( cPlane );
    cPlane->setVerticalRange( QPair< qreal, qreal >( -2, 2 ) );

    KChart::CartesianAxis* xAxis = new KChart::CartesianAxis( m_plotter );
    xAxis->setPosition( KChart::CartesianAxis::Bottom );
    xAxis->setTitleText("X");
    m_plotter->addAxis( xAxis );

    KChart::CartesianAxis* yAxis = new KChart::CartesianAxis( m_plotter );
    yAxis->setPosition( KChart::CartesianAxis::Left );
    yAxis->setTitleText("Y");
    m_plotter->addAxis( yAxis );

    // wire up the UI

    // index of elements in vector must match corresponding Model::Function enum values
    m_functionSelector << m_controls.sineRadio << m_controls.triangleRadio << m_controls.squareRadio
                       << m_controls.noiseRadio << m_controls.oneDivSineRadio
                       << m_controls.sineOneDivRadio;
    foreach ( QRadioButton* r, m_functionSelector ) {
        connect( r, SIGNAL(toggled(bool)), SLOT(functionToggled(bool)) );
    }

    connect( m_controls.runButton, SIGNAL(toggled(bool)),
             &m_model, SLOT(setRunning(bool)) );

    // order matters again
    m_addPointsButtons << m_controls.add1kButton << m_controls.add10kButton << m_controls.add100kButton;
    foreach ( QPushButton* b, m_addPointsButtons ) {
        connect( b, SIGNAL(clicked(bool)), SLOT(addPointsButtonClicked()) );
    }
}

// slot
void MainWidget::functionToggled( bool checked )
{
    if ( !checked ) {
        return;
    }
    int idx = m_functionSelector.indexOf( qobject_cast< QRadioButton* >( sender() ) );
    Q_ASSERT( idx >= 0 );
    m_model.setFunction( static_cast< Model::Function >( idx ) );
}

// slot
void MainWidget::addPointsButtonClicked()
{
    int idx = m_addPointsButtons.indexOf( qobject_cast< QPushButton* >( sender() ) );
    Q_ASSERT( idx >= 0 );
    m_model.appendPoints( pow( qreal( 10 ), qreal( idx + 3 ) ) );
}
