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
#include <KChartChart>
#include <KChartLineDiagram>
#include <QApplication>

using namespace KChart;

class ChartWidget : public QWidget {
  Q_OBJECT
public:

  explicit ChartWidget(QWidget* parent = nullptr)
    : QWidget(parent)
  {

    m_model.insertRows( 0,6, QModelIndex() );
    m_model.insertColumns( 0,1, QModelIndex() );

    m_model.setData( m_model.index( 0, 0, QModelIndex()),  15);
    m_model.setData( m_model.index( 1, 0, QModelIndex()),  11);
    m_model.setData( m_model.index( 2, 0, QModelIndex()),  7);
    m_model.setData( m_model.index( 3, 0, QModelIndex()),  3);
    m_model.setData( m_model.index( 4, 0, QModelIndex()),  -1);
    m_model.setData( m_model.index( 5, 0, QModelIndex()),  -5);

    LineDiagram* diagram = new LineDiagram;
    diagram->setModel(&m_model);

    m_chart.coordinatePlane()->replaceDiagram(diagram);

    // paint the areas in a few cells
    // using different brushes
    LineAttributes la3(diagram->lineAttributes(m_model.index(3,0,QModelIndex())));
    la3.setDisplayArea(  true );
    la3.setTransparency( 150 );
    diagram->setBrush(m_model.index(1,0,QModelIndex()),QBrush(Qt::green));
    diagram->setLineAttributes( m_model.index( 1, 0,  QModelIndex()),la3);
    diagram->setBrush(m_model.index(3,0,QModelIndex()),QBrush(Qt::yellow));
    diagram->setLineAttributes(m_model.index(3,0,QModelIndex()),la3);
    diagram->setBrush(m_model.index(4,0,QModelIndex()),QBrush(Qt::red));
    diagram->setLineAttributes(m_model.index(4,0,QModelIndex()),la3);

    QVBoxLayout* l = new QVBoxLayout(this);
    l->addWidget(&m_chart);
    setLayout(l);
  }

private:
  Chart m_chart;
  QStandardItemModel m_model;
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    ChartWidget w;
    w.show();

    return app.exec();
}

#include "main.moc"
