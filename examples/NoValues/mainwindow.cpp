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

#include "mainwindow.h"

#include <KChartChart>
#include <KChartAbstractCoordinatePlane>
#include <KChartCartesianAxis>
#include <KChartLineDiagram>
#include <KChartLegend>


#include <QDebug>
#include <QPen>
#include <QHBoxLayout>
#include <QStandardItemModel>

using namespace KChart;

class EmptyModel : public QAbstractItemModel
{
public:
    EmptyModel( QObject* parent = nullptr )
        : QAbstractItemModel( parent )
    {
        //qDebug() << "EmptyModel::EmptyModel()";
    }

    ~EmptyModel()
    {
        //qDebug() << "EmptyModel::~EmptyModel()";
    }

    int columnCount( const QModelIndex& parent = QModelIndex() ) const Q_DECL_OVERRIDE
    {
        Q_UNUSED( parent );
        //qDebug() << "EmptyModel::columnCount(...)";
        return 0;
    }

    int rowCount( const QModelIndex& parent = QModelIndex() ) const Q_DECL_OVERRIDE
    {
        Q_UNUSED( parent );
        //qDebug() << "EmptyModel::rowCount(...)";
        return 0;
    }


    // NOTE: The following method will not be called by KD Chart,
    //       because the model is returning 0 for columnCount() / rowCount().
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const Q_DECL_OVERRIDE
    {
        Q_UNUSED( role );
        qDebug() << "EmptyModel::data(" << index.row() << index.column() << ")";
        Q_ASSERT_X( false, "EmptyModel::data", "We should not end here..." );
        return QVariant();
    }

    QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const Q_DECL_OVERRIDE
    {
        Q_UNUSED( row );
        Q_UNUSED( column );
        Q_UNUSED( parent );
        //qDebug() << "EmptyModel::index(" << row << column << ")";
        return QModelIndex();
    }

    QModelIndex parent( const QModelIndex& parent ) const Q_DECL_OVERRIDE
    {
        Q_UNUSED( parent );
        //qDebug() << "EmptyModel::parent(...)";
        return QModelIndex();
    }
};

MainWindow::MainWindow( QWidget* parent ) :
    QWidget( parent )
{
    QHBoxLayout* chartLayout = new QHBoxLayout( this );
    m_chart = new Chart();
    m_chart->setGlobalLeading( 5, 5, 5, 5 );
    chartLayout->addWidget( m_chart );

    m_model = new EmptyModel( this ); // model contains no data at all

    // Set up the diagram
    m_bars = new LineDiagram();
    m_bars->setModel( m_model );
    CartesianAxis *xAxis = new CartesianAxis( m_bars );
    CartesianAxis *yAxis = new CartesianAxis ( m_bars );
    xAxis->setPosition ( KChart::CartesianAxis::Bottom );
    yAxis->setPosition ( KChart::CartesianAxis::Left );
    xAxis->setTitleText ( "Abscissa axis at the bottom" );
    yAxis->setTitleText ( "Ordinate axis at the left side" );
    m_bars->addAxis( xAxis );
    m_bars->addAxis( yAxis );

    m_chart->coordinatePlane()->replaceDiagram( m_bars );

    Legend* legend = new Legend( m_bars, m_chart );
    legend->setPosition( Position::South );
    legend->setAlignment( Qt::AlignCenter );
    legend->setShowLines( true );
    legend->setTitleText("This is the legend - showing no data either");
    legend->setOrientation( Qt::Horizontal );
    legend->addDiagram( m_bars );
    m_chart->addLegend( legend );
}

