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

#include "KChartTernaryAxis.h"

#include <QPainter>

#include <KChartChart.h>
#include <KChartPaintContext.h>

#include "TernaryConstants.h"
#include "KChartTernaryCoordinatePlane.h"
#include "KChartAbstractTernaryDiagram.h"


#include "KChartLayoutItems.h"
#include "KChartTextLabelCache.h"

using namespace KChart;

// m_label and m_fifty do not have to be pointers, once the class is
// pimpled (PrerenderedLabel is not published API)

TernaryAxis::TernaryAxis ( AbstractTernaryDiagram* diagram)
    : AbstractAxis( diagram )
    , m_position( KChartEnums::PositionUnknown )
    , m_label( new PrerenderedLabel )
    , m_fifty( new PrerenderedLabel )
{
    resetTitleTextAttributes();
    setPosition( KChartEnums::PositionSouth ); // arbitrary
    m_fifty->setText( QObject::tr( "50%" ) ); // const
    // FIXME is this consistent with other diagram/axis/plane implementations?
    diagram->addAxis( this );
}

TernaryAxis::~TernaryAxis()
{
    delete m_label; m_label = nullptr;
    delete m_fifty; m_fifty = nullptr;
}

void  TernaryAxis::paintAll (QPainter &)
{
    // not used
}

void  TernaryAxis::paint (QPainter *)
{
    // not used
}

void  TernaryAxis::paintCtx (PaintContext * paintContext)
{
    QPainter* p = paintContext->painter();
    TernaryCoordinatePlane* plane =
        (TernaryCoordinatePlane*) paintContext->coordinatePlane();
    // QObject* refArea = plane->parent();
    QRectF titleArea;

    // paint the axis label (across the triangle, that one):
    QList<PrerenderedLabel*> labels;
    labels << m_label << m_fifty;
    Q_FOREACH( PrerenderedLabel* label, labels ) {
        const QPixmap& pixmap = label->pixmap();
        QPointF point = plane->translate( label->position() )
                        - label->referencePointLocation();
        p->drawPixmap( point, pixmap );
    }
}

bool TernaryAxis::isEmpty() const
{
    // todo: what's this method for?
    return false;
}

QRect TernaryAxis::geometry () const
{
    return m_geometry;
}

void TernaryAxis::setGeometry (const QRect &rect)
{
    m_geometry = rect;
}

QSize  TernaryAxis::minimumSize () const
{
    // todo: return realistic sizes
    return QSize( 100, 100 );
}

QSize  TernaryAxis::maximumSize () const
{
    return QSize( 300, 200 );
}

QSize  TernaryAxis::sizeHint () const
{
    return QSize( 150, 100 );
}

Qt::Orientations TernaryAxis::expandingDirections () const
{
    return Qt::Vertical | Qt::Horizontal;
}

const Position TernaryAxis::position () const
{
    return m_position;
}

void  TernaryAxis::setPosition (Position p)
{
    if ( p == position() ) return;

    if ( p != KChartEnums::PositionWest
         && p != KChartEnums::PositionEast
         && p != KChartEnums::PositionSouth )
    {
        qDebug() << "TernaryAxis::setPosition: only south, east and west are supported "
            "positions for ternary axes.";
        return;
    }

    if ( m_title.isEmpty() )
        switch ( p.value() ) {
        case KChartEnums::PositionSouth:
            m_label->setText( tr( "A" ) );
            break;
        case KChartEnums::PositionWest:
            m_label->setText( tr( "C" ) );
            break;
        case KChartEnums::PositionEast:
            m_label->setText( tr( "B" ) );
            break;
        default:
            break;
        }

    m_position = p;
    updatePrerenderedLabels(); // position has changed
}

void TernaryAxis::setTitleText( const QString& text )
{
    m_title = text; // do not remove
    m_label->setText( text );
}

QString TernaryAxis::titleText() const
{
    return m_label->text();
}

void TernaryAxis::setTitleTextAttributes( const TextAttributes &a )
{
    m_titleAttributes = a;
    updatePrerenderedLabels();
}

TextAttributes TernaryAxis::titleTextAttributes() const
{
    return m_titleAttributes;
}

