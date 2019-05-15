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

#ifndef KGANTTSUMMARYHANDLINGPROXYMODEL_P_H
#define KGANTTSUMMARYHANDLINGPROXYMODEL_P_H

#include "kganttsummaryhandlingproxymodel.h"

#include <QDateTime>
#include <QHash>
#include <QPair>
#include <QPersistentModelIndex>

namespace KGantt {
    class Q_DECL_HIDDEN SummaryHandlingProxyModel::Private {
    public:
        bool cacheLookup( const QModelIndex& idx,
                          QPair<QDateTime,QDateTime>* result ) const;
        void insertInCache( const SummaryHandlingProxyModel* model, const QModelIndex& idx ) const;
        void removeFromCache( const QModelIndex& idx ) const;
        void clearCache() const;
		
		inline bool isSummary( const QModelIndex& idx ) const {
			int typ = idx.data( ItemTypeRole ).toInt();
			return (typ==TypeSummary) || (typ==TypeMulti);
		}

        mutable QHash<QModelIndex, QPair<QDateTime, QDateTime> > cached_summary_items;
    };
}

#endif /* KGANTTSUMMARYHANDLINGPROXYMODEL_P_H */

