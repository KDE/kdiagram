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

#ifndef KCHARTRINGDIAGRAM_P_H
#define KCHARTRINGDIAGRAM_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the KD Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "KChartRingDiagram.h"
#include "KChartAbstractPieDiagram_p.h"
#include "KChartMath_p.h"


namespace KChart {

/**
 * \internal
 */
class Q_DECL_HIDDEN RingDiagram::Private : public AbstractPieDiagram::Private
{
    friend class RingDiagram;
public:
    Private();
    ~Private();

    Private( const Private& rhs ) :
        AbstractPieDiagram::Private( rhs ),
        startAngles(),
        angleLens(),
        position(),
        size( 0 ),
        polygonsToRender()
        {
            relativeThickness = rhs.relativeThickness;
            expandWhenExploded = rhs.expandWhenExploded;
        }

protected:
    // this information needed temporarily at drawing time
    QVector< QVector < qreal > > startAngles;
    QVector< QVector < qreal > > angleLens;
    QRectF position;
    qreal size;
    bool relativeThickness;
    bool expandWhenExploded;
    // polygons associated to their 3d depth
    QMap<qreal, QPolygon> polygonsToRender;
};

KCHART_IMPL_DERIVED_DIAGRAM( RingDiagram, AbstractPieDiagram, PolarCoordinatePlane )

}

#endif /* KCHARTRINGDIAGRAM_P_H */
