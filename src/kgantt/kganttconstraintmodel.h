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

#ifndef KGANTTCONSTRAINTMODEL_H
#define KGANTTCONSTRAINTMODEL_H

#include <QModelIndex>
#include <QDebug>

#include "kganttglobal.h"
#include "kganttconstraint.h"

namespace KGantt {


    /*!\class KGantt::ConstraintModel
     *\ingroup KGantt
     * The ConstraintModel keeps track of the
     * interdependencies between gantt items in
     * a View.
     *
     */
    class KGANTT_EXPORT ConstraintModel : public QObject {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_DERIVED_PARENT( ConstraintModel, QObject* )
     public:


        /*! Constructor. Creates an empty ConstraintModel with parent \a parent
         */
        explicit ConstraintModel( QObject* parent = nullptr );


        /*! Destroys this ConstraintModel */
        virtual ~ConstraintModel();

        /*! Adds the constraint \a c to this ConstraintModel
         *  If the Constraint \a c is already in this ConstraintModel,
         *  nothing happens.
         *
         * Subclassing ConstraintModel and overriding addConstraint() and removeConstraint() can provide
         * re-entrancy issues in the ConstraintModel<->ConstraintProxy interaction. Therefore it is recommed
         * to better subclass GraphicsView and override addConstraint() there.
         */
        virtual void addConstraint( const Constraint& c );

        /*! Removes the Constraint \a c from this
         * ConstraintModel. If \a c was found and removed,
         * the signal constraintRemoved(const Constraint&) is emitted.
         *
         * \returns If \a c was found and removed, it returns true,
         * otherwise it returns false.
         */
        virtual bool removeConstraint( const Constraint& c );

        /*! Removes all Constraints from this model
         * The signal constraintRemoved(const Constraint&) is emitted
         * for every Constraint that is removed.
         */
        void clear();

        /*! Not used */
        void cleanup();

        /*! \returns A list of all Constraints in this
         * ConstraintModel.
         */
        QList<Constraint> constraints() const;

        /*! Returns true if a Constraint with start \a s and end \a e
         * exists, otherwise false.
         */
        bool hasConstraint( const Constraint& c ) const;
        inline bool hasConstraint( const QModelIndex& s,
                                   const QModelIndex& e ) const;


        /*! \returns A list of all Constraints in this ConstraintModel
         * that have an endpoint at \a idx.
         */
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

