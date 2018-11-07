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

#ifndef KCHARTPOLARDIAGRAM_H
#define KCHARTPOLARDIAGRAM_H


#include "KChartPosition.h"
#include "KChartAbstractPolarDiagram.h"

QT_BEGIN_NAMESPACE
class QPolygonF;
QT_END_NAMESPACE

namespace KChart {

/**
  * @brief PolarDiagram defines a common polar diagram
  */
class KCHART_EXPORT PolarDiagram : public AbstractPolarDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY( PolarDiagram )
    KCHART_DECLARE_DERIVED_DIAGRAM( PolarDiagram, PolarCoordinatePlane )

public:
    explicit PolarDiagram(
        QWidget* parent = nullptr, PolarCoordinatePlane* plane = nullptr );
    virtual ~PolarDiagram();

protected:
    // Implement AbstractDiagram
    /** \reimpl */
    void paint ( PaintContext* paintContext ) Q_DECL_OVERRIDE;

public:
    /** \reimpl */
    void resize ( const QSizeF& area ) Q_DECL_OVERRIDE;

    // Implement AbstractPolarDiagram
    /** \reimpl */
    qreal valueTotals () const Q_DECL_OVERRIDE;
    /** \reimpl */
    qreal numberOfValuesPerDataset() const Q_DECL_OVERRIDE;
    /** \reimpl */
    qreal numberOfGridRings() const Q_DECL_OVERRIDE;

    virtual PolarDiagram * clone() const;

    /** \deprecated Use PolarCoordinatePlane::setStartPosition( qreal degrees ) instead. */
    void setZeroDegreePosition( int degrees );
    /** \deprecated Use qreal PolarCoordinatePlane::startPosition instead. */
    int zeroDegreePosition() const;

    void setRotateCircularLabels( bool rotateCircularLabels );
    bool rotateCircularLabels() const;

    /** Close each of the data series by connecting the last point to its
     * respective start point
     */
    void setCloseDatasets( bool closeDatasets );
    bool closeDatasets() const;

    void setShowDelimitersAtPosition( Position position,
                                      bool showDelimiters );
    void setShowLabelsAtPosition( Position position,
                                  bool showLabels );

    bool showDelimitersAtPosition( Position position ) const;

    bool showLabelsAtPosition( Position position ) const;

    virtual void paint ( PaintContext* paintContext,
                         bool calculateListAndReturnScale,
                         qreal& newZoomX, qreal& newZoomY ); // KChart 3: references -> pointers

protected:
    /** \reimpl */
    const QPair<QPointF, QPointF> calculateDataBoundaries() const Q_DECL_OVERRIDE;
    void paintEvent ( QPaintEvent* ) Q_DECL_OVERRIDE;
    void resizeEvent ( QResizeEvent* ) Q_DECL_OVERRIDE;
    virtual void paintPolarMarkers( PaintContext* ctx, const QPolygonF& polygon );

}; // End of class PolarDiagram

}


#endif // KCHARTPOLARDIAGRAM_H
