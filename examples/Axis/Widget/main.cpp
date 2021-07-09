/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <QApplication>
#include <KChartWidget>
#include <KChartLineDiagram>
#include <KChartCartesianAxis>
#include <KChartDataValueAttributes>

using namespace KChart;

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    Widget widget;
    widget.resize( 600, 600 );

    QVector< qreal > vec1;

    vec1 << 25 << 16 << 9 << 4 << 1 << 0
         << 1 << 4 << 9 << 16 << 25;

    // assign your datasets
    // while setting the legend
    // items text
    widget.setDataset( 0, vec1, "vec1" );


    // add and position
    widget.addLegend(Position::North);

    // configure the axes
    CartesianAxis *xAxis = new CartesianAxis( widget.lineDiagram() );
    CartesianAxis *yAxis = new CartesianAxis (widget.lineDiagram() );
    xAxis->setPosition ( CartesianAxis::Bottom );
    yAxis->setPosition ( CartesianAxis::Left );
    xAxis->setTitleText ( "Abscissa bottom position" );
    yAxis->setTitleText ( "Ordinate left position" );

    // configure Xaxis labels
    // no need to re-write labels it iterates until all
    // labels are written
    QStringList daysOfWeek;
    daysOfWeek << "Monday" << "Tuesday" << "Wednesday";
    QStringList shortDays;
    shortDays << "Mon" << "Tue" << "Wed";

    // set user configured x axis labels
    xAxis->setLabels( daysOfWeek );
    xAxis->setShortLabels(  shortDays );

    widget.lineDiagram()->addAxis( xAxis );
    widget.lineDiagram()->addAxis( yAxis );

    // show data values
    DataValueAttributes a( widget.lineDiagram()->dataValueAttributes() );
    a.setVisible( true );
    widget.lineDiagram()->setDataValueAttributes( a );

    // make sure data values are displayed at the borders
    widget.setGlobalLeading( 20, 20, 20, 20 );

    widget.show();

    return app.exec();
}
