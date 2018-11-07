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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KCHARTABSTRACTPIEDIAGRAM_H
#define KCHARTABSTRACTPIEDIAGRAM_H

#include "KChartAbstractPolarDiagram.h"

namespace KChart {
    class PieAttributes;
    class ThreeDPieAttributes;

/**
  * @brief Base class for any diagram type
  */
class KCHART_EXPORT AbstractPieDiagram : public AbstractPolarDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY( AbstractPieDiagram )
    KCHART_DECLARE_DERIVED_DIAGRAM( AbstractPieDiagram, PolarCoordinatePlane )

public:
    explicit AbstractPieDiagram(
        QWidget* parent = nullptr, PolarCoordinatePlane* plane = nullptr );
    virtual ~AbstractPieDiagram();

    /**
     * Returns true if both diagrams have the same settings.
     */
    bool compare( const AbstractPieDiagram* other ) const;

    /** Set the granularity: the smaller the granularity the more your diagram
     * segments will show facettes instead of rounded segments.
     * \param value the granularity value between 0.05 (one twentieth of a degree)
     * and 36.0 (one tenth of a full circle), other values will be interpreted as 1.0.
     */
    void setGranularity( qreal value );

    /** @return the granularity. */
    qreal granularity() const;

    /** \deprecated Use PolarCoordinatePlane::setStartPosition( qreal degrees ) instead. */
    void setStartPosition( int degrees );
    /** \deprecated Use qreal PolarCoordinatePlane::startPosition instead. */
    int startPosition() const;

    /** If this property is set, and if a pie's TextAttributes have no rotation set, its labels will
     * automatically be rotated according to the pie's angle.
     */
    void setAutoRotateLabels( bool autoRotate );
    /** \see setAutoRotateLabels( bool autoRotate )
     */
    bool autoRotateLabels() const;

    void setPieAttributes( const PieAttributes & a );
    void setPieAttributes( int   column,
                           const PieAttributes & a );
    void setPieAttributes( const QModelIndex & index,
                           const PieAttributes & a );
    PieAttributes pieAttributes() const;
    PieAttributes pieAttributes( int column ) const;
    PieAttributes pieAttributes( const QModelIndex & index ) const;

    void setThreeDPieAttributes( const ThreeDPieAttributes & a );
    void setThreeDPieAttributes( int   column,
                                 const ThreeDPieAttributes & a );
    void setThreeDPieAttributes( const QModelIndex & index,
                                 const ThreeDPieAttributes & a );
    ThreeDPieAttributes threeDPieAttributes() const;
    ThreeDPieAttributes threeDPieAttributes( int column ) const;
    ThreeDPieAttributes threeDPieAttributes( const QModelIndex & index ) const;
}; // End of class KChartAbstractPieDiagram

}

#endif // KCHARTABSTACTPIEDIAGRAM_H
