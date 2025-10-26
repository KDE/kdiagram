/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTTHREEDBARATTRIBUTES_H
#define KCHARTTHREEDBARATTRIBUTES_H

#include "KChartAbstractThreeDAttributes.h"
#include "KChartGlobal.h"
#include <QMetaType>

namespace KChart
{

/**
 * @brief A set of 3D bar attributes
 */
class KCHART_EXPORT ThreeDBarAttributes : public AbstractThreeDAttributes
{
public:
    ThreeDBarAttributes();
    ThreeDBarAttributes(const ThreeDBarAttributes &);
    ThreeDBarAttributes &operator=(const ThreeDBarAttributes &);

    ~ThreeDBarAttributes() override;

    /* threeD Bars specific */
    void setUseShadowColors(bool useShadowColors);
    bool useShadowColors() const;

    // Pending Michel I am not sure this will be used
    void setAngle(uint threeDAngle);
    uint angle() const;

    bool operator==(const ThreeDBarAttributes &) const;
    inline bool operator!=(const ThreeDBarAttributes &other) const
    {
        return !operator==(other);
    }

    KCHART_DECLARE_SWAP_DERIVED(ThreeDBarAttributes)

    KCHART_DECLARE_PRIVATE_DERIVED(ThreeDBarAttributes)

}; // End of class ThreeDBarAttributes

}

#if !defined(QT_NO_DEBUG_STREAM)
KCHART_EXPORT QDebug operator<<(QDebug, const KChart::ThreeDBarAttributes &);
#endif /* QT_NO_DEBUG_STREAM */

KCHART_DECLARE_SWAP_SPECIALISATION_DERIVED(KChart::ThreeDBarAttributes)

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(KChart::ThreeDBarAttributes, Q_MOVABLE_TYPE);
QT_END_NAMESPACE

Q_DECLARE_METATYPE(KChart::ThreeDBarAttributes)

#endif // KCHARTTHREEDBARATTRIBUTES_H
