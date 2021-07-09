/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMap>

#include "ui_mainwindow.h"
#include "ui_addheaderdialog.h"
#include <TableModel.h>
#include <KChartHeaderFooter>
#include <KChartPosition>

class QPrinter;

namespace KChart {
    class Chart;
    class DatasetProxyModel;
    class LineDiagram;
}

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );

private Q_SLOTS:
    void on_defaultButton_clicked();
    void slotPaintRequested(QPrinter *printer);
    void on_printButton_clicked();
    void on_addHeaderPB_clicked();
    void on_editHeaderPB_clicked();
    void on_removeHeaderPB_clicked();
    void on_headersTV_itemSelectionChanged();
private:
    void setupAddHeaderDialog( QDialog* dlg,
                               Ui::AddHeaderDialog& conf ) const;
    void addHeaderFooter( const QString &text,
                          KChart::HeaderFooter::HeaderFooterType type,
                          KChart::Position position ) const;

    KChart::Chart* m_chart;
    TableModel m_model;
    KChart::DatasetProxyModel* m_datasetProxy;
    KChart::LineDiagram* m_lines;
};


#endif /* MAINWINDOW_H */

