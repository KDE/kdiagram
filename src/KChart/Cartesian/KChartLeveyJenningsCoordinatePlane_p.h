/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTLEVEYJENNINGSCOORDINATEPLANE_P_H
#define KCHARTLEVEYJENNINGSCOORDINATEPLANE_P_H

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

#include <QRectF>

#include "KChartCartesianCoordinatePlane_p.h"
#include "KChartLeveyJenningsCoordinatePlane.h"
#include "KChartLeveyJenningsGrid.h"
#include "KChartMath_p.h"

namespace KChart
{

class CartesianAxis;

/**
 * \internal
 */

class Q_DECL_HIDDEN LeveyJenningsCoordinatePlane::Private : public CartesianCoordinatePlane::Private
{
    friend class LeveyJenningsCoordinatePlane;

public:
    explicit Private();

    ~Private() override
    {
        // grid is delete in base class dtor
    }

    void initialize() override
    {
        grid = new LeveyJenningsGrid();
    }

    LeveyJenningsGridAttributes gridAttributes;
};

KCHART_IMPL_DERIVED_PLANE(LeveyJenningsCoordinatePlane, CartesianCoordinatePlane)
}

#endif /* KCHARTTERNARYCOORDINATEPLANE_P_H */
