/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <QApplication>

#include "mainwindow.h"

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    MainWindow mw;
    mw.resize( 800, 600 );
    mw.show();

    return app.exec();
}
