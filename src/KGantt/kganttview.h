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

#ifndef KGANTTVIEW_H
#define KGANTTVIEW_H

#include <QWidget>
#include <QModelIndex>
#include "kganttglobal.h"
#include "kganttprintingcontext.h"

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


    /*!\class KGantt::View kganttview.h KGanttView
     * \ingroup KGantt
     * \brief This widget that consists of a QTreeView and a GraphicsView
     *
     * This is the easy to use, complete gantt chart widget. It
     * consists of a QTreeView on the left and a KGantt::GraphicsView
     * on the right separated by a QSplitter. The two views share the same
     * model.
     */
    class KGANTT_EXPORT View : public QWidget {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC_QWIDGET(View)
        Q_PRIVATE_SLOT( d, void slotCollapsed(const QModelIndex&) )
        Q_PRIVATE_SLOT( d, void slotExpanded(const QModelIndex&) )
        Q_PRIVATE_SLOT( d, void slotVerticalScrollValueChanged( int ) )
        Q_PRIVATE_SLOT( d, void slotLeftWidgetVerticalRangeChanged( int, int ) )
        Q_PRIVATE_SLOT( d, void slotGfxViewVerticalRangeChanged( int, int ) )

    public:
        /*! Constructor. Creates a View with parent \a parent,
         * a DateTimeGrid as default grid implementaion and no model etc.
         */
        explicit View(QWidget* parent = nullptr);
        virtual ~View();

        /*! \returns the current model displayed by this view
         */
        QAbstractItemModel* model() const;

        /*! \returns the QItemSelectionModel used by this view
         */
        QItemSelectionModel* selectionModel() const;

        /*! \returns the ItemDelegate used by this view to render items
        */
        ItemDelegate* itemDelegate() const;

        /*! \returns the KGantt::ConstraintModel displayed by this view.
         */
        ConstraintModel* constraintModel() const;

        /*! \returns the AbstractGrid used by this view.
         */
        AbstractGrid* grid() const;

        /*! \returns the rootindex for this view.
         */
        QModelIndex rootIndex() const;

        /*!\returns The QModelIndex for the item located at
         * position \a pos in the view or an invalid index
         * if no item was present at that position.
         *
         * \see GraphicsView::indexAt
         */
        QModelIndex indexAt( const QPoint& pos ) const;



        /*! Replaces the left widget with a custom QAbstractItemView.
         *
         * \param aiv The view to be used to the left, instead of the default tree view
         * \sa setRowController()
         */
        void setLeftView( QAbstractItemView* );

        /*!
         * \returns a pointer to the QAbstractItemView in the left
         * part of the widget.
         * */
        const QAbstractItemView* leftView() const;

        /*!
         * \overload const QAbstractItemView* KGantt::View::leftView() const
         */
        QAbstractItemView* leftView();



        /*!
         * \overload const QSplitter* KGantt::View::splitter() const
         */
        const QSplitter* splitter() const;
        /*!
         * \returns a pointer to the QSplitter that manages the left view and graphicsView
         */
        QSplitter* splitter();

        /*! Sets \a ctrl to be the rowcontroller used by this View.
         * The default rowcontroller is owned by KGantt::View and is
         * suitable for the default treeview in the left part of the view.
         * You probably only want to change this if you replace the treeview.
         */
        void setRowController( AbstractRowController* );


        /*! \returns a pointer to the current rowcontroller.
         * \see AbstractRowController
         */
        AbstractRowController* rowController();
        /*! \overload AbstractRowController* KGantt::View::rowController()
         */
        const AbstractRowController* rowController() const;

        /*! Set the GraphicsView to be used for this View. It only makes sense to call this
         * if you need to subclass GraphicsView.
         *
         * NOTE: _Only_ call this right after creating the View, before setting a model or any other
         * attributes.
         */
        void setGraphicsView( GraphicsView* );

        /*!
         * \overload const GraphicsView* KGantt::View::graphicsView() const
         */
        const GraphicsView* graphicsView() const;

        /*!
         * \returns a pointer to the GraphicsView
         */
        GraphicsView* graphicsView();
        const QAbstractProxyModel* ganttProxyModel() const;
        QAbstractProxyModel* ganttProxyModel();

        void ensureVisible(const QModelIndex& index);

        /*! Print the Gantt chart using \a printer. If \a drawRowLabels
         * is true (the default), each row will have it's label printed
         * on the left side. If \a drawColumnLabels is true (the
         * default), each column will have it's label printed at the
         * top side.
         *
         * This version of print() will print multiple pages.
         */
        void print( QPrinter* printer, bool drawRowLabels=true, bool drawColumnLabels=true );

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
        void print( QPrinter* printer, qreal start, qreal end, bool drawRowLabels=true, bool drawColumnLabels=true );

        /*! Render the GanttView inside the rectangle \a target using the painter \a painter.
         * If \a drawRowLabels is true (the default), each row will have it's
         * label printed on the left side. If \a drawColumnLabels is true (the
         * default), each column will have it's label printed at the
         * top side.
         */
        void print( QPainter* painter, const QRectF& target = QRectF(), bool drawRowLabels=true, bool drawColumnLabels=true);

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
                    const QRectF& target = QRectF(), bool drawRowLabels=true, bool drawColumnLabels=true);

        /*! Print the Gantt chart on the \a printer in accordance with the PrintingContext \a context
         * 
         * \see PrintingContext
         * 
         * \since 2.8.0
         */
        void printDiagram( QPrinter *printer, const PrintingContext &context = PrintingContext() );

    public Q_SLOTS:
        /*! Sets the QAbstractItemModel to be displayed in this view
         * to \a model.
         *
         * \see GraphicsView::setModel
         */
        void setModel(QAbstractItemModel* model);

        /*! Sets the root index of the model displayed by this view.
         * Similar to QAbstractItemView::setRootIndex, default is QModelIndex().
         */
        void setRootIndex( const QModelIndex& idx );

        /*! Sets the QItemSelectionModel used by this view to manage
         * selections. Similar to QAbstractItemView::setSelectionModel
         */
        void setSelectionModel( QItemSelectionModel* smodel );

        /*! Sets the KGantt::ItemDelegate used for rendering items on this
         * view. \see ItemDelegate and QAbstractItemDelegate.
         */
        void setItemDelegate( ItemDelegate* );

        /*! Sets the constraintmodel displayed by this view.
         * \see KGantt::ConstraintModel.
         */
        void setConstraintModel( ConstraintModel* );

        /*! Sets the AbstractGrid for this view. The grid is an
         * object that controls how QModelIndexes are mapped
         * to and from the view and how the background and header
         * is rendered. \see AbstractGrid and DateTimeGrid.
         */
        void setGrid( AbstractGrid* );
        void expandAll( QModelIndex index = QModelIndex() );
        void collapseAll( QModelIndex index = QModelIndex() );

    protected:
        /*reimp*/ void resizeEvent(QResizeEvent*) override;
    };
}

#endif /* KGANTTVIEW_H */
