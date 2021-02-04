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
