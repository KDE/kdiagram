/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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



    /*!\class KGantt::ConstraintProxy
     * \internal
     */
    class KGANTT_EXPORT ConstraintProxy : public QObject {
        Q_OBJECT
    public:
        explicit ConstraintProxy( QObject* parent = nullptr );
        ~ConstraintProxy() override;

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

