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
    void paint( PaintContext* paintContext ) override;

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
   virtual PieDiagram * clone() const;

protected:
    /** \reimpl */
    const QPair<QPointF, QPointF> calculateDataBoundaries() const override;
    void paintEvent( QPaintEvent* ) override;
    void resizeEvent( QResizeEvent* ) override;

private:
    // ### move to private class?
    void placeLabels( PaintContext* paintContext );
    // Solve problems with label overlap by changing label positions inside d->labelPaintCache.
    void shuffleLabels( QRectF* textBoundingRect );
    void paintInternal( PaintContext* paintContext );

    /**
      Internal method that draws one of the slices in a pie chart.

      \param painter the QPainter to draw in
      \param dataset the dataset to draw the pie for
      \param slice the slice to draw
      \param threeDPieHeight the height of the three dimensional effect
      */
    void drawSlice( QPainter* painter, const QRectF& drawPosition, uint slice );

    /**
      Internal method that draws the surface of one of the slices in a pie chart.

      \param painter the QPainter to draw in
      \param dataset the dataset to draw the slice for
      \param slice the slice to draw
      */
    void drawSliceSurface( QPainter* painter, const QRectF& drawPosition, uint slice );
    void addSliceLabel( LabelPaintCache* lpc, const QRectF& drawPosition, uint slice );

    /**
      Internal method that draws the shadow creating the 3D effect of a pie

      \param painter the QPainter to draw in
      \param drawPosition the position to draw at
      \param slice the slice to draw the shadow for
      */
    void draw3DEffect( QPainter* painter, const QRectF& drawPosition, uint slice );

    /**
      Internal method that draws the cut surface of a slice (think of a real pie cut into slices)
      in 3D mode, for surfaces that are facing the observer.

      \param painter the QPainter to draw in
      \param rect the position to draw at
      \param threeDHeight the height of the shadow
      \param angle the angle of the segment
      */
    void draw3dCutSurface( QPainter* painter,
        const QRectF& rect,
        qreal threeDHeight,
        qreal angle );

    /**
      Internal method that draws the outer rim of a slice when the rim is facing the observer.

      \param painter the QPainter to draw in
      \param rect the position to draw at
      \param threeDHeight the height of the shadow
      \param startAngle the starting angle of the segment
      \param endAngle the ending angle of the segment
      */
    void draw3dOuterRim( QPainter* painter,
        const QRectF& rect,
        qreal threeDHeight,
        qreal startAngle,
        qreal endAngle );
    void calcSliceAngles();
    void calcPieSize( const QRectF &contentsRect );
    QRectF twoDPieRect( const QRectF &contentsRect, const ThreeDPieAttributes& threeDAttrs ) const;
    QRectF explodedDrawPosition( const QRectF& drawPosition, uint slice ) const;

    /**
      Internal method that finds the slice that is located at the position specified by \c angle.

      \param angle the angle at which to search for a slice
      \return the number of the slice found
      */
    uint findSliceAt( qreal angle, int columnCount );

    /**
      Internal method that finds the slice that is located to the left of \c slice.

      \param slice the slice to start the search from
      \return the number of the pie to the left of \c pie
      */
    uint findLeftSlice( uint slice, int columnCount );

    /**
      Internal method that finds the slice that is located to the right of \c slice.

      \param slice the slice to start the search from
      \return the number of the slice to the right of \c slice
      */
    uint findRightSlice( uint slice, int columnCount );

    /**
      * Auxiliary method returning a point to a given boundary
      * rectangle of the enclosed ellipse and an angle.
      */
    QPointF pointOnEllipse( const QRectF& boundingBox, qreal angle );
}; // End of class KChartPieDiagram

Q_DECLARE_OPERATORS_FOR_FLAGS( PieDiagram::LabelDecorations )

}
#endif // KCHARTPIEDIAGRAM_H
