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
        explicit Legend( QWidget* parent = nullptr );
        virtual ~Legend();

        /*reimp*/ QModelIndex indexAt( const QPoint& point ) const Q_DECL_OVERRIDE;
        /*reimp*/ QRect visualRect( const QModelIndex& index ) const Q_DECL_OVERRIDE;

        /*reimp*/ void scrollTo( const QModelIndex&, ScrollHint = EnsureVisible ) Q_DECL_OVERRIDE {}

        /*reimp*/ QSize sizeHint() const Q_DECL_OVERRIDE;
        /*reimp*/ QSize minimumSizeHint() const Q_DECL_OVERRIDE;

        /*reimp*/ void setModel( QAbstractItemModel* model ) Q_DECL_OVERRIDE;

    protected:
        virtual QRect drawItem( QPainter* painter, const QModelIndex& index, const QPoint& pos = QPoint() ) const;
        virtual QSize measureItem( const QModelIndex& index, bool recursive = true ) const;
        virtual StyleOptionGanttItem getStyleOption( const QModelIndex& index ) const;

        /*reimp*/ void paintEvent( QPaintEvent* event ) Q_DECL_OVERRIDE;

        /*reimp*/ int horizontalOffset() const Q_DECL_OVERRIDE { return 0; }
        /*reimp*/ bool isIndexHidden( const QModelIndex& ) const Q_DECL_OVERRIDE { return false; }
        /*reimp*/ QModelIndex moveCursor( CursorAction, Qt::KeyboardModifiers ) Q_DECL_OVERRIDE { return QModelIndex(); }
        /*reimp*/ void setSelection( const QRect&, QItemSelectionModel::SelectionFlags ) Q_DECL_OVERRIDE {}
        /*reimp*/ int verticalOffset() const Q_DECL_OVERRIDE { return 0; }
        /*reimp*/ QRegion visualRegionForSelection( const QItemSelection& ) const Q_DECL_OVERRIDE { return QRegion(); }

    protected Q_SLOTS:
        virtual void modelDataChanged();
    };
}

#endif
