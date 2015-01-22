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

#ifndef KDCHARTFRAMEATTRIBUTES_H
#define KDCHARTFRAMEATTRIBUTES_H

#include <QDebug>
#include <QMetaType>
#include <QPen>
#include "KDChartGlobal.h"

namespace KDChart {

/**
  * @brief A set of attributes for frames around items
  */
class KDCHART_EXPORT FrameAttributes
{
public:
    FrameAttributes();
    FrameAttributes( const FrameAttributes& );
    FrameAttributes &operator= ( const FrameAttributes& );

    ~FrameAttributes();

    void setVisible( bool visible );
    bool isVisible() const;

    void setPen( const QPen & pen );
    QPen pen() const;

    void setCornerRadius( qreal radius );
    qreal cornerRadius() const;

    void setPadding( int padding );
    int padding() const;

    bool operator==( const FrameAttributes& ) const;
    inline bool operator!=( const FrameAttributes& other ) const { return !operator==(other); }

private:

    KDCHART_DECLARE_PRIVATE_BASE_VALUE( FrameAttributes )
}; // End of class FrameAttributes

}

#if !defined(QT_NO_DEBUG_STREAM)
KDCHART_EXPORT QDebug operator<<(QDebug, const KDChart::FrameAttributes& );
#endif /* QT_NO_DEBUG_STREAM */

KDCHART_DECLARE_SWAP_SPECIALISATION( KDChart::FrameAttributes )

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO( KDChart::FrameAttributes, Q_MOVABLE_TYPE );
QT_END_NAMESPACE

Q_DECLARE_METATYPE( KDChart::FrameAttributes )

#endif // KDCHARTFRAMEATTRIBUTES_H
