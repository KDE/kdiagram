/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTLEVEYJENNINGSGRIDATTRIBUTES_H
#define KCHARTLEVEYJENNINGSGRIDATTRIBUTES_H

#include "KChartEnums.h"
#include "KChartGlobal.h"
#include <QMetaType>

QT_BEGIN_NAMESPACE
class QPen;
QT_END_NAMESPACE

namespace KChart
{

/**
 * @brief A set of attributes controlling the appearance of grids
 */
class KCHART_EXPORT LeveyJenningsGridAttributes
{
public:
    LeveyJenningsGridAttributes();
    LeveyJenningsGridAttributes(const LeveyJenningsGridAttributes &);
    LeveyJenningsGridAttributes &operator=(const LeveyJenningsGridAttributes &);

    ~LeveyJenningsGridAttributes();

    enum GridType {
        Expected,
        Calculated
    };

    enum Range {
        NormalRange,
        CriticalRange,
        OutOfRange
    };

    void setGridVisible(GridType type, bool visible);
    bool isGridVisible(GridType type) const;

    void setGridPen(GridType type, const QPen &pen);
    QPen gridPen(GridType type) const;

    void setRangeBrush(Range range, const QBrush &brush);
    QBrush rangeBrush(Range range) const;

    bool operator==(const LeveyJenningsGridAttributes &) const;
    inline bool operator!=(const LeveyJenningsGridAttributes &other) const
    {
        return !operator==(other);
    }

private:
    KCHART_DECLARE_PRIVATE_BASE_VALUE(LeveyJenningsGridAttributes)
}; // End of class GridAttributes

}

KCHART_DECLARE_SWAP_SPECIALISATION(KChart::LeveyJenningsGridAttributes)

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(KChart::LeveyJenningsGridAttributes, Q_MOVABLE_TYPE);
QT_END_NAMESPACE

Q_DECLARE_METATYPE(KChart::LeveyJenningsGridAttributes)

#endif // KCHARTLEVEYJENNINGSGRIDATTRIBUTES_H
