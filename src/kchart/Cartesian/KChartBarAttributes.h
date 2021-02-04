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

#ifndef KCHARTBARATTRIBUTES_H
#define KCHARTBARATTRIBUTES_H

#include <QMetaType>
#include "KChartGlobal.h"

namespace KChart {

/**
  * @brief Set of attributes for changing the appearance of bar charts
  */
class KCHART_EXPORT BarAttributes
{
public:
    BarAttributes();
    BarAttributes( const BarAttributes& );
    BarAttributes &operator= ( const BarAttributes& );

    ~BarAttributes();

    void setFixedDataValueGap( qreal gap );
    qreal fixedDataValueGap() const;

    void setUseFixedDataValueGap( bool gapIsFixed );
    bool useFixedDataValueGap() const;

    void setFixedValueBlockGap( qreal gap );
    qreal fixedValueBlockGap() const;

    void setUseFixedValueBlockGap( bool gapIsFixed );
    bool useFixedValueBlockGap() const;

    void setFixedBarWidth( qreal width );
    qreal fixedBarWidth() const;

    void setUseFixedBarWidth( bool useFixedBarWidth );
    bool useFixedBarWidth() const;

    void setGroupGapFactor ( qreal gapFactor );
    qreal groupGapFactor() const;

    void setBarGapFactor( qreal gapFactor );
    qreal barGapFactor() const;

    void setDrawSolidExcessArrows( bool solidArrows );
    bool drawSolidExcessArrows() const;

    bool operator==( const BarAttributes& ) const;
    inline bool operator!=( const BarAttributes& other ) const { return !operator==(other); }

private:
    class Private;
    Private * _d;
    Private * d_func() { return _d; }
    const Private * d_func() const { return _d; }
}; // End of class BarAttributes

}

Q_DECLARE_METATYPE( KChart::BarAttributes )

#endif // KCHARTBARATTRIBUTES_H
