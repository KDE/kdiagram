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

#include "KChartAbstractPieDiagram.h"
#include "KChartAbstractPieDiagram_p.h"

#include "KChartAttributesModel.h"
#include "KChartPieAttributes.h"
#include "KChartThreeDPieAttributes.h"
#include "KChartMath_p.h"

#include <QMap>


using namespace KChart;

AbstractPieDiagram::Private::Private()
    : granularity( 1.0 )
    , autoRotateLabels( false )
{
}

AbstractPieDiagram::Private::~Private() {}

AbstractPieDiagram::AbstractPieDiagram( QWidget* parent, PolarCoordinatePlane *plane ) :
    AbstractPolarDiagram( new Private(), parent, plane )
{
    init();
}

AbstractPieDiagram::~AbstractPieDiagram()
{
}


void AbstractPieDiagram::init()
{
}


bool AbstractPieDiagram::compare( const AbstractPieDiagram* other ) const
{
    if ( other == this ) return true;
    if ( ! other ) {
        //qDebug() << "AbstractPieDiagram::compare() cannot compare to Null pointer";
        return false;
    }
    /*
    qDebug() << "\n             AbstractPieDiagram::compare():";
            // compare own properties
    qDebug() <<
            (granularity() == other->granularity()) &&
            (startPosition() == other->startPosition());
    */
    return  // compare the base class
            ( static_cast<const AbstractPolarDiagram*>(this)->compare( other ) ) &&
            // compare own properties
            (granularity() == other->granularity()) &&
            (startPosition() == other->startPosition());
}


#define d d_func()

void AbstractPieDiagram::setGranularity( qreal value )
{
    d->granularity = value;
}

qreal AbstractPieDiagram::granularity() const
{
    return (d->granularity < 0.05 || d->granularity > 36.0)
            ? 1.0
    : d->granularity;
}


void AbstractPieDiagram::setStartPosition( int degrees )
{
    Q_UNUSED( degrees );
    qWarning() << "Deprecated AbstractPieDiagram::setStartPosition() called, setting ignored.";
}

int AbstractPieDiagram::startPosition() const
{
    qWarning() << "Deprecated AbstractPieDiagram::startPosition() called.";
    return 0;
}

void AbstractPieDiagram::setAutoRotateLabels( bool autoRotate )
{
    d->autoRotateLabels = autoRotate;
}

bool AbstractPieDiagram::autoRotateLabels() const
{
    return d->autoRotateLabels;
}

void AbstractPieDiagram::setPieAttributes( const PieAttributes & attrs )
{
    d->attributesModel->setModelData( QVariant::fromValue( attrs ), PieAttributesRole );
    Q_EMIT layoutChanged( this );
}

void AbstractPieDiagram::setPieAttributes( int column, const PieAttributes & attrs )
{
    d->setDatasetAttrs( column, QVariant::fromValue( attrs ), PieAttributesRole );
    Q_EMIT layoutChanged( this );
}

void AbstractPieDiagram::setPieAttributes( const QModelIndex & index, const PieAttributes & attrs )
{
	d->attributesModel->setData( index, QVariant::fromValue( attrs), PieAttributesRole );
    Q_EMIT layoutChanged( this );
}

PieAttributes AbstractPieDiagram::pieAttributes() const
{
    return d->attributesModel->data( PieAttributesRole ).value<PieAttributes>();
}

PieAttributes AbstractPieDiagram::pieAttributes( int column ) const
{
    const QVariant attrs( d->datasetAttrs( column, PieAttributesRole ) );
    if ( attrs.isValid() )
        return attrs.value< PieAttributes >();
    return pieAttributes();
}

PieAttributes AbstractPieDiagram::pieAttributes( const QModelIndex & index ) const
{
    return d->attributesModel->data(
            d->attributesModel->mapFromSource( index ),
            PieAttributesRole ).value<PieAttributes>();
}


void AbstractPieDiagram::setThreeDPieAttributes( const ThreeDPieAttributes & tda )
{
    d->attributesModel->setModelData( QVariant::fromValue( tda ), ThreeDPieAttributesRole );
    Q_EMIT layoutChanged( this );
}

void AbstractPieDiagram::setThreeDPieAttributes( int column, const ThreeDPieAttributes & tda )
{
    d->setDatasetAttrs( column, QVariant::fromValue( tda ), ThreeDPieAttributesRole );
    Q_EMIT layoutChanged( this );
}

void AbstractPieDiagram::setThreeDPieAttributes( const QModelIndex & index, const ThreeDPieAttributes & tda )
{
    model()->setData( index, QVariant::fromValue( tda ), ThreeDPieAttributesRole );
    Q_EMIT layoutChanged( this );
}

ThreeDPieAttributes AbstractPieDiagram::threeDPieAttributes() const
{
    return d->attributesModel->data( ThreeDPieAttributesRole ).value<ThreeDPieAttributes>();
}

ThreeDPieAttributes AbstractPieDiagram::threeDPieAttributes( int column ) const
{
    const QVariant attrs( d->datasetAttrs( column, ThreeDPieAttributesRole ) );
    if ( attrs.isValid() )
        return attrs.value< ThreeDPieAttributes >();
    return threeDPieAttributes();
}

ThreeDPieAttributes AbstractPieDiagram::threeDPieAttributes( const QModelIndex & index ) const
{
    return d->attributesModel->data(
            d->attributesModel->mapFromSource( index ),
            ThreeDPieAttributesRole ).value<ThreeDPieAttributes>();
}

