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

#include <KChartPalette>
#include <QtTest/QtTest>

using namespace KChart;

class TestKChartPalette: public QObject {
  Q_OBJECT
private Q_SLOTS:

  void testKChartPaletteInit()
  {
    Palette p;
    QCOMPARE( p.isValid(), false );
    Palette *p2 = new Palette();
    QCOMPARE( p2->isValid(), false );
    QCOMPARE( p2->size(), 0 );
    delete p2;
  }

  void testKChartPaletteAddBrush()
  {
    Palette p;
    p.addBrush( Qt::red );
    QCOMPARE( p.isValid(), true );
    QCOMPARE( p.size(), 1 );
    // make sure adding a brush at an invalid position does the right thing
    p.addBrush( Qt::blue, 7 );
    QCOMPARE( p.isValid(), true );
    QCOMPARE( p.size(), 2 );
  }

  void testKChartPaletteGetBrush()
  {
    Palette p;
    p.addBrush( Qt::red );
    p.addBrush( Qt::blue, 7 );
    QCOMPARE( p.isValid(), true );
    QCOMPARE( p.size(), 2 );
    QBrush brush = p.getBrush( 1 );
    // work around the lack of qCompare for QBrushes
    bool result = brush == Qt::blue;
    QCOMPARE( result, true );
    // test wrap around
    brush = p.getBrush( 2 );
    result = brush == Qt::red;
    QCOMPARE( result, true );
  }

  void testKChartPaletteRemoveBrush()
  {
    Palette p;
    p.addBrush( Qt::red );
    p.removeBrush( 2 );
    QCOMPARE( p.size(), 1 );
    QCOMPARE( p.isValid(), true );
    p.removeBrush( 0 );
    QCOMPARE( p.isValid(), false );
  }

  void testKChartPaletteDefaultPalette()
  {
    const Palette def = Palette::defaultPalette();
    QBrush brush = def.getBrush( 5 );
    bool result = brush == Qt::yellow;
    QCOMPARE( result, true );
  }

  void testKChartPaletteSuduedPalette()
  {
    const Palette def = Palette::subduedPalette();
    QBrush brush = def.getBrush( 5 );
    bool result = brush == QColor( 0x86,0xe0,0x70 );
    QCOMPARE( result, true );
  }

  void testKChartPaletteRainbowPalette()
  {
    const Palette def = Palette::rainbowPalette();
    QBrush brush = def.getBrush( 5 );
    bool result = brush == Qt::cyan;
    QCOMPARE( result, true );
  }

  void testKChartPaletteCopying()
  {
    const Palette def = Palette::rainbowPalette();
    const Palette other = def;
    QBrush brush = other.getBrush( 5 );
    bool result = brush == Qt::cyan;
    QCOMPARE( result, true );
    QCOMPARE( def.size(), other.size() );
  }

};

QTEST_MAIN(TestKChartPalette)

#include "main.moc"
