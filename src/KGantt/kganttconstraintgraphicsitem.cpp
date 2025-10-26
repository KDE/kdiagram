/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "kganttconstraintgraphicsitem.h"
#include "kganttconstraintmodel.h"
#include "kganttgraphicsscene.h"
#include "kganttitemdelegate.h"
#include "kganttsummaryhandlingproxymodel.h"

#include <QApplication>
#include <QDebug>
#include <QPainter>

using namespace KGantt;

ConstraintGraphicsItem::ConstraintGraphicsItem(const Constraint &c, QGraphicsItem *parent, GraphicsScene *scene)
    : QGraphicsItem(parent)
    , m_constraint(c)
{
    if (scene)
        scene->addItem(this);
    setPos(QPointF(0., 0.));
    setAcceptHoverEvents(false);
    setAcceptedMouseButtons(Qt::NoButton);
    setZValue(10.);
}

ConstraintGraphicsItem::~ConstraintGraphicsItem()
{
}

int ConstraintGraphicsItem::type() const
{
    return Type;
}

GraphicsScene *ConstraintGraphicsItem::scene() const
{
    return qobject_cast<GraphicsScene *>(QGraphicsItem::scene());
}

Constraint ConstraintGraphicsItem::proxyConstraint() const
{
    return Constraint(scene()->summaryHandlingModel()->mapFromSource(m_constraint.startIndex()),
                      scene()->summaryHandlingModel()->mapFromSource(m_constraint.endIndex()),
                      m_constraint.type(),
                      m_constraint.relationType(),
                      m_constraint.dataMap());
}

QRectF ConstraintGraphicsItem::boundingRect() const
{
    return scene()->itemDelegate()->constraintBoundingRect(m_start, m_end, m_constraint);
}

void ConstraintGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    // qDebug() << "ConstraintGraphicsItem::paint(...), c=" << m_constraint;
    QStyleOptionGraphicsItem opt = *option;
    if (widget) {
        opt.palette = widget->palette();
    } else {
        opt.palette = QApplication::palette();
    }
    scene()->itemDelegate()->paintConstraintItem(painter, opt, m_start, m_end, m_constraint);
}

QString ConstraintGraphicsItem::ganttToolTip() const
{
    return m_constraint.data(Qt::ToolTipRole).toString();
}

void ConstraintGraphicsItem::setStart(const QPointF &start)
{
    prepareGeometryChange();
    m_start = start;
    update();
}

void ConstraintGraphicsItem::setEnd(const QPointF &end)
{
    prepareGeometryChange();
    m_end = end;
    update();
}

void ConstraintGraphicsItem::updateItem(const QPointF &start, const QPointF &end)
{
    setStart(start);
    setEnd(end);
}
