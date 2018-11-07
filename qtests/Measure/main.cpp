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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtTest/QtTest>
#include <KChartChart>
#include <KChartGlobal>
#include <KChartBarDiagram>
#include <KChartCartesianCoordinatePlane>
#include <KChartMeasure>

#include <TableModel.h>

using namespace KChart;

class TestMeasure : public QObject {
  Q_OBJECT
private slots:

  void initTestCase()
  {
      m_chart = new Chart(nullptr);
      m_model = new TableModel( this );
      m_model->loadFromCSV( ":/data" );
      m_bars = new BarDiagram();
      m_bars->setModel( m_model );
      m_chart->coordinatePlane()->replaceDiagram( m_bars );
      m_chart->setGeometry(100,100, 300,200);
      m_chart->show();
  }

  void testMeasureCalculationModeAbsolute()
  {
      KChart::Measure m( 100.0 );
      m.setCalculationMode( KChartEnums::MeasureCalculationModeAbsolute );
      QCOMPARE(
          m.calculatedValue(nullptr, KChartEnums::MeasureOrientationAuto),
          100.0 );
  }

  void testMeasureCalculationModeRelativeHorizontalOrientation()
  {
      KChart::Measure m(
          100.0,
          KChartEnums::MeasureCalculationModeRelative,
          KChartEnums::MeasureOrientationHorizontal );
      m.setReferenceArea( m_chart );
      QCOMPARE(
          m.calculatedValue(nullptr, KChartEnums::MeasureOrientationAuto),
          m_chart->size().width() / 10.0 );
  }

  void testMeasureCalculationModeRelativeVerticalOrientation()
  {
      KChart::Measure m(
          100.0,
          KChartEnums::MeasureCalculationModeRelative,
          KChartEnums::MeasureOrientationVertical );
      m.setReferenceArea( m_chart );
      QCOMPARE(
          m.calculatedValue(nullptr, KChartEnums::MeasureOrientationAuto),
          m_chart->size().height() / 10.0 );
  }

  void testMeasureCalculationModeAuto()
  {
      KChart::Measure m( 100.0 );
      m.setCalculationMode( KChartEnums::MeasureCalculationModeAuto );
      QCOMPARE(
          m.calculatedValue(m_chart, KChartEnums::MeasureOrientationHorizontal),
          m_chart->size().width() / 10.0 );
      QCOMPARE(
          m.calculatedValue(m_chart, KChartEnums::MeasureOrientationVertical),
          m_chart->size().height() / 10.0 );
      QCOMPARE(
          m.calculatedValue(m_chart, KChartEnums::MeasureOrientationMinimum),
          qMin( m_chart->size().width(), m_chart->size().height() ) / 10.0 );
      QCOMPARE(
          m.calculatedValue(m_chart, KChartEnums::MeasureOrientationMaximum),
          qMax( m_chart->size().width(), m_chart->size().height() ) / 10.0 );
  }

  void testMeasureCalculationModeAutoArea()
  {
      KChart::Measure m(
          100.0,
          KChartEnums::MeasureCalculationModeAutoArea,
          KChartEnums::MeasureOrientationHorizontal );
      QCOMPARE(
          m.calculatedValue(m_chart, KChartEnums::MeasureOrientationAuto),
          m_chart->size().width() / 10.0 );
      m.setReferenceOrientation( KChartEnums::MeasureOrientationVertical );
      QCOMPARE(
          m.calculatedValue(m_chart, KChartEnums::MeasureOrientationAuto),
          m_chart->size().height() / 10.0 );
      m.setReferenceOrientation( KChartEnums::MeasureOrientationMinimum );
      QCOMPARE(
          m.calculatedValue(m_chart, KChartEnums::MeasureOrientationAuto),
          qMin( m_chart->size().width(), m_chart->size().height() ) / 10.0 );
      m.setReferenceOrientation( KChartEnums::MeasureOrientationMaximum );
      QCOMPARE(
          m.calculatedValue(m_chart, KChartEnums::MeasureOrientationAuto),
          qMax( m_chart->size().width(), m_chart->size().height() ) / 10.0 );
  }

  void testMeasureAutoOrientation()
  {
      KChart::Measure m(
          100.0,
          KChartEnums::MeasureCalculationModeAutoOrientation,
          KChartEnums::MeasureOrientationAuto );
      m.setReferenceArea( m_chart );
      QCOMPARE(
          m.calculatedValue(nullptr, KChartEnums::MeasureOrientationHorizontal),
          m_chart->size().width() / 10.0 );
      QCOMPARE(
          m.calculatedValue(nullptr, KChartEnums::MeasureOrientationVertical),
          m_chart->size().height() / 10.0 );
      QCOMPARE(
          m.calculatedValue(nullptr, KChartEnums::MeasureOrientationMinimum),
          qMin( m_chart->size().width(), m_chart->size().height() ) / 10.0 );
      QCOMPARE(
          m.calculatedValue(nullptr, KChartEnums::MeasureOrientationMaximum),
          qMax( m_chart->size().width(), m_chart->size().height() ) / 10.0 );
  }


  void cleanupTestCase()
  {
  }

private:
    Chart *m_chart;
    BarDiagram *m_bars;
    TableModel *m_model;

};

QTEST_MAIN(TestMeasure)

#include "main.moc"
