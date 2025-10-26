/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTLEGEND_P_H
#define KGANTTLEGEND_P_H

#include "kganttlegend.h"

#include "kganttproxymodel.h"

namespace KGantt
{
class Q_DECL_HIDDEN Legend::Private
{
public:
    ProxyModel proxyModel;
};
}

#endif /* KGANTTLEGEND_P_H */
