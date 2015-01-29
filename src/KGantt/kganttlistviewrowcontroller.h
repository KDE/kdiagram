/**
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KGANTTLISTVIEWROWCONTROLLER_H
#define KGANTTLISTVIEWROWCONTROLLER_H

#include "kganttabstractrowcontroller.h"

QT_BEGIN_NAMESPACE
class QAbstractProxyModel;
class QListView;
QT_END_NAMESPACE

namespace KGantt {
    class KGANTT_EXPORT ListViewRowController : public AbstractRowController {
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC(ListViewRowController)
    public:
	ListViewRowController( QListView* lv, QAbstractProxyModel* proxy );
        ~ListViewRowController();

        /*reimp*/ int headerHeight() const;
        /*reimp*/ int maximumItemHeight() const;
        /*reimp*/ int totalHeight() const;
        /*reimp*/ bool isRowVisible( const QModelIndex& idx ) const;
        /*reimp*/ bool isRowExpanded( const QModelIndex& idx ) const;
        /*reimp*/ Span rowGeometry( const QModelIndex& idx ) const;
        /*reimp*/ QModelIndex indexAt( int height ) const;
        /*reimp*/ QModelIndex indexAbove( const QModelIndex& idx ) const;
        /*reimp*/ QModelIndex indexBelow( const QModelIndex& idx ) const;
    };
}

#endif /* KGANTTLISTVIEWROWCONTROLLER_H */

