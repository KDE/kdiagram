/**
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QLabel>
#include <QString>
#include <QTextStream>

#include <KChartChart>
#include <KChartTernaryAxis>
#include <KChartTernaryLineDiagram>
#include <KChartTernaryPointDiagram>
#include <KChartTernaryCoordinatePlane>

#include "mainwindow.h"

MainWindow::MainWindow( QWidget* parent )
    : QDialog( parent )
    , m_chart( 0 )
    , m_diagram( 0 )
    , m_ternaryPlane( 0 )
{
    setupUi( this );
    // make a chart
    m_chart = new KChart::Chart;
    // replace the default (cartesian) coordinate plane with a ternary one
    m_ternaryPlane = new KChart::TernaryCoordinatePlane;
    m_chart->replaceCoordinatePlane( m_ternaryPlane );
    // make a ternary line diagram
    m_diagram = new KChart::TernaryPointDiagram;
    // and replace the default diagram with it
    m_ternaryPlane->replaceDiagram( m_diagram );

    // add the three ternary axes, see the positions
    KChart::TernaryAxis* axisA = new KChart::TernaryAxis( m_diagram );
    axisA->setPosition( KChartEnums::PositionSouth );
    KChart::TernaryAxis* axisB = new KChart::TernaryAxis( m_diagram );
    axisB->setPosition( KChartEnums::PositionWest );
    KChart::TernaryAxis* axisC = new KChart::TernaryAxis( m_diagram );
    axisC->setPosition( KChartEnums::PositionEast );

    QHBoxLayout* chartLayout = new QHBoxLayout( frame );
    chartLayout->addWidget( m_chart );

    setupModel();
    m_diagram->setModel( &m_model );
    connect( m_diagram, SIGNAL(clicked(QModelIndex)),
             SLOT(indexClicked(QModelIndex)) );
}

void MainWindow::setupModel()
{
    m_model.insertRows( 0, 5 );
    m_model.insertColumns(  0,  3 );

    const float column0Share = 1.0f/3.0f;
    const float column1Share = 1.0f/3.0f;
    const float column2Share = 1.0f/3.0f;

    for ( int row = 0; row < m_model.rowCount(); ++row ) {
        const qreal SkewX = column0Share * ( 1 - 1.0/( 5 * row*row*row + 1 ) );
        const qreal SkewY = SkewX;
        QModelIndex index;

        index = m_model.index( row, 0 );
        m_model.setData( index, QVariant( column0Share - SkewX ) );
        index = m_model.index( row, 1 );
        m_model.setData( index, QVariant( column1Share + SkewX - SkewY) );
        index = m_model.index( row, 2 );
        m_model.setData( index, QVariant( column2Share + SkewY ) );
    }
}

void MainWindow::indexClicked( const QModelIndex& index )
{
    qDebug() << "MainWindow::indexClicked:" << index;
    if ( index.isValid() ) {
        QString text;
        QTextStream stream( &text );
        stream << "Row: " << index.row() << " - Column: " << index.column();
        label->setText( text );
    }
}

