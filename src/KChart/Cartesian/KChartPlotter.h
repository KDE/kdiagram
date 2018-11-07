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

#ifndef KCHARTPLOTTER_H
#define KCHARTPLOTTER_H

#include "KChartAbstractCartesianDiagram.h"

#include "KChartLineAttributes.h"
#include "KChartValueTrackerAttributes.h"

namespace KChart {

    class ThreeDLineAttributes;

/**
  * @brief Plotter defines a diagram type plotting two-dimensional data.
  */
class KCHART_EXPORT Plotter : public AbstractCartesianDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY( Plotter )
    Q_ENUMS( CompressionMode )

    KCHART_DECLARE_DERIVED_DIAGRAM( Plotter, CartesianCoordinatePlane )
    Q_PROPERTY( CompressionMode useDataCompression READ useDataCompression WRITE setUseDataCompression )
    Q_PROPERTY( qreal mergeRadiusPercentage READ mergeRadiusPercentage WRITE setMergeRadiusPercentage )

public:
    // SLOPE enables a compression based on minmal slope changes
    // DISTANCE is still buggy and can fail, same for BOTH, NONE is the default mode
    enum CompressionMode{ SLOPE, DISTANCE, BOTH, NONE };
    class PlotterType;
    friend class PlotterType;

    explicit Plotter( QWidget* parent = nullptr, CartesianCoordinatePlane* plane = nullptr );
    virtual ~Plotter();

    virtual Plotter* clone() const;

    /**
     * Returns true if both diagrams have the same settings.
     */
    bool compare( const Plotter* other ) const;

    enum PlotType {
        Normal =  0,
        Percent,
        Stacked
    };


    void setType( const PlotType type );
    PlotType type() const;

    void setLineAttributes( const LineAttributes & a );
    void setLineAttributes( int column, const LineAttributes & a );
    void setLineAttributes( const QModelIndex & index, const LineAttributes & a );
    void resetLineAttributes( int column );
    void resetLineAttributes( const QModelIndex & index );
    LineAttributes lineAttributes() const;
    LineAttributes lineAttributes( int column ) const;
    LineAttributes lineAttributes( const QModelIndex & index ) const;

    void setThreeDLineAttributes( const ThreeDLineAttributes & a );
    void setThreeDLineAttributes( int column, const ThreeDLineAttributes & a );
    void setThreeDLineAttributes( const QModelIndex & index,
                                  const ThreeDLineAttributes & a );

    ThreeDLineAttributes threeDLineAttributes() const;
    ThreeDLineAttributes threeDLineAttributes( int column ) const;
    ThreeDLineAttributes threeDLineAttributes( const QModelIndex & index ) const;

    void setValueTrackerAttributes( const QModelIndex & index,
                                    const ValueTrackerAttributes & a );
    ValueTrackerAttributes valueTrackerAttributes( const QModelIndex & index ) const;

    CompressionMode useDataCompression() const;
    void setUseDataCompression( CompressionMode value );

    qreal maxSlopeChange() const;
    void setMaxSlopeChange( qreal value );

    qreal mergeRadiusPercentage() const;
    void setMergeRadiusPercentage( qreal value );

#if defined(Q_COMPILER_MANGLES_RETURN_TYPE)
    // implement AbstractCartesianDiagram
    /* reimpl */
    const int numberOfAbscissaSegments () const;
    /* reimpl */
    const int numberOfOrdinateSegments () const;
#else
    // implement AbstractCartesianDiagram
    /* reimpl */
    int numberOfAbscissaSegments () const Q_DECL_OVERRIDE;
    /* reimpl */
    int numberOfOrdinateSegments () const Q_DECL_OVERRIDE;
#endif

protected Q_SLOTS:
    void connectAttributesModel( AttributesModel* );

protected:
    void paint ( PaintContext* paintContext ) Q_DECL_OVERRIDE;

public:
    void resize ( const QSizeF& area ) Q_DECL_OVERRIDE;

protected:
    qreal threeDItemDepth( const QModelIndex & index ) const Q_DECL_OVERRIDE;
    qreal threeDItemDepth( int column ) const Q_DECL_OVERRIDE;
    /** \reimpl */
    const QPair<QPointF, QPointF> calculateDataBoundaries() const Q_DECL_OVERRIDE;
    void paintEvent ( QPaintEvent* ) Q_DECL_OVERRIDE;
    void resizeEvent ( QResizeEvent* ) Q_DECL_OVERRIDE;
protected Q_SLOTS:
    void setDataBoundariesDirty();
    void calcMergeRadius();
}; // End of class KChart::Plotter

}

#endif // KCHARTLINEDIAGRAM_H
