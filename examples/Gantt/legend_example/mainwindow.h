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
class QStandardItemModel;
class QCloseEvent;
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

namespace KGantt {
    class ConstraintModel;
    class DateTimeGrid;
    class Legend;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow( QWidget * parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~MainWindow();
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void addNewEntry();
    void removeEntry();
    void showContextMenu( const QPoint& );
    void enableActions( const QItemSelection& selected );
    void zoomIn();
    void zoomOut();
    void zoomFit();
    void scaleAuto();
    void scaleHour();
    void scaleDay();
    void scaleWeek();
    void scaleMonth();

private:
    void initModel();
    void initActions();
    void initItemDelegate();
    void initGrid();

    void setReadOnly( const QModelIndex& index, bool readOnly );
    void addConstraint( const QModelIndex& index1, const QModelIndex& index2 );

    QStandardItemModel* model;
    KGantt::ConstraintModel* constraintModel;
    KGantt::DateTimeGrid* grid;
    KGantt::Legend* smallLegend;
    KGantt::Legend* detailedLegend;

    QAction* newEntryAction;
    QAction* removeEntryAction;
    QAction* zoomInAction;
    QAction* zoomOutAction;
    QAction* zoomFitAction;

    Ui::MainWindow* ui;
};

#endif /* MAINWINDOW_H */
