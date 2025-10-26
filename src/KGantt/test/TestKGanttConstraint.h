/*
 * SPDX-FileCopyrightText: 2018 Dag Andersen <danders@get2net.dk>
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#ifndef TESTGANTTCONSTRAINT_H
#define TESTGANTTCONSTRAINT_H

#include <QtTest>

class TestKGanttConstraint : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void test();
};
#endif
