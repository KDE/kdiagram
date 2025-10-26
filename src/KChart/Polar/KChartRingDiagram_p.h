/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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

#include "KChartAbstractPieDiagram_p.h"
#include "KChartMath_p.h"
#include "KChartRingDiagram.h"

namespace KChart
{

/**
 * \internal
 */
class Q_DECL_HIDDEN RingDiagram::Private : public AbstractPieDiagram::Private
{
    friend class RingDiagram;

public:
    Private();
    ~Private() override;

    Private(const Private &rhs)
        : AbstractPieDiagram::Private(rhs)
        , startAngles()
        , angleLens()
        , position()
        , size(0)
        , polygonsToRender()
    {
        relativeThickness = rhs.relativeThickness;
        expandWhenExploded = rhs.expandWhenExploded;
    }

protected:
    // this information needed temporarily at drawing time
    QVector<QVector<qreal>> startAngles;
    QVector<QVector<qreal>> angleLens;
    QRectF position;
    qreal size;
    bool relativeThickness;
    bool expandWhenExploded;
    // polygons associated to their 3d depth
    QMap<qreal, QPolygon> polygonsToRender;
};

KCHART_IMPL_DERIVED_DIAGRAM(RingDiagram, AbstractPieDiagram, PolarCoordinatePlane)

}

#endif /* KCHARTRINGDIAGRAM_P_H */
