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

#ifndef KCHARTRULERATTRIBUTES_H
#define KCHARTRULERATTRIBUTES_H

#include <QMetaType>
#include "KChartGlobal.h"
#include "KChartEnums.h"

QT_BEGIN_NAMESPACE
class QPen;
QT_END_NAMESPACE

namespace KChart {

/**
  * @brief A set of attributes controlling the appearance of axis rulers
  */
class KCHART_EXPORT RulerAttributes
{
public:
	RulerAttributes();
	RulerAttributes( const RulerAttributes& );
	RulerAttributes &operator= ( const RulerAttributes& );

    ~RulerAttributes();

    /**
      * Sets the pen used to draw the tick marks
      */
    void setTickMarkPen( const QPen& pen );
    QPen tickMarkPen() const;

    /**
      * Sets the pen used to draw major tick marks
      */
    void setMajorTickMarkPen( const QPen& pen );
    bool majorTickMarkPenIsSet() const;
    QPen majorTickMarkPen() const;

    /**
      * Sets the pen used to draw minor tick marks
      */
    void setMinorTickMarkPen( const QPen& pen );
    bool minorTickMarkPenIsSet() const;
    QPen minorTickMarkPen() const;

    /**
      * Sets the pen used to draw the tick mark at a specific value
      *
      * Note: This will not paint a tick mark at the specified value
      * if it wasn't already drawn before.
      */
    void setTickMarkPen( qreal value, const QPen& pen );
    QPen tickMarkPen( qreal value ) const;
    typedef QMap<qreal, QPen> TickMarkerPensMap;
    TickMarkerPensMap tickMarkPens() const;

    bool hasTickMarkPenAt( qreal value) const;

    /**
      * Color setter method provided for convenience
      */
    void setTickMarkColor( const QColor& color );
    QColor tickMarkColor() const;

    /**
      * Shows or hides minor tick marks
      */
    void setShowMinorTickMarks( bool show );
    bool showMinorTickMarks() const;

    /**
     * Set the ruler line pen to @p pen
     */
    void setRulerLinePen(const QPen &pen);
    /** @return the ruler line pen
     */
    QPen rulerLinePen() const;

    void setShowRulerLine( bool show );
    bool showRulerLine() const;

    /**
      * Shows or hides major tick marks
      */
    void setShowMajorTickMarks( bool show );
    bool showMajorTickMarks() const;

    /**
     * Sets the length of major tick marks
     */
    void setMajorTickMarkLength( int length );
    int majorTickMarkLength() const;
    bool majorTickMarkLengthIsSet() const;

    /**
     * Sets the length of minor tick marks
     */
    void setMinorTickMarkLength( int length );
    int minorTickMarkLength() const;
    bool minorTickMarkLengthIsSet() const;

    /**
     * Set margin that should be used between the labels and the ticks. By
     * default the value is -1, which means that half of the label's font
     * height/width should be used as margin.
     */
    void setLabelMargin(int margin);
    int labelMargin() const;

    /**
     * Shows or hides the first tick. This is usually where the axes cross.
     * The tick itself may be obscured by the other axis, but the label will be visible.
     */
    void setShowFirstTick( bool show );
    bool showFirstTick() const;

    bool operator==( const RulerAttributes& ) const;
    inline bool operator!=( const RulerAttributes& other ) const { return !operator==(other); }

private:
    KCHART_DECLARE_PRIVATE_BASE_VALUE( RulerAttributes )
}; // End of class RulerAttributes

}

#if !defined(QT_NO_DEBUG_STREAM)
KCHART_EXPORT QDebug operator<<(QDebug, const KChart::RulerAttributes& );
#endif /* QT_NO_DEBUG_STREAM */

KCHART_DECLARE_SWAP_SPECIALISATION( KChart::RulerAttributes )

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO( KChart::RulerAttributes, Q_MOVABLE_TYPE );
QT_END_NAMESPACE

Q_DECLARE_METATYPE( KChart::RulerAttributes )

#endif // KCHARTRULERATTRIBUTES_H
