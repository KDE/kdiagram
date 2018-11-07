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

#ifndef KGANTTGRAPHICSSCENE_H
#define KGANTTGRAPHICSSCENE_H

#include <QDateTime>
#include <QList>
#include <QGraphicsScene>
#include <QModelIndex>

#include "kganttglobal.h"

QT_BEGIN_NAMESPACE
class QAbstractProxyModel;
class QItemSelectionModel;
class QPrinter;
QT_END_NAMESPACE

namespace KGantt {
    class AbstractGrid;
    class AbstractRowController;
    class GraphicsItem;
    class Constraint;
    class ConstraintModel;
    class ConstraintGraphicsItem;
    class ItemDelegate;

    class KGANTT_EXPORT GraphicsScene : public QGraphicsScene {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( GraphicsScene )
    public:
        explicit GraphicsScene( QObject* parent = nullptr );
        virtual ~GraphicsScene();

        //qreal dateTimeToSceneX( const QDateTime& dt ) const;
        //QDateTime sceneXtoDateTime( qreal x ) const;

        static QModelIndex mainIndex( const QModelIndex& idx );
        static QModelIndex dataIndex( const QModelIndex& idx );

        QAbstractItemModel* model() const;
        QAbstractProxyModel* summaryHandlingModel() const;
        QModelIndex rootIndex() const;
        ConstraintModel* constraintModel() const;
        QItemSelectionModel* selectionModel() const;

        void insertItem( const QPersistentModelIndex&, GraphicsItem* );
        void removeItem( const QModelIndex& );
        using QGraphicsScene::removeItem;
        GraphicsItem* findItem( const QModelIndex& ) const;
        GraphicsItem* findItem( const QPersistentModelIndex& ) const;

        void updateItems();
        void clearItems();
        void deleteSubtree( const QModelIndex& );

        ConstraintGraphicsItem* findConstraintItem( const Constraint& ) const;
        QList<ConstraintGraphicsItem*> findConstraintItems( const QModelIndex& idx ) const;

        void setItemDelegate( ItemDelegate* );
        ItemDelegate* itemDelegate() const;

        void setRowController( AbstractRowController* rc );
        AbstractRowController* rowController() const;

        void setGrid( AbstractGrid* grid );
        AbstractGrid* grid() const;

        bool isReadOnly() const;

        void updateRow( const QModelIndex& idx );
        GraphicsItem* createItem( ItemType type ) const;

        /* used by GraphicsItem */
        void itemEntered( const QModelIndex& );
        void itemPressed( const QModelIndex& );
        void itemClicked( const QModelIndex& );
        void itemDoubleClicked( const QModelIndex& );
        void setDragSource( GraphicsItem* item );
        GraphicsItem* dragSource() const;

        /* Printing */
        void print( QPrinter* printer, bool drawRowLabels = true, bool drawColumnLabels = true );
        void print( QPrinter* printer, qreal start, qreal end, bool drawRowLabels = true, bool drawColumnLabels = true );
        void print( QPainter* painter, const QRectF& target = QRectF(), bool drawRowLabels=true, bool drawColumnLabels = true );
        void print( QPainter* painter, qreal start, qreal end, const QRectF& target = QRectF(), bool drawRowLabels=true, bool drawColumnLabels = true );

    Q_SIGNALS:
        void gridChanged();

        void clicked( const QModelIndex & index );
        void qrealClicked( const QModelIndex & index );
        void entered( const QModelIndex & index );
        void pressed( const QModelIndex & index );

    protected:
        /*reimp*/ void helpEvent( QGraphicsSceneHelpEvent *helpEvent ) Q_DECL_OVERRIDE;
        /*reimp*/ void drawBackground( QPainter* painter, const QRectF& rect ) Q_DECL_OVERRIDE;
        /*reimp*/ void drawForeground( QPainter* painter, const QRectF& rect ) Q_DECL_OVERRIDE;

    public Q_SLOTS:
        void setModel( QAbstractItemModel* );
        void setSummaryHandlingModel( QAbstractProxyModel* );
        void setConstraintModel( ConstraintModel* );
        void setRootIndex( const QModelIndex& idx );
        void setSelectionModel( QItemSelectionModel* selectionmodel );
        void setReadOnly( bool );

    private Q_SLOTS:
        /* slots for ConstraintModel */
        void slotConstraintAdded( const KGantt::Constraint& );
        void slotConstraintRemoved( const KGantt::Constraint& );
        void slotGridChanged();
    private:
        void doPrint( QPainter* painter, const QRectF& targetRect,
                      qreal start, qreal end,
                      QPrinter* printer, bool drawRowLabels, bool drawColumnLabels );
    };
}

#endif /* KGANTTGRAPHICSSCENE_H */
