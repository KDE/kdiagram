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

#ifndef KCHARTABSTRACTTHREEDATTRIBUTES_H
#define KCHARTABSTRACTTHREEDATTRIBUTES_H

#include <QMetaType>
#include "KChartGlobal.h"

namespace KChart {

/**
  * @brief Base class for 3D attributes
  */
class KCHART_EXPORT AbstractThreeDAttributes
{
public:
    AbstractThreeDAttributes();
    AbstractThreeDAttributes( const AbstractThreeDAttributes& );
    AbstractThreeDAttributes &operator= ( const AbstractThreeDAttributes& );

    virtual ~AbstractThreeDAttributes() = 0;

    void setEnabled( bool enabled );
    bool isEnabled() const;

    void setDepth( qreal depth );
    qreal depth() const;

    // returns the depth(), if is isEnabled() is true, otherwise returns 0.0
    qreal validDepth() const;

    bool isThreeDBrushEnabled() const;
    void setThreeDBrushEnabled( bool enabled );
    virtual QBrush threeDBrush( const QBrush& brush, const QRectF& rect ) const;

    bool operator==( const AbstractThreeDAttributes& ) const;
    inline bool operator!=( const AbstractThreeDAttributes& other ) const { return !operator==(other); }

    KCHART_DECLARE_PRIVATE_BASE_POLYMORPHIC(AbstractThreeDAttributes)

    KCHART_DECLARE_SWAP_BASE(AbstractThreeDAttributes)

}; // End of class AbstractThreeDAttributes

}

#if !defined(QT_NO_DEBUG_STREAM)
KCHART_EXPORT QDebug operator<<(QDebug, const KChart::AbstractThreeDAttributes& );
#endif /* QT_NO_DEBUG_STREAM */



#endif // KCHARTABSTRACTTHREEDATTRIBUTES_H
