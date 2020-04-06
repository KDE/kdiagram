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

#include "kganttconstraint.h"
#include "kganttconstraint_p.h"

#include <QDateTime>

using namespace KGantt;


Constraint::Private::Private()
    : type( TypeSoft ),
      relationType( FinishStart )
{
}

Constraint::Private::Private( const Private& other )
    : QSharedData( other ),
      start( other.start ),
      end( other.end ),
      type( other.type ),
      relationType( other.relationType ),
      data( other.data )
{
}

Constraint::Constraint( const QModelIndex& idx1,
                        const QModelIndex& idx2,
                        Constraint::Type type,
                        Constraint::RelationType relationType,
                        const Constraint::DataMap& datamap )
    : d( new Private )
{
    d->start=idx1;
    d->end=idx2;
    d->type=type;
    d->relationType=relationType;
    d->data=datamap;
    Q_ASSERT_X( idx1 != idx2 || !idx1.isValid(), "Constraint::Constraint", "cannot create a constraint with idx1 == idx2" );
}

Constraint::Constraint()
    : d( new Private )
{
}

Constraint::Constraint( const Constraint& other )
    : d( other.d )
{
}

Constraint::~Constraint()
{
}

Constraint& Constraint::operator=( const Constraint& other )
{
    d = other.d;
    return *this;
}

Constraint::Type Constraint::type() const
{
    return d->type;
}

Constraint::RelationType Constraint::relationType() const
{
    return d->relationType;
}

QModelIndex Constraint::startIndex() const
{
    return d->start;
}

QModelIndex Constraint::endIndex() const
{
    return d->end;
}

QVariant Constraint::data( int role ) const
{
    return d->data.value( role );
}

void Constraint::setData( int role, const QVariant& value )
{
    d->data.insert( role, value );
}

void Constraint::setDataMap( const QMap< int, QVariant >& datamap )
{
    d->data = datamap;
}

QMap< int, QVariant > Constraint::dataMap() const
{
    return d->data;
}

bool Constraint::compareIndexes(const Constraint& other) const
{
    return (d->start==other.startIndex() || (!d->start.isValid() && !other.startIndex().isValid()))
        && (d->end==other.endIndex() || (!d->end.isValid() && !other.endIndex().isValid()));
}

bool Constraint::operator==( const Constraint& other ) const
{
    if ( d == other.d ) return true;
    return ( *d ).equals( *( other.d ) );
}

uint Constraint::hash() const
{
    return ::qHash( d->start ) ^ ::qHash( d->end ) ^ ::qHash( static_cast<uint>( d->type ) );
}

#ifndef QT_NO_DEBUG_STREAM

QDebug operator<<( QDebug dbg, const Constraint& c )
{
    return c.debug( dbg );
}

QDebug Constraint::debug( QDebug dbg ) const
{
    dbg << "KGantt::Constraint[ start=" << d->start << "end=" << d->end << "relationType=" << d->relationType << "], data=" << d->data;
    return dbg;
}

#endif /* QT_NO_DEBUG_STREAM */

#ifndef KDAB_NO_UNIT_TESTS

#include <QStandardItemModel>

#include "unittest/test.h"

KDAB_SCOPED_UNITTEST_SIMPLE( KGantt, Constraint, "test" )
{
    QStandardItemModel dummyModel( 100, 100 );
    QModelIndex idx1 = dummyModel.index( 7, 17, QModelIndex() );
    QModelIndex idx2 = dummyModel.index( 42, 17, QModelIndex() );

    Constraint c1 = Constraint( QModelIndex(), QModelIndex(), Constraint::TypeSoft );
    Constraint c2 = Constraint( QModelIndex(), QModelIndex(), Constraint::TypeSoft );
    Constraint c3 = c2;
    Constraint c4( idx1, idx2 );
    Constraint c5( idx2, idx1 );

    assertTrue( c1==c2 );
    assertEqual( qHash( c1 ), qHash( c2 ) );
    assertTrue( c1==c3 );
    assertEqual( qHash( c1 ), qHash( c3 ) );
    assertTrue( c2==c3 );
    assertEqual( qHash( c2 ), qHash( c3 ) );

    assertFalse( c2==c4 );
    assertNotEqual( qHash( c2 ), qHash( c4 ) );

    assertFalse( c4==c5 );

    assertEqual( c3.type(), Constraint::TypeSoft );

    dummyModel.removeRow( 8 );
    assertFalse( c4==c5 );
}

#endif /* KDAB_NO_UNIT_TESTS */
