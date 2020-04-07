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

#ifndef KCHARTSTOCKBARATTRIBUTES_H
#define KCHARTSTOCKBARATTRIBUTES_H

#include <QMetaType>
#include "KChartGlobal.h"

namespace KChart {

/**
  * @brief Attributes to customize the appearance of a column in a stock chart
  */
class KCHART_EXPORT StockBarAttributes
{
public:
    StockBarAttributes();
    StockBarAttributes( const StockBarAttributes& );
    StockBarAttributes &operator= ( const StockBarAttributes& );

    ~StockBarAttributes();


    /**
      * Sets the width of a candlestick
      *
      * @param width The width of a candlestick
      */
    void setCandlestickWidth( qreal width );

    /**
      * @return the width of a candlestick
      */
    qreal candlestickWidth() const;

    /**
      * Sets the tick length of both the open and close marker
      *
      * @param length the tick length
      */
    void setTickLength( qreal length );

    /**
      * @return the tick length used for both the open and close marker
      */
    qreal tickLength() const;

    bool operator==( const StockBarAttributes& ) const;
    inline bool operator!=( const StockBarAttributes& other ) const { return !operator==(other); }

private:
    class Private;
    Private * _d;
    Private * d_func() { return _d; }
    const Private * d_func() const { return _d; }
};

}

Q_DECLARE_METATYPE( KChart::StockBarAttributes )

#endif // KCHARTSTOCKBARATTRIBUTES_H
