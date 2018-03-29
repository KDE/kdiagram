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
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QGroupBox>
#include <QSpacerItem>
#include <QApplication>
#include <KChartChart>
#include <KChartBarDiagram>
#include <KChartCartesianAxis>
#include <KChartCartesianCoordinatePlane>
#include <KChartLegend>

class ChartWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChartWidget(QWidget* parent=0)
    : QWidget(parent)
    {
        m_model.setHorizontalHeaderLabels(QStringList() << "A" << "B");
        m_model.insertRows(0, 1, QModelIndex());
        m_model.setData(m_model.index(0, 0), 3);
        m_model.setData(m_model.index(0, 1), 4);

        KChart::BarDiagram* diagram = new KChart::BarDiagram;
        diagram->setModel(&m_model);    

        KChart::Legend* legend = new KChart::Legend(diagram,diagram);
        legend->setPosition(KChartEnums::PositionEast);
        m_chart.addLegend(legend);

        KChart::CartesianAxis* abcissa = new KChart::CartesianAxis(diagram);
        abcissa->setPosition( KChart::CartesianAxis::Bottom );
        KChart::CartesianAxis* ordinate = new KChart::CartesianAxis(diagram);
        ordinate->setPosition( KChart::CartesianAxis::Left );
        diagram->addAxis(abcissa);
        diagram->addAxis(ordinate);

        // NOTE: If this is done before adding axes,
        // the axes don't show up at all
        m_chart.coordinatePlane()->replaceDiagram(diagram);

        // HACK: These are the default values, should be read from chart
        m_xAxisStartAtZero.setChecked(Qt::Checked);
        m_autoAdjustHorizontalRangeToData.setMaximum(100);
        m_autoAdjustHorizontalRangeToData.setValue(67);
        m_autoAdjustVerticalRangeToData.setMaximum(100);
        m_autoAdjustVerticalRangeToData.setValue(67);

        m_orientation.setText("Orientation");
        m_xAxisStartAtZero.setText("Toggle xAxisStartAtZero");
        m_label.setText("Set autoAdjustHorizontalRangeToData:");
        m_label2.setText("Set autoAdjustVerticalRangeToData:");
        m_xRange.setText("Horizontal Axis range");
        m_yRange.setText("Vertical Axis range");
        connect(&m_orientation, SIGNAL(stateChanged(int)),this, SLOT(toggleOrientation()));
        connect(&m_xAxisStartAtZero, SIGNAL(stateChanged(int)),this, SLOT(xAxisStartAtZero(int)));
        connect(&m_xRange, SIGNAL(stateChanged(int)),this, SLOT(xRange(int)));
        connect(&m_xAxisMin, SIGNAL(valueChanged(qreal)),this, SLOT(rangeChanged()));
        connect(&m_xAxisMax, SIGNAL(valueChanged(qreal)),this, SLOT(rangeChanged()));
        connect(&m_yRange, SIGNAL(stateChanged(int)),this, SLOT(yRange(int)));
        connect(&m_yAxisMin, SIGNAL(valueChanged(qreal)),this, SLOT(rangeChanged()));
        connect(&m_yAxisMax, SIGNAL(valueChanged(qreal)),this, SLOT(rangeChanged()));
        connect(&m_autoAdjustHorizontalRangeToData, SIGNAL(valueChanged(int)),this, SLOT(autoAdjustHorizontalRangeToData(int)));
        connect(&m_autoAdjustVerticalRangeToData, SIGNAL(valueChanged(int)),this, SLOT(autoAdjustVerticalRangeToData(int)));

        QBoxLayout* l = new QHBoxLayout(this);
        setLayout(l);

        QWidget *w = new QWidget(this);
        l->addWidget(w);
        l->addWidget(&m_chart);

        l = new QVBoxLayout(w);
        l->addWidget(&m_orientation);

        QGroupBox *gbh = new QGroupBox("Horizontal control", w);
        l->addWidget(gbh);
        QGroupBox *gbv = new QGroupBox("Vertical control", w);
        l->addWidget(gbv);

        QGridLayout* gl = new QGridLayout(gbh);

        gl->addWidget(&m_xAxisStartAtZero, 0, 0);
        gl->addWidget(&m_xRange, 2, 0);
        gl->addWidget(&m_xAxisMax, 2, 1);
        gl->addWidget(&m_xAxisMin, 3, 1);

        gl->addWidget(&m_label, 1, 0);
        gl->addWidget(&m_autoAdjustHorizontalRangeToData, 1, 1);

        gl = new QGridLayout(gbv);

        gl->addWidget(&m_yRange, 1, 0);
        gl->addWidget(&m_yAxisMax, 1, 1);
        gl->addWidget(&m_yAxisMin, 2, 1);

        gl->addWidget(&m_label2, 0, 0);
        gl->addWidget(&m_autoAdjustVerticalRangeToData, 0, 1);

        l->addStretch(0);
    }
    
