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
