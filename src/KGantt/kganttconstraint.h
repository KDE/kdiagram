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

#ifndef KGANTTCONSTRAINT_H
#define KGANTTCONSTRAINT_H

#include <QMap>
#include <QModelIndex>
#include <QObject>
#include <QSharedDataPointer>
#include <QVariant>

#include "kganttglobal.h"
#ifndef QT_NO_DEBUG_STREAM
#include <QDebug>
#endif

namespace KGantt {
    class KGANTT_EXPORT Constraint {
        class Private;
    public:
        enum Type
        {
            TypeSoft = 0,
            TypeHard = 1
        };
        enum RelationType
        {
            FinishStart = 0,
            FinishFinish = 1,
            StartStart = 2,
            StartFinish = 3
        };

        enum ConstraintDataRole
        {
            ValidConstraintPen = Qt::UserRole,
            InvalidConstraintPen
        };

        typedef QMap<int, QVariant> DataMap;

        Constraint();
        Constraint( const QModelIndex& idx1,
                    const QModelIndex& idx2,
                    Type type=TypeSoft,
                    RelationType relType=FinishStart,
                    const DataMap& datamap=DataMap() );
        Constraint( const Constraint& other);
        ~Constraint();

        Type type() const;
        RelationType relationType() const;
        QModelIndex startIndex() const;
        QModelIndex endIndex() const;

        void setData( int role, const QVariant& value );
        QVariant data( int role ) const;

        void setDataMap( const QMap< int, QVariant >& datamap );
        QMap< int, QVariant > dataMap() const;

        bool compareIndexes(const Constraint& other) const;

        Constraint& operator=( const Constraint& other );
        bool operator==( const Constraint& other ) const;

        inline bool operator!=( const Constraint& other ) const {
            return !operator==( other );
        }

        uint hash() const;
#ifndef QT_NO_DEBUG_STREAM
        QDebug debug( QDebug dbg) const;
#endif

    private:
        QSharedDataPointer<Private> d;
    };

    inline uint qHash( const Constraint& c ) {return c.hash();}
}

#ifndef QT_NO_DEBUG_STREAM
QDebug KGANTT_EXPORT operator<<( QDebug dbg, const KGantt::Constraint& c );
#endif /* QT_NO_DEBUG_STREAM */

#endif /* KGANTTCONSTRAINT_H */

