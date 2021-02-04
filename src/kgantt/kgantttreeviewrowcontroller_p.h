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

