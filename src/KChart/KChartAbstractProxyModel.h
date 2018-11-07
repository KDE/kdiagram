/*
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KD Chart library.
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

#ifndef KCHARTABSTRACTPROXYMODEL_H
#define KCHARTABSTRACTPROXYMODEL_H

#include <QAbstractProxyModel>

#include "KChartGlobal.h"

namespace KChart
{
    /**
      * @brief Base class for all proxy models used inside KChart
      * \internal
      */
    class KCHART_EXPORT AbstractProxyModel : public QAbstractProxyModel
    {
        Q_OBJECT
    public:
        explicit AbstractProxyModel( QObject* parent = nullptr );

        /*! \reimpl */ 
        QModelIndex mapFromSource( const QModelIndex & sourceIndex ) const Q_DECL_OVERRIDE;
        /*! \reimpl */ 
        QModelIndex mapToSource( const QModelIndex &proxyIndex ) const Q_DECL_OVERRIDE;

        /*! \reimpl */
        QModelIndex index( int row, int col, const QModelIndex& index ) const Q_DECL_OVERRIDE;
        /*! \reimpl */ 
        QModelIndex parent( const QModelIndex& index ) const Q_DECL_OVERRIDE;
    };
}

#endif /* KCHARTABSTRACTPROXYMODEL_H */
