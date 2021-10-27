/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTPROXYMODEL_H
#define KGANTTPROXYMODEL_H

#include "kganttforwardingproxymodel.h"

namespace KGantt {
    class KGANTT_EXPORT ProxyModel : public ForwardingProxyModel {
        Q_OBJECT
        Q_DISABLE_COPY(ProxyModel)
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( ProxyModel )
    public:
        explicit ProxyModel( QObject* parent = nullptr );
        ~ProxyModel() override;

        void setColumn( int ganttrole, int col );
        void removeColumn( int ganttrole );
        void setRole( int ganttrole, int role );
        void removeRole(  int ganttrole );

        int column( int ganttrole ) const;
        int role( int ganttrole ) const;

#if 0
        void setCalendarMode( bool enable );
        bool calendarMode() const;
#endif

        /*reimp*/ QModelIndex mapFromSource( const QModelIndex& idx) const override;
        /*reimp*/ QModelIndex mapToSource( const QModelIndex& proxyIdx ) const override;

        /*reimp*/ int rowCount( const QModelIndex& idx ) const override;
        /*reimp*/ int columnCount( const QModelIndex& idx ) const override;

        /*reimp*/ QVariant data( const QModelIndex& idx, int role = Qt::DisplayRole ) const override;
        /*reimp*/ bool setData( const QModelIndex& idx, const QVariant& value, int role=Qt::EditRole ) override;
    };
}

#endif /* KGANTTPROXYMODEL_H */

