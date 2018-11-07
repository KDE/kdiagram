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

#ifndef KGANTTVIEW_H
#define KGANTTVIEW_H

#include <QWidget>
#include <QModelIndex>
#include "kganttglobal.h"

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
class QAbstractProxyModel;
class QAbstractItemView;
class QItemSelectionModel;
class QPrinter;
class QSplitter;
QT_END_NAMESPACE

namespace KGantt {
    class ItemDelegate;
    class Constraint;
    class ConstraintModel;
    class AbstractGrid;
    class GraphicsView;
    class AbstractRowController;

    class KGANTT_EXPORT View : public QWidget {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC_QWIDGET(View)
        Q_PRIVATE_SLOT( d, void slotCollapsed(const QModelIndex&) )
        Q_PRIVATE_SLOT( d, void slotExpanded(const QModelIndex&) )
        Q_PRIVATE_SLOT( d, void slotVerticalScrollValueChanged( int ) )
        Q_PRIVATE_SLOT( d, void slotLeftWidgetVerticalRangeChanged( int, int ) )
        Q_PRIVATE_SLOT( d, void slotGfxViewVerticalRangeChanged( int, int ) )

    public:

        explicit View(QWidget* parent = nullptr);
        virtual ~View();

        QAbstractItemModel* model() const;
        QItemSelectionModel* selectionModel() const;
        ItemDelegate* itemDelegate() const;
        ConstraintModel* constraintModel() const;
        AbstractGrid* grid() const;
        QModelIndex rootIndex() const;

        QModelIndex indexAt( const QPoint& pos ) const;

        void setLeftView( QAbstractItemView* );
        const QAbstractItemView* leftView() const;
        QAbstractItemView* leftView();

        const QSplitter* splitter() const;
        QSplitter* splitter();

        void setRowController( AbstractRowController* );
        AbstractRowController* rowController();
        const AbstractRowController* rowController() const;

        void setGraphicsView( GraphicsView* );
        const GraphicsView* graphicsView() const;
        GraphicsView* graphicsView();
        const QAbstractProxyModel* ganttProxyModel() const;
        QAbstractProxyModel* ganttProxyModel();

        void ensureVisible(const QModelIndex& index);

        void print( QPrinter* printer, bool drawRowLabels=true, bool drawColumnLabels=true );
        void print( QPrinter* printer, qreal start, qreal end, bool drawRowLabels=true, bool drawColumnLabels=true );
        void print( QPainter* painter, const QRectF& target = QRectF(), bool drawRowLabels=true, bool drawColumnLabels=true);
        void print( QPainter* painter, qreal start, qreal end,
                    const QRectF& target = QRectF(), bool drawRowLabels=true, bool drawColumnLabels=true);

    public Q_SLOTS:
        void setModel(QAbstractItemModel* model);
        void setRootIndex( const QModelIndex& idx );
        void setSelectionModel( QItemSelectionModel* smodel );
        void setItemDelegate( ItemDelegate* );
        void setConstraintModel( ConstraintModel* );
        void setGrid( AbstractGrid* );
        void expandAll( QModelIndex index = QModelIndex() );
        void collapseAll( QModelIndex index = QModelIndex() );

    protected:
        /*reimp*/ void resizeEvent(QResizeEvent*) Q_DECL_OVERRIDE;
    };
}

#endif /* KGANTTVIEW_H */
