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
    void closeEvent(QCloseEvent *event) override;

private Q_SLOTS:
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
