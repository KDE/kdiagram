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

#ifndef KGANTTLEGEND_H
#define KGANTTLEGEND_H

#include <QAbstractItemView>

#include "kganttglobal.h"
#include "kganttstyleoptionganttitem.h"

namespace KGantt 
{
    class KGANTT_EXPORT Legend : public QAbstractItemView
    {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( Legend )
    public:
        explicit Legend( QWidget* parent = 0 );
        virtual ~Legend();

        /*reimp*/ QModelIndex indexAt( const QPoint& point ) const;
        /*reimp*/ QRect visualRect( const QModelIndex& index ) const;

        /*reimp*/ void scrollTo( const QModelIndex&, ScrollHint = EnsureVisible ) {}

        /*reimp*/ QSize sizeHint() const;
        /*reimp*/ QSize minimumSizeHint() const;

        /*reimp*/ void setModel( QAbstractItemModel* model );

    protected:
        virtual QRect drawItem( QPainter* painter, const QModelIndex& index, const QPoint& pos = QPoint() ) const;
        virtual QSize measureItem( const QModelIndex& index, bool recursive = true ) const;
        virtual StyleOptionGanttItem getStyleOption( const QModelIndex& index ) const;

        /*reimp*/ void paintEvent( QPaintEvent* event );

        /*reimp*/ int horizontalOffset() const { return 0; }
        /*reimp*/ bool isIndexHidden( const QModelIndex& ) const { return false; }
        /*reimp*/ QModelIndex moveCursor( CursorAction, Qt::KeyboardModifiers ) { return QModelIndex(); }
        /*reimp*/ void setSelection( const QRect&, QItemSelectionModel::SelectionFlags ) {}
        /*reimp*/ int verticalOffset() const { return 0; }
        /*reimp*/ QRegion visualRegionForSelection( const QItemSelection& ) const { return QRegion(); }

    protected Q_SLOTS:
        virtual void modelDataChanged();
    };
}

#endif
