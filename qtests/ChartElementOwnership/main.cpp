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
#include <KChartLineDiagram>
#include <KChartCartesianCoordinatePlane>
#include <KChartPolarCoordinatePlane>
#include <KChartLegend>
#include <KChartHeaderFooter>

using namespace KChart;

class TestChartElementOwnership: public QObject {
    Q_OBJECT
private slots:

    void initTestCase()
    {
        m_chart = new Chart(nullptr);
    }

    void testPlaneOwnership()
    {
        // check number plane
        AbstractCoordinatePlane*orig = m_chart->coordinatePlane();
        QCOMPARE( m_chart->coordinatePlanes().size(), 1 );

        // add and take
        CartesianCoordinatePlane *p = new CartesianCoordinatePlane();
        m_chart->addCoordinatePlane( p );
        QCOMPARE( m_chart->coordinatePlanes().size(), 2 );
        m_chart->takeCoordinatePlane( orig );
        QCOMPARE( m_chart->coordinatePlanes().size(), 1 );
        QCOMPARE( dynamic_cast< CartesianCoordinatePlane * >(m_chart->coordinatePlane()), p );
        m_chart->addCoordinatePlane( orig );
        QCOMPARE( m_chart->coordinatePlanes().size(), 2 );

        // replace abstract by polar
        PolarCoordinatePlane *po = new PolarCoordinatePlane();
        m_chart->replaceCoordinatePlane( po, orig );
        QCOMPARE( m_chart->coordinatePlanes().size(), 2 );
        m_chart->takeCoordinatePlane( p );
        QCOMPARE( m_chart->coordinatePlanes().size(), 1 );
        QCOMPARE( dynamic_cast< PolarCoordinatePlane * >(m_chart->coordinatePlane()), po );
        m_chart->addCoordinatePlane( p );
        QCOMPARE( m_chart->coordinatePlanes().size(), 2 );

        // delete
        delete po;
        QCOMPARE( m_chart->coordinatePlanes().size(), 1 );
        QCOMPARE( dynamic_cast< CartesianCoordinatePlane * >(m_chart->coordinatePlane()), p );

        // replace cartesian by polar
        PolarCoordinatePlane*polast = new PolarCoordinatePlane();
        m_chart->replaceCoordinatePlane( polast );
        QCOMPARE( m_chart->coordinatePlanes().size(), 1 );
        QCOMPARE( dynamic_cast< PolarCoordinatePlane * >(m_chart->coordinatePlane()), polast );

        // replace polar by cartesian
        CartesianCoordinatePlane* plast = new CartesianCoordinatePlane();
        m_chart->replaceCoordinatePlane( plast,  polast );
        QCOMPARE( m_chart->coordinatePlanes().size(), 1 );
        QCOMPARE( dynamic_cast< CartesianCoordinatePlane * >(m_chart->coordinatePlane()), plast );

    }

    void testHeaderFooterOwnership()
    {
        QCOMPARE( m_chart->headerFooters().size(), 0 );
        HeaderFooter * h = new HeaderFooter();
        m_chart->addHeaderFooter( h );
        QCOMPARE( m_chart->headerFooters().size(), 1 );
        m_chart->takeHeaderFooter( h );
        QCOMPARE( m_chart->headerFooters().size(), 0 );
        m_chart->addHeaderFooter( h );
        QCOMPARE( m_chart->headerFooters().size(), 1 );
        delete h;
        QCOMPARE( m_chart->headerFooters().size(), 0 );
    }

    void testHeaderFooterReplace()
    {
        QCOMPARE( m_chart->headerFooters().size(), 0 );
        HeaderFooter * h = new HeaderFooter();
        HeaderFooter * h1 = new HeaderFooter();
        m_chart->addHeaderFooter( h );
        QCOMPARE( m_chart->headerFooters().size(), 1 );
        m_chart->addHeaderFooter( h1 );
        QCOMPARE( m_chart->headerFooters().size(), 2 );
        m_chart->takeHeaderFooter( h );
        QCOMPARE( m_chart->headerFooters().size(), 1 );
        QCOMPARE( m_chart->headerFooter(), h1 );
        m_chart->replaceHeaderFooter( h,  h1 );
        QCOMPARE( m_chart->headerFooters().size(), 1 );
        delete h;
        QCOMPARE( m_chart->headerFooters().size(), 0 );
    }


