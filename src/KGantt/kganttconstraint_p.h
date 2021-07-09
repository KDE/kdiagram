/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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

