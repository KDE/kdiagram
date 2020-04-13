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

#include "TestKGanttConstraintModel.h"

#include "kganttglobal.h"
#include <kganttconstraintmodel.h>


using namespace KGantt;

void TestKGanttConstraintModel::initTestCase()
{
    itemModel = new QStandardItemModel(100, 100);
}

void TestKGanttConstraintModel::cleanupTestCase()
{
    delete itemModel;
}

void TestKGanttConstraintModel::testModel()
{
    ConstraintModel model;
    
    QCOMPARE(model.constraints().count(), 0);
    
    model.addConstraint(Constraint(QModelIndex(), QModelIndex()));
    QCOMPARE(model.constraints().count(), 1);
    
    model.addConstraint(Constraint(QModelIndex(), QModelIndex()));
    QCOMPARE(model.constraints().count(), 1);
    
    QPersistentModelIndex idx1 = itemModel->index(7, 17, QModelIndex());
    QPersistentModelIndex idx2 = itemModel->index(42, 17, QModelIndex());
    
    model.addConstraint(Constraint(idx1, idx2));
    QCOMPARE(model.constraints().count(), 2);
    QVERIFY(model.hasConstraint(Constraint(idx1, idx2)));
    
    QCOMPARE(model.constraintsForIndex(QModelIndex()).count(), 1);
    
    QCOMPARE(model.constraints().count(), 2);
    model.removeConstraint(Constraint(QModelIndex(), QModelIndex()));
    QCOMPARE(model.constraints().count(), 1);
    QVERIFY(!model.hasConstraint(Constraint(QModelIndex(), QModelIndex())));
    
    model.removeConstraint(Constraint(QModelIndex(), QModelIndex()));
    QCOMPARE(model.constraints().count(), 1);
    
    model.removeConstraint(Constraint(idx1, idx2));
    QCOMPARE(model.constraints().count(), 0);
    QVERIFY(!model.hasConstraint(Constraint(idx1, idx2)));
    
    model.addConstraint(Constraint(idx1, idx2));
    QVERIFY(model.hasConstraint(Constraint(idx1, idx2)));
    itemModel->removeRow(8);
    QVERIFY(idx2 == itemModel->index(41, 17, QModelIndex()));
    QVERIFY(model.hasConstraint(Constraint(idx1, idx2)));
    itemModel->removeRow(7);
    QVERIFY(!idx1.isValid());
    QVERIFY(idx2 == itemModel->index(40, 17, QModelIndex()));
    QVERIFY(model.hasConstraint(Constraint(idx1, idx2)));
}

QTEST_GUILESS_MAIN(TestKGanttConstraintModel)
