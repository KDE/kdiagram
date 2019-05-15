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

#include "KChartThreeDPieAttributes.h"
#include "KChartThreeDPieAttributes_p.h"

#include "KChartMath_p.h"

#include <QDebug>

#define d d_func()

using namespace KChart;

ThreeDPieAttributes::Private::Private()
    : useShadowColors( true )
{
}


ThreeDPieAttributes::ThreeDPieAttributes()
    : AbstractThreeDAttributes( new Private() )
{
    init();
}

ThreeDPieAttributes::ThreeDPieAttributes( const ThreeDPieAttributes& r )
    : AbstractThreeDAttributes( new Private( *r.d) )
{
}

ThreeDPieAttributes& ThreeDPieAttributes::operator= ( const ThreeDPieAttributes& r )
{
    if ( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

ThreeDPieAttributes::~ThreeDPieAttributes()
{
}

void ThreeDPieAttributes::init()
{
    setDepth( -10 );
}


bool ThreeDPieAttributes::operator==( const ThreeDPieAttributes& r ) const
{
    return ( useShadowColors() == r.useShadowColors() &&
             AbstractThreeDAttributes::operator==(r));
}

void ThreeDPieAttributes::setUseShadowColors( bool shadowColors )
{
    d->useShadowColors = shadowColors;
}

bool ThreeDPieAttributes::useShadowColors() const
{
    return d->useShadowColors;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KChart::ThreeDPieAttributes& a)
{
    dbg << "KChart::ThreeDPieAttributes(";
    dbg = operator <<( dbg, static_cast<const AbstractThreeDAttributes&>(a) );
    dbg << "useShadowColors="<< a.useShadowColors() << ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */

