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
#include <QPushButton>
#include <QComboBox>
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
        addData();

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
        m_fixedDataCoordinateSpaceRelation.setText("FixedDataCoordinateSpaceRelation");
        m_xAxisStartAtZero.setText("Toggle xAxisStartAtZero");
        m_isometricScaling.setText("Isometric scaling");
        m_label.setText("Set autoAdjustHorizontalRangeToData:");
        m_label2.setText("Set autoAdjustVerticalRangeToData:");
        m_xRange.setText("Horizontal Axis range");
        m_yRange.setText("Vertical Axis range");
        m_horizontalRangeReversed.setText("Horizontal range reversed");
        m_verticalRangeReversed.setText("Vertical range reversed");
        m_addData.setText("Append data row");
        m_removeData.setText("Remove last data row");

        m_axesCalcModes.addItem("Linear");
        m_axesCalcModes.addItem("Logarithmic");
        m_axesCalcModes.addItem("None");

        m_axesCalcModeX.addItem("Linear");
        m_axesCalcModeX.addItem("Logarithmic");
        m_axesCalcModeY.addItem("Linear");
        m_axesCalcModeY.addItem("Logarithmic");

        connect(&m_orientation, SIGNAL(stateChanged(int)),this, SLOT(toggleOrientation()));
        connect(&m_fixedDataCoordinateSpaceRelation, SIGNAL(stateChanged(int)),this, SLOT(toggleFixedSpaceRelation()));
        connect(&m_isometricScaling, SIGNAL(stateChanged(int)), this, SLOT(isometricScaling()));
        connect(&m_xAxisStartAtZero, SIGNAL(stateChanged(int)),this, SLOT(xAxisStartAtZero(int)));
        connect(&m_xRange, SIGNAL(stateChanged(int)),this, SLOT(xRange(int)));
        connect(&m_xAxisMin, SIGNAL(valueChanged(qreal)),this, SLOT(rangeChanged()));
        connect(&m_xAxisMax, SIGNAL(valueChanged(qreal)),this, SLOT(rangeChanged()));
        connect(&m_yRange, SIGNAL(stateChanged(int)),this, SLOT(yRange(int)));
        connect(&m_yAxisMin, SIGNAL(valueChanged(qreal)),this, SLOT(rangeChanged()));
        connect(&m_yAxisMax, SIGNAL(valueChanged(qreal)),this, SLOT(rangeChanged()));
        connect(&m_autoAdjustHorizontalRangeToData, SIGNAL(valueChanged(int)),this, SLOT(autoAdjustHorizontalRangeToData(int)));
        connect(&m_autoAdjustVerticalRangeToData, SIGNAL(valueChanged(int)),this, SLOT(autoAdjustVerticalRangeToData(int)));
        connect(&m_horizontalRangeReversed, SIGNAL(stateChanged(int)), this, SLOT(rangeReversedChanged()));
        connect(&m_verticalRangeReversed, SIGNAL(stateChanged(int)), this, SLOT(rangeReversedChanged()));

        connect(&m_addData, SIGNAL(clicked()), this, SLOT(addData()));
        connect(&m_removeData, SIGNAL(clicked()), this, SLOT(removeData()));

        connect(&m_axesCalcModes, SIGNAL(activated(int)), this, SLOT(axesCalcMode(int)));
        connect(&m_axesCalcModeX, SIGNAL(activated(int)), this, SLOT(axesCalcMode(int)));
        connect(&m_axesCalcModeY, SIGNAL(activated(int)), this, SLOT(axesCalcMode(int)));

        QBoxLayout* l = new QHBoxLayout(this);
        setLayout(l);

        QWidget *w = new QWidget(this);
        l->addWidget(w);
        l->addWidget(&m_chart);

        l = new QVBoxLayout(w);
        l->addWidget(&m_orientation);
        l->addWidget(&m_fixedDataCoordinateSpaceRelation);
        l->addWidget(&m_isometricScaling);

        QWidget *w1 = new QWidget(w);
        l->addWidget(w1);
        QBoxLayout* l1 = new QHBoxLayout(w1);
        l1->addWidget(new QLabel("Axes calc mode:"));
        l1->addWidget(&m_axesCalcModes);

        QGroupBox *gbh = new QGroupBox("Horizontal control", w);
        l->addWidget(gbh);
        QGroupBox *gbv = new QGroupBox("Vertical control", w);
        l->addWidget(gbv);
        QGroupBox *data = new QGroupBox("Data control", w);
        l->addWidget(data);

        QGridLayout* gl = new QGridLayout(gbh);

        gl->addWidget(&m_xAxisStartAtZero, 0, 0);

        gl->addWidget(new QLabel("X Axis calc mode:", gbh), 5, 0);
        gl->addWidget(&m_axesCalcModeX, 5, 1);

        gl->addWidget(&m_xRange, 2, 0);
        gl->addWidget(&m_xAxisMax, 2, 1);
        gl->addWidget(&m_xAxisMin, 3, 1);
        gl->addWidget(&m_horizontalRangeReversed, 4, 0);

        gl->addWidget(&m_label, 1, 0);
        gl->addWidget(&m_autoAdjustHorizontalRangeToData, 1, 1);

        gl = new QGridLayout(gbv);

        gl->addWidget(&m_label2, 0, 0);
        gl->addWidget(&m_autoAdjustVerticalRangeToData, 0, 1);

        gl->addWidget(&m_yRange, 1, 0);
        gl->addWidget(&m_yAxisMax, 1, 1);
        gl->addWidget(&m_yAxisMin, 2, 1);
        gl->addWidget(&m_verticalRangeReversed, 3, 0);

        gl->addWidget(new QLabel("Y Axis calc mode:", gbv), 4, 0);
        gl->addWidget(&m_axesCalcModeY, 4, 1);

        gl = new QGridLayout(data);
        gl->addWidget(&m_addData, 0, 0);
        gl->addWidget(&m_removeData, 1, 0);


        l->addStretch(0);
    }

