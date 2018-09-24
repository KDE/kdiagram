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

#include "diagramtypedialog.h"
#include "ui_diagramtypedialog.h"

#include <KChartChart>
#include <KChartAbstractCoordinatePlane>
#include <KChartCartesianCoordinatePlane>
#include <KChartPolarCoordinatePlane>

#include <KChartBarDiagram>
#include <KChartLineDiagram>
#include <KChartPieDiagram>
#include <KChartPlotter>

#include <QDebug>

using namespace KChart;

class DiagramTypeDialog::Private : public QObject
{
    Q_OBJECT
public:
    Private( KChart::Chart *chart, DiagramTypeDialog * q );
    void init();
    void createPlanes();

    int lastIndex;
    Chart *m_chart;
    DiagramTypeDialog::DiagramType type;
    DiagramTypeDialog::Subtype subType;
    QHash< DiagramTypeDialog::DiagramType, QAbstractItemModel* > m_defaultModels;
    QHash< DiagramTypeDialog::DiagramType, AbstractCoordinatePlane* > m_planes;
    QHash< DiagramTypeDialog::DiagramType, DiagramTypeDialog::Subtype > m_typemap;
    DiagramTypeDialog *qq;
    Ui::DiagramTypeDialog ui;
public Q_SLOTS:
    void typeChanged( int index );
    void subtypeChanged( int index );
};

DiagramTypeDialog::Private::Private( KChart::Chart *chart, DiagramTypeDialog * q )
    : lastIndex( 0 )
    , m_chart( chart )
    , type( DiagramTypeDialog::Bar )
    , subType( DiagramTypeDialog::Normal )
    , qq( q )
{

}

void DiagramTypeDialog::Private::init()
{
    ui.setupUi( qq );
    ui.typeSelector->addItem( QIcon(), tr( "BarDiagram" ), DiagramTypeDialog::Bar );
    ui.typeSelector->addItem( QIcon(), tr( "Lying BarDiagram" ), DiagramTypeDialog::LyingBar );
    ui.typeSelector->addItem( QIcon(), tr( "LineDiagram" ), DiagramTypeDialog::Line );
    ui.typeSelector->addItem( QIcon(), tr( "Plotter" ), DiagramTypeDialog::Plotter );
    ui.typeSelector->addItem( QIcon(), tr( "PieDiagram" ), DiagramTypeDialog::Pie );

    ui.subtypeSelector->addItem( QIcon(), tr( "Normal" ), DiagramTypeDialog::Normal );
    ui.subtypeSelector->addItem( QIcon(), tr( "Stacked" ), DiagramTypeDialog::Stacked );
    ui.subtypeSelector->addItem( QIcon(), tr( "Percent" ), DiagramTypeDialog::Percent );

    createPlanes();
    m_typemap[ DiagramTypeDialog::Bar ] = DiagramTypeDialog::Normal;
    m_typemap[ DiagramTypeDialog::LyingBar ] = DiagramTypeDialog::Normal;
    m_typemap[ DiagramTypeDialog::Line ] = DiagramTypeDialog::Normal;
    m_typemap[ DiagramTypeDialog::Plotter ] = DiagramTypeDialog::Normal;

    connect( ui.typeSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(typeChanged(int)) );
    connect( ui.subtypeSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(subtypeChanged(int)) );
}

void DiagramTypeDialog::Private::createPlanes()
{
    m_planes[ DiagramTypeDialog::Bar ] = m_chart->coordinatePlane();
    m_planes[ DiagramTypeDialog::LyingBar ] = m_chart->coordinatePlane();

    CartesianCoordinatePlane *linePlane = new CartesianCoordinatePlane;
    linePlane->addDiagram( new LineDiagram );
    m_planes[ DiagramTypeDialog::Line ] = linePlane;

    CartesianCoordinatePlane *plotterPlane = new CartesianCoordinatePlane;
    plotterPlane->addDiagram( new KChart::Plotter );
    m_planes[ DiagramTypeDialog::Plotter ] = plotterPlane;

    PolarCoordinatePlane *piePlane = new PolarCoordinatePlane;
    piePlane->addDiagram( new PieDiagram );
    m_planes[ DiagramTypeDialog::Pie ] = piePlane;
}

