/**
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

#include "kganttglobal.h"

using namespace KGantt;

/* Older Qt don't have this macro, so define it... */
#ifndef QT_VERSION_CHECK
#  define QT_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))
#endif

/* Version check */
#if QT_VERSION < QT_VERSION_CHECK(4,3,0)
#  error "The minimum required version of Qt for KD Gantt is 4.3.0"
#endif

/*!\enum KGantt::ItemDataRole
 *\ingroup KGantt
 * The values of this enum are used for the special data roles
 * for gantt items
 */

/*!\enum KGantt::ItemDataRole KGantt::KGanttRoleBase
 * The base value used for the KGantt role enum values.
 * The actual roles have values base+1, base+2, ...
 */

/*!\enum KGantt::ItemDataRole KGantt::StartTimeRole
 * Start time (or other start value) for a gantt item.
 */

/*!\enum KGantt::ItemDataRole KGantt::EndTimeRole
 * End time (or other end value) for a gantt item.
 */

/*!\enum KGantt::ItemDataRole KGantt::TaskCompletionRole
 * Task completetion percentage used by Task items. Should be an
 * integer og a qreal between 0 and 100.
 */

/*!\enum KGantt::ItemDataRole KGantt::ItemTypeRole
 * The item type. \see KGantt::ItemType.
 */

/*!\enum KGantt::ItemDataRole KGantt::TextPositionRole
 * The position of the text label on the item.
 * The type of this value is KGantt::StyleOptionGanttItem::Position
 * and the default values is Right.
 */

/*!\enum KGantt::ItemType
 *\ingroup KGantt
 * The values of this enum are used to represent the different
 * types of gantt items that KGantt understands. The itemtype
 * is served through the KGantt::ItemTypeRole role
 */

/*!\class KGantt::Span kganttglobal.h KGanttGlobal
 *\ingroup KGantt
 * \brief A class representing a start point and a length */

DateTimeSpan::DateTimeSpan()
{
}

DateTimeSpan::DateTimeSpan( const QDateTime& start, const QDateTime& end )
    : m_start( start ), m_end( end )
{
}

DateTimeSpan::DateTimeSpan( const DateTimeSpan& other )
{
    *this = other;
}

DateTimeSpan::~DateTimeSpan()
{
}

DateTimeSpan& DateTimeSpan::operator=( const DateTimeSpan& other )
{
    if ( this != &other ) {
        m_start = other.m_start;
        m_end = other.m_end;
    }
    return *this;
}

bool DateTimeSpan::isValid() const
{
    return m_start.isValid() && m_end.isValid();
}

bool DateTimeSpan::equals( const DateTimeSpan& other ) const
{
    return m_start==other.m_start && m_end==other.m_end;
}

#ifndef QT_NO_DEBUG_STREAM

QDebug operator<<( QDebug dbg, KGantt::ItemDataRole r)
{
  switch (r) {
  case KGantt::StartTimeRole:      dbg << "KGantt::StartTimeRole"; break;
  case KGantt::EndTimeRole:        dbg << "KGantt::EndTimeRole"; break;
  case KGantt::TaskCompletionRole: dbg << "KGantt::TaskCompletionRole"; break;
  case KGantt::ItemTypeRole:       dbg << "KGantt::ItemTypeRole"; break;
  case KGantt::LegendRole:         dbg << "KGantt::LegendRole"; break;
  default: dbg << static_cast<Qt::ItemDataRole>(r);
  }
  return dbg;
}

QDebug operator<<( QDebug dbg, KGantt::ItemType t)
{
    switch ( t ) {
    case KGantt::TypeNone:        dbg << "KGantt::TypeNone"; break;
    case KGantt::TypeEvent:       dbg << "KGantt::TypeEvent"; break;
    case KGantt::TypeTask:        dbg << "KGantt::TypeTask"; break;
    case KGantt::TypeSummary:     dbg << "KGantt::TypeSummary"; break;
    case KGantt::TypeMulti:       dbg << "KGantt::TypeMulti"; break;
    case KGantt::TypeUser:        dbg << "KGantt::TypeUser"; break;
    default: dbg << static_cast<int>(t);
    }
    return dbg;
}

QDebug operator<<( QDebug dbg, const KGantt::Span& s )
{
    dbg << "KGantt::Span[ start="<<s.start()<<" length="<<s.length()<<"]";
    return dbg;
}
QDebug operator<<( QDebug dbg, const KGantt::DateTimeSpan& s )
{
    dbg << "KGantt::DateTimeSpan[ start="<<s.start()<<" end="<<s.end()<<"]";
    return dbg;
}

#endif /* QT_NO_DEBUG_STREAM */

#ifndef KDAB_NO_UNIT_TESTS

#include <ostream>

static std::ostream& operator<<( std::ostream& os, const Span& span )
{
    os << "Span[ start="<<span.start()<<", length="<<span.length()<<"]";
    return os;
}

static std::ostream& operator<<( std::ostream& os, const DateTimeSpan& span )
{
#ifdef QT_NO_STL
    os << "DateTimeSpan[ start="<<span.start().toString().toLatin1().constData()
       << ", end="<<span.end().toString().toLatin1().constData() << "]";
#else
    os << "DateTimeSpan[ start="<<span.start().toString().toStdString()
       << ", end="<<span.end().toString().toStdString() << "]";
#endif
    return os;
}

#include "unittest/test.h"

KDAB_SCOPED_UNITTEST_SIMPLE( KGantt, Span, "test" ) {
    Span s1;
    assertFalse( s1.isValid() );
    s1.setStart( 10. );
    s1.setLength( 2. );

    Span s2( s1.start(), s1.length() );
    assertEqual( s1, s2 );
}

KDAB_SCOPED_UNITTEST_SIMPLE( KGantt, DateTimeSpan, "test" ) {
    DateTimeSpan s1;
    assertFalse( s1.isValid() );
    QDateTime dt = QDateTime::currentDateTime();
    s1.setStart( dt );
    assertTrue( dt.isValid() );
    s1.setEnd( dt.addDays( 1 ) );

    DateTimeSpan s2( dt, dt.addDays( 1 ) );

    assertEqual( s1, s2 );

    DateTimeSpan s3;

    assertNotEqual( s1, s3 );
}
#endif /* KDAB_NO_UNIT_TESTS */
