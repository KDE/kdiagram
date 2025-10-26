/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTITEMDELEGATE_P_H
#define KGANTTITEMDELEGATE_P_H

#include "kganttitemdelegate.h"

#include <QHash>

namespace KGantt
{
class Q_DECL_HIDDEN ItemDelegate::Private
{
public:
    Private();

    QPen constraintPen(const QPointF &start, const QPointF &end, const Constraint &constraint, const QStyleOptionGraphicsItem &opt);

    QHash<ItemType, QBrush> defaultbrush;
    QHash<ItemType, QPen> defaultpen;
};
}

#endif /* KGANTTITEMDELEGATE_P_H */
