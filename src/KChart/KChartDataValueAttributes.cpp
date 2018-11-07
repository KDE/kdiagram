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

#include "KChartDataValueAttributes.h"

#include <QVariant>
#include <QDebug>
#include "KChartRelativePosition.h"
#include "KChartPosition.h"
#include "KChartMath_p.h"
#include <KChartTextAttributes.h>
#include <KChartFrameAttributes.h>
#include <KChartBackgroundAttributes.h>
#include <KChartMarkerAttributes.h>

// FIXME till
#define KCHART_DATA_VALUE_AUTO_DIGITS 4


#define d d_func()

using namespace KChart;

class Q_DECL_HIDDEN DataValueAttributes::Private
{
    friend class DataValueAttributes;
public:
    Private();
private:
    TextAttributes textAttributes;
    FrameAttributes frameAttributes;
    BackgroundAttributes backgroundAttributes;
    MarkerAttributes markerAttributes;
    QString prefix;
    QString suffix;
    QString dataLabel;
    RelativePosition negativeRelPos;
    RelativePosition positiveRelPos;
    qint16 decimalDigits;
    qint16 powerOfTenDivisor;
    bool visible : 1;
    bool showInfinite : 1;
    bool showRepetitiveDataLabels : 1;
    bool showOverlappingDataLabels : 1;
    bool usePercentage : 1;
    bool mirrorNegativeValueTextRotation : 1;
};

DataValueAttributes::Private::Private() :
    decimalDigits( KCHART_DATA_VALUE_AUTO_DIGITS ),
    powerOfTenDivisor( 0 ),
    visible( false ),
    showInfinite( true )
{
    Measure me( 20.0, KChartEnums::MeasureCalculationModeAuto, KChartEnums::MeasureOrientationAuto );
    textAttributes.setFontSize( me );
    me.setValue( 8.0 );
    me.setCalculationMode( KChartEnums::MeasureCalculationModeAbsolute );
    textAttributes.setMinimalFontSize( me );
    textAttributes.setRotation( -45 );

    // we set the Position to unknown: so the diagrams can take their own decisions
    positiveRelPos.setReferencePosition( Position::Unknown );
    negativeRelPos.setReferencePosition( Position::Unknown );

    positiveRelPos.setAlignment( Qt::AlignTop | Qt::AlignRight );
    negativeRelPos.setAlignment( Qt::AlignBottom | Qt::AlignRight );

    showRepetitiveDataLabels = false;
    showOverlappingDataLabels = false;

    usePercentage = false;
    mirrorNegativeValueTextRotation = false;
}


DataValueAttributes::DataValueAttributes()
    : _d( new Private() )
{
}

DataValueAttributes::DataValueAttributes( const DataValueAttributes& r )
    : _d( new Private( *r.d ) )
{
}

