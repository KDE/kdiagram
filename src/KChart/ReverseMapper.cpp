/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "ReverseMapper.h"

#include <math.h>

#include <QGraphicsScene>
#include <QPainterPath>
#include <QPolygonF>
#include <QRect>
#include <QtDebug>

#include "ChartGraphicsItem.h"
#include "KChartAbstractDiagram.h"

using namespace KChart;

ReverseMapper::ReverseMapper()
    : m_diagram(nullptr)
    , m_scene(nullptr)
{
}

ReverseMapper::ReverseMapper(AbstractDiagram *diagram)
    : m_diagram(diagram)
    , m_scene(nullptr)
{
}

ReverseMapper::~ReverseMapper()
{
    delete m_scene;
    m_scene = nullptr;
}

void ReverseMapper::setDiagram(AbstractDiagram *diagram)
{
    m_diagram = diagram;
}

void ReverseMapper::clear()
{
    m_polygons.clear();
    if (m_scene)
        m_scene->clear();
    m_sceneDirty = true;
}

QModelIndexList ReverseMapper::indexesIn(const QRect &rect) const
{
    populateScene();

    if (m_scene->sceneRect().intersects(rect)) {
        const QList<QGraphicsItem *> items = m_scene->items(rect);
        QModelIndexList indexes;
        for (QGraphicsItem *item : items) {
            ChartGraphicsItem *i = qgraphicsitem_cast<ChartGraphicsItem *>(item);
            if (i) {
                QModelIndex index(m_diagram->model()->index(i->row(), i->column(), m_diagram->rootIndex())); // checked
                indexes << index;
            }
        }
        return indexes;
    } else {
        return QModelIndexList();
    }
}

QModelIndexList ReverseMapper::indexesAt(const QPointF &point) const
{
    populateScene();

    if (m_scene->sceneRect().contains(point)) {
        const QList<QGraphicsItem *> items = m_scene->items(point);
        QModelIndexList indexes;
        for (QGraphicsItem *item : items) {
            ChartGraphicsItem *i = qgraphicsitem_cast<ChartGraphicsItem *>(item);
            if (i) {
                QModelIndex index(m_diagram->model()->index(i->row(), i->column(), m_diagram->rootIndex())); // checked
                if (!indexes.contains(index))
                    indexes << index;
            }
        }
        return indexes;
    } else {
        return QModelIndexList();
    }
}

QPolygonF ReverseMapper::polygon(int row, int column) const
{
    if (!m_diagram->model()->hasIndex(row, column, m_diagram->rootIndex()))
        return QPolygon();
    const QModelIndex index = m_diagram->model()->index(row, column, m_diagram->rootIndex()); // checked
    return m_polygons.value(index);
}

QRectF ReverseMapper::boundingRect(int row, int column) const
{
    return polygon(row, column).boundingRect();
}

void ReverseMapper::addRect(int row, int column, const QRectF &rect)
{
    addPolygon(row, column, QPolygonF(rect));
}

void ReverseMapper::addPolygon(int row, int column, const QPolygonF &polygon)
{
    const auto index = m_diagram->model()->index(row, column, m_diagram->rootIndex());
    auto &value = m_polygons[index];
    if (value.isEmpty()) {
        value = polygon;
    } else {
        value = value.united(polygon);
    }

    m_sceneDirty = true;
}

void ReverseMapper::addCircle(int row, int column, const QPointF &location, const QSizeF &diameter)
{
    QPainterPath path;
    QPointF ossfet(-0.5 * diameter.width(), -0.5 * diameter.height());
    path.addEllipse(QRectF(location + ossfet, diameter));
    addPolygon(row, column, QPolygonF(path.toFillPolygon()));
}

void ReverseMapper::addLine(int row, int column, const QPointF &from, const QPointF &to)
{
    // that's no line, dude... make a small circle around that point, instead
    if (from == to) {
        addCircle(row, column, from, QSizeF(1.5, 1.5));
        return;
    }
    // lines do not make good polygons to click on. we calculate a 2
    // pixel wide rectangle, where the original line is exactly
    // centered in.
    // make a 3 pixel wide polygon from the line:
    QPointF left, right;
    if (from.x() < to.x()) {
        left = from;
        right = to;
    } else {
        right = from;
        left = to;
    }
    const QPointF lineVector(right - left);
    const qreal lineVectorLength = sqrt(lineVector.x() * lineVector.x() + lineVector.y() * lineVector.y());
    const QPointF lineVectorUnit(lineVector / lineVectorLength);
    const QPointF normOfLineVectorUnit(-lineVectorUnit.y(), lineVectorUnit.x());
    // now the four polygon end points:
    const QPointF one(left - lineVectorUnit + normOfLineVectorUnit);
    const QPointF two(left - lineVectorUnit - normOfLineVectorUnit);
    const QPointF three(right + lineVectorUnit - normOfLineVectorUnit);
    const QPointF four(right + lineVectorUnit + normOfLineVectorUnit);
    addPolygon(row, column, QPolygonF() << one << two << three << four);
}

void ReverseMapper::populateScene() const
{
    // we populate the scene lazily...

    Q_ASSERT(m_diagram);

    if (!m_sceneDirty) {
        return;
    }

    if (!m_scene) {
        m_scene = new QGraphicsScene;
    }

    QRectF boundingRect;
    for (auto it = m_polygons.constBegin(), end = m_polygons.constEnd(); it != end; ++it) {
        auto *item = new ChartGraphicsItem(it.key().row(), it.key().column());
        item->setPolygon(it.value());
        m_scene->addItem(item);
        boundingRect |= it.value().boundingRect();
    }

    m_scene->setSceneRect(boundingRect);
    m_sceneDirty = false;
}
