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



private slots:
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
