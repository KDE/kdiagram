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

#ifndef KGANTTGRAPHICSVIEW_H
#define KGANTTGRAPHICSVIEW_H

#include <QGraphicsView>

#include "kganttglobal.h"

QT_BEGIN_NAMESPACE
class QPrinter;
class QModelIndex;
class QAbstractItemModel;
class QAbstractProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE

namespace KGantt {
    class AbstractRowController;
    class AbstractGrid;
    class GraphicsItem;
    class ConstraintModel;
    class ItemDelegate;

    class KGANTT_EXPORT GraphicsView : public QGraphicsView {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC(GraphicsView)

        Q_PROPERTY( bool readOnly READ isReadOnly WRITE setReadOnly )

        Q_PRIVATE_SLOT( d, void slotGridChanged() )
        Q_PRIVATE_SLOT( d, void slotHorizontalScrollValueChanged( int ) )
        Q_PRIVATE_SLOT( d, void slotHeaderContextMenuRequested( const QPoint& ) )
        /* slots for QAbstractItemModel signals */
        Q_PRIVATE_SLOT( d, void slotColumnsInserted( const QModelIndex& parent,  int start, int end ) )
        Q_PRIVATE_SLOT( d, void slotColumnsRemoved( const QModelIndex& parent,  int start, int end ) )
        Q_PRIVATE_SLOT( d, void slotDataChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight ) )
        Q_PRIVATE_SLOT( d, void slotLayoutChanged() )
        Q_PRIVATE_SLOT( d, void slotModelReset() )
        Q_PRIVATE_SLOT( d, void slotRowsInserted( const QModelIndex& parent,  int start, int end ) )
        Q_PRIVATE_SLOT( d, void slotRowsAboutToBeRemoved( const QModelIndex& parent,  int start, int end ) )
        Q_PRIVATE_SLOT( d, void slotRowsRemoved( const QModelIndex& parent,  int start, int end ) )

        Q_PRIVATE_SLOT( d, void slotItemClicked( const QModelIndex& idx ) )
        Q_PRIVATE_SLOT( d, void slotItemDoubleClicked( const QModelIndex& idx ) )
    public:

        explicit GraphicsView( QWidget* parent = nullptr );
        virtual ~GraphicsView();

        QAbstractItemModel* model() const;
        QAbstractProxyModel* summaryHandlingModel() const;
        ConstraintModel* constraintModel() const;
        QModelIndex rootIndex() const;
        QItemSelectionModel* selectionModel() const;
        AbstractRowController* rowController() const;
        AbstractGrid* grid() const;
        ItemDelegate* itemDelegate() const;

        bool isReadOnly() const;

        void setHeaderContextMenuPolicy( Qt::ContextMenuPolicy );
        Qt::ContextMenuPolicy headerContextMenuPolicy() const;

        QModelIndex indexAt( const QPoint& pos ) const;

        virtual void addConstraint( const QModelIndex& from,
                                    const QModelIndex& to,
                                    Qt::KeyboardModifiers modifiers );

        void updateRow( const QModelIndex& );
        void updateScene();

    public Q_SLOTS:
        void updateSceneRect();

    public:
        void deleteSubtree( const QModelIndex& );

        void print( QPrinter* printer, bool drawRowLabels = true, bool drawColumnLabels = true );
        void print( QPrinter* printer, qreal start, qreal end, bool drawRowLabels = true, bool drawColumnLabels = true );
        void print( QPainter* painter, const QRectF& target = QRectF(), bool drawRowLabels = true, bool drawColumnLabels = true );
        void print( QPainter* painter, qreal start, qreal end,
                    const QRectF& target = QRectF(), bool drawRowLabels = true, bool drawColumnLabels = true );

    public Q_SLOTS:
        void setModel( QAbstractItemModel* );
        void setSummaryHandlingModel( QAbstractProxyModel* model );
        void setConstraintModel( ConstraintModel* );
        void setRootIndex( const QModelIndex& );
        void setSelectionModel( QItemSelectionModel* );
        void setRowController( AbstractRowController* );
        void setGrid( AbstractGrid* );
        void setItemDelegate( ItemDelegate* delegate );
        void setReadOnly( bool );

    Q_SIGNALS:
        void activated( const QModelIndex & index );
        void clicked( const QModelIndex & index );
        void qrealClicked( const QModelIndex & index );
        void entered( const QModelIndex & index );
        void pressed( const QModelIndex & index );
        void headerContextMenuRequested( const QPoint& pt );

    protected:
        void clearItems();
        /*reimp*/void resizeEvent( QResizeEvent* ) Q_DECL_OVERRIDE;
    private:
        friend class View;

        GraphicsItem* createItem( ItemType type ) const;
    };
}

#endif /* KGANTTGRAPHICSVIEW_H */

