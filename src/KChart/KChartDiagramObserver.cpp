/*
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

#include <KChartDiagramObserver.h>

#include <KChartAbstractDiagram.h>
#include <KChartAttributesModel.h>
#include "KChartMath_p.h"

#include <QDebug>

using namespace KChart;

DiagramObserver::DiagramObserver( AbstractDiagram * diagram, QObject* parent )
    : QObject( parent ), m_diagram( diagram )
{
    if ( m_diagram ) {
        connect( m_diagram, SIGNAL(destroyed(QObject*)), SLOT(slotDestroyed(QObject*)));
        connect( m_diagram, SIGNAL(aboutToBeDestroyed()), SLOT(slotAboutToBeDestroyed()));
        connect( m_diagram, SIGNAL(modelsChanged()), SLOT(slotModelsChanged()));
    }
    init();
}

DiagramObserver::~DiagramObserver()
{
}

const AbstractDiagram* DiagramObserver::diagram() const
{
    return m_diagram;
}

AbstractDiagram* DiagramObserver::diagram()
{
    return m_diagram;
}


void DiagramObserver::init()
{
    if ( !m_diagram )
        return;

    if ( m_model )
        disconnect(m_model);

    if ( m_attributesmodel )
        disconnect(m_attributesmodel);

    const bool con = connect( m_diagram, SIGNAL(viewportCoordinateSystemChanged()), this, SLOT(slotDataChanged()) );
    Q_ASSERT( con );
    Q_UNUSED( con )
    connect( m_diagram, SIGNAL(dataHidden()), SLOT(slotDataHidden()) );

    if ( m_diagram->model() ) {
        connect( m_diagram->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                 SLOT(slotDataChanged(QModelIndex,QModelIndex)));
        connect( m_diagram->model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
                 SLOT(slotDataChanged()));
        connect( m_diagram->model(), SIGNAL(columnsInserted(QModelIndex,int,int)),
                 SLOT(slotDataChanged()));
        connect( m_diagram->model(), SIGNAL(rowsRemoved(QModelIndex,int,int)),
                 SLOT(slotDataChanged()));
        connect( m_diagram->model(), SIGNAL(columnsRemoved(QModelIndex,int,int)),
                 SLOT(slotDataChanged()));
        connect( m_diagram->model(), SIGNAL(modelReset()),
                 SLOT(slotDataChanged()));
        connect( m_diagram->model(), SIGNAL(headerDataChanged(Qt::Orientation,int,int)),
                 SLOT(slotHeaderDataChanged(Qt::Orientation,int,int)));
    }

    if ( m_diagram->attributesModel() )
        connect( m_diagram->attributesModel(), SIGNAL(attributesChanged(QModelIndex,QModelIndex)),
                 SLOT(slotAttributesChanged(QModelIndex,QModelIndex)));
    m_model = m_diagram->model();
    m_attributesmodel = m_diagram->attributesModel();
}


void DiagramObserver::slotDestroyed(QObject*)
{
    //qDebug() << this << "emits signal\n"
    //        "    emit diagramDestroyed(" <<  m_diagram << ")";
    AbstractDiagram* diag = m_diagram;
    disconnect( m_diagram, nullptr, this, nullptr);
    m_diagram = nullptr;
    emit diagramDestroyed( diag );
}

void DiagramObserver::slotAboutToBeDestroyed()
{
    emit diagramAboutToBeDestroyed( m_diagram );
}

void DiagramObserver::slotModelsChanged()
{
    init();
    slotDataChanged();
    slotAttributesChanged();
}

void DiagramObserver::slotHeaderDataChanged(Qt::Orientation,int,int)
{
    //qDebug() << "DiagramObserver::slotHeaderDataChanged()";
    emit diagramDataChanged( m_diagram );
}

void DiagramObserver::slotDataChanged(QModelIndex,QModelIndex)
{
    slotDataChanged();
}

void DiagramObserver::slotDataChanged()
{
    //qDebug() << "DiagramObserver::slotDataChanged()";
    emit diagramDataChanged( m_diagram );
}

void DiagramObserver::slotDataHidden()
{
    //qDebug() << "DiagramObserver::slotDataHidden()";
    emit diagramDataHidden( m_diagram );
}

void DiagramObserver::slotAttributesChanged(QModelIndex,QModelIndex)
{
    slotAttributesChanged();
}

void DiagramObserver::slotAttributesChanged()
{
    //qDebug() << "DiagramObserver::slotAttributesChanged()";
    emit diagramAttributesChanged( m_diagram );
}

