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

#ifndef KCHARTGRIDATTRIBUTES_H
#define KCHARTGRIDATTRIBUTES_H

#include <QMetaType>
#include "KChartGlobal.h"
#include "KChartEnums.h"

QT_BEGIN_NAMESPACE
class QPen;
QT_END_NAMESPACE

namespace KChart {

/**
  * @brief A set of attributes controlling the appearance of grids
  */
class KCHART_EXPORT GridAttributes
{
public:
    GridAttributes();
    GridAttributes( const GridAttributes& );
    GridAttributes &operator= ( const GridAttributes& );

    ~GridAttributes();

    void setGridVisible( bool visible );
    bool isGridVisible() const;

    /**
     * When this is enabled, grid lines are drawn only where axis annotations are.
     * Otherwise annotations are disregarded as far as the grid is concerned.
     *
     * The default is false.
     */
    void setLinesOnAnnotations( bool );
    bool linesOnAnnotations() const;

    void setGridStepWidth( qreal stepWidth = 0.0 );
    qreal gridStepWidth() const;

    void setGridSubStepWidth( qreal subStepWidth = 0.0 );
    qreal gridSubStepWidth() const;

    /**
     * Specify which granularity sequence is to be used to find a matching
     * grid granularity.
     *
     * See details explained at KChartEnums::GranularitySequence.
     *
     * You might also want to use setAdjustBoundsToGrid for fine-tuning the
     * start/end value.
     *
     * \sa setAdjustBoundsToGrid, GranularitySequence
     */
    void setGridGranularitySequence( KChartEnums::GranularitySequence sequence );
    KChartEnums::GranularitySequence gridGranularitySequence() const;

    /**
     * By default visible bounds of the data area are adjusted to match
     * a main grid line.
     * If you set the respective adjust flag to false the bound will
     * not start at a grid line's value but it will be the exact value
     * of the data range set.
     *
     * \sa CartesianCoordinatePlane::setHorizontalRange
     * \sa CartesianCoordinatePlane::setVerticalRange
     */
    void setAdjustBoundsToGrid( bool adjustLower, bool adjustUpper );
    bool adjustLowerBoundToGrid() const;
    bool adjustUpperBoundToGrid() const;

    void setGridPen( const QPen & pen );
    QPen gridPen() const;

    void setSubGridVisible( bool visible );
    bool isSubGridVisible() const;

    void setSubGridPen( const QPen & pen );
    QPen subGridPen() const;

    void setOuterLinesVisible( bool visible );
    bool isOuterLinesVisible() const;

    void setZeroLinePen( const QPen & pen );
    QPen zeroLinePen() const;

    bool operator==( const GridAttributes& ) const;
    inline bool operator!=( const GridAttributes& other ) const { return !operator==(other); }

private:
    KCHART_DECLARE_PRIVATE_BASE_VALUE( GridAttributes )
}; // End of class GridAttributes

}

#if !defined(QT_NO_DEBUG_STREAM)
KCHART_EXPORT QDebug operator<<(QDebug, const KChart::GridAttributes& );
#endif /* QT_NO_DEBUG_STREAM */

KCHART_DECLARE_SWAP_SPECIALISATION( KChart::GridAttributes )

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO( KChart::GridAttributes, Q_MOVABLE_TYPE );
QT_END_NAMESPACE

Q_DECLARE_METATYPE( KChart::GridAttributes )

#endif // KCHARTGRIDATTRIBUTES_H
