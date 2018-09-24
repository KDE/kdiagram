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
#include "AdjustedCartesianAxis.h"

#include <KChartCartesianCoordinatePlane>
#include <KChartChart>
#include <KChartGridAttributes>
#include <KChartLegend>
#include <KChartLineDiagram>
#include <KChartTextAttributes>

#include <QDebug>
#include <QLinearGradient>
#include <QTextDocument>

MainWindow::MainWindow( QWidget* parent ) :
    QWidget( parent )
{
    setupUi( this );

    QHBoxLayout* chartLayout = new QHBoxLayout( m_chartFrame );
    m_chart = new KChart::Chart;
    chartLayout->addWidget( m_chart );

    m_model.loadFromCSV( ":/data" );

    // Set up the diagram
    m_lines = new KChart::LineDiagram();
    m_lines->setModel( &m_model );

    m_xAxis = new KChart::CartesianAxis( m_lines );
    KChart::TextAttributes ta( m_xAxis->textAttributes() );

    AdjustedCartesianAxis *yAxis = new AdjustedCartesianAxis( m_lines );
    yAxis->setBounds( 3, 6 );
    m_xAxis->setPosition( KChart::CartesianAxis::Bottom );
    yAxis->setPosition( KChart::CartesianAxis::Left );

// set the following to 0, to see the default Abscissa labels (== X headers, as read from the data file)
#if 1
    QStringList daysOfWeek;
    daysOfWeek << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday" << "Saturday" << "Sunday";
    m_xAxis->setLabels( daysOfWeek );

    //QStringList shortDays;
    //shortDays << "Mon" << "Tue" << "Wed" << "Thu" << "Fri" << "Sat" << "Sun";
    //m_xAxis->setShortLabels( shortDays );
#endif

// Use HTML for drawing the text in the axis labels.
#if 0
    QStringList htmlStyles;
    htmlStyles << "<b>Bold</b>" << "<i>Italic</i>" << "<u>Underline</u>" << "<font color='red'>Red</font>";
    m_xAxis->setLabels( htmlStyles );
    ta.setTextDocument(new QTextDocument);
#endif

    // Illustration of custom ticks
    QList<qreal> ticks;
    ticks.append( 0.5 );
    ticks.append( 3.5 );
    ticks.append( 4.2 );
    ticks.append( 6.5 );
    m_xAxis->setCustomTicks(ticks);
    yAxis->setCustomTicks(ticks);

    // rotate abscissa labels by -60 degrees:
    ta.setRotation( -60 );

    m_xAxis->setTextAttributes( ta );
    m_lines->addAxis( m_xAxis );
    m_lines->addAxis( yAxis );
    m_chart->coordinatePlane()->replaceDiagram( m_lines );
    // Set up the legend
    m_xAxis->setCustomTickLength( 11 );
    yAxis->setCustomTickLength( 11 );
    m_legend = new KChart::Legend( m_lines, m_chart );
    m_legend->setPosition( KChart::Position::East );
    m_legend->setAlignment( Qt::AlignTop );
    m_chart->addLegend( m_legend );

    connect( m_annotations, SIGNAL(toggled(bool)), SLOT(annotationsToggled(bool)) );
    connect( m_linesOnAnnotations, SIGNAL(toggled(bool)), SLOT(gridLinesOnAnnotationsToggled(bool)) );
}

void MainWindow::annotationsToggled( bool showAnnotations )
{
    QMap< qreal, QString > annotations;
    if ( showAnnotations ) {
        // set custom axis labels at custom positions
        annotations[ 0.5 ] = "Left";
        annotations[ 3.5 ] = "Center";
        annotations[ 4.2 ] = "Off Center";
        annotations[ 6.5 ] = "Right";
    }
    m_xAxis->setAnnotations( annotations );
    m_chart->update();
}

void MainWindow::gridLinesOnAnnotationsToggled( bool onAnnotations )
{
        // Draw grid lines where the annotations are
    KChart::CartesianCoordinatePlane* plane =
        static_cast< KChart::CartesianCoordinatePlane* >( m_chart->coordinatePlane() );
    KChart::GridAttributes ga = plane->gridAttributes( Qt::Horizontal );
    ga.setLinesOnAnnotations( onAnnotations );
    plane->setGridAttributes( Qt::Horizontal, ga );
    m_chart->update();
}
