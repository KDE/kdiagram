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

class QLabel;

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );
    void updateData(QString data);

    protected:
        /**
         * Adjusts the two small charts when the window is resized.
         */
        /* reimp */ void resizeEvent ( QResizeEvent * ) override;

private Q_SLOTS:

    void setLineType( const QString & text );
    void setLegendVisible( bool visible );
    void setValuesVisible( bool visible );
    void setMarkersVisible( bool visible );
    void updateMarkers();
    void updateMarkersHeight();
    void updateMarkersWidth();
    void updateAreas( bool visible );
    void updateAreasTransparency();
    void setZoomFactor( qreal factor );
    void setHPos( int value );
    void setVPos( int value );
    void saveChart();

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
