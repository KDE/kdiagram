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

#ifndef KCHARTPIEDIAGRAM_H
#define KCHARTPIEDIAGRAM_H

#include "KChartAbstractPieDiagram.h"

namespace KChart {

    class LabelPaintCache;

/**
  * @brief PieDiagram defines a common pie diagram
  */
class KCHART_EXPORT PieDiagram : public AbstractPieDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY( PieDiagram )
    KCHART_DECLARE_DERIVED_DIAGRAM( PieDiagram, PolarCoordinatePlane )

public:
    explicit PieDiagram(
        QWidget* parent = nullptr, PolarCoordinatePlane* plane = nullptr );
    virtual ~PieDiagram();

protected:
    // Implement AbstractDiagram
    /** \reimpl */
    void paint( PaintContext* paintContext ) Q_DECL_OVERRIDE;

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
    void resize ( const QSizeF& area ) Q_DECL_OVERRIDE;

    // Implement AbstractPolarDiagram
    /** \reimpl */
    qreal valueTotals () const Q_DECL_OVERRIDE;
    /** \reimpl */
    qreal numberOfValuesPerDataset() const Q_DECL_OVERRIDE;
    /** \reimpl */
    qreal numberOfGridRings() const Q_DECL_OVERRIDE;

    virtual PieDiagram * clone() const;

protected:
    /** \reimpl */
    const QPair<QPointF, QPointF> calculateDataBoundaries() const Q_DECL_OVERRIDE;
    void paintEvent( QPaintEvent* ) Q_DECL_OVERRIDE;
    void resizeEvent( QResizeEvent* ) Q_DECL_OVERRIDE;

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
}; // End of class KChartPieDiagram

Q_DECLARE_OPERATORS_FOR_FLAGS( PieDiagram::LabelDecorations )

}
#endif // KCHARTPIEDIAGRAM_H
