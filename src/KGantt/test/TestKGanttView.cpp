/*
 * Copyright (C) 2018 Dag Andersen <danders@get2net.dk>
 *
 * This file is part of the KGantt library.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * 
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#undef QT_NO_CAST_FROM_ASCII

#include "TestKGanttView.h"

#include "kganttglobal.h"
#include "kganttgraphicsview.h"
#include "kganttgraphicsitem.h"
#include "kganttconstraintmodel.h"
#include "kgantttreeviewrowcontroller.h"
#include "kganttlistviewrowcontroller.h"

#include <QListView>


using namespace KGantt;

void TestKGanttView::init()
{
    view = new KGantt::View();

    itemModel = new QStandardItemModel();
 
    view->setModel(itemModel);
    view->setConstraintModel(new KGantt::ConstraintModel());
    QCOMPARE(view->model(), itemModel);

    QCOMPARE(itemModel->rowCount(), 0);
}

void TestKGanttView::cleanup()
{
    delete view;
    delete itemModel;
}

void TestKGanttView::initTreeModel()
{
    if (itemModel->columnCount() == 0) {
        itemModel->setHorizontalHeaderLabels(QStringList()<< "Title"<<"Type"<<"Start"<<"End");
    }

    QList<QStandardItem*> items;
    QStandardItem *sum = new QStandardItem("Summary 1");
    items << sum;
    QStandardItem *item = new QStandardItem(QString::number((int)KGantt::TypeSummary));
    items << item;
    itemModel->appendRow(items);
    
    items.clear();
    item = new QStandardItem("T1");
    items << item;
    item = new QStandardItem(QString::number((int)KGantt::TypeTask));
    items << item;
    QDateTime now = QDateTime::currentDateTime();
    item = new QStandardItem(now.toString());
    items << item;
    item = new QStandardItem(now.addDays(1).toString());
    items << item;
    sum->appendRow(items);
    
    items.clear();
    item = new QStandardItem("T2");
    items << item;
    item = new QStandardItem(QString::number((int)KGantt::TypeTask));
    items << item;
    item = new QStandardItem(now.addDays(1).toString());
    items << item;
    item = new QStandardItem(now.addDays(2).toString());
    items << item;
    sum->appendRow(items);
    
}

void TestKGanttView::testDefaultView()
{
    initTreeModel();

    QCOMPARE(itemModel->rowCount(), 1);
    QCOMPARE(view->graphicsView()->scene()->items().count(), 1);
    view->expandAll();
    QCOMPARE(view->graphicsView()->scene()->items().count(), 3);
    view->collapseAll();
    QCOMPARE(view->graphicsView()->scene()->items().count(), 1);
    
}

void TestKGanttView::testTreeView()
{
    QTreeView *treeview = new QTreeView(view);
    view->setLeftView(treeview);
    view->setModel(itemModel); // must be set again
    
    initTreeModel();

    QCOMPARE(itemModel->rowCount(), 1);
    QCOMPARE(view->graphicsView()->scene()->items().count(), 1);
    view->expandAll();
    QEXPECT_FAIL("", "expandAll() only works with the default treeview", Continue);
    QCOMPARE(view->graphicsView()->scene()->items().count(), 3);
    view->collapseAll();
    QCOMPARE(view->graphicsView()->scene()->items().count(), 1);

    treeview->expandAll();
    QCOMPARE(view->graphicsView()->scene()->items().count(), 3);
    treeview->collapseAll();
    QCOMPARE(view->graphicsView()->scene()->items().count(), 1);
}

void TestKGanttView::initListModel()
{
    QList<QStandardItem*> items;
    QStandardItem *item = new QStandardItem("T1");
    items << item;
    item = new QStandardItem(QString::number((int)KGantt::TypeTask));
    items << item;
    QDateTime now = QDateTime::currentDateTime();
    item = new QStandardItem(now.toString());
    items << item;
    item = new QStandardItem(now.addDays(1).toString());
    items << item;
    itemModel->appendRow(items);
    
    QCOMPARE(view->graphicsView()->scene()->items().count(), 1);
    
    items.clear();
    item = new QStandardItem("T2");
    items << item;
    item = new QStandardItem(QString::number((int)KGantt::TypeTask));
    items << item;
    item = new QStandardItem(now.addDays(1).toString());
    items << item;
    item = new QStandardItem(now.addDays(2).toString());
    items << item;
    itemModel->appendRow(items);
}

void TestKGanttView::testListView()
{
    QListView *listview = new QListView(view);
    view->setLeftView(listview);
    view->setRowController(new KGantt::ListViewRowController(listview, view->ganttProxyModel()));
    view->setModel(itemModel); // must be set again
    initListModel();
}

void TestKGanttView::testConstraints()
{
    initTreeModel();

    ConstraintModel *model = view->constraintModel();
    
    QPersistentModelIndex idx1 = itemModel->index(0, 0, itemModel->index(0, 0));
    QPersistentModelIndex idx2 = itemModel->index(1, 0, itemModel->index(0, 0));

    model->addConstraint(Constraint(idx1, idx2));
    QCOMPARE(model->constraints().count(), 1);
    QVERIFY(model->hasConstraint(Constraint(idx1, idx2)));
    
    QCOMPARE(view->graphicsView()->scene()->items().count(), 1);
    view->expandAll();
    QCOMPARE(view->graphicsView()->scene()->items().count(), 4);
    view->collapseAll();
    QCOMPARE(view->graphicsView()->scene()->items().count(), 1); // constraint item also removed
    QCOMPARE(model->constraints().count(), 1); // the constraint is not removed

    view->expandAll();
    model->removeConstraint(model->constraints().first());
    QCOMPARE(view->graphicsView()->scene()->items().count(), 3); // constraint item also removed
    QCOMPARE(model->constraints().count(), 0); // the constraint is removed

    model->addConstraint(Constraint(idx1, idx2));
    QCOMPARE(view->graphicsView()->scene()->items().count(), 4);

    QVERIFY(itemModel->removeRows(idx1.row(), 1, idx1.parent()));
    QCOMPARE(view->graphicsView()->scene()->items().count(), 2); // constraint item also removed
    QCOMPARE(model->constraints().count(), 0); // the constraint is also removed

    itemModel->clear();
    QCOMPARE(view->graphicsView()->scene()->items().count(), 0);
    initTreeModel();

    idx1 = itemModel->index(0, 0, itemModel->index(0, 0));
    idx2 = itemModel->index(1, 0, itemModel->index(0, 0));
    
    model->addConstraint(Constraint(idx1, idx2));
    QCOMPARE(model->constraints().count(), 1);
    QVERIFY(model->hasConstraint(Constraint(idx1, idx2)));

    // adding new items shall not affect existing constraints
    initTreeModel(); // add more items, will also collapseAll()
    QCOMPARE(view->graphicsView()->scene()->items().count(), 2);
    view->expandAll();
    QCOMPARE(view->graphicsView()->scene()->items().count(), 7);

    // removing items wo constraints shall not affect existing constraints
    QVERIFY(itemModel->removeRows(0, 1, itemModel->index(1, 0)));
    QCOMPARE(view->graphicsView()->scene()->items().count(), 6);

    // must be possible to add constraints between items with different parent
    QPersistentModelIndex idx3 = itemModel->index(0, 0, itemModel->index(1, 0));
    
    model->addConstraint(Constraint(idx2, idx3));
    QCOMPARE(model->constraints().count(), 2);
    QVERIFY(model->hasConstraint(Constraint(idx2, idx3)));
    QCOMPARE(view->graphicsView()->scene()->items().count(), 7);

    // removing summary item shall also remove child item + any constraints to the child item
    QVERIFY(itemModel->removeRows(1, 1));
    QCOMPARE(model->constraints().count(), 1);
    QCOMPARE(view->graphicsView()->scene()->items().count(), 4);
    
}

QTEST_MAIN(TestKGanttView)
