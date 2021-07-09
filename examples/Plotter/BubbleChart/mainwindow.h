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

QT_BEGIN_NAMESPACE
class QStandardItemModel;
QT_END_NAMESPACE

namespace KChart {
    class Chart;
    class Plotter;
}

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );

private Q_SLOTS:
    void initializeDataModel();
    void setMarkerAttributes();

private:
    QStandardItemModel* m_model;
    KChart::Chart* m_chart;
    KChart::Plotter* m_plotter;
};


#endif /* MAINWINDOW_H */

