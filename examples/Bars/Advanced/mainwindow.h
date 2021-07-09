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
    class BarDiagram;
}

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );

private Q_SLOTS:

    void on_barTypeCB_currentIndexChanged( const QString & text );
    void on_barOrientationCB_currentIndexChanged( const QString & text );
    void on_paintValuesCB_toggled( bool checked );
    void on_paintThreeDBarsCB_toggled( bool checked );
    void on_markColumnCB_toggled( bool checked );
    void on_markColumnSB_valueChanged( int i );
    void on_threeDDepthCB_toggled( bool checked );
    void on_depthSB_valueChanged( int i );
    void on_widthCB_toggled( bool checked );
    void on_widthSB_valueChanged( int i );
    void on_fixPlaneSizeCB_toggled( bool checked );

    void setReverseDirection(bool);

private:
    KChart::Chart* m_chart;
    KChart::BarDiagram* m_bars;
    TableModel m_model;
};


#endif /* MAINWINDOW_H */

