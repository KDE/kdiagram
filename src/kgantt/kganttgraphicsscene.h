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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
class QItemSelection;
class QPrinter;
class QAbstractItemModel;


/*!\class KGantt::GraphicsScene
 * \internal
 */
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

namespace KGantt {
    class AbstractGrid;
    class AbstractRowController;
    class GraphicsItem;
    class Constraint;
    class ConstraintModel;
    class ConstraintGraphicsItem;
    class ItemDelegate;
    class PrintingContext;

    class KGANTT_EXPORT GraphicsScene : public QGraphicsScene {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( GraphicsScene )
    public:
        explicit GraphicsScene( QObject* parent = nullptr );
        virtual ~GraphicsScene();

        //qreal dateTimeToSceneX( const QDateTime& dt ) const;
        //QDateTime sceneXtoDateTime( qreal x ) const;

        static QModelIndex mainIndex( const QModelIndex& idx );

        /*! Returns the index pointing to the last column
         * in the same row as idx. This can be thought of
         * as in "inverse" of mainIndex()
         */
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

        /**
         * Set the grid to @p grid.
         * The current grid (if set) is deleted.
         * If @p grid is nullptr, the scene reverts to use the default_grid
         */
        void setGrid( AbstractGrid* grid );
        /**
         * @return the grid set with setGrid().
         * Note: Returns nullptr if no grid has been set.
         */
        AbstractGrid* grid() const;
        /**
         * @return the current grid.
         */
        const AbstractGrid *getGrid() const;
        /**
         * @return the grid set with setGrid()
         * Note: Returns nullptr if no grid has been set.
         * The scene reverts to use the default_grid.
         */
        AbstractGrid *takeGrid();

        bool isReadOnly() const;

        void updateRow( const QModelIndex& idx );

        /*! Creates a new item of type type.
         */
        GraphicsItem* createItem( ItemType type ) const;

        /* used by GraphicsItem */
        void itemEntered( const QModelIndex& );
        void itemPressed( const QModelIndex& idx, QGraphicsSceneMouseEvent *event );
        void itemClicked( const QModelIndex& );
        void itemDoubleClicked( const QModelIndex& );
        void setDragSource( GraphicsItem* item );
        GraphicsItem* dragSource() const;

        /* Printing */

        /*! Print the Gantt chart using \a printer. If \a drawRowLabels
         * is true (the default), each row will have it's label printed
         * on the left side. If \a drawColumnLabels is true (the
         * default), each column will have it's label printed at the
         * top side.
         *
         * This version of print() will print multiple pages.
         */
        void print( QPrinter* printer, bool drawRowLabels = true, bool drawColumnLabels = true );

        /*! Print part of the Gantt chart from \a start to \a end using \a printer.
         * If \a drawRowLabels is true (the default), each row will have it's
         * label printed on the left side. If \a drawColumnLabels is true (the
         * default), each column will have it's label printed at the
         * top side.
         *
         * This version of print() will print multiple pages.
         *
         * To print a certain range of a chart with a DateTimeGrid, use
         * qreal DateTimeGrid::mapFromDateTime( const QDateTime& dt) const
         * to figure out the values for \a start and \a end.
         */
        void print( QPrinter* printer, qreal start, qreal end, bool drawRowLabels = true, bool drawColumnLabels = true );

        /*! Render the GanttView inside the rectangle \a target using the painter \a painter.
         * If \a drawRowLabels is true (the default), each row will have it's
         * label printed on the left side. If \a drawColumnLabels is true (the
         * default), each column will have it's label printed at the
         * top side.
         */
        void print( QPainter* painter, const QRectF& target = QRectF(), bool drawRowLabels=true, bool drawColumnLabels = true );

        /*! Render the GanttView inside the rectangle \a target using the painter \a painter.
         * If \a drawRowLabels is true (the default), each row will have it's
         * label printed on the left side. If \a drawColumnLabels is true (the
         * default), each column will have it's label printed at the
         * top side.
         *
         * To print a certain range of a chart with a DateTimeGrid, use
         * qreal DateTimeGrid::mapFromDateTime( const QDateTime& dt) const
         * to figure out the values for \a start and \a end.
         */
        void print( QPainter* painter, qreal start, qreal end, const QRectF& target = QRectF(), bool drawRowLabels=true, bool drawColumnLabels = true );

        /*! Print the Gantt chart on the \a printer in accordance with the PrintingContext \a context
         * 
         * \see PrintingContext
         * 
         * \since 2.8.0
         */
        void printDiagram( QPrinter *printer, const PrintingContext &context );

    Q_SIGNALS:
        void gridChanged();

        void clicked( const QModelIndex & index );
        void qrealClicked( const QModelIndex & index );
        void entered( const QModelIndex & index );
        void pressed( const QModelIndex & index );

    protected:
        /*reimp*/ void helpEvent( QGraphicsSceneHelpEvent *helpEvent ) override;
        /*reimp*/ void drawBackground( QPainter* painter, const QRectF& rect ) override;
        /*reimp*/ void drawForeground( QPainter* painter, const QRectF& rect ) override;

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
        void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
        void selectionModelChanged(QAbstractItemModel *);

    private:
        /*\internal
         */
        void doPrint( QPainter* painter, const QRectF& targetRect,
                      qreal start, qreal end,
                      QPrinter* printer, bool drawRowLabels, bool drawColumnLabels );

        void doPrintScene( QPrinter *printer, QPainter *painter, const QRectF& targetRect, const PrintingContext &context );

        void drawLabelsHeader( QPainter *painter, const QRectF &sourceRect, const QRectF &targetRect );
    };
}

#endif /* KGANTTGRAPHICSSCENE_H */
