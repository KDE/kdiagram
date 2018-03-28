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
#include <KChartRingDiagram>
#include <KChartPieAttributes>
#include <KChartThreeDPieAttributes>
#include <KChartPolarCoordinatePlane>

#include <TableModel.h>

using namespace KChart;

class TestRingDiagrams: public QObject {
    Q_OBJECT
private slots:

    void initTestCase()
    {
        m_chart = new Chart(0);
        PolarCoordinatePlane* polarPlane = new PolarCoordinatePlane( m_chart );
        m_chart->replaceCoordinatePlane( polarPlane );
        m_model = new TableModel( this );
        m_model->loadFromCSV( ":/data" );
        m_ring = new RingDiagram();
        m_ring->setModel( m_model );
        m_chart->coordinatePlane()->replaceDiagram( m_ring );
    }

    void testRingDiagramsSettings()
    {
        QVERIFY( m_ring->granularity() == 1 );
        m_ring->setGranularity( 2 );
        QVERIFY( m_ring->granularity() == 2 );
    }


    void testRingAttributesLevelSettings()
    {
        //check segments
        const int cols = m_ring->model()->columnCount();
        QCOMPARE( m_ring->columnCount(), cols );
        // create attribut
        PieAttributes pa( m_ring->pieAttributes() );
        PieAttributes paCol( m_ring->pieAttributes() );

        // modify at different level and compare
        paCol.setExplode ( true );
        m_ring->setPieAttributes( pa );
        m_ring->setPieAttributes( cols-2,  paCol );

        QVERIFY( m_ring->pieAttributes() != m_ring->pieAttributes(cols-2) );

        QCOMPARE( m_ring->pieAttributes(),  pa );
        QCOMPARE( m_ring->pieAttributes( cols - 2 ),  paCol );

        // try and override the cols and index level - should not work
        m_ring->setPieAttributes( pa );
        QVERIFY( m_ring->pieAttributes().explode() == false );
        QVERIFY( m_ring->pieAttributes( cols-2 ).explode() == true );

    }

    void testRingAttributesValueSettings()
    {
        PieAttributes pa( m_ring->pieAttributes() );

        // check default values
        QVERIFY( pa.explode() == false );
        QVERIFY( pa.explodeFactor() == 0.0 );
        //change settings
        pa.setExplode ( true );
        pa.setExplodeFactor( 0.2 );
        m_ring->setPieAttributes(  pa );
        // get new values
        QVERIFY( m_ring->pieAttributes().explode() == true );
        QVERIFY( m_ring->pieAttributes().explodeFactor() == 0.2 );
    }

    void testThreeDRingAttributesLevelSettings()
    {
        //check segments
        const int cols = m_ring->model()->columnCount();
        QCOMPARE( m_ring->columnCount(), cols );

        // create attribut
        ThreeDPieAttributes td( m_ring->threeDPieAttributes() );
        ThreeDPieAttributes tdCol( m_ring->threeDPieAttributes() );
        // modify at different level and compare
        tdCol.setDepth(25 );
        m_ring->setThreeDPieAttributes( td  );
        m_ring->setThreeDPieAttributes( cols-2,  tdCol );
        QVERIFY( m_ring->threeDPieAttributes() !=
                 m_ring->threeDPieAttributes(cols-2) );
        QCOMPARE( m_ring->threeDPieAttributes(),  td );
        QCOMPARE( m_ring->threeDPieAttributes( cols - 2 ),  tdCol );
        // try and override the cols and index level - should not work
        m_ring->setThreeDPieAttributes( td );
        QVERIFY( m_ring->threeDPieAttributes().depth() == -10 );
        QVERIFY( m_ring->threeDPieAttributes( cols-2 ).depth() == 25 );
    }

    void testThreeDRingAttributesValueSettings()
    {
        ThreeDPieAttributes td( m_ring->threeDPieAttributes() );
        //check default values
        QVERIFY( td.isEnabled() == false );
        QVERIFY( td.depth() == -10 );
        QVERIFY( td.validDepth() == 0.0 );
        //pie specifics
        QVERIFY( td.useShadowColors() ==  true );

        //set new values
        td.setEnabled(  true );
        td.setDepth( 40 );
        td.setUseShadowColors( false ); // not implemented yet
         m_ring->setThreeDPieAttributes( td );

        //get new values
        QVERIFY( m_ring->threeDPieAttributes().isEnabled() == true );
        QVERIFY( m_ring->threeDPieAttributes().depth() == 40 );
        QVERIFY( m_ring->threeDPieAttributes().validDepth() == 40 );
        QVERIFY( m_ring->threeDPieAttributes().useShadowColors() == false );
    }

    void testRingDiagramDimension()
    {
        QCOMPARE(m_ring->datasetDimension(), 1);
        QVERIFY(m_chart->coordinatePlane()->gridDimensionsList().isEmpty());
    }

    void cleanupTestCase()
    {
        delete m_chart;
    }

private:
    Chart *m_chart;
    RingDiagram *m_ring;
    TableModel *m_model;

};

QTEST_MAIN(TestRingDiagrams)

#include "main.moc"
