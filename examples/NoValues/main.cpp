/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <QApplication>
#include "mainwindow.h"

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    MainWindow mainWindow;
    mainWindow.show();
    mainWindow.setWindowTitle(QObject::tr("You can have a chart without having any data at all."));

    return app.exec();
}
