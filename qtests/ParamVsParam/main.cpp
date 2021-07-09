/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
