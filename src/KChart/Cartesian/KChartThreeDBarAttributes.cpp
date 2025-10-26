/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartThreeDBarAttributes.h"
#include "KChartThreeDBarAttributes_p.h"

#include "KChartMath_p.h"

#include <QDebug>

#define d d_func()

using namespace KChart;

ThreeDBarAttributes::Private::Private()
    : useShadowColors(true)
    , angle(45)
{
}

ThreeDBarAttributes::ThreeDBarAttributes()
    : AbstractThreeDAttributes(new Private())
{
}

ThreeDBarAttributes::ThreeDBarAttributes(const ThreeDBarAttributes &r)
    : AbstractThreeDAttributes(new Private(*r.d))
{
}

ThreeDBarAttributes &ThreeDBarAttributes::operator=(const ThreeDBarAttributes &r)
{
    if (this == &r)
        return *this;

    *d = *r.d;

    return *this;
}

ThreeDBarAttributes::~ThreeDBarAttributes()
{
}

void ThreeDBarAttributes::init()
{
}

bool ThreeDBarAttributes::operator==(const ThreeDBarAttributes &r) const
{
    return (useShadowColors() == r.useShadowColors() && angle() == r.angle() && AbstractThreeDAttributes::operator==(r));
}

void ThreeDBarAttributes::setUseShadowColors(bool shadowColors)
{
    d->useShadowColors = shadowColors;
}

bool ThreeDBarAttributes::useShadowColors() const
{
    return d->useShadowColors;
}

void ThreeDBarAttributes::setAngle(uint threeDAngle)
{
    d->angle = threeDAngle;
}

uint ThreeDBarAttributes::angle() const
{
    return d->angle;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KChart::ThreeDBarAttributes &a)
{
    dbg << "KChart::ThreeDBarAttributes(";
    dbg = operator<<(dbg, static_cast<const AbstractThreeDAttributes &>(a));
    dbg << "useShadowColors=" << a.useShadowColors() << "angle=" << a.angle() << ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
