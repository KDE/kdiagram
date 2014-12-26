/**
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

#ifndef KDCHARTRINGDIAGRAM_H
#define KDCHARTRINGDIAGRAM_H

#include "KDChartAbstractPieDiagram.h"

namespace KDChart {

/**
  * @brief RingDiagram defines a common ring diagram
  */
class KDE_KDCHART_EXPORT RingDiagram : public AbstractPieDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY( RingDiagram )
    KDCHART_DECLARE_DERIVED_DIAGRAM( RingDiagram, PolarCoordinatePlane )

public:
    explicit RingDiagram(
        QWidget* parent = 0, PolarCoordinatePlane* plane = 0 );
    virtual ~RingDiagram();

protected:
    // Implement AbstractDiagram
    /** \reimpl */
    virtual void paint( PaintContext* paintContext );
public:
    /** \reimpl */
    virtual void resize( const QSizeF& area );

    // Implement AbstractPolarDiagram
    /** \reimpl */
    virtual qreal valueTotals() const;
    /** \reimpl */
    virtual qreal numberOfValuesPerDataset() const;
    virtual qreal numberOfDatasets() const;
    /** \reimpl */
    virtual qreal numberOfGridRings() const;

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
    virtual const QPair<QPointF, QPointF> calculateDataBoundaries() const;
    void paintEvent( QPaintEvent* );
    void resizeEvent( QResizeEvent* );

private:
    void drawOneSlice( QPainter* painter, uint dataset, uint slice, qreal granularity );
    void drawPieSurface( QPainter* painter, uint dataset, uint slice, qreal granularity );
    QPointF pointOnEllipse( const QRectF& rect, int dataset, int slice, bool outer, qreal angle,
                            qreal totalGapFactor, qreal totalExplodeFactor );
}; // End of class RingDiagram

}

#endif // KDCHARTRINGDIAGRAM_H
