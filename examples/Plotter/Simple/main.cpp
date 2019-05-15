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

#include <QApplication>
#include <KChartChart>
#include <KChartPlotter>
#include <KChartLineDiagram>
#include <KChartCartesianAxis>
#include <KChartCartesianCoordinatePlane>
#include <KChartLegend>
#include <QStandardItemModel>
#include <KChartDataValueAttributes>
#include <KChartTextAttributes>
#include <KChartMarkerAttributes>

#include <cmath>

#define PI 3.141592653589793


// enable the next line to see points instead of lines:
// #define PLOTTED_POINTS


int main( int argc, char** argv )
{
    QApplication app( argc, argv );

#if defined PLOTTED_POINTS
    const int points = 60;
#else
    const int points = 1000;
#endif
    const qreal xMin = -2 * PI;
    const qreal xMax = 2 * PI;
    const qreal step = ( xMax - xMin ) / ( points - 1 );

    QStandardItemModel model( points, 6 );

    double x = xMin;
    for ( int n = 0; n < points; ++n, x += step) {
        QModelIndex index = model.index( n, 0 );
        model.setData( index, x );
        index = model.index( n, 1 );
        model.setData( index, sin( x ) * 100.0 );

        index = model.index( n, 2 );
        model.setData( index, x );
        index = model.index( n, 3 );
        model.setData( index, x );

        index = model.index( n, 4 );
        model.setData( index, x );
        index = model.index( n, 5 );
        model.setData( index, x * x * x );
    }

    model.setHeaderData( 0, Qt::Horizontal, QString::fromLatin1( "100 * sin(x)" ) );
    model.setHeaderData( 2, Qt::Horizontal, QString::fromLatin1( "x" ) );
    model.setHeaderData( 4, Qt::Horizontal, QString::fromLatin1( "x^3" ) );

    KChart::Chart* chart = new KChart::Chart();

    KChart::AbstractCartesianDiagram* diagram = new KChart::Plotter;
    diagram->setModel( &model );
    chart->coordinatePlane()->replaceDiagram( diagram );

#if defined PLOTTED_POINTS
    diagram->setPen( QPen(Qt::NoPen) );
    const int colCount = model.columnCount( diagram->rootIndex() );
    for ( int iColumn = 0; iColumn<colCount; ++iColumn ) {
        const QPen markerPen( diagram->brush( iColumn ).color() );
        KChart::DataValueAttributes dva( diagram->dataValueAttributes( iColumn ) );
        KChart::TextAttributes ta( dva.textAttributes() );
        KChart::MarkerAttributes ma( dva.markerAttributes() );
        ma.setPen( markerPen );
        ma.setMarkerStyle( KChart::MarkerAttributes::MarkerCircle );
        ma.setMarkerSize( QSize( 3,3 ) );

        dva.setVisible( true );
        ta.setVisible( false );
        ma.setVisible( true );
        dva.setTextAttributes(   ta );
        dva.setMarkerAttributes( ma );
        diagram->setDataValueAttributes( iColumn, dva );
    }
#endif

    KChart::CartesianAxis* xAxis = new KChart::CartesianAxis( diagram );
    KChart::CartesianAxis* yAxis = new KChart::CartesianAxis( diagram );
    xAxis->setPosition( KChart::CartesianAxis::Bottom );
    yAxis->setPosition( KChart::CartesianAxis::Left );
    diagram->addAxis( xAxis );
    diagram->addAxis( yAxis );

    KChart::Legend* legend = new KChart::Legend( diagram, chart );
    legend->setPosition( KChart::Position::East );
    legend->setAlignment( Qt::AlignCenter );
    legend->setTitleText( "Legend" );
    chart->addLegend( legend );

    chart->show();

    return app.exec();
}
