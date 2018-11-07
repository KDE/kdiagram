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

private slots:
    void indexClicked( const QModelIndex& index );

private:
    void setupModel();

    KChart::Chart* m_chart;
    KChart::TernaryPointDiagram* m_diagram;
    KChart::TernaryCoordinatePlane* m_ternaryPlane;

    QStandardItemModel m_model;
};

#endif
