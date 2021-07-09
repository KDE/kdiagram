/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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

