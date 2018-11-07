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
#include <TableModel.h>
#include <KChartGlobal>
#include <KChartAttributesModel>
#include <KChartBarDiagram>
#include <KChartLineDiagram>
#include <KChartCartesianCoordinatePlane>
#include <KChartDataValueAttributes>

using namespace KChart;

class TestKChartAttributesModel : public QObject {
  Q_OBJECT
private slots:

  void initTestCase()
  {
      TableModel *tableModel = new TableModel( this );
      tableModel->loadFromCSV( ":/data" );
      tableModel->setSupplyHeaderData( false );
      m_model = tableModel;
      m_plane = new CartesianCoordinatePlane(nullptr);
      m_bars = new BarDiagram();
      m_bars->setModel( m_model );
      m_lines = new LineDiagram();
      m_lines->setModel( m_model );
  }

  void testKChartAttributesModelSetSimpleData()
  {
      QModelIndex idx = m_model->index( 0, 2, QModelIndex() );
      DataValueAttributes a = m_bars->dataValueAttributes( idx );
      QCOMPARE( a.isVisible(), false );
      a.setVisible( true );
      m_bars->setDataValueAttributes( 2, a );
      a = m_bars->dataValueAttributes( idx );
      QCOMPARE( a.isVisible(), true );
  }

  void testKChartAttributesModelTestPrivateModel()
  {
      // Private is now default
      //m_lines->usePrivateAttributes( true );
      // now we should be getting defaults again
      QModelIndex idx = m_bars->model()->index( 0, 2, QModelIndex() );
      DataValueAttributes a = m_lines->dataValueAttributes( idx );
      QCOMPARE( a.isVisible(), false );
      // set the defaults on the other model and make sure they have
      // an effect
      m_bars->setDataValueAttributes( 2, a );
      DataValueAttributes b = m_bars->dataValueAttributes( idx );
      QCOMPARE( b.isVisible(), false );
      // now change a, set it on the lines, check that the bars
      // didn't change
      a.setVisible( true );
      m_lines->setDataValueAttributes( 2, a );
      QCOMPARE( a.isVisible(), true );
      b = m_bars->dataValueAttributes( idx );
      QCOMPARE( b.isVisible(), false );
  }

  void testKChartAttributesModelTestSharedModel()
  {
      // Note: a SHARED atributes-model must be owned by the USER
      //       but it may not be owned by any of the diagrams
      //       see API docu of AbstractDiagram::setAttributesModel()
      AttributesModel *attrsmodel = new AttributesModel( m_model, nullptr );

      m_lines->setAttributesModel( attrsmodel );
      m_bars->setAttributesModel(  attrsmodel );

      QModelIndex idx = m_model->index( 0, 2, QModelIndex() );

      DataValueAttributes attrLin = m_lines->dataValueAttributes( idx );
      attrLin.setVisible( false );
      m_lines->setDataValueAttributes( idx, attrLin );

      DataValueAttributes attrBar = m_bars->dataValueAttributes( idx );
      QCOMPARE( attrBar.isVisible(), false );

      attrLin.setVisible( true );
      m_lines->setDataValueAttributes( idx, attrLin );

      attrBar = m_bars->dataValueAttributes( idx );
      QCOMPARE( attrBar.isVisible(), true );
  }

  void testKChartAttributesModelTestSharedFromStart()
  {
      delete m_lines;
      delete m_bars;
      delete m_plane;
      m_plane = new CartesianCoordinatePlane(nullptr);
      m_bars = new BarDiagram();
      m_bars->setModel( m_model );
      m_lines = new LineDiagram();
      m_lines->setModel( m_model );

      AttributesModel* attrsmodel = new AttributesModel( m_model, m_plane );
      m_lines->setAttributesModel(attrsmodel);
      m_bars->setAttributesModel(attrsmodel);
      
      QModelIndex idx = m_bars->model()->index( 0, 2, QModelIndex() );
      DataValueAttributes a = m_lines->dataValueAttributes( idx );
      DataValueAttributes b = m_bars->dataValueAttributes( idx );
      QCOMPARE( a.isVisible(), false );
      QCOMPARE( b.isVisible(), false );
      a.setVisible( true );
      QCOMPARE( a.isVisible(), true );
      m_lines->setDataValueAttributes( 2, a );
      b = m_bars->dataValueAttributes( idx );
      QCOMPARE( b.isVisible(), true ); // Should be true by sharing
  }

  void testKChartAttributesModelTestPrivate()
  {
      m_lines->setAttributesModel( new AttributesModel(m_model,m_lines) );
      m_bars->setAttributesModel( new AttributesModel(m_model,m_bars) );
      QModelIndex idx = m_lines->model()->index( 0, 2, QModelIndex() );
      DataValueAttributes a = m_lines->dataValueAttributes( idx );
      QCOMPARE( a.isVisible(), false ); // we got a default model again
      a.setVisible( true );
      m_lines->setDataValueAttributes( 2, a );
      // should now have propagated to the bars
      DataValueAttributes b = m_bars->dataValueAttributes( idx );
      QCOMPARE( b.isVisible(), false ); // No sharing
  }


  void cleanupTestCase()
  {
      delete m_plane;
  }

private:
  QAbstractItemModel *m_model;
  CartesianCoordinatePlane* m_plane;
  BarDiagram *m_bars;
  LineDiagram *m_lines;

};

QTEST_MAIN(TestKChartAttributesModel)

#include "main.moc"
