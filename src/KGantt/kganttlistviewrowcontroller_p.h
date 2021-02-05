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

#ifndef KGANTTLISTVIEWROWCONTROLLER_P_H
#define KGANTTLISTVIEWROWCONTROLLER_P_H

#include "kganttlistviewrowcontroller.h"

#include <QListView>

namespace KGantt {
    class Q_DECL_HIDDEN ListViewRowController::Private {
    public:
        class HackListView : public QListView {
        public:
            using QListView::verticalOffset;
            using QListView::setViewportMargins;
        };

        Private(QListView* lv, QAbstractProxyModel* pm )
            : listview(lv), proxy(pm) {}
        QListView* listview;
        QAbstractProxyModel* proxy;
    };
}

#endif /* KGANTTLISTVIEWROWCONTROLLER_P_H */

