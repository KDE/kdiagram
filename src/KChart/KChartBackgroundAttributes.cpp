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

#include "KChartBackgroundAttributes.h"

#include "KChartMath_p.h"

#include <QPixmap>

#define d d_func()


using namespace KChart;

class Q_DECL_HIDDEN BackgroundAttributes::Private
{
    friend class KChart::BackgroundAttributes;
public:
    Private();
private:
    bool visible;
    QBrush brush;
    BackgroundPixmapMode pixmapMode;
    QPixmap pixmap;
};

BackgroundAttributes::Private::Private() :
    visible( false ),
    pixmapMode( BackgroundAttributes::BackgroundPixmapModeNone )
{
}


BackgroundAttributes::BackgroundAttributes()
    : _d( new Private() )
{
}

BackgroundAttributes::BackgroundAttributes( const BackgroundAttributes& r )
    : _d( new Private( *r.d ) )
{
}

BackgroundAttributes & BackgroundAttributes::operator=( const BackgroundAttributes& r )
{
    if ( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

bool BackgroundAttributes::operator==( const BackgroundAttributes& r ) const
{
    return isEqualTo( r );
}


bool BackgroundAttributes::isEqualTo(
        const BackgroundAttributes& other, bool ignorePixmap ) const
{
    /*
    qDebug() << "BackgroundAttributes::operator==";
    qDebug() << "isVisible" << (isVisible() == other.isVisible());
    qDebug() << "brush"     << (brush() == other.brush());
    qDebug() << "pixmapMode"<< (pixmapMode() == other.pixmapMode());
    qDebug() << "pixmap"    << (pixmap().serialNumber() == other.pixmap().serialNumber());
    */
    return (
            isVisible()  == other.isVisible() &&
            brush()      == other.brush() &&
            pixmapMode() == other.pixmapMode() &&
            (ignorePixmap ||
            pixmap().cacheKey() == other.pixmap().cacheKey()) );
}


BackgroundAttributes::~BackgroundAttributes()
{
    delete _d; _d = nullptr;
}




void BackgroundAttributes::setVisible( bool visible )
{
    d->visible = visible;
}


bool BackgroundAttributes::isVisible() const
{
    return d->visible;
}

void BackgroundAttributes::setBrush( const QBrush &brush )
{
    d->brush = brush;
}

QBrush BackgroundAttributes::brush() const
{
    return d->brush;
}

void BackgroundAttributes::setPixmapMode( BackgroundPixmapMode mode )
{
    d->pixmapMode = mode;
}

BackgroundAttributes::BackgroundPixmapMode BackgroundAttributes::pixmapMode() const
{
    return d->pixmapMode;
}

void BackgroundAttributes::setPixmap( const QPixmap &backPixmap )
{
    d->pixmap = backPixmap;
}

QPixmap BackgroundAttributes::pixmap() const
{
    return d->pixmap;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KChart::BackgroundAttributes& ba)
{
    dbg << "KChart::BackgroundAttributes("
	<< "visible="<<ba.isVisible()
	<< "brush="<<ba.brush()
	<< "pixmapmode="<<ba.pixmapMode()
	<< "pixmap="<<ba.pixmap().cacheKey()
	<< ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
