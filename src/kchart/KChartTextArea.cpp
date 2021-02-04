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

#include "KChartTextArea.h"
#include "KChartTextArea_p.h"

#include "KChartMath_p.h"

#include <qglobal.h>

#include <QPainter>
#include <QRect>


using namespace KChart;

TextArea::Private::Private() :
    AbstractAreaBase::Private()
{
    // this bloc left empty intentionally
}


TextArea::Private::~Private()
{
    // this bloc left empty intentionally
}


TextArea::TextArea()
    : QObject()
    , KChart::AbstractAreaBase()
    , KChart::TextLayoutItem()
{
    // this bloc left empty intentionally
}

TextArea::~TextArea()
{
    // this bloc left empty intentionally
}


void TextArea::init()
{
    // this bloc left empty intentionally
}

void TextArea::paintIntoRect( QPainter& painter, const QRect& rect )
{
    const QRect oldGeometry( geometry() );
    if ( oldGeometry != rect )
        setGeometry( rect );
    painter.translate( rect.left(), rect.top() );
    paintAll( painter );
    painter.translate( -rect.left(), -rect.top() );
    if ( oldGeometry != rect )
        setGeometry( oldGeometry );
}

void TextArea::paintAll( QPainter& painter )
{
    // Paint the background and frame
    paintBackground( painter, geometry() );
    paintFrame( painter, geometry() );

    // temporarily adjust the widget size, to be sure all content gets calculated
    // to fit into the inner rectangle
    const QRect oldGeometry( areaGeometry() );
    QRect inner( innerRect() );
    inner.moveTo(
        oldGeometry.left() + inner.left(),
        oldGeometry.top()  + inner.top() );
    const bool needAdjustGeometry = oldGeometry != inner;
    if ( needAdjustGeometry )
        setGeometry( inner );
    paint( &painter );
    if ( needAdjustGeometry )
        setGeometry( oldGeometry );
    //qDebug() << "TextAreaWidget::paintAll() done.";
}

QRect TextArea::areaGeometry() const
{
    return geometry();
}

void TextArea::positionHasChanged()
{
    Q_EMIT positionChanged( this );
}

