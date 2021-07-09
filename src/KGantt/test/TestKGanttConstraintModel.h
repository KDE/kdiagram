/*
 * SPDX-FileCopyrightText: 2018 Dag Andersen <danders@get2net.dk>
 *
 * This file is part of the KGantt library.
 * 
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#ifndef TESTKGANTTCONSTRAINTMODEL_H
#define TESTKGANTTCONSTRAINTMODEL_H

#include <QtTest>
#include <QStandardItemModel>


class TestKGanttConstraintModel : public QObject
{
    Q_OBJECT
private:
    QStandardItemModel *itemModel;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testModel();
};
#endif
