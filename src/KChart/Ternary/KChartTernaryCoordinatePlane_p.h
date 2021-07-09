/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTTERNARYCOORDINATEPLANE_P_H
#define KCHARTTERNARYCOORDINATEPLANE_P_H

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

#include "KChartTernaryCoordinatePlane.h"
#include "KChartTernaryGrid.h"
#include "KChartAbstractCoordinatePlane_p.h"
#include "KChartMath_p.h"

#include <QRectF>

namespace KChart {

    class TernaryAxis;

    /**
     * \internal
     */

    class Q_DECL_HIDDEN TernaryCoordinatePlane::Private : public AbstractCoordinatePlane::Private
    {
        friend class TernaryCoordinatePlane;

    public:
        explicit Private();

        virtual ~Private() {
            // grid is delete in base class dtor
        }

        void initialize() override
        {
            grid = new TernaryGrid();
            xUnit = 0.0;
            yUnit = 0.0;
        }

        QList<TernaryAxis*> axes;

        TextAttributes labelAttributes;

        // the diagram is drawn within this rectangle, which is within
        // this widget:
        QRectF diagramRectContainer;
        // this is the "frame" of the plot area
        QRectF diagramRect;
        // multiply m_xUnit with a [0..1] value to get an isometric
        // widget coordinate
        qreal xUnit;
        // same for y:
        qreal yUnit;

    };

    KCHART_IMPL_DERIVED_PLANE(TernaryCoordinatePlane, AbstractCoordinatePlane)
}

#endif /* KCHARTTERNARYCOORDINATEPLANE_P_H */
