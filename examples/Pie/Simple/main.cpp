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
#include <KChartPieDiagram>
#include <KChartPolarCoordinatePlane>
#include <QPen>


using namespace KChart;

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    Widget widget;
    widget.resize( 600, 600 );
    widget.setGlobalLeading( 5, 5, 5, 5 );

    QVector< qreal > vec0,  vec1,  vec2;

    vec0 << 1 << -4 << -3 << -2 << -1 << 0
         << 1 << 2 << 3 << 4 << 5;
    vec1 << 2 << 16 << 9 << 4 << 1 << 0
         << 1 << 4 << 9 << 16 << 25;
    vec2 << 3 << -64 << -27 << -8 << -1 << 0
         << 1 << 8 << 27 << 64 << 125;

    widget.setDataset( 0, vec0, "v0" );
    widget.setDataset( 1, vec1, "v1" );
    widget.setDataset( 2, vec2, "v2" );
    widget.setType( Widget::Pie );

    // Draw a line around the
    // third sections
    // for example
    QPen piePen;
    piePen.setWidth( 3 );
    piePen.setColor( Qt::white );
    widget.pieDiagram()->setPen( 2,  piePen );
    ((PolarCoordinatePlane*)widget.coordinatePlane())->setStartPosition( 90 );

    widget.show();

    return app.exec();
}
