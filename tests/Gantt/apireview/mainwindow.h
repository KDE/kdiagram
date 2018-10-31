/**
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KGantt library.
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
    MainWindow( QWidget * parent = 0, Qt::WindowFlags flags = Qt::WindowFlags() );

private slots:
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