DataValueAttributes & DataValueAttributes::operator=( const DataValueAttributes& r )
{
    if ( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

DataValueAttributes::~DataValueAttributes()
{
    delete _d; _d = nullptr;
}


bool DataValueAttributes::operator==( const DataValueAttributes& r ) const
{
    return  isVisible() == r.isVisible() &&
            textAttributes() == r.textAttributes() &&
            frameAttributes() == r.frameAttributes() &&
            backgroundAttributes() == r.backgroundAttributes() &&
            markerAttributes() == r.markerAttributes() &&
            decimalDigits() == r.decimalDigits() &&
            prefix() == r.prefix() &&
            suffix() == r.suffix() &&
            dataLabel() == r.dataLabel() &&
            powerOfTenDivisor() == r.powerOfTenDivisor() &&
            showInfinite() == r.showInfinite() &&
            negativePosition() == r.negativePosition() &&
            positivePosition() == r.positivePosition() &&
            showRepetitiveDataLabels() == r.showRepetitiveDataLabels() &&
            showOverlappingDataLabels() == r.showOverlappingDataLabels() &&
            usePercentage() == r.usePercentage() &&
            mirrorNegativeValueTextRotation() == r.mirrorNegativeValueTextRotation();
}

/*static*/
const DataValueAttributes& DataValueAttributes::defaultAttributes()
{
    static const DataValueAttributes theDefaultDataValueAttributes;
    return theDefaultDataValueAttributes;
}

/*static*/
const QVariant& DataValueAttributes::defaultAttributesAsVariant()
{
    static const QVariant theDefaultDataValueAttributesVariant = qVariantFromValue(defaultAttributes());
    return theDefaultDataValueAttributesVariant;
}


void DataValueAttributes::setVisible( bool visible )
{
    d->visible = visible;
}

bool DataValueAttributes::isVisible() const
{
    return d->visible;
}

void DataValueAttributes::setTextAttributes( const TextAttributes &a )
{
    d->textAttributes = a;
}

TextAttributes DataValueAttributes::textAttributes() const
{
    return d->textAttributes;
}

void DataValueAttributes::setFrameAttributes( const FrameAttributes &a )
{
    d->frameAttributes = a;
}

FrameAttributes DataValueAttributes::frameAttributes() const
{
    return d->frameAttributes;
}

void DataValueAttributes::setBackgroundAttributes( const BackgroundAttributes &a )
{
    d->backgroundAttributes = a;
}

BackgroundAttributes DataValueAttributes::backgroundAttributes() const
{
    return d->backgroundAttributes;
}

void DataValueAttributes::setMarkerAttributes( const MarkerAttributes &a )
{
    d->markerAttributes = a;
}

MarkerAttributes DataValueAttributes::markerAttributes() const
{
    return d->markerAttributes;
}

void DataValueAttributes::setMirrorNegativeValueTextRotation( bool enable )
{
    d->mirrorNegativeValueTextRotation = enable;
}

bool DataValueAttributes::mirrorNegativeValueTextRotation() const
{
    return d->mirrorNegativeValueTextRotation;
}

void DataValueAttributes::setUsePercentage( bool enable )
{
    d->usePercentage = enable;
}

bool DataValueAttributes::usePercentage() const
{
    return d->usePercentage;
}

void DataValueAttributes::setDecimalDigits( int digits )
{
    d->decimalDigits = digits;
}

int DataValueAttributes::decimalDigits() const
{
    return d->decimalDigits;
}

void DataValueAttributes::setPrefix( const QString prefixString )
{
    d->prefix = prefixString;
}

QString DataValueAttributes::prefix() const
{
    return d->prefix;
}

void DataValueAttributes::setSuffix( const QString suffixString )
{
    d->suffix  = suffixString;
}

QString DataValueAttributes::suffix() const
{
    return d->suffix;
}

void DataValueAttributes::setDataLabel( const QString label )
{
    d->dataLabel =  label;
}

QString DataValueAttributes::dataLabel() const
{
    return d->dataLabel;
}

bool DataValueAttributes::showRepetitiveDataLabels() const
{
    return d->showRepetitiveDataLabels;
}

void DataValueAttributes::setShowRepetitiveDataLabels( bool showRepetitiveDataLabels )
{
    d->showRepetitiveDataLabels = showRepetitiveDataLabels;
}

bool DataValueAttributes::showOverlappingDataLabels() const
{
    return d->showOverlappingDataLabels;
}

void DataValueAttributes::setShowOverlappingDataLabels( bool showOverlappingDataLabels )
{
    d->showOverlappingDataLabels = showOverlappingDataLabels;
}

void DataValueAttributes::setPowerOfTenDivisor( int powerOfTenDivisor )
{
    d->powerOfTenDivisor = powerOfTenDivisor;
}

int DataValueAttributes::powerOfTenDivisor() const
{
    return d->powerOfTenDivisor;
}

void DataValueAttributes::setShowInfinite( bool infinite )
{
    d->showInfinite = infinite;
}

bool DataValueAttributes::showInfinite() const
{
    return d->showInfinite;
}

void DataValueAttributes::setNegativePosition( const RelativePosition& relPosition )
{
    d->negativeRelPos = relPosition;
}

const RelativePosition DataValueAttributes::negativePosition() const
{
    return d->negativeRelPos;
}

void DataValueAttributes::setPositivePosition( const RelativePosition& relPosition )
{
    d->positiveRelPos = relPosition;
}

const RelativePosition DataValueAttributes::positivePosition() const
{
    return d->positiveRelPos;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KChart::DataValueAttributes& val )
{
    dbg << "RelativePosition DataValueAttributes("
	<< "visible="<<val.isVisible()
	<< "textattributes="<<val.textAttributes()
	<< "frameattributes="<<val.frameAttributes()
	<< "backgroundattributes="<<val.backgroundAttributes()
	<< "decimaldigits="<<val.decimalDigits()
	<< "poweroftendivisor="<<val.powerOfTenDivisor()
	<< "showinfinite="<<val.showInfinite()
	<< "negativerelativeposition="<<val.negativePosition()
	<< "positiverelativeposition="<<val.positivePosition()
    << "showRepetitiveDataLabels="<<val.showRepetitiveDataLabels()
    << "showOverlappingDataLabels="<<val.showOverlappingDataLabels()
    <<")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
