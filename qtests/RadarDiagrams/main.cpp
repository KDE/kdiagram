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
#include <KChartRadarDiagram>
#include <KChartPieAttributes>
#include <KChartThreeDPieAttributes>
#include <KChartPolarCoordinatePlane>

#include <TableModel.h>

using namespace KChart;

class TestRadarDiagrams: public QObject {
    Q_OBJECT
private slots:

    void initTestCase()
    {
        m_chart = new Chart(0);
        RadarCoordinatePlane* polarPlane = new RadarCoordinatePlane( m_chart );
        m_chart->replaceCoordinatePlane( polarPlane );
        m_model = new TableModel( this );
        m_model->loadFromCSV( ":/data" );
        m_radar = new RadarDiagram();
        m_radar->setModel( m_model );
        m_chart->coordinatePlane()->replaceDiagram( m_radar );
    }

    void testRadarDiagramDimension()
    {
        QCOMPARE(m_radar->datasetDimension(), 1);
        QVERIFY(m_chart->coordinatePlane()->gridDimensionsList().isEmpty());
    }

    void cleanupTestCase()
    {
        delete m_chart;
    }

private:
    Chart *m_chart;
    RadarDiagram *m_radar;
    TableModel *m_model;

};

QTEST_MAIN(TestRadarDiagrams)

#include "main.moc"
