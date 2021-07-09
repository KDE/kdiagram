/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
