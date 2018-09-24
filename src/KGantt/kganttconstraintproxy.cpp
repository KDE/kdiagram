/*
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KGantt library.
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

#include "kganttconstraintproxy.h"
#include "kganttconstraintmodel.h"

#include <QAbstractProxyModel>

using namespace KGantt;

/*!\class KGantt::ConstraintProxy
 * \internal
 */

ConstraintProxy::ConstraintProxy( QObject* parent )
    : QObject( parent )
{
}

ConstraintProxy::~ConstraintProxy()
{
}

void ConstraintProxy::setSourceModel( ConstraintModel* src )
{
    if ( m_source ) m_source->disconnect( this );
    m_source = src;

    copyFromSource();

    connect( m_source, SIGNAL(constraintAdded(KGantt::Constraint)),
             this, SLOT(slotSourceConstraintAdded(KGantt::Constraint)) );
    connect( m_source, SIGNAL(constraintRemoved(KGantt::Constraint)),
             this, SLOT(slotSourceConstraintRemoved(KGantt::Constraint)) );
}

void ConstraintProxy::setDestinationModel( ConstraintModel* dest )
{
    if ( m_destination ) m_destination->disconnect( this );
    m_destination = dest;

    copyFromSource();

    connect( m_destination, SIGNAL(constraintAdded(KGantt::Constraint)),
             this, SLOT(slotDestinationConstraintAdded(KGantt::Constraint)) );
    connect( m_destination, SIGNAL(constraintRemoved(KGantt::Constraint)),
             this, SLOT(slotDestinationConstraintRemoved(KGantt::Constraint)) );
}

void ConstraintProxy::setProxyModel( QAbstractProxyModel* proxy )
{
    if ( m_proxy == proxy ) return;
    if ( m_proxy ) m_proxy->disconnect( this );
    m_proxy = proxy;
    if ( m_proxy ) {
        connect( m_proxy, SIGNAL(layoutChanged()), this, SLOT(slotLayoutChanged()) );
        connect( m_proxy, SIGNAL(modelReset()), this, SLOT(slotLayoutChanged()) );
    }
}

ConstraintModel* ConstraintProxy::sourceModel() const { return m_source; }
ConstraintModel* ConstraintProxy::destinationModel() const { return m_destination; }
QAbstractProxyModel* ConstraintProxy::proxyModel() const { return m_proxy; }


void ConstraintProxy::copyFromSource()
{
    if ( m_destination ) {
        m_destination->clear();
        if ( !m_source ) return;
        const QList<Constraint> lst = m_source->constraints();
        Q_FOREACH( const Constraint& c, lst )
        {
           Constraint temp( m_proxy->mapFromSource( c.startIndex() ), m_proxy->mapFromSource( c.endIndex() ),
                            c.type(), c.relationType(), c.dataMap() );
           m_destination->addConstraint( temp );
        }
    }
}

void ConstraintProxy::slotSourceConstraintAdded( const KGantt::Constraint& c )
{
    if ( m_destination )
    {
        Constraint temp( m_proxy->mapFromSource( c.startIndex() ), m_proxy->mapFromSource( c.endIndex() ),
                         c.type(), c.relationType(), c.dataMap() );
        m_destination->addConstraint( temp );
    }
}

void ConstraintProxy::slotSourceConstraintRemoved( const KGantt::Constraint& c )
{
    if ( m_destination )
    {
        Constraint temp( m_proxy->mapFromSource( c.startIndex() ), m_proxy->mapFromSource( c.endIndex() ),
                         c.type(), c.relationType(), c.dataMap() );
        m_destination->removeConstraint( temp );
    }
}

void ConstraintProxy::slotDestinationConstraintAdded( const KGantt::Constraint& c )
{
    if ( m_source )
    {
        Constraint temp( m_proxy->mapToSource( c.startIndex() ), m_proxy->mapToSource( c.endIndex() ),
                         c.type(), c.relationType(), c.dataMap() );
        m_source->addConstraint( temp );
    }
}

void ConstraintProxy::slotDestinationConstraintRemoved( const KGantt::Constraint& c )
{
    if ( m_source )
    {
        Constraint temp( m_proxy->mapToSource( c.startIndex() ), m_proxy->mapToSource( c.endIndex() ),
                         c.type(), c.relationType(), c.dataMap() );
        m_source->removeConstraint( temp );
    }
}

void ConstraintProxy::slotLayoutChanged()
{
    copyFromSource();
}

#include "moc_kganttconstraintproxy.cpp"
