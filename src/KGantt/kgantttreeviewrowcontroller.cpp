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

#include "kgantttreeviewrowcontroller.h"
#include "kgantttreeviewrowcontroller_p.h"

#include <QAbstractProxyModel>
#include <QHeaderView>
#include <QScrollBar>

#include <cassert>

using namespace KGantt;

/*!\class TreeViewRowController
 * This is an implementation of AbstractRowController that
 * aligns a gantt view with a QTreeView.
 */

TreeViewRowController::TreeViewRowController( QTreeView* tv,
					      QAbstractProxyModel* proxy )
  : _d( new Private )
{
    _d->treeview = static_cast<Private::HackTreeView*>(tv);
    _d->proxy = proxy;
}

TreeViewRowController::~TreeViewRowController()
{
    delete _d; _d = nullptr;
}

#define d d_func()

int TreeViewRowController::headerHeight() const
{
  //return d->treeview->header()->sizeHint().height();
    return d->treeview->viewport()->y()-d->treeview->frameWidth();
}

int TreeViewRowController::maximumItemHeight() const
{
    return d->treeview->fontMetrics().height();
}

int TreeViewRowController::totalHeight() const
{
    return d->treeview->verticalScrollBar()->maximum()+d->treeview->viewport()->height();
}

bool TreeViewRowController::isRowVisible( const QModelIndex& _idx ) const
{
  //qDebug() << _idx.model()<<d->proxy << d->treeview->model();
    const QModelIndex idx = d->proxy->mapToSource( _idx );
    assert( idx.isValid() ? ( idx.model() == d->treeview->model() ):( true ) );
    return d->treeview->visualRect(idx).isValid();
}

bool TreeViewRowController::isRowExpanded( const QModelIndex& _idx ) const
{
    const QModelIndex idx = d->proxy->mapToSource( _idx );
    assert( idx.isValid() ? ( idx.model() == d->treeview->model() ):( true ) );
    return d->treeview->isExpanded( idx );
}

Span TreeViewRowController::rowGeometry( const QModelIndex& _idx ) const
{
    const QModelIndex idx = d->proxy->mapToSource( _idx );
    assert( idx.isValid() ? ( idx.model() == d->treeview->model() ):( true ) );
    QRect r = d->treeview->visualRect(idx).translated( QPoint( 0, d->treeview->verticalOffset() ) );
    return Span( r.y(), r.height() );
}

QModelIndex TreeViewRowController::indexAt( int height ) const
{
  /* using indexAt( QPoint ) wont work here, since it does hit detection
   *   against the actual item text/icon, so we would return wrong values
   *   for items with no text etc.
   *
   *   The code below could cache for performance, but currently it doesn't
   *   seem to be the performance bottleneck at all.
   */
    if ( !d->treeview->model() ) return QModelIndex();
    int y = d->treeview->verticalOffset();
    QModelIndex idx = d->treeview->model()->index( 0, 0, d->treeview->rootIndex() );
    do {
        if ( y >= height ) break;
        y += d->treeview->rowHeight( idx );
        idx = d->treeview->indexBelow( idx );
    } while ( idx.isValid() );
    return d->proxy->mapFromSource( idx );
}

QModelIndex TreeViewRowController::indexAbove( const QModelIndex& _idx ) const
{
    const QModelIndex idx = d->proxy->mapToSource( _idx );
    return d->proxy->mapFromSource( d->treeview->indexAbove( idx ) );
}

QModelIndex TreeViewRowController::indexBelow( const QModelIndex& _idx ) const
{
    const QModelIndex idx = d->proxy->mapToSource( _idx );
    return d->proxy->mapFromSource( d->treeview->indexBelow( idx ) );
}
