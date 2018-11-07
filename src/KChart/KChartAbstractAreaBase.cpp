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

#include "KChartAbstractAreaBase.h"
#include "KChartAbstractAreaBase_p.h"

#include <KChartBackgroundAttributes.h>
#include <KChartFrameAttributes.h>
#include <KChartTextAttributes.h>
#include "KChartPainterSaver_p.h"
#include "KChartPrintingParameters.h"
#include "KChartMath_p.h"

#include <QPainter>


using namespace KChart;

AbstractAreaBase::Private::Private() :
    visible( true )
{
    init();
}


AbstractAreaBase::Private::~Private() {}


void AbstractAreaBase::Private::init()
{
}


AbstractAreaBase::AbstractAreaBase() :
    _d( new Private() )
{
}

AbstractAreaBase::~AbstractAreaBase()
{
    delete _d; _d = nullptr;
}


void AbstractAreaBase::init()
{
}


#define d d_func()

bool AbstractAreaBase::compare( const AbstractAreaBase* other ) const
{
    if ( other == this ) return true;
    if ( !other ) {
        return false;
    }
    return  (frameAttributes()      == other->frameAttributes()) &&
            (backgroundAttributes() == other->backgroundAttributes());
}

void AbstractAreaBase::alignToReferencePoint( const RelativePosition& position )
{
    Q_UNUSED( position );
    // PENDING(kalle) FIXME
    qWarning( "Sorry, not implemented: void AbstractAreaBase::alignToReferencePoint( const RelativePosition& position )" );
}

void AbstractAreaBase::setFrameAttributes( const FrameAttributes &a )
{
    if ( d->frameAttributes == a )
        return;

    d->frameAttributes = a;
    positionHasChanged();
}

FrameAttributes AbstractAreaBase::frameAttributes() const
{
    return d->frameAttributes;
}

void AbstractAreaBase::setBackgroundAttributes( const BackgroundAttributes &a )
{
    if ( d->backgroundAttributes == a )
        return;

    d->backgroundAttributes = a;
    positionHasChanged();
}

BackgroundAttributes AbstractAreaBase::backgroundAttributes() const
{
    return d->backgroundAttributes;
}


/* static */
void AbstractAreaBase::paintBackgroundAttributes( QPainter& painter, const QRect& rect,
    const KChart::BackgroundAttributes& attributes )
{
    if ( !attributes.isVisible() ) return;

    /* first draw the brush (may contain a pixmap)*/
    if ( Qt::NoBrush != attributes.brush().style() ) {
        KChart::PainterSaver painterSaver( &painter );
        painter.setPen( Qt::NoPen );
        const QPointF newTopLeft( painter.deviceMatrix().map( rect.topLeft() ) );
        painter.setBrushOrigin( newTopLeft );
        painter.setBrush( attributes.brush() );
        painter.drawRect( rect.adjusted( 0, 0, -1, -1 ) );
    }
    /* next draw the backPixmap over the brush */
    if ( !attributes.pixmap().isNull() &&
        attributes.pixmapMode() != BackgroundAttributes::BackgroundPixmapModeNone ) {
        QPointF ol = rect.topLeft();
        if ( BackgroundAttributes::BackgroundPixmapModeCentered == attributes.pixmapMode() )
        {
            ol.setX( rect.center().x() - attributes.pixmap().width() / 2 );
            ol.setY( rect.center().y() - attributes.pixmap().height()/ 2 );
            painter.drawPixmap( ol, attributes.pixmap() );
        } else {
            QMatrix m;
            qreal zW = (qreal)rect.width()  / (qreal)attributes.pixmap().width();
            qreal zH = (qreal)rect.height() / (qreal)attributes.pixmap().height();
            switch ( attributes.pixmapMode() ) {
            case BackgroundAttributes::BackgroundPixmapModeScaled:
            {
                qreal z;
                z = qMin( zW, zH );
                m.scale( z, z );
            }
            break;
            case BackgroundAttributes::BackgroundPixmapModeStretched:
                m.scale( zW, zH );
                break;
            default:
                ; // Cannot happen, previously checked
            }
            QPixmap pm = attributes.pixmap().transformed( m );
            ol.setX( rect.center().x() - pm.width() / 2 );
            ol.setY( rect.center().y() - pm.height()/ 2 );
            painter.drawPixmap( ol, pm );
        }
    }
}

/* static */
void AbstractAreaBase::paintFrameAttributes( QPainter& painter, const QRect& rect,
    const KChart::FrameAttributes& attributes )
{

    if ( !attributes.isVisible() ) return;

    // Note: We set the brush to NoBrush explicitly here.
    //       Otherwise we might get a filled rectangle, so any
    //       previously drawn background would be overwritten by that area.

    const QPen oldPen( painter.pen() );
    const QBrush oldBrush( painter.brush() );

    painter.setPen( PrintingParameters::scalePen( attributes.pen() ) );
    painter.setBrush( Qt::NoBrush );
    painter.drawRoundedRect( rect.adjusted( 0, 0, -1, -1 ), attributes.cornerRadius(), attributes.cornerRadius() );

    painter.setBrush( oldBrush );
    painter.setPen( oldPen );
}

void AbstractAreaBase::paintBackground( QPainter& painter, const QRect& rect )
{
    Q_ASSERT_X ( d != nullptr, "AbstractAreaBase::paintBackground()",
                "Private class was not initialized!" );

    PainterSaver painterSaver( &painter );

    const qreal radius = d->frameAttributes.cornerRadius();
    QPainterPath path;
    path.addRoundedRect( rect.adjusted( 0, 0, -1, -1 ), radius, radius );
    painter.setClipPath(path);

    paintBackgroundAttributes( painter, rect, d->backgroundAttributes );
}


void AbstractAreaBase::paintFrame( QPainter& painter, const QRect& rect )
{
    Q_ASSERT_X ( d != nullptr, "AbstractAreaBase::paintFrame()",
                "Private class was not initialized!" );
    paintFrameAttributes( painter, rect, d->frameAttributes );
}


void AbstractAreaBase::getFrameLeadings(int& left, int& top, int& right, int& bottom ) const
{
    int padding = 0;
    if ( d && d->frameAttributes.isVisible() ) {
        padding = qMax( d->frameAttributes.padding(), 0 );
    }
    left = padding;
    top = padding;
    right = padding;
    bottom = padding;
}

QRect AbstractAreaBase::innerRect() const
{
    int left;
    int top;
    int right;
    int bottom;
    getFrameLeadings( left, top, right, bottom );
    return QRect ( QPoint( 0, 0 ), areaGeometry().size() ).adjusted( left, top, -right, -bottom );
}

void AbstractAreaBase::positionHasChanged()
{
    // this bloc left empty intentionally
}
