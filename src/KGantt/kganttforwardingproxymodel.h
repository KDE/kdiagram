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

#ifndef KGANTTFORWARDINGPROXYMODEL_H
#define KGANTTFORWARDINGPROXYMODEL_H

#include <QAbstractProxyModel>

#include "kganttglobal.h"

namespace KGantt {
    class KGANTT_EXPORT ForwardingProxyModel : public QAbstractProxyModel {
        Q_OBJECT
        Q_DISABLE_COPY(ForwardingProxyModel)
    public:
        explicit ForwardingProxyModel( QObject* parent = nullptr );
        virtual ~ForwardingProxyModel();

        /*reimp*/ QModelIndex mapFromSource ( const QModelIndex & sourceIndex ) const override;
        /*reimp*/ QModelIndex mapToSource ( const QModelIndex & proxyIndex ) const override;

        /*reimp*/ void setSourceModel( QAbstractItemModel* model ) override;

        /*reimp*/ QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const override;
        /*reimp*/ QModelIndex parent( const QModelIndex& idx ) const override;

        /*reimp*/ int rowCount( const QModelIndex& idx = QModelIndex() ) const override;
        /*reimp*/ int columnCount( const QModelIndex& idx = QModelIndex() ) const override;

        /*reimp*/ bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole ) override;

        /*reimp*/ QMimeData *mimeData(const QModelIndexList &indexes) const override;
        /*reimp*/ bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
        /*reimp*/ QStringList mimeTypes() const override;
        /*reimp*/ Qt::DropActions supportedDropActions() const override;
    
    protected Q_SLOTS:
        virtual void sourceModelAboutToBeReset();
        virtual void sourceModelReset();
        virtual void sourceLayoutAboutToBeChanged();
        virtual void sourceLayoutChanged();
        virtual void sourceDataChanged( const QModelIndex& from, const QModelIndex& to );
        virtual void sourceColumnsAboutToBeInserted( const QModelIndex& idx, int start, int end );
        virtual void sourceColumnsInserted( const QModelIndex& idx, int start, int end );
        virtual void sourceColumnsAboutToBeRemoved( const QModelIndex& idx, int start, int end );
        virtual void sourceColumnsRemoved( const QModelIndex& idx, int start, int end );
        virtual void sourceRowsAboutToBeInserted( const QModelIndex& idx, int start, int end );
        virtual void sourceRowsInserted( const QModelIndex& idx, int start, int end );
        virtual void sourceRowsAboutToBeRemoved( const QModelIndex&, int start, int end );
        virtual void sourceRowsRemoved( const QModelIndex&, int start, int end );
    };
}

#endif /* KGANTTFORWARDINGPROXYMODEL_H */

