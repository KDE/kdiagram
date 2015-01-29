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

#ifndef KDCHARTPIEDIAGRAM_H
#define KDCHARTPIEDIAGRAM_H

#include "KDChartAbstractPieDiagram.h"

namespace KDChart {

    class LabelPaintCache;

/**
  * @brief PieDiagram defines a common pie diagram
  */
class KDEKDCHART_EXPORT PieDiagram : public AbstractPieDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY( PieDiagram )
    KDCHART_DECLARE_DERIVED_DIAGRAM( PieDiagram, PolarCoordinatePlane )

public:
    explicit PieDiagram(
        QWidget* parent = 0, PolarCoordinatePlane* plane = 0 );
    virtual ~PieDiagram();

protected:
    // Implement AbstractDiagram
    /** \reimpl */
    virtual void paint( PaintContext* paintContext );

public:
    /**
     * Describes which decorations are painted around data labels.
     */
    enum LabelDecoration {
        NoDecoration = 0, ///< No decoration
        FrameDecoration = 1, ///< A rectangular frame is painted around the label text
        LineFromSliceDecoration = 2 ///< A line is drawn from the pie slice to its label
    };
    Q_DECLARE_FLAGS( LabelDecorations, LabelDecoration )
    /// Set the decorations to be painted around data labels according to @p decorations.
    void setLabelDecorations( LabelDecorations decorations );
    /// Return the decorations to be painted around data labels.
    LabelDecorations labelDecorations() const;

    /// If @p enabled is set to true, labels that would overlap will be shuffled to avoid overlap.
    /// \note Collision avoidance may allow labels to be closer than AbstractDiagram with
    ///       allowOverlappingDataValueTexts() == false, so you should usually also call
    ///       setAllowOverlappingDataValueTexts( true ) if you enable this feature.
    void setLabelCollisionAvoidanceEnabled( bool enabled );
    /// Return whether overlapping labels will be moved to until they don't overlap anymore.
    bool isLabelCollisionAvoidanceEnabled() const;

    /** \reimpl */
    virtual void resize ( const QSizeF& area );

    // Implement AbstractPolarDiagram
    /** \reimpl */
    virtual qreal valueTotals () const;
    /** \reimpl */
    virtual qreal numberOfValuesPerDataset() const;
    /** \reimpl */
    virtual qreal numberOfGridRings() const;

    virtual PieDiagram * clone() const;

protected:
    /** \reimpl */
    virtual const QPair<QPointF, QPointF> calculateDataBoundaries() const;
    void paintEvent( QPaintEvent* );
    void resizeEvent( QResizeEvent* );

private:
    // ### move to private class?
    void placeLabels( PaintContext* paintContext );
    // Solve problems with label overlap by changing label positions inside d->labelPaintCache.
    void shuffleLabels( QRectF* textBoundingRect );
    void paintInternal( PaintContext* paintContext );
    void drawSlice( QPainter* painter, const QRectF& drawPosition, uint slice );
    void drawSliceSurface( QPainter* painter, const QRectF& drawPosition, uint slice );
    void addSliceLabel( LabelPaintCache* lpc, const QRectF& drawPosition, uint slice );
    void draw3DEffect( QPainter* painter, const QRectF& drawPosition, uint slice );
    void draw3dCutSurface( QPainter* painter,
        const QRectF& rect,
        qreal threeDHeight,
        qreal angle );
    void draw3dOuterRim( QPainter* painter,
        const QRectF& rect,
        qreal threeDHeight,
        qreal startAngle,
        qreal endAngle );
    void calcSliceAngles();
    void calcPieSize( const QRectF &contentsRect );
    QRectF twoDPieRect( const QRectF &contentsRect, const ThreeDPieAttributes& threeDAttrs ) const;
    QRectF explodedDrawPosition( const QRectF& drawPosition, uint slice ) const;
    uint findSliceAt( qreal angle, int columnCount );
    uint findLeftSlice( uint slice, int columnCount );
    uint findRightSlice( uint slice, int columnCount );
    QPointF pointOnEllipse( const QRectF& boundingBox, qreal angle );
}; // End of class KDChartPieDiagram

Q_DECLARE_OPERATORS_FOR_FLAGS( PieDiagram::LabelDecorations )

}
#endif // KDCHARTPIEDIAGRAM_H
