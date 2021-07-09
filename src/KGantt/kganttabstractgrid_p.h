/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTABSTRACTGRID_P_H
#define KGANTTABSTRACTGRID_P_H

#include <QPointer>
#include <QAbstractItemModel>
#include <QPersistentModelIndex>

#include "kganttabstractgrid.h"

namespace KGantt {
    class Q_DECL_HIDDEN AbstractGrid::Private {
    public:
        virtual ~Private() {}
        QPointer<QAbstractItemModel> model;
        QPersistentModelIndex root;
    };

    inline AbstractGrid::AbstractGrid( Private* d ) : _d( d ) {}
}

#endif /* KGANTTABSTRACTGRID_P_H */

