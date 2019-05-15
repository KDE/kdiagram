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

#include <QDebug>
#include <QVector>

#include "mainwindow.h"

using namespace KChart;

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    MainWindow window;

    window.resize( 800, 600 );

    QVector< qreal > vec0;
    vec0.append( -5 );
    vec0.append( -4 );
    vec0.append( -3 );
    vec0.append( -2 );
    vec0.append( -1 );
    vec0.append( 0 );
    vec0.append( 1 );
    vec0.append( 2 );
    vec0.append( 3 );
    vec0.append( 4 );
    vec0.append( 5 );
    window.widget->setDataset( 0, vec0);

    QVector< qreal > vec1;
    vec1.append( 25 );
    vec1.append( 16 );
    vec1.append( 9 );
    vec1.append( 4 );
    vec1.append( 1 );
    vec1.append( 0 );
    vec1.append( 1 );
    vec1.append( 4 );
    vec1.append( 9 );
    vec1.append( 16 );
    vec1.append( 25 );
    window.widget->setDataset( 1, vec1 );

    QVector< qreal > vec2;
    vec2.append( -125 );
    vec2.append( -64 );
    vec2.append( -27 );
    vec2.append( -8 );
    vec2.append( -1 );
    vec2.append( 0 );
    vec2.append( 1 );
    vec2.append( 8 );
    vec2.append( 27 );
    vec2.append( 64 );
    vec2.append( 125 );
    window.widget->setDataset( 2, vec2 );

    window.widget->addHeaderFooter( "Zoom Example",
                                    HeaderFooter::Header, Position::North );
    window.widget->addHeaderFooter( "zoom in/out: PageDn / PageUp",
                                    HeaderFooter::Footer, Position::North );
    window.widget->addHeaderFooter( "pan around: Left / Right / Up / Down",
                                    HeaderFooter::Footer, Position::South );

    window.widget->addLegend( Position::East );

    //window.widget->setType( Widget::Polar );

    window.show();

    return app.exec();
}
