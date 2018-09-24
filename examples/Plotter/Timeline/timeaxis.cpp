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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "timeaxis.h"

#include <QDateTime>

TimeAxis::TimeAxis( KChart::AbstractCartesianDiagram* parent )
    : KChart::CartesianAxis( parent )
{
    // Intentionally left blank
}

const QString TimeAxis::customizedLabel( const QString& label ) const
{
    // Here we are free to format the value to whatever we want. As example we
    // could also return a scientific notation with something like the following
    // both lines;
    //const int precision = 2;
    //return QString::number(label.toReal(), 'E', precision);

    // Format the time-value to a nice string representation.
    const QDateTime dateTime = QDateTime::fromTime_t( label.toDouble() * 3600.0 );
    return dateTime.date().toString();
}
