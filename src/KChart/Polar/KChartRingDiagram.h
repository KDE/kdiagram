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

#ifndef KCHARTRINGDIAGRAM_H
#define KCHARTRINGDIAGRAM_H

#include "KChartAbstractPieDiagram.h"

namespace KChart {

/**
  * @brief RingDiagram defines a common ring diagram
  */
class KCHART_EXPORT RingDiagram : public AbstractPieDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY( RingDiagram )
    KCHART_DECLARE_DERIVED_DIAGRAM( RingDiagram, PolarCoordinatePlane )

public:
    explicit RingDiagram(
        QWidget* parent = nullptr, PolarCoordinatePlane* plane = nullptr );
    virtual ~RingDiagram();

protected:
    // Implement AbstractDiagram
    /** \reimpl */
    void paint( PaintContext* paintContext ) override;
public:
    /** \reimpl */
    void resize( const QSizeF& area ) override;

    // Implement AbstractPolarDiagram
    /** \reimpl */
    qreal valueTotals() const override;
    /** \reimpl */
    qreal numberOfValuesPerDataset() const override;
    qreal numberOfDatasets() const override;
    /** \reimpl */
    qreal numberOfGridRings() const override;

    qreal valueTotals( int dataset ) const;


    /**
      * Creates an exact copy of this diagram.
      */
   virtual RingDiagram * clone() const;

    /**
     * Returns true if both diagrams have the same settings.
     */
    bool compare( const RingDiagram* other ) const;

    void setRelativeThickness( bool relativeThickness );
    bool relativeThickness() const;

    virtual void setExpandWhenExploded( bool expand );
    virtual bool expandWhenExploded() const;

protected:
    /** \reimpl */
    const QPair<QPointF, QPointF> calculateDataBoundaries() const override;
    void paintEvent( QPaintEvent* ) override;
    void resizeEvent( QResizeEvent* ) override;

private:

    /**
      \param painter the QPainter to draw in
      \param dataset the dataset to draw the slice for
      \param slice the slice to draw
      */
   void drawOneSlice( QPainter* painter, uint dataset, uint slice, qreal granularity );

    /**
      Internal method that draws the top surface of one of the slices in a ring chart.

      \param painter the QPainter to draw in
      \param dataset the dataset to draw the slice for
      \param slice the slice to draw
      */
   void drawPieSurface( QPainter* painter, uint dataset, uint slice, qreal granularity );

    /**
      * Auxiliary method returning a point to a given boundary
      * rectangle of the enclosed ellipse and an angle.
      */
   QPointF pointOnEllipse( const QRectF& rect, int dataset, int slice, bool outer, qreal angle,
                            qreal totalGapFactor, qreal totalExplodeFactor );
}; // End of class RingDiagram

}

#endif // KCHARTRINGDIAGRAM_H
