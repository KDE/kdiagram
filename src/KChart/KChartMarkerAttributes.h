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

#ifndef KCHARTMARKERATTRIBUTES_H
#define KCHARTMARKERATTRIBUTES_H

#include <QMetaType>
#include "KChartGlobal.h"

QT_BEGIN_NAMESPACE
class QColor;
class QSizeF;
class QPen;
class QPainterPath;
class QDebug;
template <typename T, typename K> class QMap;
QT_END_NAMESPACE

namespace KChart {

    /**
      * @brief A set of attributes controlling the appearance of data set markers
      */
    class KCHART_EXPORT MarkerAttributes
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

        enum MarkerSizeMode {
            /// the marker size is directly specified in pixels
            AbsoluteSize = 0,
            /// the marker size is specified in pixels, but scaled by the
            /// painter's zoom level
            AbsoluteSizeScaled = 1,
            /// the marker size is relative to the diagram's min(width, height)
            RelativeToDiagramWidthHeightMin = 2 };

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

        /**
         * With this method you can change the way the actual marker size is
         * calculated.
         *
         * By default, the marker size is absolute (equiv. to @a mode = AbsoluteSize)
         * and specifies the size in pixels.
         *
         * In any other case, the size specified will be relative to what is
         * specified in @a mode, e.g. the diagram's width. A marker width or
         * height of 1.0 is then 100% of the diagram's width.
         */
        void setMarkerSizeMode( MarkerSizeMode mode );
        MarkerSizeMode markerSizeMode() const;

        void setMarkerColor( const QColor& color );
        QColor markerColor() const;

        void setCustomMarkerPath( const QPainterPath& path );
        QPainterPath customMarkerPath() const;

        void setPen( const QPen& pen );
        QPen pen() const;

        bool operator==( const MarkerAttributes& ) const;
        bool operator!=( const MarkerAttributes& ) const;

    private:
        KCHART_DECLARE_PRIVATE_BASE_VALUE( MarkerAttributes )
    }; // End of class MarkerAttributes

    inline bool MarkerAttributes::operator!=( const MarkerAttributes & other ) const { return !operator==( other ); }
}

#ifndef QT_NO_DEBUG_STREAM
KCHART_EXPORT QDebug operator<<( QDebug, const KChart::MarkerAttributes & );
#endif

KCHART_DECLARE_SWAP_SPECIALISATION( KChart::MarkerAttributes )

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO( KChart::MarkerAttributes, Q_MOVABLE_TYPE );
QT_END_NAMESPACE

Q_DECLARE_METATYPE( KChart::MarkerAttributes )

#endif // KCHARTMARKERATTRIBUTES_H
