/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTPROXYMODEL_P_H
#define KGANTTPROXYMODEL_P_H

#include "kganttproxymodel.h"

#include <QHash>

namespace KGantt {
    class Q_DECL_HIDDEN ProxyModel::Private {
    public:
        explicit Private( ProxyModel* _q );

        QHash<int, int> columnMap;
        QHash<int, int> roleMap;
        bool calendarMode;
    };
}

#endif /* KGANTTPROXYMODEL_P_H */

