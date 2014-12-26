/**
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KD Chart library.
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

#ifndef KDGANTTABSTRACTROWCONTROLLER_H
#define KDGANTTABSTRACTROWCONTROLLER_H

#include <QPair>
#include "kdganttglobal.h"

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

namespace KDGantt {
    class KDE_KDGANTT_EXPORT AbstractRowController {
    public:
        AbstractRowController();
        virtual ~AbstractRowController();

        virtual int headerHeight() const = 0;
        virtual int maximumItemHeight() const = 0;
	virtual int totalHeight() const = 0;

        virtual bool isRowVisible( const QModelIndex& idx ) const = 0;
	virtual bool isRowExpanded( const QModelIndex& idx ) const = 0;
        virtual Span rowGeometry( const QModelIndex& idx ) const = 0;


        virtual QModelIndex indexAt( int height ) const = 0;
        virtual QModelIndex indexAbove( const QModelIndex& idx ) const = 0;
        virtual QModelIndex indexBelow( const QModelIndex& idx ) const = 0;
    };
}

#endif /* KDGANTTABSTRACTROWCONTROLLER_H */

