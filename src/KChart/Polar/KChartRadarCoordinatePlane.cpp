/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartRadarCoordinatePlane.h"
#include "KChartRadarCoordinatePlane_p.h"

using namespace KChart;

#define d d_func()

KChart::RadarCoordinatePlane::RadarCoordinatePlane(Chart *parent)
    : PolarCoordinatePlane(new Private(), parent)
{
}
KChart::RadarCoordinatePlane::~RadarCoordinatePlane()
{
}

void KChart::RadarCoordinatePlane::setTextAttributes(const KChart::TextAttributes &attr)
{
    d->textAttributes = attr;
}

const KChart::TextAttributes RadarCoordinatePlane::textAttributes() const
{
    return d->textAttributes;
}

void RadarCoordinatePlane::init()
{
    // this block left empty intentionally
}
