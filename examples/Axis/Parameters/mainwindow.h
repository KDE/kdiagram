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
    class DatasetProxyModel;
    class LineDiagram;
    class LineAttributes;
    class CartesianAxis;
    class Legend;
}

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );



private Q_SLOTS:

    void on_lineTypeCB_currentIndexChanged( const QString & text );
    void on_paintLegendCB_toggled( bool checked );
    void on_paintValuesCB_toggled( bool checked );
    void on_paintMarkersCB_toggled( bool checked );
    void on_markersStyleCB_currentIndexChanged( const QString & text );
    void on_markersWidthSB_valueChanged( int i );
    void on_markersHeightSB_valueChanged( int i);
    void on_displayAreasCB_toggled( bool checked );
    void on_transparencySB_valueChanged( int i );
    void on_zoomFactorSB_valueChanged( double factor );
    void on_hSBar_valueChanged( int value );
    void on_vSBar_valueChanged( int value );


private:
    KChart::Chart* m_chart;
    TableModel m_model;
    KChart::DatasetProxyModel* m_datasetProxy;
    KChart::LineDiagram* m_lines;
    KChart::Legend* m_legend;
    // mutable KChart::CartesianAxis xAxis;
    //mutable KChart::CartesianAxis yAxis;

};


#endif /* MAINWINDOW_H */

