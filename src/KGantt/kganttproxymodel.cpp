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

#include "kganttproxymodel.h"
#include "kganttproxymodel_p.h"


using namespace KGantt;

typedef ForwardingProxyModel BASE;

ProxyModel::Private::Private( ProxyModel* _q )
#if 0
    : calendarMode( false )
#endif
{
    Q_UNUSED( _q ); // for now

    columnMap[Qt::DisplayRole]    = 0;
    columnMap[ItemTypeRole]       = 1;
    columnMap[StartTimeRole]      = 2;
    columnMap[EndTimeRole]        = 3;
    columnMap[TaskCompletionRole] = 4;
    columnMap[LegendRole]         = 5;

    roleMap[Qt::DisplayRole]    = Qt::DisplayRole;
    roleMap[ItemTypeRole]       = Qt::DisplayRole;
    roleMap[StartTimeRole]      = StartTimeRole;
    roleMap[EndTimeRole]        = EndTimeRole;
    roleMap[TaskCompletionRole] = Qt::DisplayRole;
    roleMap[LegendRole]         = Qt::DisplayRole;
}

ProxyModel::ProxyModel( QObject* parent )
    : BASE( parent ), _d( new Private( this ) )
{
    init();
}

ProxyModel::~ProxyModel()
{
    delete _d; _d = nullptr;
}

#define d d_func()

void ProxyModel::init()
{
}

QModelIndex ProxyModel::mapFromSource( const QModelIndex& sourceIdx ) const
{
#if 0
    if ( sourceIdx.isValid() ) {
        if ( calendarMode() ) {
            const QAbstractItemModel* model = sourceIdx.model();
            if ( model->hasChildren( sourceIdx ) ) {
                return BASE::mapFromSource( model->index( sourceIdx.row(),0,sourceIdx.parent()));
            } else {
                // Map children to columns
                return BASE::mapFromSource( model->index( sourceIdx.row(),0,sourceIdx.parent()))
                    .child( 0, sourceIdx.column() );
            }
        }
        return BASE::mapFromSource( sourceIdx.model()->index( sourceIdx.row(),0,sourceIdx.parent()));
    }
    else return QModelIndex();
#else
    // danders:
    // this was:
    // return BASE::mapFromSource( sourceIdx.model()?sourceIdx.model()->index( sourceIdx.row(),0,sourceIdx.parent()):QModelIndex());
    // with column hardcoded to 0.
    // Please notify if this *really* needs to be hardcoded, afaics it makes it impossible to get at anything else
    // than column 0 from e.g. an item delegate.
    return BASE::mapFromSource( sourceIdx.model()?sourceIdx.model()->index( sourceIdx.row(),sourceIdx.column(),sourceIdx.parent()):QModelIndex());
#endif
}

QModelIndex ProxyModel::mapToSource( const QModelIndex& proxyIdx ) const
{
#if 0
    if ( proxyIdx.isValid() ) {
        if ( calendarMode() && proxyIdx.column() > 0 ) {
            return BASE::mapToSource( proxyIdx.model()->index( proxyIdx.column(), 0, proxyIdx ) );
        }
        return BASE::mapToSource( proxyIdx );
    }
    else return QModelIndex();
#else
    return BASE::mapToSource( proxyIdx );
#endif
}

void ProxyModel::setColumn( int ganttrole, int col )
{
    d->columnMap[ganttrole] = col;
}

void ProxyModel::removeColumn( int ganttrole )
{
    d->columnMap.remove( ganttrole );
}

int ProxyModel::column( int ganttrole ) const
{
    return d->columnMap[ganttrole];
}

void ProxyModel::removeRole( int ganttrole )
{
    d->roleMap.remove( ganttrole );
}

void ProxyModel::setRole( int ganttrole, int role )
{
    d->roleMap[ganttrole] = role;
}

int ProxyModel::role( int ganttrole ) const
{
    return d->roleMap[ganttrole];
}

#if 0
void ProxyModel::setCalendarMode( bool enable )
{
    if ( d->calendarMode != enable ) {
        d->calendarMode = enable;
        reset();
    }
}

bool ProxyModel::calendarMode() const
{
    return d->calendarMode;
}
#endif

int ProxyModel::rowCount( const QModelIndex& proxyIndex ) const
{
    // TODO
    return BASE::rowCount( proxyIndex );
}

int ProxyModel::columnCount( const QModelIndex& proxyIndex ) const
{
    return qMin( sourceModel()->columnCount( mapToSource( proxyIndex ) ), 1 );
}

QVariant ProxyModel::data( const QModelIndex& proxyIdx, int role ) const
{
    int srole = role;
    int scol  = proxyIdx.column();
    QHash<int, int>::const_iterator it = d->roleMap.find( role );
    if ( it != d->roleMap.end() ) srole = *it;
    it = d->columnMap.find( role );
    if ( it != d->columnMap.end() ) scol = *it;

#if 0
    qDebug() << "mapping "<<static_cast<ItemDataRole>(role)<<", "<<proxyIdx.column()
             << " => " << static_cast<ItemDataRole>(srole)<<", " << scol
             << "value="
             << sourceModel()->data( sourceModel()->index( proxyIdx.row(), scol,
                                                           mapToSource( proxyIdx.parent() ) ), srole );
#endif

    const QAbstractItemModel* model = sourceModel();
    return model->data( model->index( proxyIdx.row(), scol, mapToSource( proxyIdx.parent() ) ), srole );
}

bool ProxyModel::setData( const QModelIndex& proxyIdx, const QVariant& value, int role )
{
    int srole = role;
    int scol  = proxyIdx.column();
    QHash<int, int>::const_iterator it = d->roleMap.constFind( role );
    if ( it != d->roleMap.constEnd() ) srole = *it;
    it = d->columnMap.constFind( role );
    if ( it != d->columnMap.constEnd() ) scol = *it;

    QAbstractItemModel* model = sourceModel();
    return model->setData( model->index( proxyIdx.row(), scol, mapToSource( proxyIdx.parent() ) ), value, srole );
}

#include "moc_kganttproxymodel.cpp"
