/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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

