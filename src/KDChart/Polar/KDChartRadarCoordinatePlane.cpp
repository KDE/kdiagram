/**
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "KDChartRadarCoordinatePlane.h"
#include "KDChartRadarCoordinatePlane_p.h"


using namespace KDChart;

#define d d_func()

KDChart::RadarCoordinatePlane::RadarCoordinatePlane ( Chart* parent ) :
    PolarCoordinatePlane( new Private(), parent )
{
}
KDChart::RadarCoordinatePlane::~RadarCoordinatePlane()
{
}

void KDChart::RadarCoordinatePlane::setTextAttributes(const KDChart::TextAttributes& attr)
{
    d->textAttributes = attr;
}

const KDChart::TextAttributes RadarCoordinatePlane::textAttributes() const
{
    return d->textAttributes;
}

void RadarCoordinatePlane::init()
{
    // this bloc left empty intentionally
}
