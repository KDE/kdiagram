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

#include "TernaryConstants.h"

#include <cmath>

using namespace std;

using namespace std;

extern const qreal Sqrt3 = sqrt( 3.0 );
extern const qreal TriangleWidth = 1.0;
extern const qreal TriangleHeight = 0.5 * Sqrt3;
extern const QPointF TriangleTop( 0.5, TriangleHeight );
extern const QPointF TriangleBottomLeft( 0.0, 0.0 );
extern const QPointF TriangleBottomRight( 1.0, 0.0 );
extern const QPointF AxisVector_C_A( TriangleTop - TriangleBottomRight );
extern const QPointF Norm_C_A( -AxisVector_C_A.y(), AxisVector_C_A.x() );
extern const QPointF AxisVector_B_A( TriangleTop );
extern const QPointF Norm_B_A( -AxisVector_B_A.y(), AxisVector_B_A.x() );
extern const QPointF AxisVector_B_C( TriangleBottomRight );
extern const QPointF Norm_B_C( -AxisVector_B_C.y(), AxisVector_B_C.x() );

extern const qreal RelMarkerLength = 0.03 * TriangleWidth;
extern const QPointF FullMarkerDistanceBC( RelMarkerLength * Norm_B_C );
extern const QPointF FullMarkerDistanceAC( -RelMarkerLength * Norm_C_A );
extern const QPointF FullMarkerDistanceBA( RelMarkerLength * Norm_B_A );

