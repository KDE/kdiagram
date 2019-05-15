/*
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PAINTINGHELPERS_P_H
#define PAINTINGHELPERS_P_H

#include "KChartAbstractDiagram_p.h"
#include "KChartMath_p.h"

#include <QPointF>
#include <QVector>

class QBrush;
class QModelIndex;
class QPen;
class QPolygonF;

namespace KChart {

class LineAttributesInfo;
typedef QVector<LineAttributesInfo> LineAttributesInfoList;
class ThreeDLineAttributes;
class ValueTrackerAttributes;

namespace PaintingHelpers {

inline bool isFinite(const QPointF &point)
{
    return !ISINF(point.x()) && !ISNAN(point.x()) && !ISINF(point.y()) && !ISNAN(point.y());
}

const QPointF project( const QPointF& point, const ThreeDLineAttributes& tdAttributes );
void paintPolyline( PaintContext* ctx, const QBrush& brush, const QPen& pen, const QPolygonF& points );
void paintThreeDLines( PaintContext* ctx, AbstractDiagram *diagram, const QModelIndex& index,
                       const QPointF& from, const QPointF& to, const ThreeDLineAttributes& tdAttributes,
                       ReverseMapper* reverseMapper );
void paintValueTracker( PaintContext* ctx, const ValueTrackerAttributes& vt, const QPointF& at );
void paintElements( AbstractDiagram::Private *diagramPrivate, PaintContext* ctx,
                    const LabelPaintCache& lpc, const LineAttributesInfoList& lineList );
void paintAreas( AbstractDiagram::Private* diagramPrivate, PaintContext* ctx, const QModelIndex& index,
                 const QList< QPolygonF >& areas, uint opacity );

}
}

#endif
