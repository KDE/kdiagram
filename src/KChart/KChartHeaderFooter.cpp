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

#include "KChartHeaderFooter.h"
#include "KChartHeaderFooter_p.h"

#include "KChartChart.h"
#include <KChartTextAttributes.h>
#include "KTextDocument.h"
#include "KChartMath_p.h"

#include <QFont>
#include <QPainter>
#include <QAbstractTextDocumentLayout>
#include <QTextDocumentFragment>
#include <QTextBlock>
#include <QtDebug>
#include <QLabel>

using namespace KChart;

HeaderFooter::Private::Private() :
    type( Header ),
    position( Position::North )
{
}

HeaderFooter::Private::~Private()
{
}

#define d d_func()

HeaderFooter::HeaderFooter( Chart* parent ) :
    TextArea( new Private() )
{
    setParent( parent );
    init();
}

HeaderFooter::~HeaderFooter()
{
    emit destroyedHeaderFooter( this );
}

void HeaderFooter::setParent( QObject* parent )
{
    QObject::setParent( parent );
    setParentWidget( qobject_cast<QWidget*>( parent ) );
    if ( parent && ! autoReferenceArea() )
        setAutoReferenceArea( parent );
}

void HeaderFooter::init()
{
    TextAttributes ta;
    ta.setPen( QPen(Qt::black) );
    ta.setFont( QFont( QLatin1String( "helvetica" ), 10, QFont::Bold, false ) );

    Measure m( 35.0 );
    m.setRelativeMode( autoReferenceArea(), KChartEnums::MeasureOrientationMinimum );
    ta.setFontSize( m );

    m.setValue( 8.0 );
    m.setCalculationMode( KChartEnums::MeasureCalculationModeAbsolute );
    ta.setMinimalFontSize( m );

    setTextAttributes( ta );
}

/**
  * Creates an exact copy of this header/footer.
  */
HeaderFooter * HeaderFooter::clone() const
{
    HeaderFooter* headerFooter = new HeaderFooter( new Private( *d ), nullptr );
    headerFooter->setType( type() );
    headerFooter->setPosition( position() );
    headerFooter->setText( text() );
    headerFooter->setTextAttributes( textAttributes() );
    return headerFooter;
}

bool HeaderFooter::compare( const HeaderFooter& other ) const
{
    return  (type()           == other.type()) &&
            (position()       == other.position()) &&
            // also compare members inherited from the base class:
            (autoReferenceArea() == other.autoReferenceArea()) &&
            (text()              == other.text()) &&
            (textAttributes()    == other.textAttributes());
}

void HeaderFooter::setType( HeaderFooterType type )
{
    if ( d->type != type ) {
        d->type = type;
        emit positionChanged( this );
    }
}

HeaderFooter::HeaderFooterType HeaderFooter::type() const
{
    return d->type;
}

void HeaderFooter::setPosition( Position position )
{
    if ( d->position != position ) {
        d->position = position;
        emit positionChanged( this );
    }
}

Position HeaderFooter::position() const
{
    return d->position;
}
