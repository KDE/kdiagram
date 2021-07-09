/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QStandardItemModel>

namespace KChart {
    class Chart;
    class DatasetProxyModel;
    class PolarDiagram;
    class PolarCoordinatePlane;
}

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );

private Q_SLOTS:
    // start position of circular grid
    void on_startPositionSB_valueChanged( double pos );
    void on_startPositionSL_valueChanged( int pos );

    // show grid
    void on_circularGridCB_toggled( bool toggle );
    void on_sagittalGridCB_toggled( bool toggle );

    /* planned for future release:
    // show axes
    void on_circularAxisCB_toggled( bool toggle );
    void on_sagittalAxisCB_toggled( bool toggle );
    */

private:
    void initKChartClasses();
    void wireUpKChartClasses();
    void setItemModelData();

    // For a change we do not use our special TableModel here,
    // but we just use the standard model that comes with Qt.
    QStandardItemModel m_model;

    KChart::Chart* m_chart;
    KChart::PolarDiagram* m_diagram;
    KChart::PolarCoordinatePlane* m_polarPlane;

    int m_currentFactor;
    int m_currentDirection;
    int m_currentSlice;
};


#endif /* MAINWINDOW_H */