    void testLegendOwnership()
    {
        // check no legend
        QCOMPARE( m_chart->legends().size(), 0 );

        // check add legend - take legend - delete legend
        Legend * legend = new Legend( m_chart->coordinatePlane()->diagram() );
        m_chart->addLegend( legend );
        QCOMPARE( m_chart->legends().size(), 1 );
        m_chart->takeLegend( legend );
        QCOMPARE( m_chart->legends().size(), 0 );
        m_chart->addLegend( legend );
        QCOMPARE( m_chart->legends().size(), 1 );
        delete legend;
        QCOMPARE( m_chart->legends().size(), 0 );
    }

    void testLegendReplace()
    {

        // check no legend
        QCOMPARE( m_chart->legends().size(), 0 );
        // check add several legends - take legend
        // replace legend - delete legend
        Legend * legend = new Legend( m_chart->coordinatePlane()->diagram() );
        Legend * legend2 = new Legend( m_chart->coordinatePlane()->diagram() );
        m_chart->addLegend( legend );
        QCOMPARE( m_chart->legends().size(), 1 );
        m_chart->addLegend( legend2 );
        QCOMPARE( m_chart->legends().size(), 2 );
        m_chart->takeLegend( legend );
        QCOMPARE( m_chart->legends().size(), 1 );
        QCOMPARE( m_chart->legend(), legend2 );
        m_chart->replaceLegend( legend, legend2  );
        QCOMPARE( m_chart->legends().size(), 1 );
        delete legend;
        QCOMPARE( m_chart->legends().size(), 0 );
    }

    void testPadding()
    {
      QVERIFY( m_chart->globalLeadingLeft() == false );
      m_chart->setGlobalLeading( 2, 2, 2, 2 );
      QCOMPARE( m_chart->globalLeadingLeft(), 2 );
      QCOMPARE( m_chart->globalLeadingTop(), 2 );
      QCOMPARE( m_chart->globalLeadingRight(), 2 );
      QCOMPARE( m_chart->globalLeadingBottom(), 2 );
      m_chart->setGlobalLeadingLeft( 5 );
      QCOMPARE( m_chart->globalLeadingLeft(), 5 );
      QCOMPARE( m_chart->globalLeadingTop(), 2 );
      QCOMPARE( m_chart->globalLeadingRight(), 2 );
      QCOMPARE( m_chart->globalLeadingBottom(), 2 );
      m_chart->setGlobalLeadingTop( 5 );
      QCOMPARE( m_chart->globalLeadingLeft(), 5 );
      QCOMPARE( m_chart->globalLeadingTop(), 5 );
      QCOMPARE( m_chart->globalLeadingRight(), 2 );
      QCOMPARE( m_chart->globalLeadingBottom(), 2 );
      m_chart->setGlobalLeadingRight( 5 );
      QCOMPARE( m_chart->globalLeadingLeft(), 5 );
      QCOMPARE( m_chart->globalLeadingTop(), 5 );
      QCOMPARE( m_chart->globalLeadingRight(), 5 );
      QCOMPARE( m_chart->globalLeadingBottom(), 2 );
      m_chart->setGlobalLeadingBottom( 5 );
      QCOMPARE( m_chart->globalLeadingLeft(), 5 );
      QCOMPARE( m_chart->globalLeadingTop(), 5 );
      QCOMPARE( m_chart->globalLeadingRight(), 5 );
      QCOMPARE( m_chart->globalLeadingBottom(), 5 );
      m_chart->setGlobalLeading( 2, 2, 2, 2 );
      QCOMPARE( m_chart->globalLeadingLeft(), 2 );
      QCOMPARE( m_chart->globalLeadingTop(), 2 );
      QCOMPARE( m_chart->globalLeadingRight(), 2 );
      QCOMPARE( m_chart->globalLeadingBottom(), 2 );
    }


    void testChartDeletion()
    {
        delete m_chart;
    }

    void cleanupTestCase()
    {
    }

private:
    Chart *m_chart;

};

QTEST_MAIN(TestChartElementOwnership)

#include "main.moc"
