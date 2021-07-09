/*
 * SPDX-FileCopyrightText: 2018 Dag Andersen <danders@get2net.dk>
 *
 * This file is part of the KGantt library.
 * 
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#ifndef TESTKGANTTVIEW_H
#define TESTKGANTTVIEW_H

#include <QtTest>
#include <QStandardItemModel>
#include <QTreeView>

#include "kganttview.h"

namespace KGantt {
    class GraphicsScene;
}

class TestKGanttView : public QObject
{
    Q_OBJECT
private:
    QStandardItemModel *itemModel;
    KGantt::View *view;

    void initListModel();
    void initTreeModel();

private Q_SLOTS:
    void init();
    void cleanup();

    void testApi();

    // default view is a treeview
    void testDefaultView();

    void testTreeView();

    void testListView();

    void testConstraints();

    void testSetGraphicsView();

    void testSetRowController();
};
#endif