private Q_SLOTS:
    void toggleOrientation()
    {
        KChart::BarDiagram *diag = qobject_cast<KChart::BarDiagram*>(m_chart.coordinatePlane()->diagram());
        diag->setOrientation(diag->orientation() == Qt::Horizontal ? Qt::Vertical : Qt::Horizontal);
        qInfo()<<Q_FUNC_INFO<<diag->orientation();
    }
    void xAxisStartAtZero(int state)
    {
        KChart::CartesianCoordinatePlane *plane = qobject_cast<KChart::CartesianCoordinatePlane*>(m_chart.coordinatePlane());
        plane->setXAxisStartAtZero(state == Qt::Checked);
        m_chart.update();
    }
    void autoAdjustHorizontalRangeToData(int value)
    {
        KChart::CartesianCoordinatePlane *plane = qobject_cast<KChart::CartesianCoordinatePlane*>(m_chart.coordinatePlane());
        m_xRange.setCheckState(Qt::Unchecked);
        plane->setAutoAdjustHorizontalRangeToData(value);
    }
    void autoAdjustVerticalRangeToData(int value)
    {
        KChart::CartesianCoordinatePlane *plane = qobject_cast<KChart::CartesianCoordinatePlane*>(m_chart.coordinatePlane());
        m_yRange.setCheckState(Qt::Unchecked);
        plane->setAutoAdjustVerticalRangeToData(value);
    }
    void xRange(int state)
    {
        KChart::CartesianCoordinatePlane *plane = qobject_cast<KChart::CartesianCoordinatePlane*>(m_chart.coordinatePlane());
        if (state) {
            plane->setHorizontalRange(QPair<qreal, qreal>(m_xAxisMax.value(), m_xAxisMin.value()));            
        } else {
            plane->setHorizontalRange(QPair<qreal, qreal>());
            plane->adjustVerticalRangeToData();
            autoAdjustHorizontalRangeToData(m_autoAdjustHorizontalRangeToData.value());
        }
    }
    void yRange(int state)
    {
        KChart::CartesianCoordinatePlane *plane = qobject_cast<KChart::CartesianCoordinatePlane*>(m_chart.coordinatePlane());
        if (state) {
            plane->setVerticalRange(QPair<qreal, qreal>(m_yAxisMax.value(), m_yAxisMin.value()));            
        } else {
            plane->setVerticalRange(QPair<qreal, qreal>());
            plane->adjustVerticalRangeToData();
            autoAdjustVerticalRangeToData(m_autoAdjustVerticalRangeToData.value());
        }
    }
    void rangeChanged()
    {
        QDoubleSpinBox *sb = qobject_cast<QDoubleSpinBox*>(sender());
        if (sb == &m_xAxisMax) {
            if (m_xRange.checkState() == Qt::Checked) {
                xRange(Qt::Checked);
            }
        } else if (sb == &m_xAxisMin) {
            if (m_xRange.checkState() == Qt::Checked) {
                xRange(Qt::Checked);
            }
        } else if (sb == &m_yAxisMax) {
            if (m_yRange.checkState() == Qt::Checked) {
                yRange(Qt::Checked);
            }
        } else if (sb == &m_yAxisMin) {
            if (m_yRange.checkState() == Qt::Checked) {
                yRange(Qt::Checked);
            }
        }
    }
private:
    KChart::Chart m_chart;
    QCheckBox m_orientation;
    QCheckBox m_xAxisStartAtZero;
    QCheckBox m_xRange;
    QDoubleSpinBox m_xAxisMin;
    QDoubleSpinBox m_xAxisMax;
    QCheckBox m_yRange;
    QDoubleSpinBox m_yAxisMin;
    QDoubleSpinBox m_yAxisMax;
    QLabel m_label;
    QSpinBox m_autoAdjustHorizontalRangeToData;
    QLabel m_label2;
    QSpinBox m_autoAdjustVerticalRangeToData;
    QStandardItemModel m_model;
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );
    
    ChartWidget w;
    w.show();
    
    return app.exec();
}

#include "main.moc"
