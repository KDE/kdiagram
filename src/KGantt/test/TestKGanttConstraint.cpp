/*
 * SPDX-FileCopyrightText: 2018 Dag Andersen <danders@get2net.dk>
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "TestKGanttConstraint.h"

#include "kganttglobal.h"
#include <kganttconstraint.h>

#include <QModelIndex>
#include <QString>

using namespace KGantt;

void TestKGanttConstraint::initTestCase()
{
}

void TestKGanttConstraint::cleanupTestCase()
{
}

void TestKGanttConstraint::test()
{
    Constraint c1;
    QVERIFY(!c1.startIndex().isValid());
    QVERIFY(!c1.endIndex().isValid());

    QCOMPARE(c1.type(), Constraint::TypeSoft);
    QCOMPARE(c1.relationType(), Constraint::FinishStart);
    QVERIFY(c1.dataMap().isEmpty());

    Constraint c2;
    QCOMPARE(c1, c2);
    QVERIFY(c1.compareIndexes(c2));

    Constraint c3(QModelIndex(), QModelIndex(), Constraint::TypeHard);
    QCOMPARE(c3.type(), Constraint::TypeHard);
    QVERIFY(c1 != c3);
    QVERIFY(c1.compareIndexes(c3));

    Constraint c4(QModelIndex(), QModelIndex(), Constraint::TypeSoft, Constraint::StartFinish);
    QCOMPARE(c4.relationType(), Constraint::StartFinish);
    QVERIFY(c1 != c4);
    QVERIFY(c1.compareIndexes(c4));

    Constraint c5 = c4;
    QCOMPARE(c1, c2);
    QVERIFY(c1.compareIndexes(c2));

    c5.setData(1, 2);
    QCOMPARE(c5.data(1).toInt(), 2);
    QVERIFY(c5 != c4);
    QVERIFY(c5.compareIndexes(c4));
    c5.setDataMap(QMap<int, QVariant>());
    QVERIFY(c5 == c4);
    QMap<int, QVariant> map;
    map.insert(1, 2);
    c5.setDataMap(map);
    QCOMPARE(c5.data(1).toInt(), 2);
    QVERIFY(c5 != c4);
}

QTEST_GUILESS_MAIN(TestKGanttConstraint)
