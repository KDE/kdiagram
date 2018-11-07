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

#include "KChartMeasure.h"

#include <KChartAbstractArea.h>
#include <KChartCartesianCoordinatePlane.h>
#include <KChartTextAttributes.h>
#include <KChartFrameAttributes.h>
#include <KChartBackgroundAttributes.h>
#include "KChartMath_p.h"

#include <QWidget>

namespace KChart {


Measure::Measure()
  : mValue( 0.0 ),
    mMode( KChartEnums::MeasureCalculationModeAuto ),
    mArea( nullptr ),
    mOrientation( KChartEnums::MeasureOrientationAuto )
{
    // this bloc left empty intentionally
}

Measure::Measure( qreal value,
    KChartEnums::MeasureCalculationMode mode,
    KChartEnums::MeasureOrientation orientation )
  : mValue( value ),
    mMode( mode ),
    mArea( nullptr ),
    mOrientation( orientation )
{
    // this bloc left empty intentionally
}

Measure::Measure( const Measure& r )
  : mValue( r.value() ),
    mMode( r.calculationMode() ),
    mArea( r.referenceArea() ),
    mOrientation( r.referenceOrientation() )
{
    // this bloc left empty intentionally
}

Measure & Measure::operator=( const Measure& r )
{
    if ( this != &r ) {
        mValue = r.value();
        mMode  = r.calculationMode();
        mArea  = r.referenceArea();
        mOrientation = r.referenceOrientation();
    }

    return *this;
}


qreal Measure::calculatedValue( const QSizeF& autoSize,
                                KChartEnums::MeasureOrientation autoOrientation) const
{
    if ( mMode == KChartEnums::MeasureCalculationModeAbsolute ) {
        return mValue;
    } else {
        qreal value = 0.0;
        const QObject theAutoArea;
        const QObject* autoArea = &theAutoArea;
        const QObject* area = mArea ? mArea : autoArea;
        KChartEnums::MeasureOrientation orientation = mOrientation;
        switch ( mMode ) {
            case KChartEnums::MeasureCalculationModeAuto:
                area = autoArea;
                orientation = autoOrientation;
                break;
            case KChartEnums::MeasureCalculationModeAutoArea:
                area = autoArea;
                break;
            case KChartEnums::MeasureCalculationModeAutoOrientation:
                orientation = autoOrientation;
                break;
            case KChartEnums::MeasureCalculationModeAbsolute: // fall through intended
            case KChartEnums::MeasureCalculationModeRelative:
                break;
        }
        if ( area ) {
            QSizeF size;
            if ( area == autoArea )
                size = autoSize;
            else
                size = sizeOfArea( area );
            //qDebug() << ( area == autoArea ) << "size" << size;
            qreal referenceValue = 0;
            switch ( orientation ) {
                case KChartEnums::MeasureOrientationAuto: // fall through intended
                case KChartEnums::MeasureOrientationMinimum:
                    referenceValue = qMin( size.width(), size.height() );
                    break;
                case KChartEnums::MeasureOrientationMaximum:
                    referenceValue = qMax( size.width(), size.height() );
                    break;
                case KChartEnums::MeasureOrientationHorizontal:
                    referenceValue = size.width();
                    break;
                case KChartEnums::MeasureOrientationVertical:
                    referenceValue = size.height();
                    break;
            }
            value = mValue / 1000.0 * referenceValue;
        }
        return value;
    }
}


qreal Measure::calculatedValue( const QObject* autoArea,
                                KChartEnums::MeasureOrientation autoOrientation) const
{
    return calculatedValue( sizeOfArea( autoArea ), autoOrientation);
}


const QSizeF Measure::sizeOfArea( const QObject* area ) const
{
    QSizeF size;
    const CartesianCoordinatePlane* plane = dynamic_cast<const CartesianCoordinatePlane*>( area );
    if ( false ) {
        size = plane->visibleDiagramArea().size();
    } else {
        const AbstractArea* kdcArea = dynamic_cast<const AbstractArea*>(area);
        if ( kdcArea ) {
            size = kdcArea->geometry().size();
            //qDebug() << "Measure::sizeOfArea() found kdcArea with size" << size;
        } else {
            const QWidget* widget = dynamic_cast<const QWidget*>(area);
            if ( widget ) {
                /* ATTENTION: Using the layout does not work: The Legend will never get the right size then!
                const QLayout * layout = widget->layout();
                if ( layout ) {
                    size = layout->geometry().size();
                    //qDebug() << "Measure::sizeOfArea() found widget with layout size" << size;
                } else*/
                {
                    size = widget->geometry().size();
                    //qDebug() << "Measure::sizeOfArea() found widget with size" << size;
                }
            } else if ( mMode != KChartEnums::MeasureCalculationModeAbsolute ) {
                size = QSizeF(1.0, 1.0);
                //qDebug("Measure::sizeOfArea() got no valid area.");
            }
        }
    }
    const QPair< qreal, qreal > factors
            = GlobalMeasureScaling::instance()->currentFactors();
    return QSizeF(size.width() * factors.first, size.height() * factors.second);
}


bool Measure::operator==( const Measure& r ) const
{
    return( mValue == r.value() &&
            mMode  == r.calculationMode() &&
            mArea  == r.referenceArea() &&
            mOrientation == r.referenceOrientation() );
}

GlobalMeasureScaling::GlobalMeasureScaling() :
    m_paintDevice( nullptr )
{
    mFactors.push( qMakePair(qreal(1.0), qreal(1.0)) );
}

GlobalMeasureScaling::~GlobalMeasureScaling()
{
    // this space left empty intentionally
}

GlobalMeasureScaling* GlobalMeasureScaling::instance()
{
    static GlobalMeasureScaling instance;
    return &instance;
}

void GlobalMeasureScaling::setFactors(qreal factorX, qreal factorY)
{
    instance()->mFactors.push( qMakePair(factorX, factorY) );
}

void GlobalMeasureScaling::resetFactors()
{
    // never remove the initial (1.0. 1.0) setting
    if ( instance()->mFactors.count() > 1 )
        instance()->mFactors.pop();
}

const QPair< qreal, qreal > GlobalMeasureScaling::currentFactors()
{
    return instance()->mFactors.top();
}

void GlobalMeasureScaling::setPaintDevice( QPaintDevice* paintDevice )
{
    instance()->m_paintDevice = paintDevice;
}

QPaintDevice* GlobalMeasureScaling::paintDevice()
{
    return instance()->m_paintDevice;
}

}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KChart::Measure& m)
{
    dbg << "KChart::Measure("
        << "value="<<m.value()
        << "calculationmode="<<m.calculationMode()
        << "referencearea="<<m.referenceArea()
        << "referenceorientation="<<m.referenceOrientation()
        << ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
