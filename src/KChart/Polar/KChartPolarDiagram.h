/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
    ~PolarDiagram() override;

protected:
    // Implement AbstractDiagram
    /** \reimpl */
    void paint ( PaintContext* paintContext ) override;

public:
    /** \reimpl */
    void resize ( const QSizeF& area ) override;

    // Implement AbstractPolarDiagram
    /** \reimpl */
    qreal valueTotals () const override;
    /** \reimpl */
    qreal numberOfValuesPerDataset() const override;
    /** \reimpl */
    qreal numberOfGridRings() const override;


    /**
      * Creates an exact copy of this diagram.
      */
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
    const QPair<QPointF, QPointF> calculateDataBoundaries() const override;
    void paintEvent ( QPaintEvent* ) override;
    void resizeEvent ( QResizeEvent* ) override;
    virtual void paintPolarMarkers( PaintContext* ctx, const QPolygonF& polygon );

}; // End of class PolarDiagram

}


#endif // KCHARTPOLARDIAGRAM_H
