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

    KCHART_DECLARE_DERIVED_DIAGRAM( Plotter, CartesianCoordinatePlane )
    Q_PROPERTY( CompressionMode useDataCompression READ useDataCompression WRITE setUseDataCompression )
    Q_PROPERTY( qreal mergeRadiusPercentage READ mergeRadiusPercentage WRITE setMergeRadiusPercentage )

public:
    // SLOPE enables a compression based on minmal slope changes
    // DISTANCE is still buggy and can fail, same for BOTH, NONE is the default mode
    enum CompressionMode{ SLOPE, DISTANCE, BOTH, NONE };
    Q_ENUM( CompressionMode )
    class PlotterType;
    friend class PlotterType;

    explicit Plotter( QWidget* parent = nullptr, CartesianCoordinatePlane* plane = nullptr );
    virtual ~Plotter();


    /**
      * Creates an exact copy of this diagram.
      */
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



    /**
      * Sets the plotter's type to \a type
      */
   void setType( const PlotType type );

    /**
      * @return the type of the plotter
      */
    PlotType type() const;

    /**
      * Sets the global line attributes to \a la
      */
    void setLineAttributes( const LineAttributes & la );

    /**
     * Sets the line attributes of data set \a column to \a la
     */
    void setLineAttributes( int column, const LineAttributes &la );

    /**
    * Sets the line attributes for the model index \a index to \a la
    */
    void setLineAttributes( const QModelIndex & index, const LineAttributes &la );

    /**
      * Resets the line attributes of data set \a column
      */
    void resetLineAttributes( int column );

    /**
    * Remove any explicit line attributes settings that might have been specified before.
    */
    void resetLineAttributes( const QModelIndex & index );

    /**
      * @return the global line attribute set
      */
    LineAttributes lineAttributes() const;

   /**
     * @return the line attribute set of data set \a column
     */
   LineAttributes lineAttributes( int column ) const;

    /**
    * @return the line attribute set of the model index \a index
    */
    LineAttributes lineAttributes( const QModelIndex & index ) const;

    /**
      * Sets the global 3D line attributes to \a la
      */
    void setThreeDLineAttributes( const ThreeDLineAttributes & la );

    /**
     * Sets the 3D line attributes of data set \a column to \a la
     */
    void setThreeDLineAttributes( int column, const ThreeDLineAttributes & la );

    /**
    * Sets the 3D line attributes of model index \a index to \a la
    */
    void setThreeDLineAttributes( const QModelIndex & index,
                                  const ThreeDLineAttributes & la );

    /**
      * @return the global 3D line attributes
      */
    ThreeDLineAttributes threeDLineAttributes() const;

    /**
     * @return the 3D line attributes of data set \a column
     */
    ThreeDLineAttributes threeDLineAttributes( int column ) const;

    /**
    * @return the 3D line attributes of the model index \a index
    */
    ThreeDLineAttributes threeDLineAttributes( const QModelIndex & index ) const;

    /**
      * Sets the value tracker attributes of the model index \a index to \a va
      */
   void setValueTrackerAttributes( const QModelIndex & index,
                                    const ValueTrackerAttributes & va );

    /**
      * Returns the value tracker attributes of the model index \a index
      */
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
    int numberOfAbscissaSegments () const override;
    /* reimpl */
    int numberOfOrdinateSegments () const override;
#endif

protected Q_SLOTS:
    void connectAttributesModel( AttributesModel* );

protected:
    void paint ( PaintContext* paintContext ) override;

public:
    void resize ( const QSizeF& area ) override;

protected:
    qreal threeDItemDepth( const QModelIndex & index ) const override;
    qreal threeDItemDepth( int column ) const override;
    /** \reimpl */
    const QPair<QPointF, QPointF> calculateDataBoundaries() const override;
    void paintEvent ( QPaintEvent* ) override;
    void resizeEvent ( QResizeEvent* ) override;
protected Q_SLOTS:
    void setDataBoundariesDirty();
    void calcMergeRadius();
}; // End of class KChart::Plotter

}

#endif // KCHARTLINEDIAGRAM_H
