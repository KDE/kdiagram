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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"

#include <KChartChart>
#include <KChartAbstractCoordinatePlane>
#include <KChartCartesianAxis>
#include <KChartBarDiagram>


#include <QDebug>
#include <QPen>
#include <QHBoxLayout>

using namespace KChart;

MainWindow::MainWindow( QWidget* parent ) :
    QWidget( parent )
{
    QHBoxLayout* chartLayout = new QHBoxLayout( this );
    m_chart = new Chart();
    chartLayout->addWidget( m_chart );

    m_model.loadFromCSV( ":/data" );

    // Set up the diagram
    m_bars = new BarDiagram();
    m_bars->setModel( &m_model );
    m_bars->addAxis( new CartesianAxis( m_bars ) );

    m_chart->coordinatePlane()->replaceDiagram( m_bars );

    CartesianCoordinatePlane *plane 
            = dynamic_cast<CartesianCoordinatePlane*>( m_chart->coordinatePlane() );
    Q_ASSERT( plane );
    // The values in the model are all zero, so set the size of the plane 
    // to something that is non-zero manually
    plane->setVerticalRange( QPair<qreal, qreal>( -2.0, 2.0 ) );
}

