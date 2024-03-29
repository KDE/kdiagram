/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTSUMMARYHANDLINGPROXYMODEL_H
#define KGANTTSUMMARYHANDLINGPROXYMODEL_H

#include "kganttforwardingproxymodel.h"

namespace KGantt {


    /*!\class KGantt::SummaryHandlingProxyModel
     * \brief Proxy model that supports summary gantt items.
     *
     * This proxy model provides the functionality of summary items.
     * A summary item is an item with type KGantt::TypeSummary and
     * zero or more children in the model that it summarizes.
     * GraphicsView itself does not dictate any policy for summary items,
     * instead the logic for making the summary items start and end points
     * span it's children is provided by this proxy.
     *
     * The start and end times of a summary is the min/max of the
     * start/end times of it's children.
     *
     * \see GraphicsView::setModel
     */
    class KGANTT_EXPORT SummaryHandlingProxyModel : public ForwardingProxyModel {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( SummaryHandlingProxyModel )
    public:


        /*! Constructor. Creates a new SummaryHandlingProxyModel with
         * parent \a parent
         */
        explicit SummaryHandlingProxyModel( QObject* parent = nullptr );
        ~SummaryHandlingProxyModel() override;



        /*! Sets the model to be used as the source model for this proxy.
         * The proxy does not take ownership of the model.
         * \see QAbstractProxyModel::setSourceModel
         */
        /*reimp*/ void setSourceModel( QAbstractItemModel* model ) override;



        /*! \see QAbstractItemModel::data */
        /*reimp*/ QVariant data( const QModelIndex& proxyIndex, int role = Qt::DisplayRole) const override;


        /*! \see QAbstractItemModel::setData */
        /*reimp*/ bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole ) override;



        /*! \see QAbstractItemModel::flags */
        /*reimp*/ Qt::ItemFlags flags( const QModelIndex& idx ) const override;

    protected:
        /*reimp*/ void sourceModelReset() override;
        /*reimp*/ void sourceLayoutChanged() override;
        /*reimp*/ void sourceDataChanged( const QModelIndex& from, const QModelIndex& to ) override;
        /*reimp*/ void sourceColumnsAboutToBeInserted( const QModelIndex& idx, int start, int end ) override;
        /*reimp*/ void sourceColumnsAboutToBeRemoved( const QModelIndex& idx, int start, int end ) override;
        /*reimp*/ void sourceRowsAboutToBeInserted( const QModelIndex& idx, int start, int end ) override;
        /*reimp*/ void sourceRowsAboutToBeRemoved( const QModelIndex&, int start, int end ) override;
    };
}

#endif /* KGANTTSUMMARYHANDLINGPROXYMODEL_H */

