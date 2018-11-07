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
    void paint( PaintContext* paintContext ) Q_DECL_OVERRIDE;
public:
    /** \reimpl */
    void resize( const QSizeF& area ) Q_DECL_OVERRIDE;

    // Implement AbstractPolarDiagram
    /** \reimpl */
    qreal valueTotals() const Q_DECL_OVERRIDE;
    /** \reimpl */
    qreal numberOfValuesPerDataset() const Q_DECL_OVERRIDE;
    qreal numberOfDatasets() const Q_DECL_OVERRIDE;
    /** \reimpl */
    qreal numberOfGridRings() const Q_DECL_OVERRIDE;

    qreal valueTotals( int dataset ) const;

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
    const QPair<QPointF, QPointF> calculateDataBoundaries() const Q_DECL_OVERRIDE;
    void paintEvent( QPaintEvent* ) Q_DECL_OVERRIDE;
    void resizeEvent( QResizeEvent* ) Q_DECL_OVERRIDE;

private:
    void drawOneSlice( QPainter* painter, uint dataset, uint slice, qreal granularity );
    void drawPieSurface( QPainter* painter, uint dataset, uint slice, qreal granularity );
    QPointF pointOnEllipse( const QRectF& rect, int dataset, int slice, bool outer, qreal angle,
                            qreal totalGapFactor, qreal totalExplodeFactor );
}; // End of class RingDiagram

}

#endif // KCHARTRINGDIAGRAM_H
