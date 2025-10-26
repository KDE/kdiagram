/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTVIEW_P_H
#define KGANTTVIEW_P_H

#include "kganttconstraintmodel.h"
#include "kganttconstraintproxy.h"
#include "kganttgraphicsscene.h"
#include "kgantttreeviewrowcontroller.h"
#include "kganttview.h"

#include "kganttdatetimegrid.h"
#include "kganttgraphicsview.h"

#include "kganttproxymodel.h"

#include <QGraphicsView>
#include <QModelIndex>
#include <QPointer>
#include <QSplitter>
#include <QTreeView>

QT_BEGIN_NAMESPACE
class QAbstractProxyModel;
class QGraphicsView;
class QGraphicsScene;
class QGraphicsRectItem;
QT_END_NAMESPACE

namespace KGantt
{
class GraphicsItem;
class KGanttTreeView;

/*! \internal */
class KGanttTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit KGanttTreeView(QAbstractProxyModel *proxy, QWidget *parent = nullptr);
    ~KGanttTreeView() override;

    AbstractRowController *rowController()
    {
        return &m_controller;
    }

public Q_SLOTS:
    void expandAll(QModelIndex index = QModelIndex());
    void collapseAll(QModelIndex index = QModelIndex());

private:
    TreeViewRowController m_controller;
};

/*! \internal */
class Q_DECL_HIDDEN View::Private
{
public:
    explicit Private(View *);
    virtual ~Private();

    void init();

    GraphicsItem *createItem(ItemType type) const;

    void updateScene();

    void setupGraphicsView();

    // slots
    void slotCollapsed(const QModelIndex &);
    void slotExpanded(const QModelIndex &);
    void slotVerticalScrollValueChanged(int);
    void slotLeftWidgetVerticalRangeChanged(int, int);
    void slotGfxViewVerticalRangeChanged(int, int);

    View *q;

    QSplitter splitter;

    /* TODO: Refine/subclass */
    // KGanttTreeView treeview;
    QPointer<QAbstractItemView> leftWidget;
    AbstractRowController *rowController;
    QPointer<GraphicsView> gfxview;
    // KGanttHeaderWidget headerwidget;

    QPointer<QAbstractItemModel> model;
    ProxyModel ganttProxyModel;
    // KGanttTreeViewRowController rowController;
    ConstraintModel mappedConstraintModel;
    ConstraintProxy constraintProxy;
};

}
#endif /* KGANTTVIEW_P_H */
