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
#include <QStandardItemModel>

#include <KChartChart>
#include <KChartGlobal>
#include <KChartPieDiagram>
#include <KChartPolarDiagram>
#include <KChartPolarCoordinatePlane>
#include <KChartAbstractCoordinatePlane>
#include <KChartLegend>
#include <KChartGridAttributes>

#include <TableModel.h>

using namespace KChart;

class TestPolarPlanes: public QObject {
    Q_OBJECT
private slots:

    void initTestCase()
    {
        m_chart = new Chart(0);
        m_tableModel = new TableModel( this );
        m_tableModel->loadFromCSV( ":/data" );
        m_pie = new PieDiagram();
        m_pie->setModel( m_tableModel );
        m_polar = new PolarDiagram();
        m_polar->setModel( m_tableModel );
        m_plane = new PolarCoordinatePlane();
        m_chart->addCoordinatePlane( m_plane );
        m_plane->setReferenceCoordinatePlane( m_chart->coordinatePlane() );
    }

    void testIntialOwnership()
    {
        AbstractCoordinatePlane *plane = m_chart->coordinatePlane();
        QCOMPARE( m_plane->referenceCoordinatePlane(), m_chart->coordinatePlane() );
        m_chart->takeCoordinatePlane( 0 );
        delete plane;
        QCOMPARE( m_plane->referenceCoordinatePlane(), (AbstractCoordinatePlane*)0 );
    }

    void testStartPositionSettings()
    {
        m_plane->addDiagram(  m_pie );
        QVERIFY( m_plane->startPosition() ==  0.0 );
        qreal pos = 45;
        m_plane->addDiagram(  m_pie );
        m_plane->setStartPosition( pos );
        QVERIFY( m_plane->startPosition() ==  pos );
        m_plane->takeDiagram(  m_pie );
    }

      void testZoomFactorsSettings()
    {
        m_plane->addDiagram(  m_pie );
        QCOMPARE( m_plane->zoomFactorX(),  1.0 );
        QCOMPARE( m_plane->zoomFactorY(),  1.0 );
        QCOMPARE( m_plane->zoomCenter(), QPointF( 0.5, 0.5 ) );
        m_plane->setZoomFactorX( 1.5 );
        m_plane->setZoomFactorY( 1.5 );
        m_plane->setZoomCenter( QPointF ( 1.0, 1.0 ) );
        QCOMPARE( m_plane->zoomFactorX(),  1.5 );
        QCOMPARE( m_plane->zoomFactorY(),  1.5 );
        QCOMPARE( m_plane->zoomCenter(),  QPointF( 1.0, 1.0 ) );
        m_plane->takeDiagram(  m_pie );
    }

    void testDiagramOwnership()
    {

        QCOMPARE( m_plane->diagrams().size(),  1 );
        m_plane->addDiagram(  m_polar );
        QCOMPARE( m_plane->diagrams().size(),  2 );
        QCOMPARE( dynamic_cast< PieDiagram * >(m_plane->diagram()),  m_pie );
        m_plane->takeDiagram( m_pie );
        QCOMPARE( m_plane->diagrams().size(),  1 );
        QCOMPARE( dynamic_cast< PolarDiagram * >(m_plane->diagram()),  m_polar );
        m_plane->replaceDiagram( m_pie,  m_polar );
        QCOMPARE( m_plane->diagrams().size(),  1 );
        QCOMPARE( dynamic_cast< PieDiagram * >(m_plane->diagram()),  m_pie );
        m_plane->takeDiagram( m_pie );
        QCOMPARE( m_plane->diagrams().size(),  0 );
        delete m_pie;
    }

    void testGlobalGridAttributesSettings()
    {
        GridAttributes ga = m_plane->globalGridAttributes();
        QVERIFY( ga.isGridVisible() == true );
        ga.setGridVisible(  false );
        m_plane->setGlobalGridAttributes(  ga );
        QVERIFY( m_plane->globalGridAttributes().isGridVisible() == false );
        //reset to normal
        ga.setGridVisible(  true );
        QVERIFY( m_plane->globalGridAttributes().isGridVisible() == false );
        m_plane->setGlobalGridAttributes(  ga );
        QVERIFY( m_plane->globalGridAttributes().isGridVisible() == true );
    }

      void testGridAttributesSettings()
    {
        GridAttributes gcircular = m_plane->gridAttributes( true );
        GridAttributes gsagittal = m_plane->gridAttributes( false );
        QVERIFY( gcircular.isGridVisible() == true );
        gcircular.setGridVisible( false );
        m_plane->setGridAttributes( true, gcircular );
        QVERIFY( m_plane->hasOwnGridAttributes( true ) == true );
        QVERIFY( m_plane->hasOwnGridAttributes( false ) == false );
        QVERIFY( m_plane->gridAttributes( true ).isGridVisible() == false );
        QVERIFY( m_plane->gridAttributes( false ).isGridVisible() == true );
        gsagittal.setGridVisible( false );
        m_plane->setGridAttributes( false, gsagittal );
        QVERIFY( m_plane->hasOwnGridAttributes( true ) == true );
        QVERIFY( m_plane->hasOwnGridAttributes( true ) == true );
        QVERIFY( m_plane->gridAttributes( true ).isGridVisible() == false );
        QVERIFY( m_plane->gridAttributes( false ).isGridVisible() == false );
        m_plane->resetGridAttributes( true );
        m_plane->resetGridAttributes( false );
        QVERIFY( m_plane->gridAttributes( true ).isGridVisible() == true );
        QVERIFY( m_plane->gridAttributes( false ).isGridVisible() == true );
        QVERIFY( m_plane->hasOwnGridAttributes( true ) == false );
        QVERIFY( m_plane->hasOwnGridAttributes( false ) == false );
    }

    void cleanupTestCase()
    {
    }

private:
    Chart *m_chart;
    PieDiagram *m_pie;
    PolarDiagram *m_polar;
    PolarCoordinatePlane *m_plane;
    TableModel *m_tableModel;

};

QTEST_MAIN(TestPolarPlanes)

#include "main.moc"
