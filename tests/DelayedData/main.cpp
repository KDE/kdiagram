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

#include <QStandardItemModel>
#include <QPushButton>
#include <QApplication>
#include <KChartChart>
#include <KChartBarDiagram>
#include <KChartCartesianAxis>
#include <KChartCartesianCoordinatePlane>
#include <KChartLegend>

class ChartWidget : public QWidget {
  Q_OBJECT
public:
  explicit ChartWidget(QWidget* parent = nullptr)
    : QWidget(parent)
  {
    m_model.insertRows( 0, 0, QModelIndex() );
    KChart::BarDiagram* diagram = new KChart::BarDiagram;
    diagram->setModel(&m_model);    

    KChart::Legend* legend = new KChart::Legend(diagram,diagram);
    m_chart.addLegend(legend);

    // The code below doesn't work, but it would 
    // be nice if it did:
#if 0
    KChart::Legend* legend = new KChart::Legend;
    legend->addDiagram(diagram1);
    legend->addDiagram(diagram2);
    ...
    m_chart.addLegend(legend);
#endif

    KChart::CartesianAxis* abcissa = new KChart::CartesianAxis(diagram);
    abcissa->setPosition( KChart::CartesianAxis::Bottom );
    KChart::CartesianAxis* ordinate = new KChart::CartesianAxis(diagram);
    ordinate->setPosition( KChart::CartesianAxis::Left );
    diagram->addAxis(abcissa);
    diagram->addAxis(ordinate);

    // NOTE: If this is done before adding axes,
    // the axes don't show up at all
    m_chart.coordinatePlane()->replaceDiagram(diagram);

    m_rowbutton.setText( tr("Add rows") );
    m_colbutton.setText( tr("Add columns") );
    connect( &m_rowbutton, SIGNAL(clicked()),
	     this, SLOT(addRows()));
    connect( &m_colbutton, SIGNAL(clicked()),
	     this, SLOT(addCols()));

    QVBoxLayout* l = new QVBoxLayout(this);
    l->addWidget(&m_chart);
    l->addWidget(&m_rowbutton);
    l->addWidget(&m_colbutton);

    setLayout(l);
  }

private slots:

  void addRows()
  {
    m_model.insertRows(m_model.rowCount(),1);
    for ( int i = 0; i < m_model.columnCount(); ++i ) {
      m_model.setData( m_model.index(m_model.rowCount()-1,i), i );
    }
  }
  void addCols()
  {
    m_model.insertColumns(m_model.columnCount(),1);
    for ( int i = 0; i < m_model.rowCount(); ++i ) {
      m_model.setData( m_model.index(i,m_model.columnCount()-1), i );
    }
  }

private:
  KChart::Chart m_chart;
  QPushButton m_rowbutton;
  QPushButton m_colbutton;
  QStandardItemModel m_model;
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );
    
    ChartWidget w;
    w.show();

    return app.exec();
}

#include "main.moc"
