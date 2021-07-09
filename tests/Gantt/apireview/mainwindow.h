/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QItemSelection>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QStandardItem;
class QStandardItemModel;
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

namespace KGantt {
    class ConstraintModel;
    class DateTimeGrid;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow( QWidget * parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );

private Q_SLOTS:
    void addNewEntry();
    void removeEntry();
    void addDemoEntry();
    void printPreview();
    void showContextMenu( const QPoint& );
    void enableActions( const QItemSelection& selected );
    void zoomIn();
    void zoomOut();

    void slotClicked( const QModelIndex& );
    void slotDoubleClicked( const QModelIndex& );

private:
    void initModel();
    void initActions();
    void initItemDelegate();
    void initGrid();

    void setReadOnly( const QModelIndex& index, bool readOnly );
    void addConstraint( const QModelIndex& index1, const QModelIndex& index2 );
    void addConstraint( const QStandardItem* item1, const QStandardItem* item2 );

    QStandardItemModel* model;
    KGantt::ConstraintModel* constraintModel;
    KGantt::DateTimeGrid* grid;
    int dayWidth;

    QAction* newEntryAction;
    QAction* removeEntryAction;
    QAction* demoAction;
    QAction* printAction;
    QAction* zoomInAction;
    QAction* zoomOutAction;

    Ui::MainWindow* ui;
};

#endif /* MAINWINDOW_H */
