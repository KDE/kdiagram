/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTGRAPHICSSCENE_P_H
#define KGANTTGRAPHICSSCENE_P_H

#include <QAbstractProxyModel>
#include <QHash>
#include <QItemSelectionModel>
#include <QPersistentModelIndex>
#include <QPointer>

#include "kganttconstraintmodel.h"
#include "kganttdatetimegrid.h"
#include "kganttgraphicsscene.h"

namespace KGantt
{
class AbstractGrid;

class Q_DECL_HIDDEN GraphicsScene::Private
{
public:
    explicit Private(GraphicsScene *);
    ~Private();

    void clearConstraintItems();
    void resetConstraintItems();
    void createConstraintItem(const Constraint &c);
    void deleteConstraintItem(ConstraintGraphicsItem *citem);
    void deleteConstraintItem(const Constraint &c);
    ConstraintGraphicsItem *findConstraintItem(const Constraint &c) const;

    void recursiveUpdateMultiItem(const Span &span, const QModelIndex &idx);

    void clearItems();
    AbstractGrid *getGrid();
    const AbstractGrid *getGrid() const;

    GraphicsScene *q;

    QHash<QPersistentModelIndex, GraphicsItem *> items;
    QList<ConstraintGraphicsItem *> constraintItems;
    GraphicsItem *dragSource;

    QPointer<ItemDelegate> itemDelegate;
    AbstractRowController *rowController;
    DateTimeGrid default_grid;
    QPointer<AbstractGrid> grid;
    bool readOnly;

    /* printing related members */
    bool isPrinting;
    bool drawColumnLabels;
    qreal labelsWidth;

    QPointer<QAbstractProxyModel> summaryHandlingModel;

    QPointer<ConstraintModel> constraintModel;

    QPointer<QItemSelectionModel> selectionModel;
};

GraphicsScene::GraphicsScene(GraphicsScene::Private *d)
    : _d(d)
{
    init();
}
}

#endif /* KGANTTGRAPHICSSCENE_P_H */
