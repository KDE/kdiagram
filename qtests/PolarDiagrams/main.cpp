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
#include <KChartPolarDiagram>
#include <KChartPolarCoordinatePlane>

#include <TableModel.h>

using namespace KChart;

class TestPolarDiagrams: public QObject {
    Q_OBJECT
private slots:

    void initTestCase()
    {
        m_chart = new Chart(0);
        PolarCoordinatePlane* polarPlane = new PolarCoordinatePlane( m_chart );
        m_chart->replaceCoordinatePlane( polarPlane );
        m_model = new TableModel( this );
        m_model->loadFromCSV( ":/data" );
        m_polar = new PolarDiagram();
        m_polar->setModel( m_model );
        m_chart->coordinatePlane()->replaceDiagram( m_polar );
    }

    void testPolarDiagramsSettings()
    {
        QVERIFY( m_polar->rotateCircularLabels() == false );
        QVERIFY( m_polar->showDelimitersAtPosition( Position::NorthWest ) == false );
        QVERIFY( m_polar->showDelimitersAtPosition( Position::North ) == false );
        QVERIFY( m_polar->showDelimitersAtPosition( Position::NorthEast ) == false );
        QVERIFY( m_polar->showDelimitersAtPosition( Position::West ) == false );
        QVERIFY( m_polar->showDelimitersAtPosition( Position::East ) == false );
        QVERIFY( m_polar->showDelimitersAtPosition( Position::SouthWest ) == false );
        QVERIFY( m_polar->showDelimitersAtPosition( Position::South ) == false );
        QVERIFY( m_polar->showDelimitersAtPosition( Position::SouthEast ) == false );
        QVERIFY( m_polar->showLabelsAtPosition( Position::NorthWest ) == false );
        QVERIFY( m_polar->showLabelsAtPosition( Position::North ) == false );
        QVERIFY( m_polar->showLabelsAtPosition( Position::NorthEast ) == false );
        QVERIFY( m_polar->showLabelsAtPosition( Position::West ) == false );
        QVERIFY( m_polar->showLabelsAtPosition( Position::East ) == false );
        QVERIFY( m_polar->showLabelsAtPosition( Position::SouthWest ) == false );
        QVERIFY( m_polar->showLabelsAtPosition( Position::South ) == false );
        QVERIFY( m_polar->showLabelsAtPosition( Position::SouthEast ) == false );
        qDebug() << "void PolarDiagram::init() is never called.....(?)";
        m_polar->setRotateCircularLabels(  true );
        m_polar->setShowDelimitersAtPosition( Position::North, true );
        m_polar->setShowDelimitersAtPosition( Position::South, true );
        m_polar->setShowLabelsAtPosition( Position::North, true );
        m_polar->setShowLabelsAtPosition( Position::South, true );
        QVERIFY( m_polar->rotateCircularLabels() == true );
        QVERIFY( m_polar->showDelimitersAtPosition( Position::North ) == true );
        QVERIFY( m_polar->showDelimitersAtPosition( Position::South ) == true );
        QVERIFY( m_polar->showLabelsAtPosition( Position::North ) == true );
        QVERIFY( m_polar->showLabelsAtPosition( Position::South ) == true );
    }

    void testPolarDiagramDimension()
    {
        QCOMPARE(m_polar->datasetDimension(), 1);
        QVERIFY(m_chart->coordinatePlane()->gridDimensionsList().isEmpty());
    }

    void cleanupTestCase()
    {
        delete m_chart;
    }

private:
    Chart *m_chart;
    PolarDiagram *m_polar;
    TableModel *m_model;

};

QTEST_MAIN(TestPolarDiagrams)

#include "main.moc"
