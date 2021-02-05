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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "KChartTextLabelCache.h"

#include <cmath>

#include <QtDebug>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QApplication>

#ifndef NDEBUG
int HitCount = 0;
int MissCount = 0;
#define INC_HIT_COUNT { ++HitCount; }
#define INC_MISS_COUNT  { ++MissCount; }
#define DUMP_CACHE_STATS \
    if ( HitCount != 0 && MissCount != 0 ) { \
        int total = HitCount + MissCount; \
        qreal hitQuote = ( 1.0 * HitCount ) / total; \
        qDebug() << "PrerenderedLabel dtor: hits/misses/total:" \
        << HitCount << "/" << MissCount << "/" << total \
                 << "(" << 100 * hitQuote << "% hits)"; \
    }
#else
#define INC_HIT_COUNT
#define INC_MISS_COUNT
#define DUMP_CACHE_STATS
#endif

PrerenderedElement::PrerenderedElement()
    : m_referencePoint( KChartEnums::PositionNorthWest )
{
}

void PrerenderedElement::setPosition( const QPointF& position )
{   // this does not invalidate the element
    m_position = position;
}

const QPointF& PrerenderedElement::position() const
{
    return m_position;
}

void PrerenderedElement::setReferencePoint( KChartEnums::PositionValue point )
{   // this does not invalidate the element
    m_referencePoint = point;
}

KChartEnums::PositionValue PrerenderedElement::referencePoint() const
{
    return m_referencePoint;
}

PrerenderedLabel::PrerenderedLabel()
    : PrerenderedElement()
    , m_dirty( true )
    , m_font( qApp->font() )
    , m_brush( Qt::black )
    , m_pen( Qt::black ) // do not use anything invisible
    , m_angle( 0.0 )
{
}

PrerenderedLabel::~PrerenderedLabel()
{
    DUMP_CACHE_STATS;
}

void PrerenderedLabel::invalidate() const
{
    m_dirty = true;
}

void PrerenderedLabel::setFont( const QFont& font )
{
    m_font = font;
    invalidate();
}

const QFont& PrerenderedLabel::font() const
{
    return m_font;
}

void PrerenderedLabel::setText( const QString& text )
{
    m_text = text;
    invalidate();
}

const QString& PrerenderedLabel::text() const
{
    return m_text;
}

void PrerenderedLabel::setBrush( const QBrush& brush )
{
    m_brush = brush;
    invalidate();
}

const QBrush& PrerenderedLabel::brush() const
{
    return m_brush;
}

void PrerenderedLabel::setAngle( qreal angle )
{
    m_angle = angle;
    invalidate();
}

qreal PrerenderedLabel::angle() const
{
    return m_angle;
}

const QPixmap& PrerenderedLabel::pixmap() const
{
    if ( m_dirty ) {
        INC_MISS_COUNT;
        paint();
    } else {
        INC_HIT_COUNT;
    }
    return m_pixmap;
}

