/**
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KD Chart library.
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

#ifndef KDGANTTVIEW_P_H
#define KDGANTTVIEW_P_H

#include "kdganttview.h"
#include "kdganttgraphicsscene.h"
#include "kdgantttreeviewrowcontroller.h"
#include "kdganttconstraintmodel.h"
#include "kdganttconstraintproxy.h"

#include "kdganttgraphicsview.h"
#include "kdganttdatetimegrid.h"

#include "kdganttproxymodel.h"

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

namespace KDGantt {
    class GraphicsItem;
    class KDGanttTreeView;

    /*! \internal */
    class KDGanttTreeView : public QTreeView {
        Q_OBJECT
    public:
        explicit KDGanttTreeView( QAbstractProxyModel* proxy, QWidget* parent=0 );
        virtual ~KDGanttTreeView();

        AbstractRowController* rowController() { return &m_controller; }

    public Q_SLOTS:
        void expandAll(QModelIndex index = QModelIndex());
        void collapseAll(QModelIndex index = QModelIndex());

    private:
        TreeViewRowController m_controller;
    };

    /*! \internal */
    class View::Private {
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
        //KDGanttTreeView treeview;
        QPointer<QAbstractItemView> leftWidget;
        AbstractRowController* rowController;
        QPointer<GraphicsView> gfxview;
        //KDGanttHeaderWidget headerwidget;

        QPointer<QAbstractItemModel> model;
        ProxyModel ganttProxyModel;
        //KDGanttTreeViewRowController rowController;
        ConstraintModel mappedConstraintModel;
        ConstraintProxy constraintProxy;
    };

}
#endif /* KDGANTTVIEW_P_H */

