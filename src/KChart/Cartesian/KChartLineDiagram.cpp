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

#include "KChartLineDiagram.h"
#include "KChartLineDiagram_p.h"

#include "KChartBarDiagram.h"
#include "KChartPalette.h"
#include "KChartAttributesModel.h"
#include "KChartAbstractGrid.h"
#include "KChartPainterSaver_p.h"

#include "KChartNormalLineDiagram_p.h"
#include "KChartStackedLineDiagram_p.h"
#include "KChartPercentLineDiagram_p.h"
#include "KChartMath_p.h"

#include <QDebug>
#include <QPainter>
#include <QString>
#include <QPainterPath>
#include <QPen>
#include <QVector>

using namespace KChart;

LineDiagram::Private::Private()
{
}

LineDiagram::Private::~Private() {}


#define d d_func()


LineDiagram::LineDiagram( QWidget* parent, CartesianCoordinatePlane* plane ) :
    AbstractCartesianDiagram( new Private(), parent, plane )
{
    init();
}

void LineDiagram::init()
{
    d->normalDiagram = new NormalLineDiagram( this );
    d->stackedDiagram = new StackedLineDiagram( this );
    d->percentDiagram = new PercentLineDiagram( this );
    d->implementor = d->normalDiagram;
    d->centerDataPoints = false;
    d->reverseDatasetOrder = false;
}

LineDiagram::~LineDiagram()
{
    delete d->normalDiagram;
    delete d->stackedDiagram;
    delete d->percentDiagram;
}

LineDiagram * LineDiagram::clone() const
{
    LineDiagram* newDiagram = new LineDiagram( new Private( *d ) );
    newDiagram->setType( type() );
    return newDiagram;
}


bool LineDiagram::compare( const LineDiagram* other ) const
{
    if ( other == this ) return true;
    if ( ! other ) {
        return false;
    }
    return  // compare the base class
            ( static_cast<const AbstractCartesianDiagram*>(this)->compare( other ) ) &&
            // compare own properties
            (type()             == other->type()) &&
            (centerDataPoints() == other->centerDataPoints()) &&
            (reverseDatasetOrder() == other->reverseDatasetOrder());
}

void LineDiagram::setType( const LineType type )
{
    if ( d->implementor->type() == type ) return;
   if ( type != LineDiagram::Normal && datasetDimension() > 1 ) {
       Q_ASSERT_X ( false, "setType()",
                    "This line chart type can't be used with multi-dimensional data." );
       return;
   }
   switch ( type ) {
   case Normal:
       d->implementor = d->normalDiagram;
       break;
   case Stacked:
       d->implementor = d->stackedDiagram;
       break;
   case Percent:
       d->implementor = d->percentDiagram;
       break;
   default:
       Q_ASSERT_X( false, "LineDiagram::setType", "unknown diagram subtype" );
   };

   // d->lineType = type;
   Q_ASSERT( d->implementor->type() == type );

   // AbstractAxis settings - see AbstractDiagram and CartesianAxis
   setPercentMode( type == LineDiagram::Percent );
   setDataBoundariesDirty();
   Q_EMIT layoutChanged( this );
   Q_EMIT propertiesChanged();
}

LineDiagram::LineType LineDiagram::type() const
{
    return d->implementor->type();
}

void LineDiagram::setCenterDataPoints( bool center )
{
    if ( d->centerDataPoints == center ) {
        return;
    }

    d->centerDataPoints = center;
    // The actual data boundaries haven't changed, but the axis will have one more or less tick
    //  A      B    =\        A      B
    //  1......2    =/    1......2......3
    setDataBoundariesDirty();
    Q_EMIT layoutChanged( this );
    Q_EMIT propertiesChanged();
}

bool LineDiagram::centerDataPoints() const
{
    return d->centerDataPoints;
}

void LineDiagram::setReverseDatasetOrder( bool reverse )
{
    d->reverseDatasetOrder = reverse;
}

bool LineDiagram::reverseDatasetOrder() const
{
    return d->reverseDatasetOrder;
}

void LineDiagram::setLineAttributes( const LineAttributes& la )
{
    d->attributesModel->setModelData(
        QVariant::fromValue( la ),
        LineAttributesRole );
    Q_EMIT propertiesChanged();
}

void LineDiagram::setLineAttributes(
        int column,
    const LineAttributes& la )
{
    d->setDatasetAttrs( column, QVariant::fromValue( la ), LineAttributesRole );
    Q_EMIT propertiesChanged();
}

void LineDiagram::resetLineAttributes( int column )
{
    d->resetDatasetAttrs( column, LineAttributesRole );
    Q_EMIT propertiesChanged();
}

void LineDiagram::setLineAttributes(
        const QModelIndex& index,
    const LineAttributes& la )
{
    d->attributesModel->setData(
            d->attributesModel->mapFromSource(index),
    QVariant::fromValue( la ),
    LineAttributesRole );
    Q_EMIT propertiesChanged();
}

void LineDiagram::resetLineAttributes( const QModelIndex & index )
{
    d->attributesModel->resetData(
            d->attributesModel->mapFromSource(index), LineAttributesRole );
    Q_EMIT propertiesChanged();
}

LineAttributes LineDiagram::lineAttributes() const
{
    return d->attributesModel->data( KChart::LineAttributesRole ).value<LineAttributes>();
}

LineAttributes LineDiagram::lineAttributes( int column ) const
{
    const QVariant attrs( d->datasetAttrs( column, LineAttributesRole ) );
    if ( attrs.isValid() )
        return attrs.value<LineAttributes>();
    return lineAttributes();
}

