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

#ifndef KCHARTLEVEYJENNINGSDIAGRAM_H
#define KCHARTLEVEYJENNINGSDIAGRAM_H

#include "KChartLineDiagram.h"
#include "KChartLeveyJenningsCoordinatePlane.h"

QT_BEGIN_NAMESPACE
class QPainter;
class QPolygonF;
class QSvgRenderer;
QT_END_NAMESPACE

namespace KChart {

    class ThreeDLineAttributes;

/**
 * @brief LeveyDiagram defines a Levey Jennings chart.
 *
 * It provides different subtypes which are set using \a setType.
 */
class KCHART_EXPORT LeveyJenningsDiagram : public LineDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY( LeveyJenningsDiagram )
//    KCHART_DECLARE_PRIVATE_DERIVED_PARENT( LineDiagram, CartesianCoordinatePlane * )

    KCHART_DECLARE_DERIVED_DIAGRAM( LeveyJenningsDiagram, LeveyJenningsCoordinatePlane )


public:
    explicit LeveyJenningsDiagram( QWidget* parent = nullptr, LeveyJenningsCoordinatePlane* plane = nullptr );
    virtual ~LeveyJenningsDiagram();


    /**
      * Creates an exact copy of this diagram.
      */
   LineDiagram * clone() const override;

    enum Symbol
    {
        OkDataPoint,
        NotOkDataPoint,
        LotChanged,
        SensorChanged,
        FluidicsPackChanged
    };

    /**
     * Returns true if both diagrams have the same settings.
     */
    bool compare( const LeveyJenningsDiagram* other ) const;


    /**
     * Sets the position of the lot change symbol to \a pos.
     * Valid values are: Qt::AlignTop (default), Qt::AlignBottom.
     */
    void setLotChangedSymbolPosition( Qt::Alignment pos );

    /**
     * Returns the position of the lot change symbol.
     */
    Qt::Alignment lotChangedSymbolPosition() const;


    /**
     * Sets the position of the fluidics pack changed symbol to \a pos.
     * Valid values are: Qt::AlignBottom (default), Qt::AlignTop.
     */
    void setFluidicsPackChangedSymbolPosition( Qt::Alignment pos );

    /**
     * Returns the position of the fluidics pack changed symbol.
     */
    Qt::Alignment fluidicsPackChangedSymbolPosition() const;


    /**
     * Sets the position of the sensor changed symbol to \a pos.
     * Valid values are: Qt::AlignBottom (default), Qt::AlignTop.
     */
    void setSensorChangedSymbolPosition( Qt::Alignment pos );

    /**
     * Returns the position of the sensor changed symbol.
     */
    Qt::Alignment sensorChangedSymbolPosition() const;


    /**
     * Sets the expected mean value over all QC values to \a meanValue.
     */
    void setExpectedMeanValue( float meanValue );

    /**
     * Returns the expected mean values over all QC values.
     */
    float expectedMeanValue() const;


    /**
     * Sets the expected standard deviaction over all QC values to \a sd.
     */
    void setExpectedStandardDeviation( float sd );

    /**
     * Returns the expected standard deviation over all QC values.
     */
    float expectedStandardDeviation() const;


    /**
     * Returns the calculated mean values over all QC values.
     */
    float calculatedMeanValue() const;

    /**
     * Returns the calculated standard deviation over all QC values.
     */
    float calculatedStandardDeviation() const;


    /**
     * Sets the date/time of all fluidics pack changes to \a changes.
     */
    void setFluidicsPackChanges( const QVector< QDateTime >& changes );

    /**
     * Returns the list of all fluidics pack changes.
     */
    QVector< QDateTime > fluidicsPackChanges() const;


    /**
     * Sets the date/time of all sensor changes to \a changes.
     */
    void setSensorChanges( const QVector< QDateTime >& changes );

    /**
     * Returns the list of all sensor changes.
     */
    QVector< QDateTime > sensorChanges() const;


    /**
     * Sets the pen used for drawing the scan line to \a pen
     */
    void setScanLinePen( const QPen& pen );

    /**
     * Returns the pen being used for drawing the scan line.
     */
    QPen scanLinePen() const;


    /**
     * Sets the symbol being used for \a symbol to a SVG file \a filename.
     */
    void setSymbol( Symbol symbol, const QString& filename );

    /**
     * Returns the SVG file name usef for \a symbol
     */
    QString symbol( Symbol symbol ) const;

    /* \reimpl */
    void setModel( QAbstractItemModel* model ) override;


    /**
     * Returns the timerange of the diagram's data.
     */
    QPair< QDateTime, QDateTime > timeRange() const;

    /**
     * Sets the \a timeRange visible on the x axis. Set it to QPair< QDateTime, QDateTime >()
     * to use the default auto calculation.
     */
    void setTimeRange( const QPair< QDateTime, QDateTime >& timeRange );

protected:

    /** \reimpl */
    void paint( PaintContext* paintContext ) override;

    /**
     * Draws the fluidics pack and sensor changed symbols.
     */
    void drawChanges( PaintContext* paintContext );


    /**
     * Draws a data point symbol for the data point at \a pos.
     * @param ok True, when the data point is ok, false otherwise (different symbol)
     * @param ctx The PaintContext being used
     * @param pos Position
     * @param ok Draw as Ok or notOK data point
     */
    virtual void drawDataPointSymbol( PaintContext* paintContext, const QPointF& pos, bool ok );

    /**
     * Draws a lot changed symbol for the data point at \a pos.
     * @param ctx The PaintContext being used
     * @param pos Position
     * \sa lotChangedSymbolPosition
     */
    virtual void drawLotChangeSymbol( PaintContext* paintContext, const QPointF& pos );

    /**
     * Draws a sensor changed symbol for the data point at \a pos.
     * @param ctx The PaintContext being used
     * @param pos Position
     * \sa sensorChangedSymbolPosition
     */
    virtual void drawSensorChangedSymbol( PaintContext* paintContext, const QPointF& pos );

    /**
     * Draws a fluidics pack changed symbol for the data point at \a pos.
     * @param ctx The PaintContext being used
     * @param pos Position
     * \sa fluidicsPackChangedSymbolPosition
     */
    virtual void drawFluidicsPackChangedSymbol( PaintContext* paintContext, const QPointF& pos );


    /**
     * Returns the rectangle being used for drawing the icons
     */
    virtual QRectF iconRect() const;


    /**
     * Returns the SVG icon renderer for \a symbol
     */
    QSvgRenderer* iconRenderer( Symbol symbol );

    /* \reimpl */

    /** \reimpl */
    const QPair<QPointF, QPointF> calculateDataBoundaries() const override;

protected Q_SLOTS:
    void calculateMeanAndStandardDeviation() const;
}; // End of class KChartLineDiagram

}

#endif // KCHARTLINEDIAGRAM_H
