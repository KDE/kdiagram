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

#include "KChartLeveyJenningsGridAttributes.h"

#include "KChartMath_p.h"

#include <QBrush>
#include <QMap>
#include <QPen>

#define d d_func()

using namespace KChart;

class Q_DECL_HIDDEN LeveyJenningsGridAttributes::Private
{
    friend class LeveyJenningsGridAttributes;
public:
    Private();
private:
    QMap< GridType, bool > visible;
    QMap< GridType, QPen > pens;
    QMap< LeveyJenningsGridAttributes::Range, QBrush > rangeBrushes;
};

LeveyJenningsGridAttributes::Private::Private()
{
    pens[ Calculated ].setCapStyle( Qt::FlatCap );
    pens[ Calculated ].setColor( Qt::blue );
    pens[ Expected ].setCapStyle( Qt::FlatCap );
    pens[ Expected ].setColor( Qt::black );
    
    visible[ Calculated ] = true;
    visible[ Expected ] = true;
    
    rangeBrushes[ LeveyJenningsGridAttributes::CriticalRange ] = QBrush( QColor( 255, 255, 192 ) );
    rangeBrushes[ LeveyJenningsGridAttributes::OutOfRange ]    = QBrush( QColor( 255, 128, 128 ) );
}


LeveyJenningsGridAttributes::LeveyJenningsGridAttributes()
    : _d( new Private() )
{
    // this bloc left empty intentionally
}

LeveyJenningsGridAttributes::LeveyJenningsGridAttributes( const LeveyJenningsGridAttributes& r )
    : _d( new Private( *r.d ) )
{
}

LeveyJenningsGridAttributes & LeveyJenningsGridAttributes::operator=( const LeveyJenningsGridAttributes& r )
{
    if ( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

LeveyJenningsGridAttributes::~LeveyJenningsGridAttributes()
{
    delete _d; _d = nullptr;
}


bool LeveyJenningsGridAttributes::operator==( const LeveyJenningsGridAttributes& r ) const
{
    return  isGridVisible( Expected ) == r.isGridVisible( Expected ) &&
            isGridVisible( Calculated ) == r.isGridVisible( Calculated ) &&
            gridPen( Expected ) == r.gridPen( Expected ) &&
            gridPen( Calculated ) == r.gridPen( Calculated );
}

void LeveyJenningsGridAttributes::setRangeBrush( Range range, const QBrush& brush )
{
    d->rangeBrushes[ range ] = brush;
}

QBrush LeveyJenningsGridAttributes::rangeBrush( Range range ) const
{
    return d->rangeBrushes[ range ];
}


void LeveyJenningsGridAttributes::setGridVisible( GridType type, bool visible )
{
    d->visible[ type ] = visible;
}

bool LeveyJenningsGridAttributes::isGridVisible( GridType type ) const
{
    return d->visible[ type ];
}

void LeveyJenningsGridAttributes::setGridPen( GridType type, const QPen& pen )
{
    d->pens[ type ] = pen;
    d->pens[ type ].setCapStyle( Qt::FlatCap );
}

QPen LeveyJenningsGridAttributes::gridPen( GridType type ) const
{
    return d->pens[ type ];
}
