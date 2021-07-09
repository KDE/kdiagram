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
class QAbstractItemModel;
QT_END_NAMESPACE

namespace KChart {
    class Chart;
    class LineDiagram;
}

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );

private Q_SLOTS:
    void on_showDataset1CB_toggled( bool checked );
    void on_showDataset2CB_toggled( bool checked );
    void on_showDataset3CB_toggled( bool checked );
    void setHidden( int dataset, bool hidden );
    void openFile(const QString &path);

private:
    KChart::Chart             * m_chart;
    KChart::LineDiagram       * m_lines;
    QAbstractItemModel         * m_model;
};


#endif /* MAINWINDOW_H */