void DiagramTypeDialog::Private::typeChanged( int index )
{
    if ( index == lastIndex )
        return;
    const DiagramTypeDialog::DiagramType type = static_cast< DiagramTypeDialog::DiagramType >( ui.typeSelector->itemData( index ).toInt() );
    const DiagramTypeDialog::DiagramType lastType = static_cast< DiagramTypeDialog::DiagramType >( ui.typeSelector->itemData( lastIndex ).toInt() );
    if ( m_planes.contains( type ) )
    {
        ui.subtypeSelector->setEnabled( true );
        if ( type == DiagramTypeDialog::LyingBar )
        {
            BarDiagram * diag = qobject_cast< BarDiagram* >( m_planes[ type ]->diagram() );
            diag->setOrientation( Qt::Horizontal );
        }
        else if ( type == DiagramTypeDialog::Bar )
        {
            BarDiagram * diag = qobject_cast< BarDiagram* >( m_planes[ type ]->diagram() );
            diag->setOrientation( Qt::Vertical );
        }
        else if ( type == DiagramTypeDialog::Pie )
            ui.subtypeSelector->setEnabled( false );
        this->type = type;
        ui.subtypeSelector->setCurrentIndex( m_typemap[ type ] );
        m_chart->takeCoordinatePlane( m_planes[ lastType ] );
        m_chart->addCoordinatePlane( m_planes[ type ] );

        lastIndex = index;
        Q_EMIT qq->diagramTypeChanged( type, subType );
    }
    else
    {
        ui.typeSelector->setCurrentIndex( lastIndex );
    }
}

void DiagramTypeDialog::Private::subtypeChanged( int index )
{
    const DiagramTypeDialog::DiagramType type = static_cast< DiagramTypeDialog::DiagramType >( ui.typeSelector->itemData( ui.typeSelector->currentIndex() ).toInt() );
    switch ( type )
    {
    case( DiagramTypeDialog::Bar ):
    case( DiagramTypeDialog::LyingBar ):
    {
        BarDiagram *bar = qobject_cast< BarDiagram* >( m_planes[ type ]->diagram() );
        Q_ASSERT( bar );
        bar->setType( static_cast< BarDiagram::BarType >( index ) );
        m_typemap[ type ] = static_cast< DiagramTypeDialog::Subtype >( index );
        break;
    }
    case( DiagramTypeDialog::Line ):
    {
        LineDiagram *line = qobject_cast< LineDiagram* >( m_planes[ type ]->diagram() );
        Q_ASSERT( line );
        line->setType( static_cast< LineDiagram::LineType >( index ) );
        m_typemap[ type ] = static_cast< DiagramTypeDialog::Subtype >( index );
        break;
        break;
    }
    case( DiagramTypeDialog::Pie ):
        break;
    default:
        Q_ASSERT( false );
    }
}

DiagramTypeDialog::DiagramTypeDialog( KChart::Chart *chart, QWidget *parent )
    : QDialog( parent )
    , d( new Private( chart, this ) )
{
    d->init();
}

DiagramTypeDialog::~DiagramTypeDialog()
{
    delete d;
}

void DiagramTypeDialog::setDefaultModels( QHash< DiagramType, QAbstractItemModel* > models )
{
    d->m_defaultModels = models;
    for ( QHash< DiagramType, AbstractCoordinatePlane* >::iterator it = d->m_planes.begin(); it != d->m_planes.end(); ++it )
    {
        AbstractDiagram * diagram = it.value()->diagram();
        diagram->setModel( d->m_defaultModels[ it.key() ] );
    }
}

#include "diagramtypedialog.moc"
