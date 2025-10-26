/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartStockBarAttributes.h"

#define d d_func()

using namespace KChart;

class Q_DECL_HIDDEN StockBarAttributes::Private
{
public:
    Private();

    qreal candlestickWidth;
    qreal tickLength;
};

StockBarAttributes::Private::Private()
    : candlestickWidth(0.3)
    , tickLength(0.15)
{
}

StockBarAttributes::StockBarAttributes()
    : _d(new Private)
{
}

StockBarAttributes::StockBarAttributes(const StockBarAttributes &r)
    : _d(new Private(*r.d))
{
}

StockBarAttributes &StockBarAttributes::operator=(const StockBarAttributes &r)
{
    if (this == &r)
        return *this;

    *d = *r.d;

    return *this;
}

StockBarAttributes::~StockBarAttributes()
{
    delete _d;
}

void StockBarAttributes::setCandlestickWidth(qreal width)
{
    d->candlestickWidth = width;
}
qreal StockBarAttributes::candlestickWidth() const
{
    return d->candlestickWidth;
}

void StockBarAttributes::setTickLength(qreal length)
{
    d->tickLength = length;
}

qreal StockBarAttributes::tickLength() const
{
    return d->tickLength;
}

bool StockBarAttributes::operator==(const StockBarAttributes &r) const
{
    return candlestickWidth() == r.candlestickWidth() && tickLength() == r.tickLength();
}