LineAttributes LineDiagram::lineAttributes(
    const QModelIndex& index ) const
{
    return d->attributesModel->data(
            d->attributesModel->mapFromSource(index),
            KChart::LineAttributesRole ).value<LineAttributes>();
}

void LineDiagram::setThreeDLineAttributes(
    const ThreeDLineAttributes& la )
{
    setDataBoundariesDirty();
    d->attributesModel->setModelData(
        QVariant::fromValue( la ),
        ThreeDLineAttributesRole );
   Q_EMIT propertiesChanged();
}

void LineDiagram::setThreeDLineAttributes(
    int column,
    const ThreeDLineAttributes& la )
{
    setDataBoundariesDirty();
    d->setDatasetAttrs( column, QVariant::fromValue( la ), ThreeDLineAttributesRole );
   Q_EMIT propertiesChanged();
}

void LineDiagram::setThreeDLineAttributes(
    const QModelIndex & index,
    const ThreeDLineAttributes& la )
{
    setDataBoundariesDirty();
    d->attributesModel->setData(
        d->attributesModel->mapFromSource(index),
        QVariant::fromValue( la ),
        ThreeDLineAttributesRole );
   Q_EMIT propertiesChanged();
}

ThreeDLineAttributes LineDiagram::threeDLineAttributes() const
{
    return d->attributesModel->data( KChart::ThreeDLineAttributesRole ).value<ThreeDLineAttributes>();
}

ThreeDLineAttributes LineDiagram::threeDLineAttributes( int column ) const
{
    const QVariant attrs( d->datasetAttrs( column, ThreeDLineAttributesRole ) );
    if ( attrs.isValid() )
        return attrs.value<ThreeDLineAttributes>();
    return threeDLineAttributes();
}

ThreeDLineAttributes LineDiagram::threeDLineAttributes( const QModelIndex& index ) const
{
    return d->attributesModel->data(
            d->attributesModel->mapFromSource( index ),
            KChart::ThreeDLineAttributesRole ).value<ThreeDLineAttributes>();
}

qreal LineDiagram::threeDItemDepth( const QModelIndex& index ) const
{
    return threeDLineAttributes( index ).validDepth();
}

qreal LineDiagram::threeDItemDepth( int column ) const
{
    return threeDLineAttributes( column ).validDepth();
}

void LineDiagram::setValueTrackerAttributes( const QModelIndex & index,
                                             const ValueTrackerAttributes & va )
{
    d->attributesModel->setData( d->attributesModel->mapFromSource(index),
                                 QVariant::fromValue( va ),
                                 KChart::ValueTrackerAttributesRole );
    Q_EMIT propertiesChanged();
}

ValueTrackerAttributes LineDiagram::valueTrackerAttributes(
        const QModelIndex & index ) const
{
    return d->attributesModel->data(
            d->attributesModel->mapFromSource( index ),
            KChart::ValueTrackerAttributesRole ).value<ValueTrackerAttributes>();
}

void LineDiagram::resizeEvent ( QResizeEvent* )
{
}

const QPair<QPointF, QPointF> LineDiagram::calculateDataBoundaries() const
{
    d->compressor.setResolution( static_cast<int>( this->size().width() * coordinatePlane()->zoomFactorX() ),
                                 static_cast<int>( this->size().height() * coordinatePlane()->zoomFactorY() ) );

    if ( !checkInvariants( true ) ) return QPair<QPointF, QPointF>( QPointF( 0, 0 ), QPointF( 0, 0 ) );

    // note: calculateDataBoundaries() is ignoring the hidden flags.
    //       That's not a bug but a feature: Hiding data does not mean removing them.
    // For totally removing data from KD Chart's view people can use e.g. a proxy model ...

    // calculate boundaries for different line types Normal - Stacked - Percent - Default Normal
    return d->implementor->calculateDataBoundaries();
}


void LineDiagram::paintEvent ( QPaintEvent*)
{
    QPainter painter ( viewport() );
    PaintContext ctx;
    ctx.setPainter ( &painter );
    ctx.setRectangle ( QRectF ( 0, 0, width(), height() ) );
    paint ( &ctx );
}

void LineDiagram::paint( PaintContext* ctx )
{
    // note: Not having any data model assigned is no bug
    //       but we can not draw a diagram then either.
    if ( !checkInvariants( true ) ) return;
    if ( !AbstractGrid::isBoundariesValid(dataBoundaries()) ) return;
    const PainterSaver p( ctx->painter() );
    if ( model()->rowCount( rootIndex() ) == 0 || model()->columnCount( rootIndex() ) == 0 )
        return; // nothing to paint for us

    AbstractCoordinatePlane* const plane = ctx->coordinatePlane();
    ctx->setCoordinatePlane( plane->sharedAxisMasterPlane( ctx->painter() ) );


    // paint different line types Normal - Stacked - Percent - Default Normal
    d->implementor->paint( ctx );

    ctx->setCoordinatePlane( plane );
}

void LineDiagram::resize ( const QSizeF& size )
{
    d->compressor.setResolution( static_cast<int>( size.width() * coordinatePlane()->zoomFactorX() ),
                                 static_cast<int>( size.height() * coordinatePlane()->zoomFactorY() ) );
    setDataBoundariesDirty();
    AbstractCartesianDiagram::resize( size );
}

#if defined(Q_COMPILER_MANGLES_RETURN_TYPE)
const
#endif
int LineDiagram::numberOfAbscissaSegments () const
{
    return d->attributesModel->rowCount(attributesModelRootIndex());
}

#if defined(Q_COMPILER_MANGLES_RETURN_TYPE)
const
#endif
int LineDiagram::numberOfOrdinateSegments () const
{
    return d->attributesModel->columnCount(attributesModelRootIndex());
}
