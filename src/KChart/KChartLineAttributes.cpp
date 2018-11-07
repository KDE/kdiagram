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

#include "KChartLineAttributes.h"

#include "KChartMath_p.h"

#include <QDebug>

#define d d_func()

using namespace KChart;

class Q_DECL_HIDDEN LineAttributes::Private
{
    friend class LineAttributes;
public:
    Private();

private:
    //Areas
    MissingValuesPolicy missingValuesPolicy;
    bool displayArea;
    bool visible;
    uint transparency;
    int areaBoundingDataset;
};


LineAttributes::Private::Private()
    : missingValuesPolicy( MissingValuesAreBridged )
    , displayArea( false )
    , visible( true )
    , transparency( 255 )
    , areaBoundingDataset( -1 )
{
}


LineAttributes::LineAttributes()
    : _d( new Private() )
{
}

LineAttributes::LineAttributes( const LineAttributes& r )
    : _d( new Private( *r.d ) )
{
}

LineAttributes& LineAttributes::operator= ( const LineAttributes& r )
{
    if ( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

LineAttributes::~LineAttributes()
{
    delete _d; _d = nullptr;
}

bool LineAttributes::operator==( const LineAttributes& r ) const
{
    return
        missingValuesPolicy() == r.missingValuesPolicy() &&
        displayArea() == r.displayArea() &&
        isVisible() == r.isVisible() &&
        transparency() == r.transparency() &&
        areaBoundingDataset() == r.areaBoundingDataset();
}

void LineAttributes::setMissingValuesPolicy( MissingValuesPolicy policy )
{
    d->missingValuesPolicy = policy;
}

LineAttributes::MissingValuesPolicy LineAttributes::missingValuesPolicy() const
{
    return d->missingValuesPolicy;
}

void LineAttributes::setDisplayArea( bool display )
{
    d->displayArea = display;
}

bool LineAttributes::displayArea() const
{
   return d->displayArea;
}

void LineAttributes::setTransparency( uint alpha )
{
     if ( alpha > 255 )
        alpha = 255;
    d->transparency = alpha;
}

uint LineAttributes::transparency() const
{
     return d->transparency;
}

void LineAttributes::setAreaBoundingDataset( int dataset )
{
   d->areaBoundingDataset = dataset;
}

int LineAttributes::areaBoundingDataset() const
{
    return d->areaBoundingDataset;
}

void LineAttributes::setVisible( bool visible )
{
    d->visible = visible;
}

bool LineAttributes::isVisible() const
{
    return d->visible;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KChart::LineAttributes& a)
{
    dbg << "KChart::LineAttributes("
            //     MissingValuesPolicy missingValuesPolicy;
            << "bool="<<a.displayArea()
            << "visible="<<a.isVisible()
            << "transparency="<<a.transparency()
            << "areaBoundingDataset="<<a.areaBoundingDataset()
            << ")";
    return dbg;

}
#endif /* QT_NO_DEBUG_STREAM */
