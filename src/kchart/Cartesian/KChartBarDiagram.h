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

#ifndef KCHARTBARDIAGRAM_H
#define KCHARTBARDIAGRAM_H

#include "KChartAbstractCartesianDiagram.h"
#include "KChartBarAttributes.h"

QT_BEGIN_NAMESPACE
class QPainter;
QT_END_NAMESPACE

namespace KChart {

    class ThreeDBarAttributes;

/**
 * @brief BarDiagram defines a common bar diagram.
 *
 * It provides different subtypes which are set using \a setType.
 */
class KCHART_EXPORT BarDiagram : public AbstractCartesianDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY( BarDiagram )

    KCHART_DECLARE_DERIVED_DIAGRAM( BarDiagram, CartesianCoordinatePlane )

public:
    class BarDiagramType;
    friend class BarDiagramType;

    explicit BarDiagram(
        QWidget* parent = nullptr, CartesianCoordinatePlane* plane = nullptr );
    virtual ~BarDiagram();


    /**
      * Creates an exact copy of this diagram.
      */
   virtual BarDiagram * clone() const;
    /**
    * Returns true if both diagrams have the same settings.
    */
    bool compare( const BarDiagram* other ) const;

    enum BarType { Normal,
                   Stacked,
                   Percent,
                   Rows ///< @deprecated Use BarDiagram::setOrientation() instead
                 };


    /**
      * Sets the bar diagram's type to \a type
      * \sa BarDiagram::BarType
      */
    void setType( const BarType type );

    /**
      * @return the type of the bar diagram
      */
    BarType type() const;


    /**
      * Sets the orientation of the bar diagram
      */
    void setOrientation( Qt::Orientation orientation );

    /**
      * @return the orientation of the bar diagram
      */
    Qt::Orientation orientation() const;


    /**
      * Sets the global bar attributes to \a ba
      */
    void setBarAttributes( const BarAttributes & a );

    /**
     * Sets the bar attributes of data set \a column to \a ba
     */
    void setBarAttributes( int column, const BarAttributes & a );

    /**
    * Sets the line attributes for the model index \a index to \a ba
    */
    void setBarAttributes( const QModelIndex & index, const BarAttributes & a );

    /**
      * @return the global bar attribute set
      */
    BarAttributes barAttributes() const;

    /**
     * @return the bar attribute set of data set \a column
     */
    BarAttributes barAttributes( int column ) const;

    /**
    * @return the bar attribute set of the model index \a index
    */
    BarAttributes barAttributes( const QModelIndex & index ) const;


    /**
      * Sets the global 3D bar attributes to \a threeDAttrs
      */
    void setThreeDBarAttributes( const ThreeDBarAttributes & a );

    /**
     * Sets the 3D bar attributes of dataset \a column to \a threeDAttrs
     */
    void setThreeDBarAttributes( int column, const ThreeDBarAttributes & a );

    /**
    * Sets the 3D line attributes of model index \a index to \a threeDAttrs
    */
    void setThreeDBarAttributes( const QModelIndex & index,
                                  const ThreeDBarAttributes & a );

    /**
      * @return the global 3D bar attributes
      */
    ThreeDBarAttributes threeDBarAttributes() const;

    /**
     * @return the 3D bar attributes of data set \a column
     */
    ThreeDBarAttributes threeDBarAttributes( int column ) const;

    /**
    * @return the 3D bar attributes of the model index \a index
    */
    ThreeDBarAttributes threeDBarAttributes( const QModelIndex & index ) const;

#if defined(Q_COMPILER_MANGLES_RETURN_TYPE)
    // implement AbstractCartesianDiagram
    /** \reimpl */
    const int numberOfAbscissaSegments () const;
    /** \reimpl */
    const int numberOfOrdinateSegments () const;
#else
    // implement AbstractCartesianDiagram
    /** \reimpl */
    int numberOfAbscissaSegments () const override;
    /** \reimpl */
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
private:

    void calculateValueAndGapWidths( int rowCount, int colCount,
                                     qreal groupWidth,
                                     qreal& barWidth,
                                     qreal& spaceBetweenBars,
                                     qreal& spaceBetweenGroups );
}; // End of class BarDiagram

}

#endif // KCHARTBARDIAGRAM_H
