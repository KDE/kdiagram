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

#ifndef KCHARTLINEDIAGRAM_H
#define KCHARTLINEDIAGRAM_H

#include "KChartAbstractCartesianDiagram.h"
#include "KChartLineAttributes.h"
#include "KChartValueTrackerAttributes.h"

QT_BEGIN_NAMESPACE
class QPainter;
class QPolygonF;
QT_END_NAMESPACE

namespace KChart {

    class ThreeDLineAttributes;

/**
 * @brief LineDiagram defines a common line diagram.
 *
 * It provides different subtypes which are set using \a setType.
 */
class KCHART_EXPORT LineDiagram : public AbstractCartesianDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY( LineDiagram )
//    KCHART_DECLARE_PRIVATE_DERIVED_PARENT( LineDiagram, CartesianCoordinatePlane * )

    KCHART_DECLARE_DERIVED_DIAGRAM( LineDiagram, CartesianCoordinatePlane )


public:
    class LineDiagramType;
    friend class LineDiagramType;

    explicit LineDiagram( QWidget* parent = nullptr, CartesianCoordinatePlane* plane = nullptr );
    virtual ~LineDiagram();

 
    /**
      * Creates an exact copy of this diagram.
      */
   virtual LineDiagram * clone() const;

    /**
     * Returns true if both diagrams have the same settings.
     */
    bool compare( const LineDiagram* other ) const;

    enum LineType {
        Normal =  0,
        Stacked = 1,
        Percent = 2
    };


 
    /**
      * Sets the line diagram's type to \a type
      * \sa LineDiagram::LineType
      */
    void setType( const LineType type );
 
    /**
      * @return the type of the line diagram
      */
    LineType type() const;

    /** If centerDataPoints() is true, all data points are moved by an
     * offset of 0.5 to the right. This is useful in conjunction with
     * bar diagrams, since data points are then centered just like bars.
     *
     * \sa centerDataPoints()
     */
    void setCenterDataPoints( bool center );
    /** @return option set by setCenterDataPoints() */
    bool centerDataPoints() const;

    /** With this property set to true, data sets in a normal line diagram
     * are drawn in reversed order. More clearly, the first (top-most) data set
     * in the source model will then appear in front. This is mostly due to
     * historical reasons.
     */
    void setReverseDatasetOrder( bool reverse );
    /** \see setReverseDatasetOrder */
    bool reverseDatasetOrder() const;

 
    /**
      * Sets the global line attributes to \a la
      */
    void setLineAttributes( const LineAttributes & a );

    /**
     * Sets the line attributes of data set \a column to \a la
     */
    void setLineAttributes( int column, const LineAttributes & a );

    /**
    * Sets the line attributes for the model index \a index to \a la
    */
    void setLineAttributes( const QModelIndex & index, const LineAttributes & a );
 
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
    void setThreeDLineAttributes( const ThreeDLineAttributes & a );

    /**
     * Sets the 3D line attributes of data set \a column to \a ta
     */
    void setThreeDLineAttributes( int column, const ThreeDLineAttributes &ta );

    /**
    * Sets the 3D line attributes of model index \a index to \a la
    */
    void setThreeDLineAttributes( const QModelIndex & index,
                                  const ThreeDLineAttributes &la );

 
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
                                    const ValueTrackerAttributes & a );
 
    /**
      * Returns the value tracker attributes of the model index \a index
      */
   ValueTrackerAttributes valueTrackerAttributes( const QModelIndex & index ) const;

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
}; // End of class KChartLineDiagram

}

#endif // KCHARTLINEDIAGRAM_H
