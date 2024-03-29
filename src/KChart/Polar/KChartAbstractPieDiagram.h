/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
    ~AbstractPieDiagram() override;

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
