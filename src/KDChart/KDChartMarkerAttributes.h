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

#ifndef KDCHARTMARKERATTRIBUTES_H
#define KDCHARTMARKERATTRIBUTES_H

#include <QMetaType>
#include "KDChartGlobal.h"

QT_BEGIN_NAMESPACE
class QColor;
class QSizeF;
class QPen;
class QPainterPath;
class QDebug;
template <typename T, typename K> class QMap;
QT_END_NAMESPACE

namespace KDChart {

    /**
      * @brief A set of attributes controlling the appearance of data set markers
      */
    class KDE_KDCHART_EXPORT MarkerAttributes
    {
    public:
        MarkerAttributes();
        MarkerAttributes( const MarkerAttributes& );
        MarkerAttributes &operator= ( const MarkerAttributes& );

        ~MarkerAttributes();

        enum MarkerStyle { NoMarker = 0,
                           MarkerCircle  = 1,
                           MarkerSquare  = 2,
                           MarkerDiamond = 3,
                           Marker1Pixel  = 4,
                           Marker4Pixels = 5,
                           MarkerRing    = 6,
                           MarkerCross   = 7,
                           MarkerFastCross = 8,
                           MarkerArrowDown     =  9,
                           MarkerArrowUp       = 10,
                           MarkerArrowRight    = 11,
                           MarkerArrowLeft     = 12,
                           MarkerBowTie        = 13,
                           MarkerHourGlass     = 14,
                           MarkerStar          = 15,
                           MarkerX             = 16,
                           MarkerAsterisk      = 17,
                           MarkerHorizontalBar = 18,
                           MarkerVerticalBar   = 19,
                           PainterPathMarker = 255,
                           StartCustomMarkers = 256 };

        void setVisible( bool visible );
        bool isVisible() const;

        typedef QMap<uint, uint> MarkerStylesMap;
        void setMarkerStylesMap( const MarkerStylesMap & map );
        MarkerStylesMap markerStylesMap() const;

        void setThreeD( bool value );
        bool threeD() const;

        /**
         * Set the marker-style to use. This could be either one of the
         * predefined \a MarkerStyle or a custom one that has a value
         * bigger or equal to StartCustomMarkers.
         *
         * Such a custom marker does then allow to fetch a custom pixmap
         * for each point (value pair) from the model using the
         * Qt::DecorationRole .
         */
        void setMarkerStyle( uint style );
        uint markerStyle() const;

        /**
         * Normally you need to specify a valid QSizeF here, but for Legends you can
         * use the invalid size QSizeF(), to enable automatic marker size calculation:
         *
         * For Markers shown in a Legend this means the marker size will be equal to
         * the font height used for the labels that are shown next to the markers.
         */
        void setMarkerSize( const QSizeF& size );
        QSizeF markerSize() const;

        void setMarkerColor( const QColor& color );
        QColor markerColor() const;

        void setCustomMarkerPath( const QPainterPath& path );
        QPainterPath customMarkerPath() const;

        void setPen( const QPen& pen );
        QPen pen() const;

        bool operator==( const MarkerAttributes& ) const;
        bool operator!=( const MarkerAttributes& ) const;

    private:
        KDCHART_DECLARE_PRIVATE_BASE_VALUE( MarkerAttributes )
    }; // End of class MarkerAttributes

    inline bool MarkerAttributes::operator!=( const MarkerAttributes & other ) const { return !operator==( other ); }
}

#ifndef QT_NO_DEBUG_STREAM
KDE_KDCHART_EXPORT QDebug operator<<( QDebug, const KDChart::MarkerAttributes & );
#endif

KDCHART_DECLARE_SWAP_SPECIALISATION( KDChart::MarkerAttributes )

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO( KDChart::MarkerAttributes, Q_MOVABLE_TYPE );
QT_END_NAMESPACE

Q_DECLARE_METATYPE( KDChart::MarkerAttributes )

#endif // KDCHARTMARKERATTRIBUTES_H
