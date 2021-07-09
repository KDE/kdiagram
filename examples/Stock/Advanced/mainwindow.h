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
#include <KChartChart>
#include <KChartStockDiagram>
#include <KChartThreeDBarAttributes>

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr );

private Q_SLOTS:
    void on_threeDProperties_toggled( bool checked );
    void on_perspectiveDepth_valueChanged( int value );
    void on_perspectiveAngle_valueChanged( int value );
    void on_useShadowColors_toggled( bool checked );
    void on_stockTypeCB_currentIndexChanged( const QString &text );
    void chooseColor();

private:
    void initValues();
    void applyColor(const QColor &color);

    KChart::Chart *m_chart;
    TableModel m_HLCModel;
    TableModel m_OHLCModel;

    KChart::StockDiagram m_diagram;
    KChart::ThreeDBarAttributes m_threeDBarAttributes;
};

#endif // MAINWINDOW_H
