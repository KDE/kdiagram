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
#include <KChartPieDiagram>
#include <KChartPieAttributes>
#include <KChartThreeDPieAttributes>
#include <KChartPolarCoordinatePlane>

#include <TableModel.h>

using namespace KChart;

class TestPieDiagrams: public QObject {
    Q_OBJECT
private slots:

    void initTestCase()
    {
        m_chart = new Chart(nullptr);
        PolarCoordinatePlane* polarPlane = new PolarCoordinatePlane( m_chart );
        m_chart->replaceCoordinatePlane( polarPlane );
        m_model = new TableModel( this );
        m_model->loadFromCSV( ":/data" );
        m_pie = new PieDiagram();
        m_pie->setModel( m_model );
        m_chart->coordinatePlane()->replaceDiagram( m_pie );
    }

    void testPieDiagramsSettings()
    {
        QVERIFY( m_pie->granularity() == 1 );
        m_pie->setGranularity( 2 );
        QVERIFY( m_pie->granularity() == 2 );
    }


    void testPieAttributesLevelSettings()
    {
        //check segments
        const int cols = m_pie->model()->columnCount();
        QCOMPARE( m_pie->columnCount(), cols );
        // create attribut
        PieAttributes pa( m_pie->pieAttributes() );
        PieAttributes paCol( m_pie->pieAttributes() );

        // modify at different level and compare
        paCol.setExplode ( true );
        m_pie->setPieAttributes( pa );
        m_pie->setPieAttributes( cols-2,  paCol );

        QVERIFY( m_pie->pieAttributes() != m_pie->pieAttributes(cols-2) );

        QCOMPARE( m_pie->pieAttributes(),  pa );
        QCOMPARE( m_pie->pieAttributes( cols - 2 ),  paCol );

        // try and override the cols and index level - should not work
        m_pie->setPieAttributes( pa );
        QVERIFY( m_pie->pieAttributes().explode() == false );
        QVERIFY( m_pie->pieAttributes( cols-2 ).explode() == true );

    }

    void testPieAttributesValueSettings()
    {
        PieAttributes pa( m_pie->pieAttributes() );

        // check default values
        QVERIFY( pa.explode() == false );
        QVERIFY( pa.explodeFactor() == 0.0 );
        //change settings
        pa.setExplode ( true );
        pa.setExplodeFactor( 0.2 );
        m_pie->setPieAttributes(  pa );
        // get new values
        QVERIFY( m_pie->pieAttributes().explode() == true );
        QVERIFY( m_pie->pieAttributes().explodeFactor() == 0.2 );
    }

    void testThreeDPieAttributesLevelSettings()
    {
        //check segments
        const int cols = m_pie->model()->columnCount();
        QCOMPARE( m_pie->columnCount(), cols );

        // create attribut
        ThreeDPieAttributes td( m_pie->threeDPieAttributes() );
        ThreeDPieAttributes tdCol( m_pie->threeDPieAttributes() );
        // modify at different level and compare
        tdCol.setDepth(25 );
        m_pie->setThreeDPieAttributes( td  );
        m_pie->setThreeDPieAttributes( cols-2,  tdCol );
        QVERIFY( m_pie->threeDPieAttributes() !=
                 m_pie->threeDPieAttributes(cols-2) );
        QCOMPARE( m_pie->threeDPieAttributes(),  td );
        QCOMPARE( m_pie->threeDPieAttributes( cols - 2 ),  tdCol );
        // try and override the cols and index level - should not work
        m_pie->setThreeDPieAttributes( td );
        QVERIFY( m_pie->threeDPieAttributes().depth() == -10 );
        QVERIFY( m_pie->threeDPieAttributes( cols-2 ).depth() == 25 );
    }


    void testThreeDPieAttributesValueSettings()
    {
        ThreeDPieAttributes td( m_pie->threeDPieAttributes() );
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
         m_pie->setThreeDPieAttributes( td );

        //get new values
        QVERIFY( m_pie->threeDPieAttributes().isEnabled() == true );
        QVERIFY( m_pie->threeDPieAttributes().depth() == 40 );
        QVERIFY( m_pie->threeDPieAttributes().validDepth() == 40 );
        QVERIFY( m_pie->threeDPieAttributes().useShadowColors() == false );
    }

    void cleanupTestCase()
    {
    }

private:
    Chart *m_chart;
    PieDiagram *m_pie;
    TableModel *m_model;

};

QTEST_MAIN(TestPieDiagrams)

#include "main.moc"
