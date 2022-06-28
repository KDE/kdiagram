/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartLeveyJenningsDiagram_p.h"

#include "KChartDataValueAttributes.h"

using namespace KChart;

LeveyJenningsDiagram::Private::Private( const Private& rhs )
    : LineDiagram::Private( rhs ),
      lotChangedPosition( rhs.lotChangedPosition ),
      fluidicsPackChangedPosition( rhs.fluidicsPackChangedPosition ),
      sensorChangedPosition( rhs.sensorChangedPosition ),
      fluidicsPackChanges( rhs.fluidicsPackChanges ),
      sensorChanges( rhs.sensorChanges ),
      scanLinePen( rhs.scanLinePen ),
      icons( rhs.icons ),
      expectedMeanValue( rhs.expectedMeanValue ),
      expectedStandardDeviation( rhs.expectedStandardDeviation )
{
}

void LeveyJenningsDiagram::Private::setYAxisRange() const
{
    CartesianCoordinatePlane* const plane = static_cast< CartesianCoordinatePlane* >( diagram->coordinatePlane() );
    if ( plane == nullptr )
        return;

    plane->setVerticalRange( QPair< qreal, qreal >( expectedMeanValue - 4 * expectedStandardDeviation, 
                                                    expectedMeanValue + 4 * expectedStandardDeviation ) );
}
