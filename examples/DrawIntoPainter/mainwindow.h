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

#include <QPixmap>

namespace KChart {
    class Chart;
    class DatasetProxyModel;
    class LineDiagram;
    class Legend;
}

QT_BEGIN_NAMESPACE
class QLabel;
class QPrinter;
QT_END_NAMESPACE

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );

    protected:
    /**
     * Adjusts the two small charts when the window is resized.
     */
    /* reimp */ void resizeEvent ( QResizeEvent * ) override;

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
    void on_zoomFactorSB_valueChanged( qreal factor );
    void on_hSBar_valueChanged( int value );
    void on_vSBar_valueChanged( int value );
    void on_savePB_clicked();
    void on_savePDF_clicked();
    void slotPaintRequested(QPrinter *printer);
    void on_printButton_clicked();
private:
    void paintMarkers( bool checked, const QSize& printSize );

private:
    KChart::Chart* m_chart;
    TableModel m_model;
    KChart::DatasetProxyModel* m_datasetProxy;
    KChart::LineDiagram* m_lines;
    KChart::Legend* m_legend;
    QPixmap m_pix1, m_pix2;
    QLabel* m_smallChart1;
    QLabel* m_smallChart2;
};

#endif /* MAINWINDOW_H */
