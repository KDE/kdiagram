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

#include "kganttstyleoptionganttitem.h"

using namespace KGantt;

/*!\class KGantt::StyleOptionGanttItem kganttstyleoptionganttitem.h KGanttStyleOptionGanttItem
 * \ingroup KGantt
 * \brief QStyleOption subclass for gantt items.
 */

typedef QStyleOptionViewItem BASE;

/*! Constructor. Sets grid to 0. */
StyleOptionGanttItem::StyleOptionGanttItem()
    : BASE(),
      displayPosition( Left ),
      grid( nullptr )
{
    type = QStyleOption::SO_CustomBase+89;
    version = 1;
}

/*! Copy constructor. Creates a copy of \a other */
StyleOptionGanttItem::StyleOptionGanttItem( const StyleOptionGanttItem& other )
    : BASE(other)
{
    operator=( other );
}

/*! Assignment operator */
StyleOptionGanttItem& StyleOptionGanttItem::operator=( const StyleOptionGanttItem& other )
{
    BASE::operator=( other );
    boundingRect = other.boundingRect;
    itemRect = other.itemRect;
    displayPosition = other.displayPosition;
    grid = other.grid;
    text = other.text;
    return *this;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<( QDebug dbg, KGantt::StyleOptionGanttItem::Position p)
{
    switch ( p ) {
    case KGantt::StyleOptionGanttItem::Left:   dbg << "KGantt::StyleOptionGanttItem::Left"; break;
    case KGantt::StyleOptionGanttItem::Right:  dbg << "KGantt::StyleOptionGanttItem::Right"; break;
    case KGantt::StyleOptionGanttItem::Center: dbg << "KGantt::StyleOptionGanttItem::Center"; break;
    case KGantt::StyleOptionGanttItem::Hidden: dbg << "KGantt::StyleOptionGanttItem::Hidden"; break;
    default: dbg << static_cast<int>( p );
    }
    return dbg;
}

QDebug operator<<( QDebug dbg, const KGantt::StyleOptionGanttItem& s )
{
    dbg << "KGantt::StyleOptionGanttItem[ boundingRect="<<s.boundingRect
        <<", itemRect="<<s.itemRect
        <<", displayPosition="<<s.displayPosition
        <<", grid="<<s.grid
        <<", text="<<s.text
        <<"]";
    return dbg;
}

#endif /* QT_NO_DEBUG_STREAM */


/*!\enum KGantt::StyleOptionGanttItem::Position
 * This enum is used to describe where the Qt::DisplayRole
 * (the label) should be located relative to the item itself.
 */

/*!\var StyleOptionGanttItem::boundingRect
 * Contains the bounding rectangle for the item
 */

/*!\var StyleOptionGanttItem::itemRect
 * Contains the "active" item rectangle that corresponds
 * to the values from the model.
 */

/*!\var StyleOptionGanttItem::displayPosition
 * \see StyleOptionGanttItem::Position.
 */

/*!\var StyleOptionGanttItem::grid
 * Contains a pointer to the AbstractGrid used by the view
 */

/*!\var StyleOptionGanttItem::text
 * Contains a string printed to the item
 */
