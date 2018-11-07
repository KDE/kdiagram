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
#include <KChartBarDiagram>
#include <KChartLineDiagram>
#include <KChartCartesianCoordinatePlane>
#include <KChartLegend>

#include <TableModel.h>

using namespace KChart;

class TestLegends: public QObject {
    Q_OBJECT
private slots:

    void initTestCase()
    {
        m_chart = new Chart(nullptr);
        m_lines = new LineDiagram();
        m_bars = new BarDiagram();
        m_tableModel = new TableModel( this );
        m_tableModel->loadFromCSV( "../../examples/tools/modeldata/KChart-Test-Datatables.csv" );
        m_lines->setModel( m_tableModel );
        m_bars->setModel( m_tableModel );
        m_chart->coordinatePlane()->replaceDiagram( m_lines );
    }

    void testIntialOwnership()
    {
        Legend* l = new Legend( m_chart );
        m_chart->addLegend( l );
        QCOMPARE( m_chart->legend(), l );
        QCOMPARE( l->diagram(), (AbstractDiagram*)nullptr);
        l->setDiagram( m_lines );
        QCOMPARE( dynamic_cast< LineDiagram * >(l->diagram()), m_lines );
    }

    void testIntialOwnershipFromCtor()
    {
        Legend* l = new Legend( m_lines, m_chart );
        m_chart->replaceLegend( l );
        QCOMPARE( m_chart->legend(), l );
        QCOMPARE( dynamic_cast< LineDiagram * >(l->diagram()), m_lines );
    }

    void testReplacing()
    {
        Legend* l = new Legend( m_chart );
        QPointer<Legend> oldLegend = m_chart->legend();
        QCOMPARE( dynamic_cast< LineDiagram * >(oldLegend->diagram()), m_lines );
        m_chart->replaceLegend( l, oldLegend );
        QVERIFY( oldLegend.isNull() );
        QCOMPARE( l->diagram(), (AbstractDiagram*)nullptr );
        l->setDiagram( m_lines );
        QCOMPARE( dynamic_cast< LineDiagram * >(l->diagram()), m_lines );
    }

    void testReferenceArea()
    {
         Legend* l = new Legend( );
         QCOMPARE( l->referenceArea(), ( const QWidget* )nullptr );
         l->setReferenceArea( m_chart );
         QCOMPARE( dynamic_cast< const Chart * >(l->referenceArea()), const_cast< const Chart * >(m_chart) );
         Legend* l1 = new Legend( m_chart );
         QCOMPARE( dynamic_cast< const Chart * >(l1->referenceArea()), const_cast< const Chart * >(m_chart) );
         Legend* l2 = new Legend( m_lines,  m_chart );
         QCOMPARE( dynamic_cast< const Chart * >(l2->referenceArea()), const_cast< const Chart * >(m_chart) );
    }

    void testDiagramOwnership()
    {
        Legend* l = new Legend( m_chart );
        QVERIFY( l->diagrams().size() == 0 );
        l->addDiagram( m_lines );
        QVERIFY( l->diagrams().size() == 1 );
        l->addDiagram( m_bars );
        QVERIFY( l->diagrams().size() == 2 );
        QCOMPARE( dynamic_cast< LineDiagram * >(l->diagram()),  m_lines );
        l->removeDiagram( m_lines );
        QVERIFY( l->diagrams().size() == 1 );
        QCOMPARE( dynamic_cast< BarDiagram * >(l->diagram()),  m_bars );
        l->replaceDiagram( m_lines, m_bars );
        QVERIFY( l->diagrams().size() == 1 );
        QCOMPARE( dynamic_cast< LineDiagram * >(l->diagram()),  m_lines );
    }

    void testLegendSettings()
    {
       Legend* l = new Legend( m_lines,  m_chart );
       QVERIFY( l->position() == Position::NorthEast );
       QVERIFY( l->alignment() == Qt::AlignCenter );
       QVERIFY( l->orientation() == Qt::Vertical );
       QVERIFY( l->showLines() == false );
       QVERIFY( !l->titleText().isEmpty() );
       QVERIFY( l->spacing() == 1 );
       QVERIFY( l->legendStyle() == Legend::MarkersOnly );
       l->setPosition( Position::North );
       l->setAlignment( Qt::AlignLeft );
       l->setOrientation( Qt::Horizontal );
       l->setShowLines( true );
       l->setTitleText( QString( tr( "Lines" ) ) );
       l->setSpacing( 2 );
       l->setLegendStyle( Legend::LinesOnly );
       QVERIFY( l->position() == Position::North );
       QVERIFY( l->alignment() == Qt::AlignLeft );
       QVERIFY( l->orientation() == Qt::Horizontal );
       QVERIFY( l->showLines() == true );
       QVERIFY( l->titleText() == QString( tr( "Lines" ) ) );
       QVERIFY( l->spacing() == 2 );
       QVERIFY( l->legendStyle() == Legend::LinesOnly );
    }


    void cleanupTestCase()
    {
    }

private:
    Chart *m_chart;
    BarDiagram *m_bars;
    LineDiagram *m_lines;
    TableModel *m_tableModel;

};

QTEST_MAIN(TestLegends)

#include "main.moc"
