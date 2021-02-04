/*
 * Copyright (C) 2020 Dag Andersen <danders@get2net.dk>
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

#include "TestMultiItems.h"

#include "kganttglobal.h"
#include "kganttgraphicsview.h"
#include "kganttgraphicsscene.h"
#include "kganttgraphicsitem.h"
#include "kganttconstraintmodel.h"
#include "kgantttreeviewrowcontroller.h"
#include "kganttlistviewrowcontroller.h"
#include "kganttforwardingproxymodel.h"
#include "kganttitemdelegate.h"
#include "kganttdatetimegrid.h"
#include "kgantttreeviewrowcontroller.h"

#include <QListView>
#include <QTreeView>


using namespace KGantt;

void TestMultiItems::init()
{
    view = new KGantt::View();

    itemModel = new QStandardItemModel();

    view->setModel(itemModel);
    view->setConstraintModel(new KGantt::ConstraintModel());
    QCOMPARE(view->model(), itemModel);

    QCOMPARE(itemModel->rowCount(), 0);
}

void TestMultiItems::cleanup()
{
    delete view;
    delete itemModel;
}

void TestMultiItems::initMultiModel()
{
    if (itemModel->columnCount() == 0) {
        itemModel->setHorizontalHeaderLabels(QStringList()<< "Title"<<"Type"<<"Start"<<"End");
    }

    QList<QStandardItem*> items;
    QStandardItem *multi = new QStandardItem("Multi 1");
    items << multi;
    QStandardItem *item = new QStandardItem(QString::number((int)KGantt::TypeMulti));
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
    multi->appendRow(items);

    items.clear();
    item = new QStandardItem("T2");
    items << item;
    item = new QStandardItem(QString::number((int)KGantt::TypeTask));
    items << item;
    item = new QStandardItem(now.addDays(1).toString());
    items << item;
    item = new QStandardItem(now.addDays(2).toString());
    items << item;
    multi->appendRow(items);

    items.clear();
    multi = new QStandardItem("Multi 2");
    items << multi;
    item = new QStandardItem(QString::number((int)KGantt::TypeMulti));
    items << item;
    itemModel->appendRow(items);

    items.clear();
    item = new QStandardItem("T1");
    items << item;
    item = new QStandardItem(QString::number((int)KGantt::TypeTask));
    items << item;
    now = QDateTime::currentDateTime();
    item = new QStandardItem(now.toString());
    items << item;
    item = new QStandardItem(now.addDays(1).toString());
    items << item;
    multi->appendRow(items);

    items.clear();
    item = new QStandardItem("T2");
    items << item;
    item = new QStandardItem(QString::number((int)KGantt::TypeTask));
    items << item;
    item = new QStandardItem(now.addDays(1).toString());
    items << item;
    item = new QStandardItem(now.addDays(2).toString());
    items << item;
    multi->appendRow(items);
}

void TestMultiItems::testDefaultView()
{
    initMultiModel();

    QCOMPARE(itemModel->rowCount(), 2);
    QCOMPARE(view->graphicsView()->scene()->items().count(), 6);
}

void TestMultiItems::testTreeView()
{
    QTreeView *treeview = new QTreeView(view);
    view->setLeftView(treeview);
    view->setModel(itemModel); // must be set again

    initMultiModel();

    QCOMPARE(itemModel->rowCount(), 2);
    QCOMPARE(view->graphicsView()->scene()->items().count(), 6);
}

void TestMultiItems::testListView()
{
    QListView *listview = new QListView(view);
    view->setLeftView(listview);
    view->setRowController(new KGantt::ListViewRowController(listview, view->ganttProxyModel()));
    view->setModel(itemModel); // must be set again
    initMultiModel();

    QCOMPARE(itemModel->rowCount(), 2);
    QCOMPARE(view->graphicsView()->scene()->items().count(), 6);
}

void TestMultiItems::testConstraints()
{
    initMultiModel();

    ConstraintModel *model = view->constraintModel();

    QPersistentModelIndex idx1 = itemModel->index(0, 0);
    QPersistentModelIndex idx2 = itemModel->index(1, 0);

    model->addConstraint(Constraint(idx1, idx2));
    QCOMPARE(model->constraints().count(), 1);
    QVERIFY(model->hasConstraint(Constraint(idx1, idx2)));

    QCOMPARE(view->graphicsView()->scene()->items().count(), 7);

    QPersistentModelIndex idx11 = itemModel->index(0, 0, idx1);
    QPersistentModelIndex idx12 = itemModel->index(0, 0, idx2);

    // Hmmm, should this be possible?
    model->addConstraint(Constraint(idx11, idx12));
    QCOMPARE(view->graphicsView()->scene()->items().count(), 8);

    QVERIFY(itemModel->removeRows(idx1.row(), 1, idx1.parent()));
    QCOMPARE(view->graphicsView()->scene()->items().count(), 3); // constraint items also removed
    QCOMPARE(model->constraints().count(), 0); // the constraints also removed

    itemModel->clear();
    QCOMPARE(view->graphicsView()->scene()->items().count(), 0);
    initMultiModel();

    idx1 = itemModel->index(0, 0);
    idx2 = itemModel->index(1, 0);

    model->addConstraint(Constraint(idx1, idx2));
    QCOMPARE(model->constraints().count(), 1);
    QVERIFY(model->hasConstraint(Constraint(idx1, idx2)));

    // adding new items shall not affect existing constraints
    initMultiModel();
    QCOMPARE(view->graphicsView()->scene()->items().count(), 13);

    // removing items wo constraints shall not affect existing constraints
    QVERIFY(itemModel->removeRows(2, 1));
    QCOMPARE(view->graphicsView()->scene()->items().count(), 10);
}

QTEST_MAIN(TestMultiItems)
