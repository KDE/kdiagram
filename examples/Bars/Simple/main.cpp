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

#include <QWidget>
#include <QStandardItemModel>
#include <QtSvg/QSvgGenerator>
#include <KChartChart>
#include <KChartBarDiagram>
#include <QApplication>

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
                /*
                // show tooltips:
                m_model.setData(index,
                QString("<table>"
                    "<tr><td>Row</td><td>Column</td><td>Value</td></tr>"
                    "<tr><th>%1</th><th>%2</th><th>%3</th></tr></table>")
                .arg(row).arg(column).arg(row+1 * column), Qt::ToolTipRole );
                */
            }
    }

    /*
    {
    // show a comment at one data item:
        const int row = 0;
        const int column = 2;
        const QModelIndex index = m_model.index(row, column, QModelIndex());
        m_model.setData(
            index,
            QString("Value %1/%2: %3")
                    .arg( row )
                    .arg( column )
                    .arg( m_model.data( index ).toInt() ),
            KChart::CommentRole );
    }
    */

    KChart::BarDiagram* diagram = new KChart::BarDiagram;
    diagram->setModel(&m_model);
    diagram->setPen( QPen( Qt::black, 0 ) );

    m_chart.coordinatePlane()->replaceDiagram(diagram);

    QVBoxLayout* l = new QVBoxLayout(this);
    l->addWidget(&m_chart);
    setLayout(l);

    /*
    // render chart to a SVG
    QSvgGenerator generator;
    generator.setFileName("/home/kdab/chart.svg");
    generator.setSize(QSize(300, 300));
    generator.setViewBox(QRect(0, 0, 300, 300));
    generator.setTitle(tr("SVG Chart"));
    QPainter painter;
    painter.begin(&generator);
    painter.setRenderHint(QPainter::Antialiasing);
    m_chart.paint(&painter, generator.viewBox());
    painter.end();
    */
  }

private:
  KChart::Chart m_chart;
  QStandardItemModel m_model;
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    ChartWidget w;
    w.show();

    return app.exec();
}

#include "main.moc"
