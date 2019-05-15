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
#include <KChartBarDiagram>
#include <KChartTextAttributes>
#include <KChartRulerAttributes>
#include <KChartFrameAttributes>

using namespace KChart;

MainWindow::MainWindow( QWidget* parent ) :
    QWidget( parent )
{
    setupUi( this );

    QHBoxLayout* chartLayout = new QHBoxLayout( chartFrame );
    m_chart = new Chart();
    m_chart->setGlobalLeading( 10, 10, 10, 10 );
    chartLayout->addWidget( m_chart );
    hSBar->setVisible( false );
    vSBar->setVisible( false );

    m_model.loadFromCSV( ":/data" );

    // Set up the diagram
    m_lines = new BarDiagram();
    m_lines->setModel( &m_model );

    // create and position axis
    CartesianAxis *topAxis = new CartesianAxis( m_lines );
    CartesianAxis *leftAxis = new CartesianAxis( m_lines );
    RulerAttributes rulerAttr = topAxis->rulerAttributes();
    rulerAttr.setTickMarkPen( 0.9999999, QPen( Qt::red ) );
    rulerAttr.setTickMarkPen( 2.0, QPen( Qt::green ) );
    rulerAttr.setTickMarkPen( 3.0, QPen( Qt::blue ) );
    rulerAttr.setShowMinorTickMarks(true);
    //rulerAttr.setShowMajorTickMarks(false);
    topAxis->setRulerAttributes( rulerAttr );
    CartesianAxis *rightAxis = new CartesianAxis( m_lines );
    CartesianAxis *bottomAxis = new CartesianAxis( m_lines );
    topAxis->setPosition( CartesianAxis::Top );
    leftAxis->setPosition( CartesianAxis::Left );
    rightAxis->setPosition( CartesianAxis::Right );
    bottomAxis->setPosition( CartesianAxis::Bottom );

// set the margin that should be used between the displayed labels and the ticks to zero
#if 0
    RulerAttributes ra = bottomAxis->rulerAttributes();
    ra.setLabelMargin( 0 );
    bottomAxis->setRulerAttributes( ra );
#endif

// show a red frame around the bottom axis
#if 0
    FrameAttributes fa( bottomAxis->frameAttributes() );
    fa.setPen( QPen( QBrush( QColor( "#ff0000" ) ), 1.0 ) );
    fa.setVisible( true );
    bottomAxis->setFrameAttributes( fa );
#endif
    
    // set axis titles
    topAxis->setTitleText( "Abscissa Top configured size and color" );
    leftAxis->setTitleText( "left Ordinate: fonts configured" );
    rightAxis->setTitleText( "right Ordinate: default settings" );
    bottomAxis->setTitleText( "Abscissa Bottom" );

    // configure titles text attributes
    TextAttributes taTop( topAxis->titleTextAttributes() );
    taTop.setPen( QPen( Qt::red ) );
    topAxis->setTitleTextAttributes ( taTop );

    TextAttributes taLeft( leftAxis->titleTextAttributes() );
    taLeft.setRotation( 180 );
    Measure me( taLeft.fontSize() );
    me.setValue( me.value() * 0.8 );
    taLeft.setFontSize( me );

// Set the following to 1, to hide the left axis title
//  - no matter if a title text is set or not
#if 0
    taLeft.setVisible( false );
#endif
    leftAxis->setTitleTextAttributes( taLeft );

    TextAttributes taBottom( bottomAxis->titleTextAttributes () );
    taBottom.setPen( QPen( Qt::blue ) );
    bottomAxis->setTitleTextAttributes( taBottom );

    // configure labels text attributes
    TextAttributes taLabels( topAxis->textAttributes() );
    taLabels.setPen( QPen( Qt::darkGreen ) );
    taLabels.setRotation( 90 );
    topAxis->setTextAttributes( taLabels );
    leftAxis->setTextAttributes( taLabels );
    bottomAxis->setTextAttributes( taLabels );


// Set the following to 0, to see the default Abscissa labels
// (== X headers, as read from the data file)
#if 1
    // configure labels and their shortened versions
    QStringList daysOfWeek;
    daysOfWeek << "M O N D A Y" << "Tuesday" << "Wednesday"
               << "Thursday" << "Friday" ;
    topAxis->setLabels( daysOfWeek );

    QStringList shortDays;
    shortDays << "MON" << "Tue" << "Wed"
              << "Thu" << "Fri";
    topAxis->setShortLabels( shortDays );

    QStringList bottomLabels;
    bottomLabels << "Team A" << "Team B" << "Team C";
    bottomAxis->setLabels( bottomLabels );

    QStringList shortBottomLabels;
    shortBottomLabels << "A" << "B";
    bottomAxis->setShortLabels( shortBottomLabels );
#endif

    // add axis
    m_lines->addAxis( topAxis );
    m_lines->addAxis( leftAxis );
    m_lines->addAxis( rightAxis );
    m_lines->addAxis( bottomAxis );

    // assign diagram to chart view
    m_chart->coordinatePlane()->replaceDiagram( m_lines );
}