private Q_SLOTS:
    void addData()
    {
        int row = m_model.rowCount();
        m_model.insertRows(row, 1, QModelIndex());
        m_model.setData(m_model.index(row, 0), 3);
        m_model.setData(m_model.index(row, 1), 4);
    }
    void removeData()
    {
        m_model.setRowCount(m_model.rowCount()-1);
    }
    void toggleOrientation()
    {
        KChart::BarDiagram *diag = qobject_cast<KChart::BarDiagram*>(m_chart.coordinatePlane()->diagram());
        diag->setOrientation(diag->orientation() == Qt::Horizontal ? Qt::Vertical : Qt::Horizontal);
    }
    void toggleFixedSpaceRelation()
    {
        KChart::CartesianCoordinatePlane *plane = qobject_cast<KChart::CartesianCoordinatePlane*>(m_chart.coordinatePlane());
        plane->setFixedDataCoordinateSpaceRelation(m_fixedDataCoordinateSpaceRelation.checkState());
    }
    void isometricScaling()
    {
        qobject_cast<KChart::CartesianCoordinatePlane*>(m_chart.coordinatePlane())->setIsometricScaling(m_isometricScaling.checkState());
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
            plane->setHorizontalRange(QPair<qreal, qreal>(m_xAxisMin.value(), m_xAxisMax.value()));
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
            plane->setVerticalRange(QPair<qreal, qreal>(m_yAxisMin.value(), m_yAxisMax.value()));
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
    void rangeReversedChanged()
    {
        QCheckBox *cb = qobject_cast<QCheckBox*>(sender());
        if (cb == &m_horizontalRangeReversed) {
            qobject_cast<KChart::CartesianCoordinatePlane*>(m_chart.coordinatePlane())->setHorizontalRangeReversed(cb->checkState());
        } else if (cb == &m_verticalRangeReversed) {
            qobject_cast<KChart::CartesianCoordinatePlane*>(m_chart.coordinatePlane())->setVerticalRangeReversed(cb->checkState());
        }
    }
    void axesCalcMode(int mode)
    {
        if (mode == 2) {
            return;
        }
        KChart::CartesianCoordinatePlane *plane = qobject_cast<KChart::CartesianCoordinatePlane*>(m_chart.coordinatePlane());
        QComboBox *cb = qobject_cast<QComboBox*>(sender());
        if (cb == &m_axesCalcModes) {
            plane->setAxesCalcModes(static_cast<KChart::AbstractCoordinatePlane::AxesCalcMode>(mode));
            m_axesCalcModeX.setCurrentIndex(mode);
            m_axesCalcModeY.setCurrentIndex(mode);
        } else if (cb == &m_axesCalcModeX) {
            plane->setAxesCalcModeX(static_cast<KChart::AbstractCoordinatePlane::AxesCalcMode>(mode));
            m_axesCalcModes.setCurrentIndex(2);
        } else if (cb == &m_axesCalcModeY) {
            plane->setAxesCalcModeY(static_cast<KChart::AbstractCoordinatePlane::AxesCalcMode>(mode));
            m_axesCalcModes.setCurrentIndex(2);
        }
    }

private:
    KChart::Chart m_chart;
    QCheckBox m_orientation;
    QCheckBox m_fixedDataCoordinateSpaceRelation;
    QCheckBox m_isometricScaling;
    QComboBox m_axesCalcModes;
    QComboBox m_axesCalcModeY;
    QComboBox m_axesCalcModeX;

    QCheckBox m_xAxisStartAtZero;
    QCheckBox m_xRange;
    QDoubleSpinBox m_xAxisMin;
    QDoubleSpinBox m_xAxisMax;
    QCheckBox m_horizontalRangeReversed;
    QCheckBox m_yRange;
    QDoubleSpinBox m_yAxisMin;
    QDoubleSpinBox m_yAxisMax;
    QCheckBox m_verticalRangeReversed;
    QLabel m_label;
    QSpinBox m_autoAdjustHorizontalRangeToData;
    QLabel m_label2;
    QSpinBox m_autoAdjustVerticalRangeToData;

    QPushButton m_addData;
    QPushButton m_removeData;
    QStandardItemModel m_model;
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    ChartWidget w;
    w.show();

    return app.exec();
}

#include "main.moc"
