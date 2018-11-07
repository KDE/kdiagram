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

#ifndef KGANTTCONSTRAINTMODEL_H
#define KGANTTCONSTRAINTMODEL_H

#include <QModelIndex>
#include <QDebug>

#include "kganttglobal.h"
#include "kganttconstraint.h"

namespace KGantt {
    class KGANTT_EXPORT ConstraintModel : public QObject {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_DERIVED_PARENT( ConstraintModel, QObject* )
     public:
        explicit ConstraintModel( QObject* parent = nullptr );
        virtual ~ConstraintModel();

        /**
        * Subclassing ConstraintModel and overriding addConstraint() and removeConstraint() can provide
        * re-entrancy issues in the ConstraintModel<->ConstraintProxy interaction. Therefore it is recommed
        * to better subclass GraphicsView and override addConstraint() there.
        */
        virtual void addConstraint( const Constraint& c );
        virtual bool removeConstraint( const Constraint& c );

        void clear();
        void cleanup();

        QList<Constraint> constraints() const;

        bool hasConstraint( const Constraint& c ) const;
        inline bool hasConstraint( const QModelIndex& s,
                                   const QModelIndex& e ) const;

        QList<Constraint> constraintsForIndex( const QModelIndex& ) const;

    Q_SIGNALS:
        void constraintAdded(const KGantt::Constraint&);
        void constraintRemoved(const KGantt::Constraint&);

    private:
        Private* _d;
    };

    inline const ConstraintModel::Private* ConstraintModel::d_func() const { return _d; }
    inline ConstraintModel::Private* ConstraintModel::d_func() { return _d; }
    inline bool ConstraintModel::hasConstraint( const QModelIndex& s, const QModelIndex& e ) const {
        return hasConstraint( Constraint( s, e ) );
    }
}

#ifndef QT_NO_DEBUG_STREAM

QDebug KGANTT_EXPORT operator<<( QDebug dbg, const KGantt::ConstraintModel& model );
inline QDebug operator<<( QDebug dbg, KGantt::ConstraintModel* model )
{
    return operator<<(dbg,*model);
}

#endif /* QT_NO_DEBUG_STREAM */

#endif /* KGANTTCONSTRAINTMODEL_H */

