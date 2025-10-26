/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTSUMMARYHANDLINGPROXYMODEL_P_H
#define KGANTTSUMMARYHANDLINGPROXYMODEL_P_H

#include "kganttsummaryhandlingproxymodel.h"

#include <QDateTime>
#include <QHash>
#include <QPair>
#include <QPersistentModelIndex>

namespace KGantt
{
class Q_DECL_HIDDEN SummaryHandlingProxyModel::Private
{
public:
    bool cacheLookup(const QModelIndex &idx, QPair<QDateTime, QDateTime> *result) const;
    void insertInCache(const SummaryHandlingProxyModel *model, const QModelIndex &idx) const;
    void removeFromCache(const QModelIndex &idx) const;
    void clearCache() const;

    inline bool isSummary(const QModelIndex &idx) const
    {
        int typ = idx.data(ItemTypeRole).toInt();
        return (typ == TypeSummary) || (typ == TypeMulti);
    }

    mutable QHash<QModelIndex, QPair<QDateTime, QDateTime>> cached_summary_items;
};
}

#endif /* KGANTTSUMMARYHANDLINGPROXYMODEL_P_H */
