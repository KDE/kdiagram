/**
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

#include "zoomwidget.h"
#include <KChartAbstractCoordinatePlane>
#include <QWheelEvent>
#include <QDebug>

ZoomWidget::ZoomWidget( QWidget* parent ) :
    KChart::Widget( parent )
{
    setFocusPolicy( Qt::WheelFocus );
}


QPointF ZoomWidget::findNewZoomCenter( const QPoint & pos )
{
    if ( ! height() || ! width() ) return coordinatePlane()->zoomCenter();

    const qreal coordWidth = 1.0;
    const qreal coordHeight = 1.0;

//    qDebug() << "pos = " << pos;
    const qreal resX = static_cast<qreal>( coordWidth /coordinatePlane()->zoomFactorX() )/ width();
    const qreal resY = static_cast<qreal>( coordHeight/coordinatePlane()->zoomFactorY() )/ height();
//    qDebug() << "resX = " << resX << "  resY = " << resY;
    const qreal dX = (pos.x() - 0.5*width() ) * resX;
    const qreal dY = (pos.y() - 0.5*height()) * resY;
//    qDebug() << "dX = " << dX << "  dY = " << dY;
    const qreal zoomCenterX = coordinatePlane()->zoomCenter().x() + dX;
    const qreal zoomCenterY = coordinatePlane()->zoomCenter().y() + dY;
    return QPointF( zoomCenterX, zoomCenterY );
}


void ZoomWidget::mousePressEvent( QMouseEvent * e )
{
    const QPointF zoomCenter( findNewZoomCenter( e->pos() ) );
    if ( zoomCenter != coordinatePlane()->zoomCenter() ) {
//        qDebug() << "zoom center = " << zoomCenter;
        coordinatePlane()->setZoomCenter( zoomCenter );
        update();
    }
}


void ZoomWidget::wheelEvent( QWheelEvent* e )
{
    qreal delta = static_cast<qreal>( e->angleDelta().y() ) / 120.0 / 10.0;
    coordinatePlane()->setZoomFactorX( coordinatePlane()->zoomFactorX() + delta );
    coordinatePlane()->setZoomFactorY( coordinatePlane()->zoomFactorY() + delta );
/* new:
    const QPointF zoomCenter( findNewZoomCenter( e->pos() ) );
    if ( zoomCenter != coordinatePlane()->zoomCenter() ) {
        qDebug() << "zoom center = " << zoomCenter;
        coordinatePlane()->setZoomCenter( zoomCenter );
    }
*/
/* old:
    qreal zoomCenterX = static_cast<qreal>( e->pos().x() ) / static_cast<qreal>( width() );
    qreal zoomCenterY = static_cast<qreal>( e->pos().y() ) / static_cast<qreal>( height() );
    QPointF zoomCenter( zoomCenterX, zoomCenterY );
    coordinatePlane()->setZoomCenter( zoomCenter );
*/
    update();
}

void ZoomWidget::keyPressEvent( QKeyEvent* e )
{
    int dZoom = 0;
    qreal dX = 0;
    qreal dY = 0;
    switch ( e->key() ) {
        case Qt::Key_PageDown:
            dZoom = 1;
            break;
        case Qt::Key_Down:
            dY = 0.1;
            break;
        case Qt::Key_Right:
            dX = 0.1;
            break;
        case Qt::Key_PageUp:
            dZoom = -1;
            break;
        case Qt::Key_Up:
            dY = -0.1;
            break;
        case Qt::Key_Left:
            dX = -0.1;
            break;
        default:
            e->ignore();
    }
    if ( dZoom || dX || dY ) {
        const double factor = qMax( double(1.0), coordinatePlane()->zoomFactorX() + dZoom );
        const qreal x = coordinatePlane()->zoomCenter().x() + dX;
        const qreal y = coordinatePlane()->zoomCenter().y() + dY;
        coordinatePlane()->setZoomFactorX( factor );
        coordinatePlane()->setZoomFactorY( factor );
        coordinatePlane()->setZoomCenter( QPointF(x,y) );
        update();
    }
}
