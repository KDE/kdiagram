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


    /*!\class KGantt::Constraint
     *\ingroup KGantt
     * \brief A class used to represent a dependency.
     *
     * Instances of this class represent a dependency between the
     * data items pointed to by a start-QModelIndex and an
     * end-QModelIndex.
     */
    class KGANTT_EXPORT Constraint {
        class Private;
    public:
        /*!\enum KGantt::Constraint::Type
         * This enum is unused for now.
         */
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

        /*!\enum KGantt::Constraint::ConstraintDataRole
         * Data roles used when specifying the pen to draw constraints with.
         * \sa setData
         */
        enum ConstraintDataRole
        {
            ValidConstraintPen = Qt::UserRole,
            InvalidConstraintPen
        };

        typedef QMap<int, QVariant> DataMap;

        /*! Default constructor, created an invalid constraint. */
        Constraint();

        /*! Constructor. Creates a dependency for \a idx2 on \a idx1.
         * \param type controls if the constraint is a soft one that
         * is allowed to be broken (ie, go backwards in time) or a hard
         * constraint that will not allow the user to move an item so
         * that the constraint would have to go backwards. The default is
         * TypeSoft.
         *
         * Actually enforcing hard constraints is the responsibility of
         * the AbstractGrid subclass used in the view.
         *
         * \param relationType defines how the tasks depends on each other.
         * relationType can be FinishStart (default), FinishFinish, StartStart or StartFinish.
         */
        Constraint( const QModelIndex& idx1,
                    const QModelIndex& idx2,
                    Type type=TypeSoft,
                    RelationType relType=FinishStart,
                    const DataMap& datamap=DataMap() );

        /*! Copy-Constructor. */
        Constraint( const Constraint& other);


        /*! Destructor */
        ~Constraint();

        /*! This is unused for now. */
        Type type() const;

        /*! This is unused for now. */
        RelationType relationType() const;

        /*! \returns The dependency index */
        QModelIndex startIndex() const;

        /*! \returns The constrained index */
        QModelIndex endIndex() const;

        /*! Set data on this index for the specified role.
         * \param role The role to set the data for.
         * \param value The data to set on the index.
         * \sa ConstraintDataRole
         */
        void setData( int role, const QVariant& value );

        /*! \returns The data associated with this index for the specified role.
         * \param role The role to fetch the data for.
         * \sa ConstraintDataRole
         */
        QVariant data( int role ) const;

        /*! Set data on this constraint to the keys/values in \a datamap.
         * Clears any existing data from the constraint.
         */
        void setDataMap( const QMap< int, QVariant >& datamap );

        /*! \returns all the data set on this constraint. \see setDataMap
         */
        QMap< int, QVariant > dataMap() const;

        bool compareIndexes(const Constraint& other) const;

        /*! Assignment operator. */
        Constraint& operator=( const Constraint& other );

        /*! Compare two Constraint objects. Two Constraints are equal
         * if the have the same start and end indexes
         */
        bool operator==( const Constraint& other ) const;

        inline bool operator!=( const Constraint& other ) const {
            return !operator==( other );
        }

        /*!\internal*/
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

