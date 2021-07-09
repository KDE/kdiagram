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

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE
namespace KChart {
    class Chart;
    class PieDiagram;
}

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );

private Q_SLOTS:
    // start position
    void on_startPositionSB_valueChanged( double pos );
    void on_startPositionSL_valueChanged( int pos );

    // explode
    void on_explodeSubmitPB_clicked();
    void on_animateExplosionCB_toggled( bool toggle );
    void setExplodeFactor( int column, qreal value );

    // animation
    void slotNextFrame();

    // 3D
    void on_threeDGB_toggled( bool toggle );
    void on_threeDFactorSB_valueChanged( int factor );

private:
    KChart::Chart* m_chart;
    TableModel m_model;
    KChart::PieDiagram* m_pie;
    QTimer* m_timer;

    int m_currentFactor;
    int m_currentDirection;
    int m_currentSlice;
};


#endif /* MAINWINDOW_H */

