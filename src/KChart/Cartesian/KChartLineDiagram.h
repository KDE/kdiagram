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


    void setType( const LineType type );
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
}; // End of class KChartLineDiagram

}

#endif // KCHARTLINEDIAGRAM_H
