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
    class LineDiagram;
    class BarDiagram;
    class LineAttributes;
    class CartesianAxis;
    class CartesianCoordinatePlane;
}

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );

private:
    KChart::Chart* m_chart;
    QStandardItemModel m_model;
    QStandardItemModel m_model2;
    KChart::DatasetProxyModel* m_datasetProxy;
    KChart::LineDiagram* m_lines;
    KChart::BarDiagram* m_bars;
    KChart::CartesianCoordinatePlane* plane;
    // mutable KChart::CartesianAxis xAxis;
    //mutable KChart::CartesianAxis yAxis;
    
};


#endif /* MAINWINDOW_H */

