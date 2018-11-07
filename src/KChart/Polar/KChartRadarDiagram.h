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

#ifndef KCHARTRADARDIAGRAM_H
#define KCHARTRADARDIAGRAM_H


#include "KChartPosition.h"
#include "KChartPolarDiagram.h"
#include "KChartRadarCoordinatePlane.h"

QT_BEGIN_NAMESPACE
class QPolygonF;
QT_END_NAMESPACE

namespace KChart {

/**
  * @brief RadarDiagram defines a common radar diagram
  */
class KCHART_EXPORT RadarDiagram : public AbstractPolarDiagram
{
  Q_OBJECT

  Q_DISABLE_COPY( RadarDiagram )
  KCHART_DECLARE_DERIVED_DIAGRAM( RadarDiagram, RadarCoordinatePlane )

public:
    explicit RadarDiagram(
        QWidget* parent = nullptr, RadarCoordinatePlane* plane = nullptr );
    virtual ~RadarDiagram();

    virtual void paint ( PaintContext* paintContext,
                         bool calculateListAndReturnScale,
                         qreal& newZoomX, qreal& newZoomY );
    /** \reimpl */
    void resize ( const QSizeF& area ) Q_DECL_OVERRIDE;

    /** \reimpl */
    qreal valueTotals () const Q_DECL_OVERRIDE;
    /** \reimpl */
    qreal numberOfValuesPerDataset() const Q_DECL_OVERRIDE;
    /** \reimpl */
    qreal numberOfGridRings() const Q_DECL_OVERRIDE;

    /**
     * if val is true the diagram will mirror the diagram datapoints
     */
    void setReverseData( bool val );
    bool reverseData();

    virtual RadarDiagram * clone() const;

    /**
     * Close each of the data series by connecting the last point to its
     * respective start point
     */
    void setCloseDatasets( bool closeDatasets );
    bool closeDatasets() const;

    /**
     * Fill the areas of the radar chart with there respective color defined
     * via KChart::DatasetBrushRole. The value defines the alpha of the
     * color to use. If set to 0.0 (the default) then the radar areas will
     * not be filled with any color. If set to 1.0 then the areas will be
     * solid filled and are not transparent.
     */
    qreal fillAlpha() const;
    void setFillAlpha(qreal alphaF);

protected:
    /** \reimpl */
    const QPair<QPointF, QPointF> calculateDataBoundaries() const Q_DECL_OVERRIDE;
    void paintEvent ( QPaintEvent* ) Q_DECL_OVERRIDE;
    void resizeEvent ( QResizeEvent* ) Q_DECL_OVERRIDE;
    void paint ( PaintContext* paintContext ) Q_DECL_OVERRIDE;

}; // End of class RadarDiagram

}

#endif // KCHARTRADARDIAGRAM_H
