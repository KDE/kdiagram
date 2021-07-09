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
#include "derivedaddlegenddialog.h"
#include <TableModel.h>

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
    void on_addLegendPB_clicked();
    void on_editLegendPB_clicked();
    void on_removeLegendPB_clicked();
    void on_legendsTV_itemSelectionChanged();

private:
    void initAddLegendDialog( DerivedAddLegendDialog& conf,
                              Qt::Alignment alignment ) const;

    KChart::Chart* m_chart;
    TableModel m_model;
    KChart::LineDiagram* m_lines;
    QMap<Qt::Alignment, QString> alignmentMap;
};


#endif /* MAINWINDOW_H */

