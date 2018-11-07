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

#include "KChartFrameAttributes.h"

#include "KChartMath_p.h"

#define d d_func()

using namespace KChart;

class Q_DECL_HIDDEN FrameAttributes::Private
{
    friend class FrameAttributes;
public:
    Private();
private:
    bool visible;
    QPen pen;
    qreal cornerRadius;
    int padding;
};

FrameAttributes::Private::Private() :
    visible( false ),
    cornerRadius( 0 ),
    padding( 0 )
{
}


FrameAttributes::FrameAttributes()
    : _d( new Private() )
{
}

FrameAttributes::FrameAttributes( const FrameAttributes& r )
    : _d( new Private( *r.d ) )
{
}

FrameAttributes & FrameAttributes::operator=( const FrameAttributes& r )
{
    if ( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

FrameAttributes::~FrameAttributes()
{
    delete _d; _d = nullptr;
}


bool FrameAttributes::operator==( const FrameAttributes& r ) const
{
    return ( isVisible() == r.isVisible() &&
            pen() == r.pen() &&
            cornerRadius() == r.cornerRadius() &&
            padding() == r.padding() );
}




void FrameAttributes::setVisible( bool visible )
{
    d->visible = visible;
}

bool FrameAttributes::isVisible() const
{
    return d->visible;
}

void FrameAttributes::setPen( const QPen & pen )
{
    d->pen = pen;
}

QPen FrameAttributes::pen() const
{
    return d->pen;
}

void FrameAttributes::setCornerRadius(qreal radius)
{
    d->cornerRadius = radius;
}

qreal FrameAttributes::cornerRadius() const
{
    return d->cornerRadius;
}

void FrameAttributes::setPadding( int padding )
{
    d->padding = padding;
}

int FrameAttributes::padding() const
{
    return d->padding;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KChart::FrameAttributes& fa)
{
    dbg << "KChart::FrameAttributes("
	<< "visible="<<fa.isVisible()
	<< "pen="<<fa.pen()
        << "cornerRadius="<<fa.cornerRadius()
        << "padding="<<fa.padding()
	<< ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
