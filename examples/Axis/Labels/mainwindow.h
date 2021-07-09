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
#include <TableModel.h>

namespace KChart {
class Chart;
class DatasetProxyModel;
class LineDiagram;
class CartesianAxis;
class Legend;
}

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );

private Q_SLOTS:
    void annotationsToggled( bool );
    void gridLinesOnAnnotationsToggled( bool );

private:
    KChart::Chart* m_chart;
    KChart::CartesianAxis* m_xAxis;
    TableModel m_model;
    KChart::DatasetProxyModel* m_datasetProxy;
    KChart::LineDiagram* m_lines;
    KChart::Legend* m_legend;
};


#endif /* MAINWINDOW_H */

