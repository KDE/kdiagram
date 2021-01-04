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
