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

#ifndef KDCHARTRADARDIAGRAM_H
#define KDCHARTRADARDIAGRAM_H


#include "KDChartPosition.h"
#include "KDChartPolarDiagram.h"
#include "KDChartRadarCoordinatePlane.h"

QT_BEGIN_NAMESPACE
class QPolygonF;
QT_END_NAMESPACE

namespace KDChart {

/**
  * @brief RadarDiagram defines a common radar diagram
  */
class KDE_KDCHART_EXPORT RadarDiagram : public AbstractPolarDiagram
{
  Q_OBJECT

  Q_DISABLE_COPY( RadarDiagram )
  KDCHART_DECLARE_DERIVED_DIAGRAM( RadarDiagram, RadarCoordinatePlane )

public:
    explicit RadarDiagram(
        QWidget* parent = 0, RadarCoordinatePlane* plane = 0 );
    virtual ~RadarDiagram();

    virtual void paint ( PaintContext* paintContext,
                         bool calculateListAndReturnScale,
                         qreal& newZoomX, qreal& newZoomY );
    /** \reimpl */
    virtual void resize ( const QSizeF& area );

    /** \reimpl */
    virtual qreal valueTotals () const;
    /** \reimpl */
    virtual qreal numberOfValuesPerDataset() const;
    /** \reimpl */
    virtual qreal numberOfGridRings() const;

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
     * via KDChart::DatasetBrushRole. The value defines the alpha of the
     * color to use. If set to 0.0 (the default) then the radar areas will
     * not be filled with any color. If set to 1.0 then the areas will be
     * solid filled and are not transparent.
     */
    qreal fillAlpha() const;
    void setFillAlpha(qreal alphaF);

protected:
    /** \reimpl */
    virtual const QPair<QPointF, QPointF> calculateDataBoundaries() const;
    void paintEvent ( QPaintEvent* );
    void resizeEvent ( QResizeEvent* );
    virtual void paint ( PaintContext* paintContext );

}; // End of class RadarDiagram

}

#endif // KDCHARTRADARDIAGRAM_H
