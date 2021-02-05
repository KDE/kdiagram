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

#include "KChartAbstractTernaryDiagram.h"
#include "KChartAbstractTernaryDiagram_p.h"

#include "KChartTernaryCoordinatePlane.h"

using namespace KChart;

AbstractTernaryDiagram::Private::Private()
    : AbstractDiagram::Private()
{
}

void AbstractTernaryDiagram::init()
{
}

#define d d_func()

AbstractTernaryDiagram::AbstractTernaryDiagram( QWidget* parent,
                                                TernaryCoordinatePlane* plane )
    : AbstractDiagram( parent, plane )
{
}

AbstractTernaryDiagram::~AbstractTernaryDiagram()
{
    while ( ! d->axesList.isEmpty() ) {
        TernaryAxis* axis = d->axesList.takeFirst();
        delete axis;
    }
}

void AbstractTernaryDiagram::addAxis( TernaryAxis* axis )
{
    d->axesList.append( axis );
    // FIXME update
}

void AbstractTernaryDiagram::takeAxis( TernaryAxis* axis )
{

    int index = d->axesList.indexOf( axis );
    if ( index != -1 )
        d->axesList.removeAt( index );
    // FIXME update
}

TernaryAxisList AbstractTernaryDiagram::axes() const
{
    return d->axesList;
}

void AbstractTernaryDiagram::paint (PaintContext *paintContext)
{
    d->paint( paintContext );
}

