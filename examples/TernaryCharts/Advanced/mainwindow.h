/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QStandardItemModel>

#include "ui_mainwindow.h"

namespace KChart {

    class Chart;
    class TernaryLineDiagram;
    class TernaryPointDiagram;
    class TernaryCoordinatePlane;

}

class MainWindow : public QDialog,
                   private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = nullptr );

private Q_SLOTS:
    void indexClicked( const QModelIndex& index );

private:
    void setupModel();

    KChart::Chart* m_chart;
    KChart::TernaryPointDiagram* m_diagram;
    KChart::TernaryCoordinatePlane* m_ternaryPlane;

    QStandardItemModel m_model;
};

#endif
