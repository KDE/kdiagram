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

#include "KChartMarkerAttributes.h"

#include "KChartMath_p.h"

#include <QColor>
#include <QMap>
#include <QPen>
#include <QPainterPath>
#include <QSizeF>
#include <QDebug>
#include <qglobal.h>

using namespace KChart;

class Q_DECL_HIDDEN MarkerAttributes::Private
{
    friend class ::KChart::MarkerAttributes;
public:
    Private();
private:
    bool visible;
    bool threeD;
    QMap<uint,uint> markerStylesMap;
    uint markerStyle;
    MarkerSizeMode markerSizeMode;
    QSizeF markerSize;
    QColor markerColor;
    QPainterPath customMarkerPath;
    QPen markerPen;
};

MarkerAttributes::Private::Private()
    : visible( false ),
      threeD( false ),
      markerStyle( MarkerSquare ),
      markerSizeMode( AbsoluteSize ),
      markerSize( 10, 10 ),
      markerPen( Qt::black )
{
}


MarkerAttributes::MarkerAttributes()
    : _d( new Private )
{

}

MarkerAttributes::MarkerAttributes( const MarkerAttributes& r )
    : _d( new Private( *r._d ) )
{

}

MarkerAttributes & MarkerAttributes::operator=( const MarkerAttributes& r )
{
    MarkerAttributes copy( r );
    copy.swap( *this );
    return *this;
}

MarkerAttributes::~MarkerAttributes()
{
    delete _d; _d = nullptr;
}

#define d d_func()

bool MarkerAttributes::operator==( const MarkerAttributes& r ) const
{
    /*
    qDebug() << "MarkerAttributes::operator== finds"
            << "b" << (isVisible() == r.isVisible())
            << "c" << (markerStylesMap() == r.markerStylesMap())
            << "d" << (markerStyle() == r.markerStyle()) << markerStyle() <<r.markerStyle()
            << "e" << (markerSize() == r.markerSize())
            << "f" << (markerColor() == r.markerColor())
            << "p" << (customMarkerPath() == r.customMarkerPath())
            << "g" << (pen() == r.pen())
            << "h" << (markerColor() == r.markerColor()) << markerColor() << r.markerColor();
    */
    return ( isVisible() == r.isVisible() &&
            markerStylesMap() == r.markerStylesMap() &&
            markerStyle() == r.markerStyle() &&
            markerStyle() == r.markerStyle() &&
            markerSizeMode() == r.markerSizeMode() &&
            markerColor() == r.markerColor() &&
            customMarkerPath() == r.customMarkerPath() &&
            pen() == r.pen() );
}



void MarkerAttributes::setVisible( bool visible )
{
    d->visible = visible;
}

bool MarkerAttributes::isVisible() const
{
    return d->visible;
}

void MarkerAttributes::setThreeD( bool value )
{
    d->threeD = value;
}

bool MarkerAttributes::threeD() const
{
    return d->threeD;
}

void MarkerAttributes::setMarkerStylesMap( const MarkerStylesMap & map )
{
    d->markerStylesMap = map;
}

MarkerAttributes::MarkerStylesMap MarkerAttributes::markerStylesMap() const
{
    return d->markerStylesMap;
}

void MarkerAttributes::setMarkerStyle( uint style )
{
    d->markerStyle = style;
}

uint MarkerAttributes::markerStyle() const
{
    return d->markerStyle;
}

void MarkerAttributes::setMarkerSize( const QSizeF& size )
{
    d->markerSize = size;
}

QSizeF MarkerAttributes::markerSize() const
{
    return d->markerSize;
}

void MarkerAttributes::setMarkerSizeMode( MarkerSizeMode mode )
{
    d->markerSizeMode = mode;
}

MarkerAttributes::MarkerSizeMode MarkerAttributes::markerSizeMode() const
{
    return d->markerSizeMode;
}


void MarkerAttributes::setMarkerColor( const QColor& color )
{
    d->markerColor = color;
}

QColor MarkerAttributes::markerColor() const
{
    return d->markerColor;
}

void MarkerAttributes::setCustomMarkerPath( const QPainterPath& path )
{
    d->customMarkerPath = path;
}

QPainterPath MarkerAttributes::customMarkerPath() const
{
    return d->customMarkerPath;
}

void MarkerAttributes::setPen( const QPen& pen )
{
    d->markerPen = pen;
}

QPen MarkerAttributes::pen() const
{
    return d->markerPen;
}

#undef d

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<( QDebug dbg, const MarkerAttributes & ma ) {
    return dbg << "KChart::MarkerAttributes("
               << "visible=" << ma.isVisible()
               << "markerStylesMap=" << ma.markerStylesMap()
               << "markerStyle=" << ma.markerStyle()
               << "markerColor=" << ma.markerColor()
               << "customMarkerPath=" << ma.customMarkerPath()
               << "pen=" << ma.pen()
               << ")";
}
#endif

