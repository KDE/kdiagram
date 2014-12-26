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

#ifndef KDCHARTTHREEDPIEATTRIBUTES_H
#define KDCHARTTHREEDPIEATTRIBUTES_H

#include <QMetaType>
#include "KDChartAbstractThreeDAttributes.h"
#include "KDChartGlobal.h"

namespace KDChart {

  /**
    * @brief A set of 3D pie attributes
    */
  class KDE_KDCHART_EXPORT ThreeDPieAttributes : public AbstractThreeDAttributes
  {
  public:
    ThreeDPieAttributes();
    ThreeDPieAttributes( const ThreeDPieAttributes& );
    ThreeDPieAttributes &operator= ( const ThreeDPieAttributes& );

    ~ThreeDPieAttributes();

    /* threeD Pies specific */
    void setUseShadowColors( bool useShadowColors );
    bool useShadowColors() const;

    bool operator==( const ThreeDPieAttributes& ) const;
    inline bool operator!=( const ThreeDPieAttributes& other ) const { return !operator==(other); }

    KDCHART_DECLARE_SWAP_DERIVED(ThreeDPieAttributes)

private:
    KDCHART_DECLARE_PRIVATE_DERIVED(ThreeDPieAttributes)

  }; // End of class ThreeDPieAttributes

}

#if !defined(QT_NO_DEBUG_STREAM)
KDE_KDCHART_EXPORT QDebug operator<<(QDebug, const KDChart::ThreeDPieAttributes& );
#endif /* QT_NO_DEBUG_STREAM */

KDCHART_DECLARE_SWAP_SPECIALISATION_DERIVED( KDChart::ThreeDPieAttributes )

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO( KDChart::ThreeDPieAttributes, Q_MOVABLE_TYPE );
QT_END_NAMESPACE

Q_DECLARE_METATYPE( KDChart::ThreeDPieAttributes )

#endif // KDCHARTTHREEDPIEATTRIBUTES_H
