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

#ifndef KGANTTCONSTRAINT_P_H
#define KGANTTCONSTRAINT_P_H

#include <QSharedData>
#include <QPersistentModelIndex>
#include <QMap>

#include "kganttconstraint.h"

namespace KGantt {
    class Q_DECL_HIDDEN Constraint::Private : public QSharedData {
    public:
        Private();
        Private( const Private& other );

        inline bool equals( const Private& other ) const {
            /* Due to a Qt bug we have to check separately for invalid indexes */
            return (start==other.start || (!start.isValid() && !other.start.isValid()))
                && (end==other.end || (!end.isValid() && !other.end.isValid()))
                && type==other.type
                && relationType==other.relationType
                && data==other.data;
        }

        QPersistentModelIndex start;
        QPersistentModelIndex end;
        Type type;
        RelationType relationType;
        QMap< int, QVariant > data;
    };
}

#endif /* KGANTTCONSTRAINT_P_H */

