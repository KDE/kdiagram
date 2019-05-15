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

#ifndef KCHARTMEASURE_H
#define KCHARTMEASURE_H

#include <QDebug>
#include <Qt>
#include <QStack>
#include "KChartGlobal.h"
#include "KChartEnums.h"

/** \file KChartMeasure.h
 *  \brief Declaring the class KChart::Measure.
 *
 *
 */

QT_BEGIN_NAMESPACE
class QObject;
class QPaintDevice;
QT_END_NAMESPACE

namespace KChart {

/**
  * \class Measure KChartMeasure.h KChartMeasure
  * \brief Measure is used to specify relative and absolute sizes in KChart, e.g. font sizes.
  *
  */

class KCHART_EXPORT Measure
{
public:
    Measure();
    /*implicit*/ Measure( qreal value,
                          KChartEnums::MeasureCalculationMode mode = KChartEnums::MeasureCalculationModeAuto,
                          KChartEnums::MeasureOrientation orientation = KChartEnums::MeasureOrientationAuto );
    Measure( const Measure& );
    Measure &operator= ( const Measure& );

    void setValue( qreal val ) { mValue = val; }
    qreal value() const { return mValue; }

    void setCalculationMode( KChartEnums::MeasureCalculationMode mode ) { mMode = mode; }
    KChartEnums::MeasureCalculationMode calculationMode() const { return mMode; }

    /**
      * The reference area must either be derived from AbstractArea
      * or from QWidget, so it can also be derived from AbstractAreaWidget.
      */
    void setRelativeMode( const QObject * area,
                          KChartEnums::MeasureOrientation orientation )
    {
        mMode = KChartEnums::MeasureCalculationModeRelative;
        mArea = area;
        mOrientation = orientation;
    }

    /**
     * \brief This is a convenience method for specifying a value,
     *  implicitly setting the calculation mode to MeasureCalculationModeAbsolute.
     *
     * Calling setAbsoluteValue( value ) is the same as calling
\verbatim
    setValue( value );
    setCalculationMode( KChartEnums::MeasureCalculationModeAbsolute );
\endverbatim
     */
    void setAbsoluteValue( qreal val )
    {
        mMode = KChartEnums::MeasureCalculationModeAbsolute;
        mValue = val;
    }

    /**
      * The reference area must either be derived from AbstractArea
      * or from QWidget, so it can also be derived from AbstractAreaWidget.
      */
    void setReferenceArea( const QObject * area ) { mArea = area; }
    /**
      * The returned reference area will be derived from AbstractArea
      * or QWidget or both.
      */
    const QObject * referenceArea() const { return mArea; }

    void setReferenceOrientation( KChartEnums::MeasureOrientation orientation ) { mOrientation = orientation; }
    KChartEnums::MeasureOrientation referenceOrientation() const { return mOrientation; }

    /**
      * The reference area must either be derived from AbstractArea
      * or from QWidget, so it can also be derived from AbstractAreaWidget.
      */
    qreal calculatedValue( const QObject * autoArea, KChartEnums::MeasureOrientation autoOrientation ) const;
    qreal calculatedValue( const QSizeF& autoSize, KChartEnums::MeasureOrientation autoOrientation ) const;
    const QSizeF sizeOfArea( const QObject* area ) const;

    bool operator==( const Measure& ) const;
    bool operator!=( const Measure& other ) const { return !operator==(other); }

private:
    qreal mValue;
    KChartEnums::MeasureCalculationMode mMode;
    const QObject* mArea;
    KChartEnums::MeasureOrientation mOrientation;
}; // End of class Measure



/**
 * Auxiliary class used by the KChart::Measure and KChart::Chart class.
 *
 * Normally there should be no need to call any of these methods yourself.
 *
 * They are used by KChart::Chart::paint( QPainter*, const QRect& )
 * to adjust all of the relative Measures according to the target
 * rectangle's size.
 *
 * Default factors are (1.0, 1.0)
 */
class GlobalMeasureScaling
{
public:
    static GlobalMeasureScaling* instance();

    GlobalMeasureScaling();
    virtual ~GlobalMeasureScaling();

public:
    /**
     * Set new factors to be used by all Measure objects from now on.
     * Previous values will be saved on a stack internally.
     */
    static void setFactors(qreal factorX, qreal factorY);

    /**
     * Restore factors to the values before the previous call to
     * setFactors. The current values are popped off a stack internally.
     */
    static void resetFactors();

    /**
     * Return the currently active factors.
     */
    static const QPair< qreal, qreal > currentFactors();

    /**
     * Set the paint device to use for calculating font metrics.
     */
    static void setPaintDevice( QPaintDevice* paintDevice );

    /**
     * Return the paint device to use for calculating font metrics.
     */
    static QPaintDevice* paintDevice();

private:
    QStack< QPair< qreal, qreal > > mFactors;
    QPaintDevice* m_paintDevice;
};

}

#if !defined(QT_NO_DEBUG_STREAM)
KCHART_EXPORT QDebug operator<<(QDebug, const KChart::Measure& );
#endif /* QT_NO_DEBUG_STREAM */

#endif // KCHARTMEASURE_H
