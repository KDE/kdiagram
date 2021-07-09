/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwindow.h"

#include <QtTest/QtTest>

class TestDrawIntoPainter: public QObject {
    Q_OBJECT
private Q_SLOTS:

  void initTestCase()
  {
    qputenv("QTEST_FUNCTION_TIMEOUT", QByteArray("600000"));
  }

  void testOriginal()
  {
    mainWindow.updateData(QStringLiteral(":/original"));
  }

  void testTest()
  {
    // The test in :/test is so large it times out on CI
    // so we run the half sized :/test4000 for now
#if 0
    mainWindow.updateData(QStringLiteral(":/test"));
#else
    mainWindow.updateData(QStringLiteral(":/test_small"));
#endif
  }

private:
    MainWindow mainWindow;

};

QTEST_MAIN(TestDrawIntoPainter)

#include "main.moc"
