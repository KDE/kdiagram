/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef REVERSEMAPPER_H
#define REVERSEMAPPER_H

#include <QModelIndex>
#include <QHash>

QT_BEGIN_NAMESPACE
class QRectF;
class QGraphicsScene;
class QPolygonF;
QT_END_NAMESPACE

namespace KChart {

    class AbstractDiagram;
    class ChartGraphicsItem;

    /**
      * @brief The ReverseMapper stores information about objects on a chart and their respective model indexes
      * \internal
      */
    class ReverseMapper
    {

    public:
        ReverseMapper();
        explicit ReverseMapper( AbstractDiagram* diagram );

        ~ReverseMapper();

        void setDiagram( AbstractDiagram* diagram );

        void clear();

        QModelIndexList indexesAt( const QPointF& point ) const;
        QModelIndexList indexesIn( const QRect& rect ) const;

        QPolygonF polygon( int row, int column ) const;
        QRectF boundingRect( int row, int column ) const;

        // convenience methods:
        void addPolygon( int row, int column, const QPolygonF& polygon );
        void addRect( int row, int column, const QRectF& rect );
        void addCircle( int row, int column, const QPointF& location, const QSizeF& diameter );
        void addLine( int row, int column, const QPointF& from, const QPointF& to );

    private:
        void populateScene() const;

        AbstractDiagram* m_diagram;
        QHash<QModelIndex, QPolygonF> m_polygons;
        mutable QGraphicsScene* m_scene;
        mutable bool m_sceneDirty = true;
    };

}

#endif
