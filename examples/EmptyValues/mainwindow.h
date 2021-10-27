/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <TableModel.h>

namespace KChart {
    class Chart;
    class BarDiagram;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow() override { }

private:
    KChart::Chart* m_chart;
    KChart::BarDiagram* m_bars;
    TableModel m_model;
};


#endif /* MAINWINDOW_H */

