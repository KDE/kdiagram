/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTCONSTRAINTMODEL_P_H
#define KGANTTCONSTRAINTMODEL_P_H

#include "kganttconstraintmodel.h"

#include <QList>
#include <QMultiHash>
#include <QPersistentModelIndex>

namespace KGantt
{
class Q_DECL_HIDDEN ConstraintModel::Private
{
public:
    Private();

    void addConstraintToIndex(const QModelIndex &idx, const Constraint &c);
    void removeConstraintFromIndex(const QModelIndex &idx, const Constraint &c);

    typedef QMultiHash<QPersistentModelIndex, Constraint> IndexType;

    QList<Constraint> constraints;
    IndexType indexMap;
};
}

#endif /* KGANTTCONSTRAINTMODEL_P_H */
