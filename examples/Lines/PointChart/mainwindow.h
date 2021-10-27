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
#include <TableModel.h>

namespace KChart {
    class Chart;
    class LineDiagram;
}

QT_BEGIN_NAMESPACE
class QPainterPath;
QT_END_NAMESPACE

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow() override;

private Q_SLOTS:

    void on_lineTypeCB_currentIndexChanged( const QString & text );
    void on_paintValuesCB_toggled( bool checked );
    void on_paintMarkersCB_toggled( bool checked );
    void on_paintLinesCB_toggled( bool checked );
    void on_markersStyleCB_currentIndexChanged( const QString & text );
    void on_markersWidthSB_valueChanged( int i );
    void on_markersHeightSB_valueChanged( int i);
   
private:
    KChart::Chart* m_chart;
    KChart::LineDiagram* m_lines;
    TableModel m_model;
    QPainterPath* path;
};


#endif /* MAINWINDOW_H */

