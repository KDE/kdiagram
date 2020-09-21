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

#ifndef KGANTTITEMDELEGATE_P_H
#define KGANTTITEMDELEGATE_P_H

#include "kganttitemdelegate.h"

#include <QHash>

namespace KGantt {
    class Q_DECL_HIDDEN ItemDelegate::Private {
    public:
        Private();

        QPen constraintPen( const QPointF& start, const QPointF& end, const Constraint& constraint, const QStyleOptionGraphicsItem& opt  );

        QHash<ItemType, QBrush> defaultbrush;
        QHash<ItemType, QPen> defaultpen;
    };
}

#endif /* KGANTTITEMDELEGATE_P_H */

