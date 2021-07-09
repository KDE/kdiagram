/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
    const QDateTime dateTime = QDateTime::fromSecsSinceEpoch( label.toDouble() * 3600.0 );
    return dateTime.date().toString();
}
