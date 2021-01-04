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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "kganttconstraintmodel.h"
#include "kganttconstraintmodel_p.h"

#include <QDebug>

#include <cassert>
#include <algorithm>
#include <functional>

using namespace KGantt;



ConstraintModel::Private::Private()
{
}

void ConstraintModel::Private::addConstraintToIndex( const QModelIndex& idx, const Constraint& c )
{
    IndexType::iterator it = indexMap.find(idx);
    while (it != indexMap.end() && it.key() == idx) {
        // Check if we already have this
        if ( *it == c ) return;
        ++it;
    }

    indexMap.insert( idx, c );
}

void ConstraintModel::Private::removeConstraintFromIndex( const QModelIndex& idx,  const Constraint& c )
{
    IndexType::iterator it = indexMap.find(idx);
    while (it != indexMap.end() && it.key() == idx) {
        if ( c.compareIndexes(*it) ) {
            it =indexMap.erase( it );
        } else {
            ++it;
        }
    }
}


ConstraintModel::ConstraintModel( QObject* parent )
    : QObject( parent ), _d( new Private )
{
    init();
}


ConstraintModel::ConstraintModel( Private* d_ptr, QObject* parent )
    : QObject( parent ), _d( d_ptr )
{
    init();
}


ConstraintModel::~ConstraintModel()
{
    delete _d;
}

#define d d_func()

void ConstraintModel::init()
{
}

namespace {
    struct compare_constraint_indexes_to : public std::unary_function<bool,Constraint> {
        compare_constraint_indexes_to( const Constraint& c )
            : m_c( c ) {
        }
        bool operator()( const Constraint& c ) const
        {
            return m_c.compareIndexes( c );
        }

        const Constraint& m_c;
    };
}

void ConstraintModel::addConstraint( const Constraint& c )
{
    //qDebug() << "ConstraintModel::addConstraint("<<c<<") (this="<<this<<") items=" << d->constraints.size();
    QList<Constraint>::iterator it = std::find_if ( d->constraints.begin(),
                                                    d->constraints.end(),
                                                    compare_constraint_indexes_to(c) );

    if ( it == d->constraints.end() ) {
        d->constraints.push_back( c );
        d->addConstraintToIndex( c.startIndex(), c );
        d->addConstraintToIndex( c.endIndex(), c );
        Q_EMIT constraintAdded( c );
    } else if ( ( *it ).dataMap() != c.dataMap() || ( *it ).type() != c.type() || ( *it ).relationType() != c.relationType() ) {
        Constraint tmp( *it ); // save to avoid re-entrancy issues
        removeConstraint( tmp );
        d->constraints.push_back( c );
        d->addConstraintToIndex( c.startIndex(), c );
        d->addConstraintToIndex( c.endIndex(), c );
        Q_EMIT constraintAdded( c );
    }
}

bool ConstraintModel::removeConstraint( const Constraint& c )
{
    bool rc = false;

    for (int i = 0; i < d->constraints.count(); i++)
    {
        if (c.compareIndexes(d->constraints.at(i)))
        {
            d->constraints.removeAt(i);
            rc = true;
        }
    }

    if ( rc ) {
        d->removeConstraintFromIndex( c.startIndex(), c );
        d->removeConstraintFromIndex( c.endIndex(), c );
        Q_EMIT constraintRemoved( c );
    }

    return rc;
}

void ConstraintModel::clear()
{
    const QList<Constraint> lst = constraints();
    for ( const Constraint& c : lst ) {
        removeConstraint( c );
    }
}

void ConstraintModel::cleanup()
{
#if 0
    QSet<Constraint> orphans;
    Q_FOREACH( const Constraint& c, d->constraints ) {
        if ( !c.startIndex().isValid() || !c.endIndex().isValid() ) orphans.insert( c );
    }
    //qDebug() << "Constraint::cleanup() found" << orphans << "orphans";
    d->constraints.subtract( orphans );
#endif
}

QList<Constraint> ConstraintModel::constraints() const
{
    //return d->constraints.toList();
    return d->constraints;
}

