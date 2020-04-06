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
        /*! Constructor. Creates a new ForwardingProxyModel with
         * parent \a parent
         */
        explicit ForwardingProxyModel( QObject* parent = nullptr );
        virtual ~ForwardingProxyModel();

        /*! Converts indexes in the source model to indexes in the proxy model */
        /*reimp*/ QModelIndex mapFromSource ( const QModelIndex & sourceIndex ) const override;

        /*! Converts indexes in the proxy model to indexes in the source model */
        /*reimp*/ QModelIndex mapToSource ( const QModelIndex & proxyIndex ) const override;

        /*! Sets the model to be used as the source model for this proxy.
         * The proxy does not take ownership of the model.
         * \see QAbstractProxyModel::setSourceModel
         */
        /*reimp*/ void setSourceModel( QAbstractItemModel* model ) override;

        /*! \see QAbstractItemModel::index */
        /*reimp*/ QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const override;

        /*! \see QAbstractItemModel::parent */
        /*reimp*/ QModelIndex parent( const QModelIndex& idx ) const override;

        /*! \see QAbstractItemModel::rowCount */
        /*reimp*/ int rowCount( const QModelIndex& idx = QModelIndex() ) const override;

        /*! \see QAbstractItemModel::columnCount */
        /*reimp*/ int columnCount( const QModelIndex& idx = QModelIndex() ) const override;

        /*! \see QAbstractItemModel::setData */
        /*reimp*/ bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole ) override;

        /*reimp*/ QMimeData *mimeData(const QModelIndexList &indexes) const override;
        /*reimp*/ bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
        /*reimp*/ QStringList mimeTypes() const override;
        /*reimp*/ Qt::DropActions supportedDropActions() const override;
    
    protected Q_SLOTS:
        /*! Called when the source model is about to be reset.
         * \sa QAbstractItemModel::modelAboutToBeReset()
         */
        virtual void sourceModelAboutToBeReset();

        /*! Called when the source model is reset
         * \sa QAbstractItemModel::modelReset()
         */
        virtual void sourceModelReset();

        /*! Called just before the layout of the source model is changed.
         * \sa QAbstractItemModel::layoutAboutToBeChanged()
         */
        virtual void sourceLayoutAboutToBeChanged();

        /*! Called when the layout of the source model has changed.
         * \sa QAbstractItemModel::layoutChanged()
         */
        virtual void sourceLayoutChanged();

        /*! Called when the data in an existing item in the source model changes.
         * \sa QAbstractItemModel::dataChanged()
         */
        virtual void sourceDataChanged( const QModelIndex& from, const QModelIndex& to );

        /*! Called just before columns are inserted into the source model.
         * \sa QAbstractItemModel::columnsAboutToBeInserted()
         */
        virtual void sourceColumnsAboutToBeInserted( const QModelIndex& idx, int start, int end );

        /*! Called after columns have been inserted into the source model.
         * \sa QAbstractItemModel::columnsInserted()
         */
        virtual void sourceColumnsInserted( const QModelIndex& idx, int start, int end );

        /*! Called just before columns are removed from the source model.
         * \sa QAbstractItemModel::columnsAboutToBeRemoved()
         */
        virtual void sourceColumnsAboutToBeRemoved( const QModelIndex& idx, int start, int end );

        /*! Called after columns have been removed from the source model.
         * \sa QAbstractItemModel::columnsRemoved()
         */
        virtual void sourceColumnsRemoved( const QModelIndex& idx, int start, int end );


        /*! Called just before rows are inserted into the source model.
         * \sa QAbstractItemModel::rowsAboutToBeInserted()
         */
        virtual void sourceRowsAboutToBeInserted( const QModelIndex& idx, int start, int end );

        /*! Called after rows have been inserted into the source model.
         * \sa QAbstractItemModel::rowsInserted()
         */
        virtual void sourceRowsInserted( const QModelIndex& idx, int start, int end );

        /*! Called just before rows are removed from the source model.
         * \sa QAbstractItemModel::rowsAboutToBeRemoved()
         */
        virtual void sourceRowsAboutToBeRemoved( const QModelIndex&, int start, int end );

        /*! Called after rows have been removed from the source model.
         * \sa QAbstractItemModel::rowsRemoved()
         */
        virtual void sourceRowsRemoved( const QModelIndex&, int start, int end );
    };
}

#endif /* KGANTTFORWARDINGPROXYMODEL_H */

