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

#include "KChartStockBarAttributes.h"

#define d d_func()

using namespace KChart;

class Q_DECL_HIDDEN StockBarAttributes::Private {
public:
    Private();

    qreal candlestickWidth;
    qreal tickLength;
};

StockBarAttributes::Private::Private()
    : candlestickWidth( 0.3 )
    , tickLength( 0.15 )
{
}

StockBarAttributes::StockBarAttributes()
    : _d( new Private )
{
}

StockBarAttributes::StockBarAttributes( const StockBarAttributes& r )
    : _d( new Private( *r.d ) )
{
}

StockBarAttributes &StockBarAttributes::operator= ( const StockBarAttributes& r )
{
    if ( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

StockBarAttributes::~StockBarAttributes()
{
    delete _d;
}

void StockBarAttributes::setCandlestickWidth( qreal width )
{
    d->candlestickWidth = width;
}
qreal StockBarAttributes::candlestickWidth() const
{
    return d->candlestickWidth;
}

void StockBarAttributes::setTickLength( qreal length )
{
    d->tickLength = length;
}

qreal StockBarAttributes::tickLength() const
{
    return d->tickLength;
}

bool StockBarAttributes::operator==( const StockBarAttributes& r ) const
{
    return candlestickWidth() == r.candlestickWidth() &&
           tickLength() == r.tickLength();
}
