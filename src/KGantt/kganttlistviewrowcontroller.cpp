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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kganttlistviewrowcontroller.h"
#include "kganttlistviewrowcontroller_p.h"

#include <QAbstractProxyModel>
#include <QScrollBar>

#include <cassert>

using namespace KGantt;

/*!\class TreeViewRowController
 * This is an implementation of AbstractRowController that
 * aligns a gantt view with a QListView. Provided for
 * convenience for users who want to use View with QListView
 * instead of QTreeView.
 */

ListViewRowController::ListViewRowController( QListView* lv, QAbstractProxyModel* proxy )
  : _d( new Private(lv,proxy) )
{
}

ListViewRowController::~ListViewRowController()
{
    delete _d; _d = nullptr;
}

#define d d_func()

int ListViewRowController::headerHeight() const
{
    return d->listview->viewport()->y()-d->listview->frameWidth();
}

int ListViewRowController::maximumItemHeight() const
{
    return d->listview->fontMetrics().height();
}

int ListViewRowController::totalHeight() const
{
    return d->listview->verticalScrollBar()->maximum()+d->listview->viewport()->height();
}

bool ListViewRowController::isRowVisible( const QModelIndex& _idx ) const
{
    const QModelIndex idx = d->proxy->mapToSource( _idx );
    assert( idx.isValid() ? ( idx.model() == d->listview->model() ):( true ) );
    return d->listview->visualRect(idx).isValid();
}

bool ListViewRowController::isRowExpanded( const QModelIndex& _idx ) const
{
    Q_UNUSED(_idx);

    return false;
}

Span ListViewRowController::rowGeometry( const QModelIndex& _idx ) const
{
    const QModelIndex idx = d->proxy->mapToSource( _idx );
    assert( idx.isValid() ? ( idx.model() == d->listview->model() ):( true ) );
    QRect r = d->listview->visualRect(idx).translated( QPoint( 0,
		  static_cast<Private::HackListView*>(d->listview)->verticalOffset() ) );
    return Span( r.y(), r.height() );
}

QModelIndex ListViewRowController::indexAt( int height ) const
{
    return d->proxy->mapFromSource( d->listview->indexAt( QPoint( 1,height ) ) );
}

QModelIndex ListViewRowController::indexAbove( const QModelIndex& _idx ) const
{
    const QModelIndex idx = d->proxy->mapToSource( _idx );
    return d->proxy->mapFromSource( idx.sibling( idx.row()-1, idx.column()) );
}

QModelIndex ListViewRowController::indexBelow( const QModelIndex& _idx ) const
{
    const QModelIndex idx = d->proxy->mapToSource( _idx );
    if ( !idx.isValid() || idx.column()!=0 ) return QModelIndex();
    if ( idx.model()->rowCount(idx.parent())<idx.row()+1 ) return QModelIndex();
    return d->proxy->mapFromSource( idx.sibling( idx.row()+1, idx.column()) );
}

