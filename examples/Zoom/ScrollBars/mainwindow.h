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
    class LineDiagram;
    class Legend;
}

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );



private Q_SLOTS:
    void on_zoomFactorSB_valueChanged( double factor );
    void on_adjustGridCB_toggled( bool checked );
    void on_rubberBandZoomCB_toggled( bool checked );
    void on_hSBar_valueChanged( int value );
    void on_vSBar_valueChanged( int value );
    
    void applyNewZoomParameters();

private:
    KChart::Chart* m_chart;
    TableModel m_model;
    KChart::LineDiagram* m_lines;
    KChart::Legend* m_legend;
};

#endif /* MAINWINDOW_H */
