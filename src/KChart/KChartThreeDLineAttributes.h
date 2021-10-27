/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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

    ~ThreeDLineAttributes() override;

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
