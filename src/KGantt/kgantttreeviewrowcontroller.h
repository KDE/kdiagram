/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTTREEVIEWROWCONTROLLER_H
#define KGANTTTREEVIEWROWCONTROLLER_H

#include "kganttabstractrowcontroller.h"

QT_BEGIN_NAMESPACE
class QAbstractProxyModel;
class QTreeView;
QT_END_NAMESPACE

namespace KGantt
{

/*!\class TreeViewRowController
 * This is an implementation of AbstractRowController that
 * aligns a gantt view with a QTreeView.
 */
class KGANTT_EXPORT TreeViewRowController : public AbstractRowController
{
    KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC(TreeViewRowController)
public:
    TreeViewRowController(QTreeView *tv, QAbstractProxyModel *proxy);
    ~TreeViewRowController() override;

    /*reimp*/ int headerHeight() const override;
    /*reimp*/ int maximumItemHeight() const override;
    /*reimp*/ int totalHeight() const override;
    /*reimp*/ bool isRowVisible(const QModelIndex &idx) const override;
    /*reimp*/ bool isRowExpanded(const QModelIndex &idx) const override;
    /*reimp*/ Span rowGeometry(const QModelIndex &idx) const override;
    /*reimp*/ QModelIndex indexAt(int height) const override;
    /*reimp*/ QModelIndex indexAbove(const QModelIndex &idx) const override;
    /*reimp*/ QModelIndex indexBelow(const QModelIndex &idx) const override;
};
}

#endif /* KGANTTTREEVIEWROWCONTROLLER_H */
