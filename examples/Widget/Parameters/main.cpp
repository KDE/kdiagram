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
#include <KChartBarDiagram>
#include <QPen>
#include <KChartThreeDBarAttributes>

using namespace KChart;

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    Widget widget;
    widget.resize( 600, 600 );

    QVector< qreal > vec0,  vec1;

    vec0 << 5 << 4 << 3 << 2 << 1 << 0
         << 1 << 2 << 3 << 4 << 5;
    vec1 << 25 << 16 << 9 << 4 << 1 << 0
         << 1 << 4 << 9 << 16 << 25;

    widget.setDataset( 0, vec0, "vec0" );
    widget.setDataset( 1, vec1, "vec1" );
    widget.setType( Widget::Bar ,  Widget::Stacked );

    //Configure a pen and draw a line
    //surrounding the bars
    QPen pen;
    pen.setWidth( 2 );
    pen.setColor(  Qt::darkGray );
    // call your diagram and set the new pen
    widget.barDiagram()->setPen(  pen );

    //Set up your ThreeDAttributes
    //display in ThreeD mode
    ThreeDBarAttributes td( widget.barDiagram()->threeDBarAttributes() );
    td.setDepth(  15 );
    td.setEnabled(  true );
    widget.barDiagram()->setThreeDBarAttributes( td );
    widget.setGlobalLeadingTop( 20 );
    widget.show();

    return app.exec();
}
