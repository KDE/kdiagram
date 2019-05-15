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
#include <KChartDataValueAttributes>



using namespace KChart;

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    Widget widget;
    widget.resize( 600, 600 );

    QVector< qreal > vec0,  vec1,  vec2;

    vec0 << 5 << 1 << 3 << 4 << 1;
    vec1 << 3 << 6 << 2 << 4 << 8;
    vec2 << 2 << 7 << 1 << 2 << 1;

    widget.setDataset( 0, vec0, "vec0" );
    widget.setDataset( 1, vec1, "vec1" );
    widget.setDataset( 2, vec2, "vec2" );

    widget.lineDiagram()->setPen(  Qt::NoPen );

    DataValueAttributes dva( widget.lineDiagram()->dataValueAttributes() );
    MarkerAttributes ma(  dva.markerAttributes() );
    TextAttributes ta(  dva.textAttributes() );
    ma.setVisible( true );
    // display values or not
    ta.setVisible(  false );
    dva.setTextAttributes(  ta );
    dva.setMarkerAttributes(  ma );
    dva.setVisible( true );

    widget.lineDiagram()->setDataValueAttributes( dva );
    widget.setGlobalLeading( 10,  10,  10, 10 );

    widget.show();

    return app.exec();
}
