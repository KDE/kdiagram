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

#include <QApplication>
#include <QStandardItemModel>
#include <QWidget>
#include <KChartChart>
#include <KChartBarDiagram>
#include <KChartDataValueAttributes>

using namespace KChart;

class ChartWidget : public QWidget
{
  Q_OBJECT
public:
    explicit ChartWidget( QWidget *parent = nullptr );

private:
  Chart m_chart;
  QStandardItemModel m_model;
};

ChartWidget::ChartWidget( QWidget *parent )
   : QWidget( parent )
{
    m_model.insertRows( 0, 2, QModelIndex() );
    m_model.insertColumns( 0, 3, QModelIndex() );
    for ( int row = 0; row < 3; ++row ) {
        for ( int column = 0; column < 3; ++column ) {
            QModelIndex index = m_model.index( row, column, QModelIndex() );
            m_model.setData(index, row * 3 + column );
        }
    }

    BarDiagram* diagram = new KChart::BarDiagram;
    diagram->setModel( &m_model );

    BarAttributes ba( diagram->barAttributes() );
    //set the bar width and enable it
    ba.setFixedBarWidth( 140 );
    ba.setUseFixedBarWidth( true );
    //configure gap between values
    //and blocks
    ba.setGroupGapFactor( 0.50 );
    ba.setBarGapFactor( 0.125 );

    //assign to the diagram
    diagram->setBarAttributes( ba );

    // display the values
    DataValueAttributes dva( diagram->dataValueAttributes() );
    TextAttributes ta( dva.textAttributes() );
    //rotate if you wish
    //ta.setRotation( 0 );
    ta.setFont( QFont( "Comic", 9 ) );
    ta .setPen( QPen( QColor( Qt::darkGreen ) ) );
    ta.setVisible( true );
    dva.setTextAttributes( ta );
    dva.setVisible( true );
    diagram->setDataValueAttributes( dva );

    //draw a surrounding line around bars
    QPen linePen;
    linePen.setColor( Qt::magenta );
    linePen.setWidth( 4 );
    linePen.setStyle( Qt::DotLine );
    //draw only around a dataset
    //to draw around all the bars
    // call setPen( myPen );
    diagram->setPen( 1, linePen );

    m_chart.coordinatePlane()->replaceDiagram( diagram );
    m_chart.setGlobalLeadingTop( 40 );

    QVBoxLayout *l = new QVBoxLayout( this );
    l->addWidget( &m_chart );
    setLayout( l );
}


int main( int argc, char** argv )
{
    QApplication app( argc, argv );

    ChartWidget w;
    w.show();

    return app.exec();
}

#include "main.moc"
