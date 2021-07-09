/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTTREEVIEWROWCONTROLLER_P_H
#define KGANTTTREEVIEWROWCONTROLLER_P_H

#include "kgantttreeviewrowcontroller.h"

#include <QTreeView>

QT_BEGIN_NAMESPACE
class QAbstractProxyModel;
QT_END_NAMESPACE

namespace KGantt {
    class Q_DECL_HIDDEN TreeViewRowController::Private {
    public:
        class HackTreeView : public QTreeView {
        public:
            using QTreeView::verticalOffset;
            using QTreeView::rowHeight;
        };
        HackTreeView* treeview;
        QAbstractProxyModel* proxy;
    };
}

#endif /* KGANTTTREEVIEWROWCONTROLLER_P_H */

