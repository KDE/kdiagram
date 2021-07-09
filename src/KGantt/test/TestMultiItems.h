/*
 * SPDX-FileCopyrightText: 2020 Dag Andersen <danders@get2net.dk>
 *
 * This file is part of the KGantt library.
 * 
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#ifndef TESTMULTIITEMS_H
#define TESTMULTIITEMS_H

#include <QtTest>
#include <QStandardItemModel>
#include <QTreeView>

#include "kganttview.h"

class TestMultiItems : public QObject
{
    Q_OBJECT
private:
    QStandardItemModel *itemModel;
    KGantt::View *view;

    void initMultiModel();

private Q_SLOTS:
    void init();
    void cleanup();

    // default view is a treeview
    void testDefaultView();

    void testTreeView();

    void testListView();

    void testConstraints();
};
#endif
