/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartThreeDLineAttributes.h"
#include "KChartThreeDLineAttributes_p.h"

#include "KChartMath_p.h"

#include <QDebug>

#define d d_func()

using namespace KChart;

ThreeDLineAttributes::Private::Private()
    : lineXRotation(15)
    , lineYRotation(15)
{
}

ThreeDLineAttributes::ThreeDLineAttributes()
    : AbstractThreeDAttributes(new Private())
{
}

ThreeDLineAttributes::ThreeDLineAttributes(const ThreeDLineAttributes &r)
    : AbstractThreeDAttributes(new Private(*r.d))
{
}

ThreeDLineAttributes &ThreeDLineAttributes::operator=(const ThreeDLineAttributes &r)
{
    if (this == &r)
        return *this;

    *d = *r.d;

    return *this;
}

ThreeDLineAttributes::~ThreeDLineAttributes()
{
}

void ThreeDLineAttributes::init()
{
}

bool ThreeDLineAttributes::operator==(const ThreeDLineAttributes &r) const
{
    return (lineXRotation() == r.lineXRotation() && lineYRotation() == r.lineYRotation() && AbstractThreeDAttributes::operator==(r));
}

void ThreeDLineAttributes::setLineXRotation(const uint degrees)
{
    d->lineXRotation = degrees;
}

uint ThreeDLineAttributes::lineXRotation() const
{
    return d->lineXRotation;
}

void ThreeDLineAttributes::setLineYRotation(const uint degrees)
{
    d->lineYRotation = degrees;
}

uint ThreeDLineAttributes::lineYRotation() const
{
    return d->lineYRotation;
}

#if !defined(QT_NO_DEBUG_STREAM)

QDebug operator<<(QDebug dbg, const KChart::ThreeDLineAttributes &a)
{
    dbg << "KChart::ThreeDLineAttributes(";
    dbg = operator<<(dbg, static_cast<const AbstractThreeDAttributes &>(a));
    dbg << " lineXRotation=" << a.lineXRotation() << " lineYRotation=" << a.lineYRotation() << ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
