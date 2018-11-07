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
#include <KChartBarDiagram>
#include <KChartHeaderFooter>
#include <KChartPosition>
#include <KChartBackgroundAttributes>
#include <KChartFrameAttributes>
#include <QApplication>

using namespace KChart;

class ChartWidget : public QWidget {
  Q_OBJECT
public:
  explicit ChartWidget(QWidget* parent = nullptr)
    : QWidget(parent)
  {

    m_model.insertRows( 0, 2, QModelIndex() );
    m_model.insertColumns(  0,  3,  QModelIndex() );
    for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 3; ++column) {
                QModelIndex index = m_model.index(row, column, QModelIndex());
                m_model.setData(index, QVariant(row+1 * column) );
            }
    }

    BarDiagram* diagram = new BarDiagram;
    diagram->setModel(&m_model);

    m_chart.coordinatePlane()->replaceDiagram(diagram);

    // Add at one Header and set it up
    HeaderFooter* header = new HeaderFooter( &m_chart );
    header->setPosition( Position::North );
    header->setText( "A Simple Bar Chart" );
    m_chart.addHeaderFooter( header );

    // Configure the Header text attributes
    TextAttributes hta;
    hta.setPen( QPen(  Qt::blue ) );

    // let the header resize itself
    // together with the widget.
    // so-called relative size
    Measure m( 35.0 );
    m.setRelativeMode( header->autoReferenceArea(), KChartEnums::MeasureOrientationMinimum );
    hta.setFontSize( m );
    // min font size
    m.setValue( 3.0 );
    m.setCalculationMode( KChartEnums::MeasureCalculationModeAbsolute );
    hta.setMinimalFontSize( m );
    header->setTextAttributes( hta );

    // Configure the header Background attributes
    BackgroundAttributes hba;
    hba.setBrush(  Qt::white );
    hba.setVisible( true );
    header->setBackgroundAttributes(  hba );

    // Configure the header Frame attributes
    FrameAttributes hfa;
    hfa.setPen( QPen ( QBrush( Qt::darkGray ), 2 ) );
    hfa.setVisible( true );
    header->setFrameAttributes(  hfa );

    QVBoxLayout* l = new QVBoxLayout(this);
    l->addWidget(&m_chart);
    m_chart.setGlobalLeadingTop( 10 );
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
