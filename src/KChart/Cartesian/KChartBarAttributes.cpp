/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartBarAttributes.h"

#include "KChartMath_p.h"

#include <qglobal.h>

#define d d_func()


using namespace KChart;

class Q_DECL_HIDDEN BarAttributes::Private
{
    friend class BarAttributes;
public:
    Private();

private:
    qreal datasetGap;
    bool useFixedDatasetGap;
    qreal valueBlockGap;
    bool useFixedValueBlockGap;
    qreal barWidth;
    bool useFixedBarWidth;
    bool drawSolidExcessArrows;
    qreal groupGapFactor;
    qreal barGapFactor;
};


BarAttributes::Private::Private()
    :datasetGap( 6 ),
    useFixedDatasetGap( false ),
    valueBlockGap( 24 ),
    useFixedValueBlockGap( false ),
    barWidth( -1 ),
    useFixedBarWidth( false ),
    drawSolidExcessArrows( false ),
    groupGapFactor( 2.0 ),
    barGapFactor( 0.4 )
{
}


BarAttributes::BarAttributes()
    : _d( new Private() )
{
}

BarAttributes::BarAttributes( const BarAttributes& r )
    : _d( new Private( *r.d ) )
{
}

BarAttributes& BarAttributes::operator= ( const BarAttributes& r )
{
    if ( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

BarAttributes::~BarAttributes()
{
    delete _d; _d = nullptr;
}


bool BarAttributes::operator==( const BarAttributes& r ) const
{
    if ( fixedDataValueGap() == r.fixedDataValueGap() &&
        useFixedDataValueGap() == r.useFixedDataValueGap() &&
        fixedValueBlockGap() == r.fixedValueBlockGap() &&
        useFixedValueBlockGap() == r.useFixedValueBlockGap() &&
        fixedBarWidth() == r.fixedBarWidth() &&
        useFixedBarWidth() == r.useFixedBarWidth() &&
        groupGapFactor() == r.groupGapFactor() &&
        barGapFactor() == r.barGapFactor() &&
        drawSolidExcessArrows() == r.drawSolidExcessArrows() )
        return true;
    else
        return false;
}


void BarAttributes::setFixedDataValueGap( qreal gap )
{
    d->datasetGap = gap;
}

qreal BarAttributes::fixedDataValueGap() const
{
    return d->datasetGap;
}

void BarAttributes::setUseFixedDataValueGap( bool gapIsFixed )
{
    d->useFixedDatasetGap = gapIsFixed;
}

bool BarAttributes::useFixedDataValueGap() const
{
    return d->useFixedDatasetGap;
}

void BarAttributes::setFixedValueBlockGap( qreal gap )
{
    d->valueBlockGap = gap;
}

qreal BarAttributes::fixedValueBlockGap() const
{
    return d->valueBlockGap;
}

void BarAttributes::setUseFixedValueBlockGap( bool gapIsFixed )
{
    d->useFixedValueBlockGap = gapIsFixed;
}

bool BarAttributes::useFixedValueBlockGap() const
{
    return d->useFixedValueBlockGap;
}

void BarAttributes::setFixedBarWidth( qreal width )
{
    d->barWidth = width;
}

qreal BarAttributes::fixedBarWidth() const
{

    return d->barWidth;
}

void BarAttributes::setUseFixedBarWidth( bool useFixedBarWidth )
{
    d->useFixedBarWidth = useFixedBarWidth;
}

bool BarAttributes::useFixedBarWidth() const
{
    return d->useFixedBarWidth;
}

void BarAttributes::setGroupGapFactor( qreal gapFactor )
{
    d->groupGapFactor = gapFactor;
}

qreal BarAttributes::groupGapFactor() const
{
    return d->groupGapFactor;
}

void BarAttributes::setBarGapFactor( qreal gapFactor )
{
    d->barGapFactor = gapFactor;
}

qreal BarAttributes::barGapFactor() const
{
    return d->barGapFactor;
}

void BarAttributes::setDrawSolidExcessArrows( bool solidArrows )
{
    d->drawSolidExcessArrows = solidArrows;
}

bool BarAttributes::drawSolidExcessArrows() const
{
    return d->drawSolidExcessArrows;
}

