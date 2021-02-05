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

#ifndef KCHARTTHREEDLINEATTRIBUTES_H
#define KCHARTTHREEDLINEATTRIBUTES_H

#include <QMetaType>
#include "KChartAbstractThreeDAttributes.h"
#include "KChartGlobal.h"

namespace KChart {

  /**
    * @brief A set of 3D line attributes
    */
  class KCHART_EXPORT ThreeDLineAttributes : public AbstractThreeDAttributes
  {
  public:
    ThreeDLineAttributes();
    ThreeDLineAttributes( const ThreeDLineAttributes& );
    ThreeDLineAttributes &operator= ( const ThreeDLineAttributes& );

    ~ThreeDLineAttributes();

    /* threeD lines specific */
    void setLineXRotation( const uint degrees );
    uint lineXRotation() const;
    void setLineYRotation( const uint degrees );
    uint lineYRotation() const;

    bool operator==( const ThreeDLineAttributes& ) const;
    inline bool operator!=( const ThreeDLineAttributes& other ) const { return !operator==(other); }

    KCHART_DECLARE_SWAP_DERIVED(ThreeDLineAttributes)

    KCHART_DECLARE_PRIVATE_DERIVED(ThreeDLineAttributes)

  }; // End of class ThreeDLineAttributes

}

#if !defined(QT_NO_DEBUG_STREAM)
KCHART_EXPORT QDebug operator<<(QDebug, const KChart::ThreeDLineAttributes& );
#endif /* QT_NO_DEBUG_STREAM */

KCHART_DECLARE_SWAP_SPECIALISATION_DERIVED( KChart::ThreeDLineAttributes )

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO( KChart::ThreeDLineAttributes, Q_MOVABLE_TYPE );
QT_END_NAMESPACE

Q_DECLARE_METATYPE( KChart::ThreeDLineAttributes )

#endif // KCHARTTHREEDLINEATTRIBUTES_H
