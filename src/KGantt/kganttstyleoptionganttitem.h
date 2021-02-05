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

#ifndef KGANTTSTYLEOPTIONGANTTITEM_H
#define KGANTTSTYLEOPTIONGANTTITEM_H

#include "kganttglobal.h"

#include <QStyleOptionViewItem>
#include <QRectF>
#include <QDebug>

namespace KGantt {
    class AbstractGrid;
    class KGANTT_EXPORT StyleOptionGanttItem : public QStyleOptionViewItem {
    public:
        enum Position { Left, Right, Center, Hidden };

        StyleOptionGanttItem();
        StyleOptionGanttItem( const StyleOptionGanttItem& other );
        StyleOptionGanttItem& operator=( const StyleOptionGanttItem& other );

        QRectF boundingRect;
        QRectF itemRect;
        Position displayPosition;
        AbstractGrid* grid;
        QString text;
    };
}

#ifndef QT_NO_DEBUG_STREAM

QDebug operator<<( QDebug dbg, KGantt::StyleOptionGanttItem::Position p);
QDebug operator<<( QDebug dbg, const KGantt::StyleOptionGanttItem& s );

#endif /* QT_NO_DEBUG_STREAM */


#endif /* KGANTTSTYLEOPTIONGANTTITEM_H */

