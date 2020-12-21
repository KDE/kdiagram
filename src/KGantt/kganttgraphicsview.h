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
    class PrintingContext;

    /*!\class KGantt::GraphicsView kganttgraphicsview.h KGanttGraphicsView
     * \ingroup KGantt
     * \brief The GraphicsView class provides a model/view implementation of a gantt chart.
     */
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
        /*! Constructor. Creates a new KGantt::GraphicsView with parent
         * \a parent.
         */
        explicit GraphicsView( QWidget* parent = nullptr );


        /*! Destroys this view. */
        virtual ~GraphicsView();

        /*! \returns the current model displayed by this view
         * 
         * Note: The returned model is not the model set with \a setModel()
         * 
         * \see GraphicsView::setModel
         */
        QAbstractItemModel* model() const;

        /*! \returns the KGantt::SummaryHandlingProxyModel used by this view.
         */
        QAbstractProxyModel* summaryHandlingModel() const;

        /*! \returns the KGantt::ConstraintModel displayed by this view.
         */
        ConstraintModel* constraintModel() const;

        /*! \returns the rootindex for this view.
         */
        QModelIndex rootIndex() const;

        /*! \returns the QItemSelectionModel used by this view
         */
        QItemSelectionModel* selectionModel() const;


        /*! \returns the AbstractRowController
         * for this view. \see setRowController
         */
        AbstractRowController* rowController() const;

        /*! \returns the AbstractGrid used by this view.
         */
        AbstractGrid* grid() const;

        /*! \returns the AbstractGrid used by this view.
         */
        AbstractGrid* takeGrid();

        /*! \returns the ItemDelegate used by this view to render items
        */
        ItemDelegate* itemDelegate() const;

        /*!\returns true if the view is in read-only mode
         */
        bool isReadOnly() const;

        /*! Sets the context menu policy for the header. The default value
         * Qt::DefaultContextMenu results in a standard context menu on the header
         * that allows the user to set the scale and zoom.
         *
         * Setting this to Qt::CustomContextMenu will cause the signal
         * headerContextMenuRequested(const QPoint& pt) to be emitted instead.
         *
         * \see QWidget::setContextMenuPolicy( Qt::ContextMenuPolicy )
         */
        void setHeaderContextMenuPolicy( Qt::ContextMenuPolicy );

        /*! \returns the context menu policy for the header
         */
        Qt::ContextMenuPolicy headerContextMenuPolicy() const;

        /*!\returns The QModelIndex for the item located at
         * position \a pos in the view or an invalid index
         * if no item was present at that position.
         *
         * This is useful for for example contextmenus.
         */
        QModelIndex indexAt( const QPoint& pos ) const;

        /*! Adds a constraint from \a from to \a to. \a modifiers are the
         * keyboard modifiers pressed by the user when the action is invoked.
         *
         * Override this to control how contraints are added. The default
         * implementation adds a soft constraint unless the Shift key is pressed,
         * in that case it adds a hard constraint. If a constraint is already
         * present, it is removed and nothing is added.
         */
        virtual void addConstraint( const QModelIndex& from,
                                    const QModelIndex& to,
                                    Qt::KeyboardModifiers modifiers );


        /*! \internal */
        void updateRow( const QModelIndex& );

        /*! \internal
         * Resets the state of the view.
         */
        void updateScene();

#if 0
        TODO: For 3.0


        /*! Creates a new GraphicsItem
         * Re-iplement to create your own flavour of GraphicsItem
         */
        virtual GraphicsItem* createItem( ItemType type ) const;
#endif

    public Q_SLOTS:
        /*! \internal
         * Adjusts the bounding rectangle of the scene.
         */
        void updateSceneRect();

    public:
        /*! \internal */
        void deleteSubtree( const QModelIndex& );

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
        void print( QPainter* painter, const QRectF& target = QRectF(), bool drawRowLabels = true, bool drawColumnLabels = true );

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
        void print( QPainter* painter, qreal start, qreal end,
                    const QRectF& target = QRectF(), bool drawRowLabels = true, bool drawColumnLabels = true );

        /*! Print the Gantt chart on the \a printer in accordance with the PrintingContext \a context
         * 
         * \see PrintingContext
         * 
         * \since 2.8.0
         */
        void printDiagram( QPrinter *printer, const PrintingContext &context );

    public Q_SLOTS:
        /*! Sets the model to be displayed in this view to
         * \a model. The view does not take ownership of the model.
         *
         * To make a model work well with GraphicsView it must
         * have a certain layout. Whether the model is flat or has a
         * treestrucure is not important, as long as an
         * AbstractRowController is provided that can navigate the
         * model.
         *
         * GraphicsView operates per row in the model. The data is always
         * taken from the _last_ item in the row. The ItemRoles used are
         * Qt::DisplayRole and the roles defined in KGantt::ItemDataRole.
         * 
         * Note: This model is not returned by \a model()
         * 
         * \see GraphicsView::model
         */
        void setModel( QAbstractItemModel* );
        void setSummaryHandlingModel( QAbstractProxyModel* model );

        /*! Sets the constraintmodel displayed by this view.
         * \see KGantt::ConstraintModel.
         */
        void setConstraintModel( ConstraintModel* );

        /*! Sets the root index of the model displayed by this view.
         * Similar to QAbstractItemView::setRootIndex, default is QModelIndex().
         */
        void setRootIndex( const QModelIndex& );

        /*! Sets the QItemSelectionModel used by this view to manage
         * selections. Similar to QAbstractItemView::setSelectionModel
         */
        void setSelectionModel( QItemSelectionModel* );

        /*! Sets the AbstractRowController used by this view. The
         * AbstractRowController deals with the height and position
         * of each row and with which parts of the model are
         * displayed. \see AbstractRowController
         */
        void setRowController( AbstractRowController* );

        /*! Sets the AbstractGrid for this view. The grid is an
         * object that controls how QModelIndexes are mapped
         * to and from the view and how the background and header
         * is rendered. \see AbstractGrid and DateTimeGrid.
         */
        void setGrid( AbstractGrid* );

        /*! Sets the KGantt::ItemDelegate used for rendering items on this
         * view. \see ItemDelegate and QAbstractItemDelegate.
         */
        void setItemDelegate( ItemDelegate* delegate );

        /*! Sets the view to read-only mode if \a to is true. The default is
         * read/write if the model permits it.
         */
        void setReadOnly( bool );

    Q_SIGNALS:
        /*! \fn void GraphicsView::activated( const QModelIndex & index ) */
        void activated( const QModelIndex & index );

        /*! \fn void GraphicsView::clicked( const QModelIndex & index ); */
        void clicked( const QModelIndex & index );

        /*! \fn void GraphicsView::qrealClicked( const QModelIndex & index ); */
        void qrealClicked( const QModelIndex & index );

        /*! \fn void GraphicsView::entered( const QModelIndex & index ); */
        void entered( const QModelIndex & index );

        /*! \fn void GraphicsView::pressed( const QModelIndex & index ); */
        void pressed( const QModelIndex & index );

        /*! \fn void GraphicsView::headerContextMenuRequested( const QPoint& pt )
         * This signal is emitted when the header has contextMenuPolicy Qt::CustomContextMenu
         * and the widget wants to show a context menu for the header. Unlike in
         * QWidget::customContextMenuRequested() signal, \a pt is here in global coordinates.
         */
        void headerContextMenuRequested( const QPoint& pt );

    protected:
        /*! \internal */
        void clearItems();
        /*reimp*/void resizeEvent( QResizeEvent* ) override;
    private:
        friend class View;
    };
}

#endif /* KGANTTGRAPHICSVIEW_H */

