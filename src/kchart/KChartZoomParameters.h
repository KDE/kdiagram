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

#ifndef ZOOMPARAMETERS_H
#define ZOOMPARAMETERS_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the KD Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

namespace KChart {
    /**
      * ZoomParameters stores the center and the factor of zooming internally
      * \internal
      */
    class ZoomParameters {
    public:
        ZoomParameters()
        : xFactor( 1.0 ),
          yFactor( 1.0 ),
          xCenter( 0.5 ),
          yCenter( 0.5)
        {
        }

        ZoomParameters( qreal xFactor, qreal yFactor, const QPointF& center )
        : xFactor( xFactor ),
          yFactor( yFactor ),
          xCenter( center.x() ),
          yCenter( center.y() )
        {
        }

        void setCenter( const QPointF& center )
        {
            xCenter = center.x();
            yCenter = center.y();
        }
        const QPointF center() const
        {
            return QPointF( xCenter, yCenter );
        }

        qreal xFactor;
        qreal yFactor;

        qreal xCenter;
        qreal yCenter;
    };
}

#endif
