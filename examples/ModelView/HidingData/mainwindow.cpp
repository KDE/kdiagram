/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwindow.h"

#include <QStandardItemModel>
#include <QFileDialog>

#include <KChartChart>
#include <KChartDataValueAttributes>
#include <KChartLegend>
#include <KChartLineDiagram>
#include <KChartTextAttributes>
#include <KChartThreeDLineAttributes>


using namespace KChart;

MainWindow::MainWindow( QWidget* parent ) :
    QWidget( parent )
{
    setupUi( this );

    QHBoxLayout* chartLayout = new QHBoxLayout( chartFrame );
    m_chart = new Chart();
    m_chart->setGlobalLeading( 20,  20,  20,  20 );
    chartLayout->addWidget( m_chart );


    // Initialize the model, and fill it with data
    const int rowCount = 8;
    const int columnCount = 3;
    m_model = new QStandardItemModel(rowCount, columnCount, this);
    m_model->setHeaderData(0, Qt::Horizontal, tr("Product A"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("Product B"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("Product C"));
    openFile(":/Charts/qtdata.cht");

    // Set up the diagram
    m_lines = new LineDiagram();
    // Register the data model at the diagram
    m_lines->setModel( m_model );
    // Add axes to the diagram
    CartesianAxis *xAxis = new CartesianAxis( m_lines );
    CartesianAxis *yAxis = new CartesianAxis ( m_lines );
    xAxis->setPosition ( KChart::CartesianAxis::Bottom );
    yAxis->setPosition ( KChart::CartesianAxis::Left );
    m_lines->addAxis( xAxis );
    m_lines->addAxis( yAxis );
    // Make the lines thicker
    for ( int iColumn = 0; iColumn < columnCount; ++iColumn ) {
        QPen linePen( m_lines->pen( iColumn ) );
        linePen.setWidth( 3 );
        m_lines->setPen( iColumn, linePen );
    }
    // Register the diagram at the coordinate plane
    m_chart->coordinatePlane()->replaceDiagram( m_lines );

    // Add a legend
    Legend* legend = new Legend( m_lines, m_chart );
    legend->setPosition( Position::South );
    legend->setAlignment( Qt::AlignCenter );
    legend->setShowLines( true );
    legend->setTitleText("");
    legend->setOrientation( Qt::Horizontal );
    legend->addDiagram( m_lines );
    m_chart->addLegend( legend );
}

void MainWindow::on_showDataset1CB_toggled( bool checked )
{
    setHidden( 0, ! checked );
}

void MainWindow::on_showDataset2CB_toggled( bool checked )
{
    setHidden( 1, ! checked );
}

void MainWindow::on_showDataset3CB_toggled( bool checked )
{
    setHidden( 2, ! checked );
}

void MainWindow::setHidden( int dataset, bool hidden )
{
    m_lines->setHidden( dataset, hidden );
    m_chart->update();
}

void MainWindow::openFile(const QString &path)
{
    QString fileName;
    if (path.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Choose a data file"),
            "", "*.cht");
    else
        fileName = path;

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream stream(&file);
            QString line;

            m_model->removeRows(0, m_model->rowCount(QModelIndex()), QModelIndex());

            int row = 0;
            do {
                line = stream.readLine();
                if (!line.isEmpty()) {

                    m_model->insertRows(row, 1, QModelIndex());

                    QStringList pieces = line.split(',', Qt::SkipEmptyParts);
                    m_model->setData(m_model->index(row, 0, QModelIndex()), pieces.value(0));
                    m_model->setData(m_model->index(row, 1, QModelIndex()), pieces.value(1));
                    m_model->setData(m_model->index(row, 2, QModelIndex()), pieces.value(2));
                    ++row;
                }
            } while (!line.isEmpty());

            file.close();
        }
    }
}

