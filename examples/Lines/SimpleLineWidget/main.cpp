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
#include <KChartWidget>
#include <KChartLineDiagram>
#include <KChartLegend>


using namespace KChart;

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    Widget widget;
    widget.resize( 600, 600 );

    QVector< qreal > vec0,  vec1,  vec2;

    vec0 << 5 << 1 << 3 << 4 << 1;
    vec1 << 3 << 6 << 2 << 4 << 8;
    vec2 << 0 << 7 << 1 << 2 << 1;

    widget.setDataset( 0, vec0, "vec0" );
    widget.setDataset( 1, vec1, "vec1" );
    widget.setDataset( 2, vec2, "vec2" );
    widget.setSubType(  Widget::Percent );

    //Configure a pen and draw a line
    //a dot line for column 1
    QPen pen;
    QBrush brush;
    pen.setWidth(3);
    pen.setStyle( Qt::DotLine );
    pen.setColor(  Qt::yellow );
    brush.setColor(  Qt::yellow );
    // call your diagram and set the new pen
    // and brush
    widget.lineDiagram()->setPen(  1 , pen );
    widget.lineDiagram()->setBrush( 1,  brush );

    //set up a legend
    Legend* legend = new Legend( &widget );
    legend->setPosition( Position::East );
    legend->setAlignment( Qt::AlignCenter );
    legend->setOrientation( Qt::Vertical );
    legend->setLegendStyle( Legend::LinesOnly );
    legend->setShowLines(  true );
    widget.addLegend( legend );
    //Set up your Attributes
    //display areas
    LineAttributes la( widget.lineDiagram()->lineAttributes() );
    la.setDisplayArea(  true );
    la.setTransparency( 25 );
    widget.lineDiagram()->setLineAttributes( la );

    widget.show();

    return app.exec();
}
