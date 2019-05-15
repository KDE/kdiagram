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

#ifndef KCHARTVALUETRACKERATTRIBUTES_H
#define KCHARTVALUETRACKERATTRIBUTES_H

#include <QDebug>
#include <QMetaType>
#include "KChartGlobal.h"

namespace KChart {

    /**
     * \class ValueTrackerAttributes KChartValueTrackerAttributes.h KChartValueTrackerAttributes
     * \brief Cell-specific attributes regarding value tracking
     *
     * ValueTrackerAttributes groups the properties regarding
     * value tracking, and how it is displayed.
     * Value tracking can be used to emphasize on one or several
     * specific points in a line diagram.
   */

    class KCHART_EXPORT ValueTrackerAttributes
    {
        public:
            ValueTrackerAttributes();
            ValueTrackerAttributes( const ValueTrackerAttributes& );
            ValueTrackerAttributes &operator= ( const ValueTrackerAttributes& );

            ~ValueTrackerAttributes();

            /** Set the pen the value tracking lines and markers will be drawn with
             * \param pen The pen the lines and markers will be drawn with
             */
            void setPen( const QPen& pen );

            /**
             * @return The pen the lines and markers are drawn with
             */
            QPen pen() const;

            void setLinePen( const QPen &pen );
            QPen linePen() const;

            void setMarkerPen( const QPen &pen );
            QPen markerPen() const;

            void setMarkerBrush( const QBrush &brush );
            QBrush markerBrush() const;

            void setArrowBrush( const QBrush &brush );
            QBrush arrowBrush() const;

            /** Set the brush the area below the value tracking
             * lines should be filled with. Default is a black brush
             * with the style Qt::NoBrush.
             * \param brush The brush the area should be filled with
             */
            void setAreaBrush( const QBrush& brush );

            /**
             * @return The brush the area below the value tracking lines is filled with
             */
            QBrush areaBrush() const;

            /** Set the size of the markers. This includes both the arrows at
             * the axises and the circle at the data point.
             * \param size The size of the markers
             */
            void setMarkerSize( const QSizeF& size );

            /**
             * @return The size of the markers
             */
            QSizeF markerSize() const;

            /**
             * @return The orientations used to show the value tracking. Using only a
             * vertical line, horizontal line or both (the default).
             */
            Qt::Orientations orientations() const;

            /** Set the orientations used to show the value tracking.
             * \param orientations The orientations of the value tracking lines.
             */
            void setOrientations( Qt::Orientations orientations );

            /** Set whether value tracking should be enabled for a specific
             * index or not
             * \param enabled Whether value tracking should be enabled or not
             */
            void setEnabled( bool enabled );

            /**
             * @return Whether value tracking is enabled or not
             */
            bool isEnabled() const;

            bool operator==( const ValueTrackerAttributes& ) const;
            inline bool operator!=( const ValueTrackerAttributes& other ) const { return !operator==(other); }

        private:
            KCHART_DECLARE_PRIVATE_BASE_VALUE( ValueTrackerAttributes )
    }; // End of class ValueTrackerAttributes

}

#if !defined(QT_NO_DEBUG_STREAM)
KCHART_EXPORT QDebug operator<<(QDebug, const KChart::ValueTrackerAttributes& );
#endif /* QT_NO_DEBUG_STREAM */

KCHART_DECLARE_SWAP_SPECIALISATION( KChart::ValueTrackerAttributes )

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO( KChart::ValueTrackerAttributes, Q_MOVABLE_TYPE );
QT_END_NAMESPACE

Q_DECLARE_METATYPE( KChart::ValueTrackerAttributes )

#endif // KCHARTVALUETRACKERATTRIBUTES_H
