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

#ifndef KGANTTSUMMARYHANDLINGPROXYMODEL_H
#define KGANTTSUMMARYHANDLINGPROXYMODEL_H

#include "kganttforwardingproxymodel.h"

namespace KGantt {
    class KGANTT_EXPORT SummaryHandlingProxyModel : public ForwardingProxyModel {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( SummaryHandlingProxyModel )
    public:
        explicit SummaryHandlingProxyModel( QObject* parent = nullptr );
        virtual ~SummaryHandlingProxyModel();

        /*reimp*/ void setSourceModel( QAbstractItemModel* model ) Q_DECL_OVERRIDE;

        /*reimp*/ QVariant data( const QModelIndex& proxyIndex, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
        /*reimp*/ bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole ) Q_DECL_OVERRIDE;

        /*reimp*/ Qt::ItemFlags flags( const QModelIndex& idx ) const Q_DECL_OVERRIDE;

    protected:
        /*reimp*/ void sourceModelReset() Q_DECL_OVERRIDE;
        /*reimp*/ void sourceLayoutChanged() Q_DECL_OVERRIDE;
        /*reimp*/ void sourceDataChanged( const QModelIndex& from, const QModelIndex& to ) Q_DECL_OVERRIDE;
        /*reimp*/ void sourceColumnsAboutToBeInserted( const QModelIndex& idx, int start, int end ) Q_DECL_OVERRIDE;
        /*reimp*/ void sourceColumnsAboutToBeRemoved( const QModelIndex& idx, int start, int end ) Q_DECL_OVERRIDE;
        /*reimp*/ void sourceRowsAboutToBeInserted( const QModelIndex& idx, int start, int end ) Q_DECL_OVERRIDE;
        /*reimp*/ void sourceRowsAboutToBeRemoved( const QModelIndex&, int start, int end ) Q_DECL_OVERRIDE;
    };
}

#endif /* KGANTTSUMMARYHANDLINGPROXYMODEL_H */

