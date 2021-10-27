/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTRADARCOORDINATEPLANE_P_H
#define KCHARTRADARCOORDINATEPLANE_P_H

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

#include "KChartPolarCoordinatePlane_p.h"
#include "KChartRadarCoordinatePlane.h"
#include "KChartRadarGrid.h"


namespace KChart {
  
class Q_DECL_HIDDEN RadarCoordinatePlane::Private : public PolarCoordinatePlane::Private
{
    friend class RadarCoordinatePlane;
public:
    explicit Private() { }

    ~Private() override { }
    TextAttributes textAttributes;
    
    void initialize() override
    {
        grid = new RadarGrid();
    }
};


KCHART_IMPL_DERIVED_PLANE(RadarCoordinatePlane, PolarCoordinatePlane)

}

#endif /* KCHARTBARDIAGRAM_P_H */
