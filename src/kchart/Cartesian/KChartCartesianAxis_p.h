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

#ifndef KCHARTCARTESIANAXIS_P_H
#define KCHARTCARTESIANAXIS_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the KD Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "KChartCartesianAxis.h"
#include "KChartAbstractCartesianDiagram.h"
#include "KChartAbstractAxis_p.h"
#include "KChartMath_p.h"


namespace KChart {

/**
  * \internal
  */
class Q_DECL_HIDDEN CartesianAxis::Private : public AbstractAxis::Private
{
    friend class CartesianAxis;

public:
    Private( AbstractCartesianDiagram* diagram, CartesianAxis* axis )
        : AbstractAxis::Private( diagram, axis )
        , useDefaultTextAttributes( true )
        , cachedHeaderLabels( QStringList() )
        , cachedLabelHeight( 0.0 )
        , cachedFontHeight( 0 )
        , axisTitleSpace( 1.0 )
    {}
    ~Private() {}

    static const Private *get( const CartesianAxis *axis ) { return axis->d_func(); };

    CartesianAxis* axis() const { return static_cast<CartesianAxis *>( mAxis ); }
    void drawTitleText( QPainter*, CartesianCoordinatePlane* plane, const QRect& areaGeoRect ) const;
    const TextAttributes titleTextAttributesWithAdjustedRotation() const;
    QSize calculateMaximumSize() const;
    QString customizedLabelText( const QString& text, Qt::Orientation orientation, qreal value ) const;
    bool isVertical() const;

    QMap< qreal, QString > annotations;

private:
    friend class TickIterator;
    QString titleText;
    TextAttributes titleTextAttributes;
    bool useDefaultTextAttributes;
    Position position;
    QRect geometry;
    int customTickLength;
    QList< qreal > customTicksPositions;
    mutable QStringList cachedHeaderLabels;
    mutable qreal cachedLabelHeight;
    mutable qreal cachedLabelWidth;
    mutable int cachedFontHeight;
    mutable int cachedFontWidth;
    mutable QSize cachedMaximumSize;
    qreal axisTitleSpace;
};

inline CartesianAxis::CartesianAxis( Private * p, AbstractDiagram* diagram )
    : AbstractAxis( p, diagram )
{
    init();
}

inline CartesianAxis::Private * CartesianAxis::d_func()
{ return static_cast<Private*>( AbstractAxis::d_func() ); }
inline const CartesianAxis::Private * CartesianAxis::d_func() const
{ return static_cast<const Private*>( AbstractAxis::d_func() ); }


class XySwitch
{
public:
    explicit XySwitch( bool _isY ) : isY( _isY ) {}

    // for rvalues
    template< class T >
    T operator()( T x, T y ) const { return isY ? y : x; }

    // lvalues
    template< class T >
    T& lvalue( T& x, T& y ) const { return isY ? y : x; }

    bool isY;
};

class TickIterator
{
public:
    enum TickType {
        NoTick = 0,
        MajorTick,
        MajorTickHeaderDataLabel,
        MajorTickManualShort,
        MajorTickManualLong,
        MinorTick,
        CustomTick
    };
    // this constructor is for use in CartesianAxis
    TickIterator( CartesianAxis *a, CartesianCoordinatePlane* plane, uint majorThinningFactor,
                  bool omitLastTick /* sorry about that */ );
    // this constructor is for use in CartesianGrid
    TickIterator( bool isY, const DataDimension& dimension, bool useAnnotationsForTicks,
                  bool hasMajorTicks, bool hasMinorTicks, CartesianCoordinatePlane* plane );

    qreal position() const { return m_position; }
    QString text() const { return m_text; }
    TickType type() const { return m_type; }
    bool hasShorterLabels() const { return m_axis && !m_axis->labels().isEmpty() &&
                                    m_axis->shortLabels().count() == m_axis->labels().count(); }
    bool isAtEnd() const { return m_position == std::numeric_limits< qreal >::infinity(); }
    void operator++();

    bool areAlmostEqual( qreal r1, qreal r2 ) const;

private:
    // code shared by the two constructors
    void init( bool isY, bool hasMajorTicks, bool hasMinorTicks, CartesianCoordinatePlane* plane );

    bool isHigherPrecedence( qreal importantLabelValue, qreal unimportantLabelValue ) const;
    void computeMajorTickLabel( int decimalPlaces );

    // these are generally set once in the constructor
    CartesianAxis* m_axis;
    DataDimension m_dimension; // upper and lower bounds
    int m_decimalPlaces; // for numeric labels
    bool m_isLogarithmic;
    QMap< qreal, QString > m_annotations;
    QMap< qreal, QString > m_dataHeaderLabels;
    QList< qreal > m_customTicks;
    QStringList m_manualLabelTexts;
    uint m_majorThinningFactor;
    uint m_majorLabelCount;

    // these generally change in operator++(), i.e. from one label to the next
    int m_customTickIndex;
    int m_manualLabelIndex;
    TickType m_type;
    qreal m_position;
    qreal m_customTick;
    qreal m_majorTick;
    qreal m_minorTick;
    QString m_text;
};

}

#endif
