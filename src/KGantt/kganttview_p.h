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

#ifndef KGANTTVIEW_P_H
#define KGANTTVIEW_P_H

#include "kganttview.h"
#include "kganttgraphicsscene.h"
#include "kgantttreeviewrowcontroller.h"
#include "kganttconstraintmodel.h"
#include "kganttconstraintproxy.h"

#include "kganttgraphicsview.h"
#include "kganttdatetimegrid.h"

#include "kganttproxymodel.h"

#include <QSplitter>
#include <QTreeView>
#include <QGraphicsView>
#include <QModelIndex>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QAbstractProxyModel;
class QGraphicsView;
class QGraphicsScene;
class QGraphicsRectItem;
QT_END_NAMESPACE

namespace KGantt {
    class GraphicsItem;
    class KGanttTreeView;

    /*! \internal */
    class KGanttTreeView : public QTreeView {
        Q_OBJECT
    public:
        explicit KGanttTreeView( QAbstractProxyModel* proxy, QWidget* parent = nullptr );
        virtual ~KGanttTreeView();

        AbstractRowController* rowController() { return &m_controller; }

    public Q_SLOTS:
        void expandAll(QModelIndex index = QModelIndex());
        void collapseAll(QModelIndex index = QModelIndex());

    private:
        TreeViewRowController m_controller;
    };

    /*! \internal */
    class Q_DECL_HIDDEN View::Private {
    public:
        explicit Private(View*);
        virtual ~Private();

        void init();

        GraphicsItem* createItem( ItemType type ) const;

        void updateScene();

        void setupGraphicsView();

        // slots
        void slotCollapsed(const QModelIndex&);
        void slotExpanded(const QModelIndex&);
        void slotVerticalScrollValueChanged( int );
        void slotLeftWidgetVerticalRangeChanged( int, int );
        void slotGfxViewVerticalRangeChanged( int, int );

        View* q;

        QSplitter splitter;

        /* TODO: Refine/subclass */
        //KGanttTreeView treeview;
        QPointer<QAbstractItemView> leftWidget;
        AbstractRowController* rowController;
        QPointer<GraphicsView> gfxview;
        //KGanttHeaderWidget headerwidget;

        QPointer<QAbstractItemModel> model;
        ProxyModel ganttProxyModel;
        //KGanttTreeViewRowController rowController;
        ConstraintModel mappedConstraintModel;
        ConstraintProxy constraintProxy;
    };

}
#endif /* KGANTTVIEW_P_H */

