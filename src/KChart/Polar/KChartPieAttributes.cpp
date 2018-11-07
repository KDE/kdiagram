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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "KChartPieAttributes.h"
#include "KChartPieAttributes_p.h"

#include "KChartMath_p.h"

#include <QDebug>

#define d d_func()


using namespace KChart;


PieAttributes::Private::Private()
    : explodeFactor( 0.0 )
    , tangentialGapFactor( 0.0 )
    , radialGapFactor( 0.0 )
{
}


PieAttributes::PieAttributes()
    : _d( new Private() )
{
}

PieAttributes::PieAttributes( const PieAttributes& r )
    : _d( new Private( *r.d ) )
{
}

PieAttributes& PieAttributes::operator= ( const PieAttributes& r )
{
    if ( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

PieAttributes::~PieAttributes()
{
    delete _d; _d = nullptr;
}


bool PieAttributes::operator==( const PieAttributes& r ) const
{
    return 
        explodeFactor()   == r.explodeFactor() &&
        gapFactor( true ) == r.gapFactor( true ) &&
        gapFactor( false) == r.gapFactor( false);
}


void PieAttributes::init( )
{

}

void PieAttributes::setExplode( bool enabled )
{
    d->explodeFactor = (enabled ? 0.1 : 0.0);
}

bool PieAttributes::explode() const
{
    return (d->explodeFactor != 0.0);
}

void PieAttributes::setExplodeFactor( qreal factor )
{
    d->explodeFactor = factor;
}

qreal PieAttributes::explodeFactor() const
{
    return d->explodeFactor;
}

void PieAttributes::setGapFactor( bool circular, qreal factor )
{
	if ( circular )
		d->tangentialGapFactor = factor;
	else
		d->radialGapFactor = factor;
}

qreal PieAttributes::gapFactor( bool circular ) const
{
	return circular ? d->tangentialGapFactor : d->radialGapFactor;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KChart::PieAttributes& a)
{
    dbg << "KChart::PieAttributes(";
    dbg << "explodeFactor="<< a.explodeFactor() << ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */

