/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
    for ( QRadioButton* r : std::as_const(m_functionSelector) ) {
        connect( r, SIGNAL(toggled(bool)), SLOT(functionToggled(bool)) );
    }

    connect( m_controls.runButton, SIGNAL(toggled(bool)),
             &m_model, SLOT(setRunning(bool)) );

    // order matters again
    m_addPointsButtons << m_controls.add1kButton << m_controls.add10kButton << m_controls.add100kButton;
    for ( QPushButton* b : std::as_const(m_addPointsButtons) ) {
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
