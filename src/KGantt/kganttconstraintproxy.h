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

#ifndef KGANTTCONSTRAINTPROXY_H
#define KGANTTCONSTRAINTPROXY_H

#include "kganttglobal.h"

#include <QPointer>

QT_BEGIN_NAMESPACE
class QAbstractProxyModel;
QT_END_NAMESPACE

namespace KGantt {
    class Constraint;
    class ConstraintModel;

    class KGANTT_EXPORT ConstraintProxy : public QObject {
        Q_OBJECT
    public:
        explicit ConstraintProxy( QObject* parent = nullptr );
        virtual ~ConstraintProxy();

        void setSourceModel( ConstraintModel* src );
        void setDestinationModel( ConstraintModel* dest );
        void setProxyModel( QAbstractProxyModel* proxy );

        ConstraintModel* sourceModel() const;
        ConstraintModel* destinationModel() const;
        QAbstractProxyModel* proxyModel() const;


    private Q_SLOTS:

        void slotSourceConstraintAdded( const KGantt::Constraint& );
        void slotSourceConstraintRemoved( const KGantt::Constraint& );

        void slotDestinationConstraintAdded( const KGantt::Constraint& );
        void slotDestinationConstraintRemoved( const KGantt::Constraint& );

        void slotLayoutChanged();

    private:
        void copyFromSource();

        QPointer<QAbstractProxyModel> m_proxy;
        QPointer<ConstraintModel> m_source;
        QPointer<ConstraintModel> m_destination;
    };
}

#endif /* KGANTTCONSTRAINTPROXY_H */

