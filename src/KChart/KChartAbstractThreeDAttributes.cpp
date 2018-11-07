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

#include "KChartAbstractThreeDAttributes.h"
#include "KChartAbstractThreeDAttributes_p.h"

#include "KChartMath_p.h"

#include <QDebug>
#include <QBrush>

#define d d_func()


using namespace KChart;


AbstractThreeDAttributes::Private::Private()
    : enabled( false ),
      depth( 20 ),
      threeDBrushEnabled( false )
{
}


AbstractThreeDAttributes::AbstractThreeDAttributes()
    : _d( new Private() )
{
}

AbstractThreeDAttributes::AbstractThreeDAttributes( const AbstractThreeDAttributes& r )
    : _d( new Private( *r.d ) )
{
}

AbstractThreeDAttributes& AbstractThreeDAttributes::operator= ( const AbstractThreeDAttributes& r )
{
    if ( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

AbstractThreeDAttributes::~AbstractThreeDAttributes()
{
    delete _d; _d = nullptr;
}


bool AbstractThreeDAttributes::operator==( const AbstractThreeDAttributes& r ) const
{
    return isEnabled() == r.isEnabled() &&
        depth() == r.depth() && 
        isThreeDBrushEnabled() == r.isThreeDBrushEnabled();
}


void AbstractThreeDAttributes::init( )
{

}

void AbstractThreeDAttributes::setEnabled( bool enabled )
{
    d->enabled = enabled;
}

bool AbstractThreeDAttributes::isEnabled() const
{
    return d->enabled;
}

void AbstractThreeDAttributes::setDepth( qreal depth )
{
    d->depth = depth;
}


qreal AbstractThreeDAttributes::depth() const
{
    return d->depth;
}


qreal AbstractThreeDAttributes::validDepth() const
{
    return isEnabled() ? d->depth : 0.0;
}

bool AbstractThreeDAttributes::isThreeDBrushEnabled() const
{
    return d->threeDBrushEnabled;
}

void AbstractThreeDAttributes::setThreeDBrushEnabled( bool enabled )
{
    d->threeDBrushEnabled = enabled;
}

QBrush AbstractThreeDAttributes::threeDBrush( const QBrush& brush, const QRectF& rect ) const
{
    if ( isThreeDBrushEnabled() ) {
        QLinearGradient gr(rect.topLeft(), rect.bottomRight());
        gr.setColorAt(0.0, brush.color());
        gr.setColorAt(0.5, brush.color().lighter(180));
        gr.setColorAt(1.0, brush.color());
        return QBrush(gr);
    }
    return brush;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KChart::AbstractThreeDAttributes& a)
{
    dbg << "enabled="<<a.isEnabled()
        << "depth="<<a.depth();
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
