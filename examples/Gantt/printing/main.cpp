/**
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KGantt library.
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

#include "mainwindow.h"

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    // Set a dark palette that does not print well on white paper
    #define VeryLightGray   "#939393"
    #define LightLightGray  "#707070"
    #define DarkGray        "#505050"
    #define DarkDarkGray    "#333333"
    #define VeryDarkGray    "#131313"
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::black);
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, Qt::black);
    palette.setColor(QPalette::AlternateBase, VeryDarkGray);
    palette.setColor(QPalette::ToolTipBase, Qt::black);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(DarkGray));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::white);
    palette.setColor(QPalette::Link, Qt::cyan);
    palette.setColor(QPalette::Highlight, Qt::blue);
    palette.setColor(QPalette::HighlightedText, Qt::white);
    palette.setColor(QPalette::Light, QColor(VeryLightGray));
    palette.setColor(QPalette::Midlight, QColor(LightLightGray));
    palette.setColor(QPalette::Dark, QColor(DarkDarkGray));
    palette.setColor(QPalette::Mid, QColor(VeryDarkGray));
    palette.setColor(QPalette::Shadow, Qt::black);
    app.setPalette(palette);

    MainWindow mw;
    mw.resize( 800, 600 );
    mw.show();

    return app.exec();
}
