/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwindow.h"
#include "zoomwidget.h"
#include <KChartWidget>
#include <QDebug>

using namespace KChart;

MainWindow::MainWindow( QWidget* parent )
 : QWidget( parent )
{
    setupUi( this );

    QHBoxLayout* chartLayout = new QHBoxLayout( chartFrame );
    widget = new ZoomWidget( chartFrame );
    widget->setGlobalLeadingRight( 10 );
    chartLayout->addWidget( widget );
}

