/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartGridAttributes.h"

#include "KChartMath_p.h"

#include <QPen>
#include <QDebug>

#define d d_func()

using namespace KChart;

class Q_DECL_HIDDEN GridAttributes::Private
{
    friend class GridAttributes;
public:
    Private();
private:
    bool visible;
    KChartEnums::GranularitySequence sequence;
    bool linesOnAnnotations;
    qreal stepWidth;
    qreal subStepWidth;
    bool adjustLower;
    bool adjustUpper;
    QPen pen;
    bool subVisible;
    QPen subPen;
    bool outerVisible;
    QPen zeroPen;
};

GridAttributes::Private::Private()
    : visible( true ),
      sequence( KChartEnums::GranularitySequence_10_20 ),
      linesOnAnnotations( false ),
      stepWidth( 0.0 ),
      subStepWidth( 0.0 ),
      adjustLower( true ),
      adjustUpper( true ),
      pen( QColor(0xa0, 0xa0, 0xa0 ) ),
      subVisible( true ),
      subPen( QColor(0xd0, 0xd0, 0xd0 ) ),
      outerVisible( true ),
      zeroPen( QColor( 0x00, 0x00, 0x80 ) )
{
    pen.setCapStyle( Qt::FlatCap );
    subPen.setCapStyle( Qt::FlatCap );
    zeroPen.setCapStyle( Qt::FlatCap );
}


GridAttributes::GridAttributes()
    : _d( new Private() )
{
    // this block left empty intentionally
}

GridAttributes::GridAttributes( const GridAttributes& r )
    : _d( new Private( *r.d ) )
{
}

GridAttributes & GridAttributes::operator=( const GridAttributes& r )
{
    if ( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

GridAttributes::~GridAttributes()
{
    delete _d; _d = nullptr;
}


bool GridAttributes::operator==( const GridAttributes& r ) const
{
    return  isGridVisible() == r.isGridVisible() &&
            gridGranularitySequence() == r.gridGranularitySequence() &&
            linesOnAnnotations() == r.linesOnAnnotations() &&
            adjustLowerBoundToGrid() == r.adjustLowerBoundToGrid() &&
            adjustUpperBoundToGrid() == r.adjustUpperBoundToGrid() &&
            gridPen() == r.gridPen() &&
            isSubGridVisible() == r.isSubGridVisible() &&
            subGridPen() == r.subGridPen() &&
            isOuterLinesVisible() == r.isOuterLinesVisible() &&
            zeroLinePen() == r.zeroLinePen();
}


void GridAttributes::setGridVisible( bool visible )
{
    d->visible = visible;
}

bool GridAttributes::isGridVisible() const
{
    return d->visible;
}

void GridAttributes::setLinesOnAnnotations( bool b )
{
    d->linesOnAnnotations = b;
}

bool GridAttributes::linesOnAnnotations() const
{
    return d->linesOnAnnotations;
}

void GridAttributes::setGridStepWidth( qreal stepWidth )
{
    d->stepWidth = stepWidth;
}

qreal GridAttributes::gridStepWidth() const
{
    return d->stepWidth;
}



void GridAttributes::setGridSubStepWidth( qreal subStepWidth )
{
    d->subStepWidth = subStepWidth;
}

qreal GridAttributes::gridSubStepWidth() const
{
    return d->subStepWidth;
}

void GridAttributes::setGridGranularitySequence( KChartEnums::GranularitySequence sequence )
{
    d->sequence = sequence;
}

KChartEnums::GranularitySequence GridAttributes::gridGranularitySequence() const
{
    return d->sequence;
}

void GridAttributes::setAdjustBoundsToGrid( bool adjustLower, bool adjustUpper )
{
    d->adjustLower = adjustLower;
    d->adjustUpper = adjustUpper;
}
bool GridAttributes::adjustLowerBoundToGrid() const
{
    return d->adjustLower;
}
bool GridAttributes::adjustUpperBoundToGrid() const
{
    return d->adjustUpper;
}

void GridAttributes::setGridPen( const QPen & pen )
{
    d->pen = pen;
    d->pen.setCapStyle( Qt::FlatCap );
}

QPen GridAttributes::gridPen() const
{
    return d->pen;
}

void GridAttributes::setSubGridVisible( bool visible )
{
    d->subVisible = visible;
}

bool GridAttributes::isSubGridVisible() const
{
    return d->subVisible;
}

void GridAttributes::setSubGridPen( const QPen & pen )
{
    d->subPen = pen;
    d->subPen.setCapStyle( Qt::FlatCap );
}

QPen GridAttributes::subGridPen() const
{
    return d->subPen;
}

void GridAttributes::setOuterLinesVisible( bool visible )
{
    d->outerVisible = visible;
}

bool GridAttributes::isOuterLinesVisible() const
{
    return d->outerVisible;
}

void GridAttributes::setZeroLinePen( const QPen & pen )
{
    d->zeroPen = pen;
    d->zeroPen.setCapStyle( Qt::FlatCap );
}

QPen GridAttributes::zeroLinePen() const
{
    return d->zeroPen;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KChart::GridAttributes& a)
{
    dbg << "KChart::GridAttributes("
            << "visible="<<a.isGridVisible()
            << "subVisible="<<a.isSubGridVisible()
            // KChartEnums::GranularitySequence sequence;
            << "stepWidth=" << a.gridStepWidth()
            << "subStepWidth=" << a.gridSubStepWidth()
            << "pen="<<a.gridPen()
            << "subPen="<<a.subGridPen()
            << "zeroPen="<<a.zeroLinePen()
            << ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */

