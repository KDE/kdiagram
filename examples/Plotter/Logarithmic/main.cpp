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

#include <math.h>

#include <QStandardItemModel>
#include <KChartChart>
#include <KChartLineDiagram>
#include <KChartDataValueAttributes>
#include <KChartFrameAttributes>

#include <KChartPlotter>
#include <KChartCartesianAxis>
#include <KChartCartesianCoordinatePlane>
#include <KChartLegend>

#include <QApplication>

using namespace KChart;

int main( int argc, char** argv )
{
    QApplication app( argc, argv );

    const int points = 420;
    const double xMin = 0;
    const double xMax = 20;
    const double step = ( xMax - xMin ) / ( points - 1 );

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

    KChart::CartesianAxis* xAxis = new KChart::CartesianAxis( diagram );
    KChart::CartesianAxis* yAxis = new KChart::CartesianAxis( diagram );
    xAxis->setPosition( KChart::CartesianAxis::Bottom );
    yAxis->setPosition( KChart::CartesianAxis::Left );
    diagram->addAxis( xAxis );
    diagram->addAxis( yAxis );

    KChart::Legend* legend = new KChart::Legend( diagram, chart );
    KChart::FrameAttributes legendAtt = legend->frameAttributes();
    legendAtt.setCornerRadius( 9 );
    legend->setFrameAttributes( legendAtt );
    legend->setPosition( KChart::Position::East );
    legend->setAlignment( Qt::AlignCenter );
    legend->setTitleText( "Legend" );
    chart->addLegend( legend );

    KChart::CartesianCoordinatePlane* cart_plane = dynamic_cast<KChart::CartesianCoordinatePlane*>(chart->coordinatePlane());
    Q_ASSERT(cart_plane);

    cart_plane->setAxesCalcModeX(KChart::AbstractCoordinatePlane::Logarithmic);
    cart_plane->setAxesCalcModeY(KChart::AbstractCoordinatePlane::Logarithmic);

    // Set the vertical range from 15 to 75 - with a logarithmic axis I actually get 1 to 100
    //cart_plane->setVerticalRange(QPair<qreal,qreal>( 0.005, 1000 ) );

    // Set the horizontal range from 1 to 9 - with a linear axis this works OK
    cart_plane->setHorizontalRange(QPair<qreal,qreal>( 0.001, 100 ) );

    chart->show();

    int ret = app.exec();

    delete chart;

    return ret;
}