QList<Constraint> ConstraintModel::constraintsForIndex( const QModelIndex& idx ) const
{
    // TODO: @Steffen: Please comment on this assert, it's long and not obvious (Johannes)
    // TODO: Afaics indexMap is not used anymore, so remove it (danders)
    //assert( !idx.isValid() || d->indexMap.isEmpty() || !d->indexMap.keys().front().model() || idx.model() == d->indexMap.keys().front().model() );
    if ( !idx.isValid() ) {
        // Because of a Qt bug we need to treat this as a special case
        QSet<Constraint> result;
        for ( const Constraint& c : qAsConst(d->constraints) ) {
            if ( !c.startIndex().isValid() || !c.endIndex().isValid() ) result.insert( c );
        }
        return result.values();
    } else {
        QList<Constraint> result;
        for ( const Constraint& c : qAsConst(d->constraints) ) {
            if ( c.startIndex() == idx || c.endIndex() == idx ) result.push_back( c );
        }
        return result;
    }

    //return d->indexMap.values( idx );
}

bool ConstraintModel::hasConstraint( const Constraint& c ) const
{
    /*
    // Because of a Qt bug we have to search like this
    Q_FOREACH( Constraint c2, d->constraints ) {
        if ( c==c2 ) return true;
    }
    return false;
    */
    bool hc = false;

    for (int i = 0; i < d->constraints.count(); i++)
        if (c.compareIndexes(d->constraints.at(i)))
            hc = true;

    return hc;
}

#ifndef QT_NO_DEBUG_STREAM

QDebug operator<<( QDebug dbg, const KGantt::ConstraintModel& model )
{
    dbg << "KGantt::ConstraintModel[ " << static_cast<const QObject*>( &model ) << ": [\n";
    Q_FOREACH( const Constraint& c, model.constraints() ) {
        dbg << "\t" << c << "\n";
    }
    dbg << "]\n";
    return dbg;
}

#endif /* QT_NO_DEBUG_STREAM */

#undef d

#ifndef KDAB_NO_UNIT_TESTS

#include <QStandardItemModel>

#include "unittest/test.h"

std::ostream& operator<<( std::ostream& os, const QModelIndex& idx )
{
    QString str;
    QDebug( &str )<<idx;
#ifdef QT_NO_STL
    os<<str.toLatin1().constData();
#else
    os<<str.toStdString();
#endif
    return os;
}

KDAB_SCOPED_UNITTEST_SIMPLE( KGantt, ConstraintModel, "test" )
{
    QStandardItemModel dummyModel( 100, 100 );
    ConstraintModel model;

    QModelIndex invalidIndex;
    assertEqual( invalidIndex, invalidIndex );

    assertEqual( model.constraints().count(), 0 );

    model.addConstraint( Constraint( QModelIndex(), QModelIndex() ) );
    assertEqual( model.constraints().count(), 1 );

    model.addConstraint( Constraint( QModelIndex(), QModelIndex() ) );
    assertEqual( model.constraints().count(), 1 );

    QPersistentModelIndex idx1 = dummyModel.index( 7, 17, QModelIndex() );
    QPersistentModelIndex idx2 = dummyModel.index( 42, 17, QModelIndex() );

    model.addConstraint( Constraint( idx1, idx2 ) );
    assertEqual( model.constraints().count(), 2 );
    assertTrue( model.hasConstraint( Constraint( idx1, idx2 ) ) );

    assertEqual( model.constraintsForIndex( QModelIndex() ).count(), 1 );

    assertEqual( model.constraints().count(), 2 );
    model.removeConstraint( Constraint( QModelIndex(), QModelIndex() ) );
    assertEqual( model.constraints().count(), 1 );
    assertFalse( model.hasConstraint( Constraint( QModelIndex(), QModelIndex() ) ) );

    model.removeConstraint( Constraint( QModelIndex(), QModelIndex() ) );
    assertEqual( model.constraints().count(), 1 );

    model.removeConstraint( Constraint( idx1, idx2 ) );
    assertEqual( model.constraints().count(), 0 );
    assertFalse( model.hasConstraint( Constraint( idx1, idx2 ) ) );

    model.addConstraint( Constraint( idx1, idx2 ) );
    assertTrue( model.hasConstraint( Constraint( idx1, idx2 ) ) );
    dummyModel.removeRow( 8 );
    assertTrue( model.hasConstraint( Constraint( idx1, idx2 ) ) );
    dummyModel.removeRow( 7 );
    assertTrue( model.hasConstraint( Constraint( idx1, idx2 ) ) );
}

#endif /* KDAB_NO_UNIT_TESTS */

#include "moc_kganttconstraintmodel.cpp"