void PrerenderedLabel::paint() const
{
    // FIXME find a better value using font metrics of text (this
    // requires finding the diameter of the circle formed by rotating
    // the bounding rect around the center):
    const int Width = 1000;
    const int Height = Width;

    QRectF boundingRect;
    const QColor FullTransparent( 255, 255, 255, 0 );
#ifdef Q_WS_X11
    QImage pixmap( Width, Height, QImage::Format_ARGB32_Premultiplied );
    qWarning() << "PrerenderedLabel::paint: using QImage for prerendered labels "
               << "to work around XRender/Qt4 bug.";
#else
    QPixmap pixmap( Width, Height );
#endif
    // pixmap.fill( FullTransparent );
    {
        static const QPointF Center ( 0.0, 0.0 );
        QPointF textBottomRight;
        QPainter painter( &pixmap );
        painter.setRenderHint(QPainter::TextAntialiasing, true );
        painter.setRenderHint(QPainter::Antialiasing, true );

        // QImage (X11 workaround) does not have fill():
        painter.setPen( FullTransparent );
        painter.setBrush( FullTransparent );
        QPainter::CompositionMode mode = painter.compositionMode();
        painter.setCompositionMode( QPainter::CompositionMode_Clear );
        painter.drawRect( 0, 0, Width, Height );
        painter.setCompositionMode( mode );

        QMatrix matrix;
        matrix.translate( 0.5 * Width,  0.5 * Height );
        matrix.rotate( m_angle );
        painter.setWorldMatrix( matrix );

        painter.setPen( m_pen );
        painter.setBrush( m_brush );
        painter.setFont( m_font );
        QRectF container( -0.5 * Width, -0.5 * Height, Width, 0.5 * Height );
        painter.drawText( container, Qt::AlignHCenter | Qt::AlignBottom,
                          m_text, &boundingRect );
        m_referenceBottomLeft = QPointF( boundingRect.bottomLeft().x(), 0.0 );
        textBottomRight = QPointF( boundingRect.bottomRight().x(), 0.0 );
        m_textAscendVector = boundingRect.topRight() - textBottomRight;
        m_textBaseLineVector = textBottomRight - m_referenceBottomLeft;

        // FIXME translate topright by char height
        boundingRect = matrix.mapRect( boundingRect );
        m_referenceBottomLeft = matrix.map( m_referenceBottomLeft )
                                - boundingRect.topLeft();
        textBottomRight = matrix.map( textBottomRight )
                          - boundingRect.topLeft();
        m_textAscendVector = matrix.map( m_textAscendVector )
                             - matrix.map( Center );
        m_textBaseLineVector = matrix.map( m_textBaseLineVector )
                            - matrix.map( Center );
    }

    m_dirty = false; // now all the calculation vectors are valid

    QPixmap temp( static_cast<int>( boundingRect.width() ),
                  static_cast<int>( boundingRect.height() ) );
    {
        temp.fill( FullTransparent );
        QPainter painter( &temp );
#ifdef Q_WS_X11
        painter.drawImage( QPointF( 0.0, 0.0 ), pixmap, boundingRect );
#else
        painter.drawPixmap( QPointF( 0.0, 0.0 ), pixmap, boundingRect );
#endif
// #define PRERENDEREDLABEL_DEBUG
#ifdef PRERENDEREDLABEL_DEBUG
        painter.setPen( QPen( Qt::red, 2 ) );
        painter.setBrush( Qt::red );
        // paint markers for the reference points
        QList<KChartEnums::PositionValue> positions;
        positions << KChartEnums::PositionCenter
                  << KChartEnums::PositionNorthWest
                  << KChartEnums::PositionNorth
                  << KChartEnums::PositionNorthEast
                  << KChartEnums::PositionEast
                  << KChartEnums::PositionSouthEast
                  << KChartEnums::PositionSouth
                  << KChartEnums::PositionSouthWest
                  << KChartEnums::PositionWest;
        Q_FOREACH( KChartEnums::PositionValue position, positions ) { //krazy:exclude=foreach
            static const double Radius = 0.5;
            static const double Diameter = 2 * Radius;

            QPointF point ( referencePointLocation( position ) );
            painter.drawEllipse( QRectF( point - QPointF( Radius, Radius ),
                                         QSizeF( Diameter, Diameter ) ) );
        }
#endif
    }

    m_pixmap = temp;
}

QPointF PrerenderedLabel::referencePointLocation() const
{
    return referencePointLocation( referencePoint() );
}

QPointF PrerenderedLabel::referencePointLocation( KChartEnums::PositionValue position ) const
{
    if ( m_dirty ) {
        INC_MISS_COUNT;
        paint();
    } else {
        INC_HIT_COUNT;
    }

    switch ( position ) {
    case KChartEnums::PositionCenter:
        return m_referenceBottomLeft + 0.5 * m_textBaseLineVector + 0.5 * m_textAscendVector;
    case KChartEnums::PositionNorthWest:
        return m_referenceBottomLeft + m_textAscendVector;
    case KChartEnums::PositionNorth:
        return m_referenceBottomLeft + 0.5 * m_textBaseLineVector + m_textAscendVector;
    case KChartEnums::PositionNorthEast:
        return m_referenceBottomLeft + m_textBaseLineVector + m_textAscendVector;
    case KChartEnums::PositionEast:
        return m_referenceBottomLeft + 0.5 * m_textAscendVector;
    case KChartEnums::PositionSouthEast:
        return m_referenceBottomLeft + m_textBaseLineVector;
    case KChartEnums::PositionSouth:
        return m_referenceBottomLeft + 0.5 * m_textBaseLineVector;
    case KChartEnums::PositionSouthWest:
        return m_referenceBottomLeft;
    case KChartEnums::PositionWest:
        return m_referenceBottomLeft + m_textBaseLineVector + 0.5 * m_textAscendVector;

    case KChartEnums::PositionUnknown: // intentional fall-through
    case KChartEnums::PositionFloating: // intentional fall-through
        return QPointF(); 
    }
    
    return QPointF();
}
