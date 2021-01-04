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

#include "mainwindow.h"
#include <QElapsedTimer>
#include <QtTest/QtTest>

class TestParamVsParam: public QObject {
    Q_OBJECT
private Q_SLOTS:

  void testMainWindow()
  {
    QElapsedTimer t;
    t.start();

    MainWindow      mainWindow;

    qDebug("time constructor: %lld ms", t.elapsed());

    mainWindow.show();
    QTimer::singleShot(0, qApp, SLOT(quit()));

    qDebug("time show(): %lld ms", t.elapsed());
    // uncomment to see it blink:
    // QTest::qWait( 10000 );

  }
};

QTEST_MAIN(TestParamVsParam)

#include "main.moc"
