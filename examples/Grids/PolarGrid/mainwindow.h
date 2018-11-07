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

private slots:
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
