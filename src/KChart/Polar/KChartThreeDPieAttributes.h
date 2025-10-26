/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTTHREEDPIEATTRIBUTES_H
#define KCHARTTHREEDPIEATTRIBUTES_H

#include "KChartAbstractThreeDAttributes.h"
#include "KChartGlobal.h"
#include <QMetaType>

namespace KChart
{

/**
 * @brief A set of 3D pie attributes
 */
class KCHART_EXPORT ThreeDPieAttributes : public AbstractThreeDAttributes
{
public:
    ThreeDPieAttributes();
    ThreeDPieAttributes(const ThreeDPieAttributes &);
    ThreeDPieAttributes &operator=(const ThreeDPieAttributes &);

    ~ThreeDPieAttributes() override;

    /* threeD Pies specific */
    void setUseShadowColors(bool useShadowColors);
    bool useShadowColors() const;

    bool operator==(const ThreeDPieAttributes &) const;
    inline bool operator!=(const ThreeDPieAttributes &other) const
    {
        return !operator==(other);
    }

    KCHART_DECLARE_SWAP_DERIVED(ThreeDPieAttributes)

private:
    KCHART_DECLARE_PRIVATE_DERIVED(ThreeDPieAttributes)

}; // End of class ThreeDPieAttributes

}

#if !defined(QT_NO_DEBUG_STREAM)
KCHART_EXPORT QDebug operator<<(QDebug, const KChart::ThreeDPieAttributes &);
#endif /* QT_NO_DEBUG_STREAM */

KCHART_DECLARE_SWAP_SPECIALISATION_DERIVED(KChart::ThreeDPieAttributes)

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(KChart::ThreeDPieAttributes, Q_MOVABLE_TYPE);
QT_END_NAMESPACE

Q_DECLARE_METATYPE(KChart::ThreeDPieAttributes)

#endif // KCHARTTHREEDPIEATTRIBUTES_H
