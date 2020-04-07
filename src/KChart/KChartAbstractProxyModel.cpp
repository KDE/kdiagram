/*
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "KChartAbstractProxyModel.h"

#include "KChartMath_p.h"

#include <QDebug>

#ifdef __GNUC__
#if __GNUC__ > 3
#define MAY_ALIAS __attribute__((__may_alias__))
#endif
#else
#define MAY_ALIAS
#endif

namespace KChart {	

  AbstractProxyModel::AbstractProxyModel(QObject* parent) 
  : QAbstractProxyModel(parent) {}

// Allows access to QModelIndex's private data via type punning and a compatible data layout.
// Due to inlining in Qt and no d-pointer, it is safe to assume that the layout won't change except
// between major Qt versions. As it happens, the layout is the same in Qt4 and Qt5.
// The only change is void * -> quintptr.
struct MAY_ALIAS KDPrivateModelIndex
{
  int r, c;
  void *p;
  const QAbstractItemModel *m;
};

QModelIndex AbstractProxyModel::mapFromSource( const QModelIndex & sourceIndex ) const
{
  if ( !sourceIndex.isValid() )
    return QModelIndex();
  //qDebug() << "sourceIndex.model()="<<sourceIndex.model();
  //qDebug() << "model()="<<sourceModel();
  Q_ASSERT( sourceIndex.model() == sourceModel() );

  // Create an index that preserves the internal pointer from the source;
  // this way AbstractProxyModel preserves the structure of the source model
  return createIndex( sourceIndex.row(), sourceIndex.column(), sourceIndex.internalPointer() );
}

QModelIndex AbstractProxyModel::mapToSource( const QModelIndex &proxyIndex ) const
{
  if ( !proxyIndex.isValid() )
    return QModelIndex();
  if ( proxyIndex.model() != this )
    qDebug() << proxyIndex.model() << this;
  Q_ASSERT( proxyIndex.model() == this );
  // So here we need to create a source index which holds that internal pointer.
  // No way to pass it to sourceModel()->index... so we have to do the ugly way:
  QModelIndex sourceIndex;
  KDPrivateModelIndex* hack = reinterpret_cast<KDPrivateModelIndex*>(&sourceIndex);
  hack->r = proxyIndex.row();
  hack->c = proxyIndex.column();
  hack->p = proxyIndex.internalPointer();
  hack->m = sourceModel();
  Q_ASSERT( sourceIndex.isValid() );
  return sourceIndex;
}

QModelIndex AbstractProxyModel::index( int row, int col, const QModelIndex& index ) const
{
    Q_ASSERT(sourceModel());
    return mapFromSource(sourceModel()->index( row, col, mapToSource(index) ));
}

QModelIndex AbstractProxyModel::parent( const QModelIndex& index ) const
{
    Q_ASSERT(sourceModel());
    return mapFromSource(sourceModel()->parent( mapToSource(index) ));
}

}
