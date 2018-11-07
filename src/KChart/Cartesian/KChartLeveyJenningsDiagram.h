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

    LineDiagram * clone() const Q_DECL_OVERRIDE;

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

    void setLotChangedSymbolPosition( Qt::Alignment pos );
    Qt::Alignment lotChangedSymbolPosition() const;

    void setFluidicsPackChangedSymbolPosition( Qt::Alignment pos );
    Qt::Alignment fluidicsPackChangedSymbolPosition() const;

    void setSensorChangedSymbolPosition( Qt::Alignment pos );
    Qt::Alignment sensorChangedSymbolPosition() const;

    void setExpectedMeanValue( float meanValue );
    float expectedMeanValue() const;

    void setExpectedStandardDeviation( float sd );
    float expectedStandardDeviation() const;

    float calculatedMeanValue() const;
    float calculatedStandardDeviation() const;

    void setFluidicsPackChanges( const QVector< QDateTime >& changes );
    QVector< QDateTime > fluidicsPackChanges() const;

    void setSensorChanges( const QVector< QDateTime >& changes );
    QVector< QDateTime > sensorChanges() const;

    void setScanLinePen( const QPen& pen );
    QPen scanLinePen() const;

    void setSymbol( Symbol symbol, const QString& filename );
    QString symbol( Symbol symbol ) const;

    /* \reimpl */
    void setModel( QAbstractItemModel* model ) Q_DECL_OVERRIDE;

    QPair< QDateTime, QDateTime > timeRange() const;
    void setTimeRange( const QPair< QDateTime, QDateTime >& timeRange );

protected:
    void paint( PaintContext* paintContext ) Q_DECL_OVERRIDE;
    void drawChanges( PaintContext* paintContext );

    virtual void drawDataPointSymbol( PaintContext* paintContext, const QPointF& pos, bool ok );
    virtual void drawLotChangeSymbol( PaintContext* paintContext, const QPointF& pos );
    virtual void drawSensorChangedSymbol( PaintContext* paintContext, const QPointF& pos );
    virtual void drawFluidicsPackChangedSymbol( PaintContext* paintContext, const QPointF& pos );

    virtual QRectF iconRect() const;

    QSvgRenderer* iconRenderer( Symbol symbol );

    /** \reimpl */
    const QPair<QPointF, QPointF> calculateDataBoundaries() const Q_DECL_OVERRIDE;

protected Q_SLOTS:
    void calculateMeanAndStandardDeviation() const;
}; // End of class KChartLineDiagram

}

#endif // KCHARTLINEDIAGRAM_H
