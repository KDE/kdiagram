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
        virtual ~ProxyModel();

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

        /*reimp*/ QModelIndex mapFromSource( const QModelIndex& idx) const Q_DECL_OVERRIDE;
        /*reimp*/ QModelIndex mapToSource( const QModelIndex& proxyIdx ) const Q_DECL_OVERRIDE;

        /*reimp*/ int rowCount( const QModelIndex& idx ) const Q_DECL_OVERRIDE;
        /*reimp*/ int columnCount( const QModelIndex& idx ) const Q_DECL_OVERRIDE;

        /*reimp*/ QVariant data( const QModelIndex& idx, int role = Qt::DisplayRole ) const Q_DECL_OVERRIDE;
        /*reimp*/ bool setData( const QModelIndex& idx, const QVariant& value, int role=Qt::EditRole ) Q_DECL_OVERRIDE;
    };
}

#endif /* KGANTTPROXYMODEL_H */