void TernaryAxis::resetTitleTextAttributes()
{
    TextAttributes a;
    m_titleAttributes = a;
    updatePrerenderedLabels();
}

bool TernaryAxis::hasDefaultTitleTextAttributes() const
{
    TextAttributes a;
    return m_titleAttributes == a;
}

void TernaryAxis::updatePrerenderedLabels()
{
    TextAttributes attributes = titleTextAttributes();
    qreal axisLabelAngle = 0.0;
    qreal fiftyMarkAngle = 0.0;
    QPointF axisLabelPosition;
    QPointF fiftyMarkPosition;
    KChartEnums::PositionValue fiftyMarkReferencePoint = KChartEnums::PositionUnknown;

    switch ( position().value() ) {
    case KChartEnums::PositionSouth:
        // this is the axis on the other side of A
        axisLabelAngle = 0.0;
        fiftyMarkAngle = 0.0;
        axisLabelPosition = TriangleTop;
        fiftyMarkPosition = 0.5 * AxisVector_B_C - RelMarkerLength * Norm_B_C;
        fiftyMarkReferencePoint = KChartEnums::PositionNorth;
        break;
    case KChartEnums::PositionEast:
        // this is the axis on the other side of B
        axisLabelAngle = 240.0;
        fiftyMarkAngle = 60;
        axisLabelPosition = TriangleBottomLeft;
        fiftyMarkPosition = AxisVector_B_C + 0.5 * AxisVector_C_A - RelMarkerLength * Norm_C_A;
        fiftyMarkReferencePoint = KChartEnums::PositionSouth;
        break;
    case KChartEnums::PositionWest:
        // this is the axis on the other side of C
        axisLabelAngle = 120.0;
        fiftyMarkAngle = 300.0;
        axisLabelPosition = TriangleBottomRight;
        fiftyMarkPosition = 0.5 * AxisVector_B_A + RelMarkerLength * Norm_B_A;
        fiftyMarkReferencePoint = KChartEnums::PositionSouth;
        break;
    case KChartEnums::PositionUnknown:
        break; // initial value
    default:
        qDebug() << "TernaryAxis::updatePrerenderedLabel: unknown location";
    };

    m_label->setFont( attributes.font() );
    // m_label->setText( titleText() ); // done by setTitleText()
    m_label->setAngle( axisLabelAngle );
    m_label->setPosition( axisLabelPosition );
    m_label->setReferencePoint( KChartEnums::PositionSouth );
    QFont font = attributes.font();
    font.setPointSizeF( 0.85 * font.pointSizeF() );
    m_fifty->setFont( font );
    m_fifty->setAngle( fiftyMarkAngle );
    m_fifty->setPosition( fiftyMarkPosition );
    m_fifty->setReferencePoint( fiftyMarkReferencePoint );
}

QPair<QSizeF, QSizeF> TernaryAxis::requiredMargins() const
{
    QSizeF topleft( 0.0, 0.0 );
    QSizeF bottomRight( 0.0, 0.0 );

    switch ( position().value() ) {
    case KChartEnums::PositionSouth:
        // the label of the south axis is, in fact, up north.
        topleft.setHeight( m_label->pixmap().height() );
        bottomRight.setHeight( m_fifty->pixmap().height() );
        break;
    case KChartEnums::PositionWest:
        bottomRight.setWidth( m_label->pixmap().width()
                              - m_label->referencePointLocation().x() );
        bottomRight.setHeight( m_label->pixmap().height()
                               - m_label->referencePointLocation().y() );
        break;
    case KChartEnums::PositionEast:
        topleft.setWidth( m_label->pixmap().width()
                          - ( m_label->pixmap().width()
                              - m_label->referencePointLocation().x() ) );
        bottomRight.setHeight( m_label->pixmap().height()
                               - ( m_label->pixmap().height()
                                   - m_label->referencePointLocation().y() ) );
        break;
    default:
        qDebug() << "TernaryAxis::requiredMargins: unknown location";
    }
//     qDebug() << "TernaryAxis::requiredMargins:" << topleft << bottomRight;
    return QPair<QSizeF, QSizeF>( topleft, bottomRight );
}
