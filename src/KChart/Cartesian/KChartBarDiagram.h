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

    void setType( const BarType type );
    BarType type() const;

    void setOrientation( Qt::Orientation orientation );
    Qt::Orientation orientation() const;

    void setBarAttributes( const BarAttributes & a );
    void setBarAttributes( int column, const BarAttributes & a );
    void setBarAttributes( const QModelIndex & index, const BarAttributes & a );

    BarAttributes barAttributes() const;
    BarAttributes barAttributes( int column ) const;
    BarAttributes barAttributes( const QModelIndex & index ) const;

    void setThreeDBarAttributes( const ThreeDBarAttributes & a );
    void setThreeDBarAttributes( int column, const ThreeDBarAttributes & a );
    void setThreeDBarAttributes( const QModelIndex & index,
                                  const ThreeDBarAttributes & a );
    ThreeDBarAttributes threeDBarAttributes() const;
    ThreeDBarAttributes threeDBarAttributes( int column ) const;
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
    int numberOfAbscissaSegments () const Q_DECL_OVERRIDE;
    /** \reimpl */
    int numberOfOrdinateSegments () const Q_DECL_OVERRIDE;
#endif

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
private:

    void calculateValueAndGapWidths( int rowCount, int colCount,
                                     qreal groupWidth,
                                     qreal& barWidth,
                                     qreal& spaceBetweenBars,
                                     qreal& spaceBetweenGroups );
}; // End of class BarDiagram

}

#endif // KCHARTBARDIAGRAM_H
