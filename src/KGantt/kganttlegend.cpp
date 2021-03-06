/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "kganttlegend.h"
#include "kganttlegend_p.h"

#include "kganttitemdelegate.h"

#include <QApplication>
#include <QPainter>

#include <cassert>

using namespace KGantt;


Legend::Legend( QWidget* parent )
    : QAbstractItemView( parent ),
      _d( new Private )
{
    setItemDelegate( new ItemDelegate( this ) );
    setFrameStyle( QFrame::NoFrame );
}


Legend::~Legend()
{
    delete _d;
}

#define d d_func()

QModelIndex Legend::indexAt( const QPoint& point ) const
{
    Q_UNUSED( point );
    return QModelIndex();
}

QRect Legend::visualRect( const QModelIndex& index ) const
{
    Q_UNUSED( index );
    return QRect();
}

QSize Legend::sizeHint() const
{
    return measureItem( rootIndex() );
}

QSize Legend::minimumSizeHint() const
{
    return measureItem( rootIndex() );
}

void Legend::setModel( QAbstractItemModel* model )
{
    if ( this->model() != nullptr )
    {
        disconnect( this->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelDataChanged()) );
        disconnect( this->model(), SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(modelDataChanged()) );
        disconnect( this->model(), SIGNAL(columnsRemoved(QModelIndex,int,int)), this, SLOT(modelDataChanged()) );
    }

    QAbstractItemView::setModel( model );
    d->proxyModel.setSourceModel( model );

    if ( this->model() != nullptr )
    {
        connect( this->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelDataChanged()) );
        connect( this->model(), SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(modelDataChanged()) );
        connect( this->model(), SIGNAL(columnsRemoved(QModelIndex,int,int)), this, SLOT(modelDataChanged()) );
    }

}


void Legend::modelDataChanged()
{
    updateGeometry();
    viewport()->update();
}

void Legend::paintEvent( QPaintEvent* event )
{
    Q_UNUSED( event );
    // no model, no legend...
    if ( model() == nullptr )
        return;

    QPainter p( viewport() );
    p.fillRect( viewport()->rect(), palette().color( QPalette::Window ) );
    drawItem( &p, rootIndex() );
}


StyleOptionGanttItem Legend::getStyleOption( const QModelIndex& index ) const
{
    StyleOptionGanttItem opt;
    opt.displayPosition = StyleOptionGanttItem::Right;
    opt.displayAlignment = Qt::Alignment( d->proxyModel.data( index, Qt::TextAlignmentRole ).toInt() );
    opt.text = index.model()->data( index, LegendRole ).toString();
    opt.font = ( index.model()->data( index, Qt::FontRole ) ).value< QFont >();
    return opt;
}


QRect Legend::drawItem( QPainter* painter, const QModelIndex& index, const QPoint& pos ) const
{
    int xPos = pos.x();
    int yPos = pos.y();

    if ( index.isValid() && index.model() == &d->proxyModel )
    {
        ItemDelegate* const delegate = qobject_cast< ItemDelegate* >( itemDelegate( index ) );
        assert( delegate != nullptr );
        const QRect r( pos, measureItem( index, false ) );
        StyleOptionGanttItem opt = getStyleOption( index );
        opt.rect = r;
        opt.rect.setWidth( r.height() );

        const ItemType typ = static_cast<ItemType>( index.model()->data( index, ItemTypeRole ).toInt() );
        const int dx = (typ == TypeEvent) ? (r.height() / 2) : 0;

        opt.itemRect = opt.rect.adjusted(dx,0,dx,0);
        opt.boundingRect = r;
        opt.boundingRect.setWidth( r.width() + r.height() );
        if ( !opt.text.isNull() )
            delegate->paintGanttItem( painter, opt, index );

        xPos = r.right();
        yPos = r.bottom();
    }

    
    const int rowCount = d->proxyModel.rowCount( index );
    for ( int row = 0; row < rowCount; ++row )
    {
        const QRect r = drawItem( painter, d->proxyModel.index( row, 0, index ), QPoint( pos.x(), yPos ) );
        xPos = qMax( xPos, r.right() );
        yPos = qMax( yPos, r.bottom() );
    }

    return QRect( pos, QPoint( xPos, yPos ) );
}


QSize Legend::measureItem( const QModelIndex& index, bool recursive ) const
{
    if ( model() == nullptr )
        return QSize();

    QSize baseSize;
    if ( index.model() != nullptr )
    {
        QFontMetrics fm( ( index.model()->data( index, Qt::FontRole ) ).value< QFont >() );
        const QString text = index.model()->data( index, LegendRole ).toString();
        if ( !text.isEmpty() )
            baseSize += QSize( fm.boundingRect( text ).width() + fm.height() + 2, fm.height() + 2 );
    }

    if ( !recursive )
        return baseSize;

    QSize childrenSize;

    const int rowCount = d->proxyModel.rowCount( index );
    for ( int row = 0; row < rowCount; ++row )
    {
        const QSize childSize = measureItem( d->proxyModel.index( row, 0, index ) );
        childrenSize.setWidth( qMax( childrenSize.width(), childSize.width() ) );
        childrenSize.rheight() += childSize.height();
    }
    return baseSize + childrenSize;
}
