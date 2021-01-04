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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <TableModel.h>

namespace KChart {
    class Chart;
    class BarDiagram;
    class DatasetProxyModel;
}

QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QStandardItemModel;
class QTableView;
class QItemSelectionModel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected Q_SLOTS:
    void selectionChanged( const QItemSelection & selected, const QItemSelection & deselected );

private Q_SLOTS:
    void initializeData();
    void openFile(const QString &path = QString());
    void saveFile();

    void itemClicked( const QModelIndex& index );

private:
    void setupModel();
    void setupViews();

    KChart::Chart* m_chart;
    KChart::DatasetProxyModel* m_datasetProxy;

    QStandardItemModel  *m_model;
    KChart::BarDiagram *m_diagramView;
    QTableView          *m_tableView;
    QItemSelectionModel *m_selectionModel;
};

#endif
