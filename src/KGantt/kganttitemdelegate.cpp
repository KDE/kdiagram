/*
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KGantt library.
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

#include "kganttitemdelegate_p.h"
#include "kganttglobal.h"
#include "kganttstyleoptionganttitem.h"
#include "kganttconstraint.h"

#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QApplication>

#ifndef QT_NO_DEBUG_STREAM

#define PRINT_INTERACTIONSTATE(x) \
    case x: dbg << #x; break;


QDebug operator<<( QDebug dbg, KGantt::ItemDelegate::InteractionState state )
{
    switch ( state ) {
        PRINT_INTERACTIONSTATE( KGantt::ItemDelegate::State_None );
        PRINT_INTERACTIONSTATE( KGantt::ItemDelegate::State_Move );
        PRINT_INTERACTIONSTATE( KGantt::ItemDelegate::State_ExtendLeft );
        PRINT_INTERACTIONSTATE( KGantt::ItemDelegate::State_ExtendRight );
    default:
        break;
    }
    return dbg;
}

#undef PRINT_INTERACTIONSTATE

#endif /* QT_NO_DEBUG_STREAM */

using namespace KGantt;


ItemDelegate::Private::Private()
{
    // Brushes
    QLinearGradient taskgrad( 0., 0., 0., QApplication::fontMetrics().height() );
    taskgrad.setColorAt( 0., Qt::green );
    taskgrad.setColorAt( 1., Qt::darkGreen );

    QLinearGradient summarygrad( 0., 0., 0., QApplication::fontMetrics().height() );
    summarygrad.setColorAt( 0., Qt::blue );
    summarygrad.setColorAt( 1., Qt::darkBlue );

    QLinearGradient eventgrad( 0., 0., 0., QApplication::fontMetrics().height() );
    eventgrad.setColorAt( 0., Qt::red );
    eventgrad.setColorAt( 1., Qt::darkRed );

    defaultbrush[TypeTask]    = taskgrad;
    defaultbrush[TypeSummary] = summarygrad;
    defaultbrush[TypeEvent]   = eventgrad;

    // Pens
    QPen pen( QGuiApplication::palette().windowText(), 1. );

    defaultpen[TypeTask]    = pen;
    defaultpen[TypeSummary] = pen;
    defaultpen[TypeEvent]   = pen;
}

QPen ItemDelegate::Private::constraintPen( const QPointF& start, const QPointF& end, const Constraint& constraint, const QStyleOptionGraphicsItem& opt )
{
    QPen pen;
    QVariant dataPen;

    // Use default pens...
    if ( start.x() <= end.x() ) {
        pen = QPen( opt.palette.windowText().color() );
        dataPen = constraint.data( Constraint::ValidConstraintPen );
    } else {
        pen = QPen( Qt::red );
        dataPen = constraint.data( Constraint::InvalidConstraintPen );
    }

    // ... unless constraint.data() returned a valid pen for this case
    if ( dataPen.canConvert( QVariant::Pen ) ) {
        pen = dataPen.value< QPen >();
    }

    return pen;
}


ItemDelegate::ItemDelegate( QObject* parent )
    : QItemDelegate( parent ), _d( new Private )
{
}


ItemDelegate::~ItemDelegate()
{
    delete _d;
}

#define d d_func()


void ItemDelegate::setDefaultBrush( ItemType type, const QBrush& brush )
{
    d->defaultbrush[type] = brush;
}


QBrush ItemDelegate::defaultBrush( ItemType type ) const
{
    return d->defaultbrush[type];
}


void ItemDelegate::setDefaultPen( ItemType type, const QPen& pen )
{
    d->defaultpen[type]=pen;
}


QPen ItemDelegate::defaultPen( ItemType type ) const
{
    return d->defaultpen[type];
}


QString ItemDelegate::toolTip( const QModelIndex &idx ) const
{
    if ( !idx.isValid() ) return QString();

    const QAbstractItemModel* model = idx.model();
    if ( !model ) return QString();
    QString tip = model->data( idx, Qt::ToolTipRole ).toString();
    if ( !tip.isNull() ) return tip;
    else return tr( "%1 -> %2: %3", "start time -> end time: item name" )
                .arg( model->data( idx, StartTimeRole ).toString() )
                .arg( model->data( idx, EndTimeRole ).toString() )
                .arg( model->data( idx, Qt::DisplayRole ).toString() );
}


Span ItemDelegate::itemBoundingSpan( const StyleOptionGanttItem& opt,
                                 const QModelIndex& idx ) const
{
    if ( !idx.isValid() ) return Span();

    const QString txt = idx.model()->data( idx, Qt::DisplayRole ).toString();
    const int typ = idx.model()->data( idx, ItemTypeRole ).toInt();
    QRectF itemRect = opt.itemRect;


    if ( typ == TypeEvent ) {
        itemRect = QRectF( itemRect.left()-itemRect.height()/2.,
                           itemRect.top(),
                           itemRect.height(),
                           itemRect.height() );
    }

    int tw = opt.fontMetrics.boundingRect( txt ).width();
    tw += static_cast<int>( itemRect.height()/2. );
    Span s;
    switch ( opt.displayPosition ) {
    case StyleOptionGanttItem::Left:
        s = Span( itemRect.left()-tw, itemRect.width()+tw ); break;
    case StyleOptionGanttItem::Right:
        s = Span( itemRect.left(), itemRect.width()+tw ); break;
    case StyleOptionGanttItem::Hidden: // fall through
    case StyleOptionGanttItem::Center:
        s = Span( itemRect.left(), itemRect.width() ); break;
    }
    return s;
}


ItemDelegate::InteractionState ItemDelegate::interactionStateFor( const QPointF& pos,
								  const StyleOptionGanttItem& opt,
								  const QModelIndex& idx ) const
{
    if ( !idx.isValid() ) return State_None;
    if ( !( idx.model()->flags( idx ) & Qt::ItemIsEditable ) ) return State_None;

    const int typ = static_cast<ItemType>( idx.model()->data( idx, ItemTypeRole ).toInt() );

    QRectF itemRect( opt.itemRect );

    // An event item is infinitely thin, basically just a line, because it has only one date instead of two.
    // It is painted with an offset of -height/2, which is taken into account here.
    if ( typ == TypeEvent )
        itemRect = QRectF( itemRect.topLeft() - QPointF( itemRect.height() / 2.0, 0 ), QSizeF( itemRect.height(),
                                                                                               itemRect.height() ) );

    if ( typ == TypeNone || typ == TypeSummary ) return State_None;
    if ( !itemRect.contains(pos) ) return State_None;
    if ( typ == TypeEvent )
        return State_Move;

    qreal delta = 5.;
    if ( itemRect.width() < 15 ) delta = 1.;
    if ( pos.x() >= itemRect.left() && pos.x() < itemRect.left()+delta ) {
        return State_ExtendLeft;
    } else   if ( pos.x() <= itemRect.right() && pos.x() > itemRect.right()-delta ) {
        return State_ExtendRight;
    } else {
        return State_Move;
    }
}


void ItemDelegate::paintGanttItem( QPainter* painter,
                                   const StyleOptionGanttItem& opt,
                                   const QModelIndex& idx )
{
    if ( !idx.isValid() ) return;
    const ItemType typ = static_cast<ItemType>( idx.model()->data( idx, ItemTypeRole ).toInt() );
    const QString& txt = opt.text;
    QRectF itemRect = opt.itemRect;
    QRectF boundingRect = opt.boundingRect;
    boundingRect.setY( itemRect.y() );
    boundingRect.setHeight( itemRect.height() );

    //qDebug() << "itemRect="<<itemRect<<", boundingRect="<<boundingRect;
    //qDebug() << painter->font() << opt.fontMetrics.height() << painter->device()->width() << painter->device()->height();

    painter->save();

    QPen pen = defaultPen( typ );
    if ( opt.state & QStyle::State_Selected ) pen.setWidth( 2*pen.width() );
    painter->setPen( pen );
    painter->setBrush( defaultBrush( typ ) );

    bool drawText = true;
    qreal pw = painter->pen().width()/2.;
    switch ( typ ) {
    case TypeTask:
        if ( itemRect.isValid() ) {
            // TODO
            qreal pw = painter->pen().width()/2.;
            pw-=1;
            QRectF r = itemRect;
            r.translate( 0., r.height()/6. );
            r.setHeight( 2.*r.height()/3. );
            painter->setBrushOrigin( itemRect.topLeft() );
            painter->save();
            painter->translate( 0.5, 0.5 );
            painter->drawRect( r );
            bool ok;
            qreal completion = idx.model()->data( idx, KGantt::TaskCompletionRole ).toReal( &ok );
            if ( ok ) {
                qreal h = r.height();
                QRectF cr( r.x(), r.y()+h/4.,
                           r.width()*completion/100., h/2.+1 /*??*/ );
                QColor compcolor( painter->pen().color() );
                compcolor.setAlpha( 150 );
                painter->fillRect( cr, compcolor );
            }
            painter->restore();
        }
        break;
    case TypeSummary:
        if ( opt.itemRect.isValid() ) {
            // TODO
            pw-=1;
            const QRectF r = QRectF( opt.itemRect ).adjusted( -pw, -pw, pw, pw );
            QPainterPath path;
            const qreal deltaY = r.height()/2.;
            const qreal deltaXBezierControl = .25*qMin( r.width(), r.height() );
            const qreal deltaX = qMin( r.width()/2, r.height() );
            path.moveTo( r.topLeft() );
            path.lineTo( r.topRight() );
            path.lineTo( QPointF( r.right(), r.top() + 2.*deltaY ) );
            //path.lineTo( QPointF( r.right()-3./2.*delta, r.top() + delta ) );
            path.quadTo( QPointF( r.right()-deltaXBezierControl, r.top() + deltaY ), QPointF( r.right()-deltaX, r.top() + deltaY ) );
            //path.lineTo( QPointF( r.left()+3./2.*delta, r.top() + delta ) );
            path.lineTo( QPointF( r.left() + deltaX, r.top() + deltaY ) );
            path.quadTo( QPointF( r.left()+deltaXBezierControl, r.top() + deltaY ), QPointF( r.left(), r.top() + 2.*deltaY ) );
            path.closeSubpath();
            painter->setBrushOrigin( itemRect.topLeft() );
            painter->save();
            painter->translate( 0.5, 0.5 );
            painter->drawPath( path );
            painter->restore();
        }
        break;
    case TypeEvent: /* TODO */
        //qDebug() << opt.boundingRect << opt.itemRect;
        if ( opt.boundingRect.isValid() ) {
            const qreal pw = painter->pen().width() / 2. - 1;
            const QRectF r = QRectF( opt.itemRect ).adjusted( -pw, -pw, pw, pw ).translated( -opt.itemRect.height()/2, 0 );
            QPainterPath path;
            const qreal delta = static_cast< int >( r.height() / 2 );
            path.moveTo( delta, 0. );
            path.lineTo( 2.*delta, delta );
            path.lineTo( delta, 2.*delta );
            path.lineTo( 0., delta );
            path.closeSubpath();
            painter->save();
            painter->translate( r.topLeft() );
            painter->translate( 0, 0.5 );
            painter->drawPath( path );
            painter->restore();
#if 0
            painter->setBrush( Qt::NoBrush );
            painter->setPen( Qt::black );
            painter->drawRect( opt.boundingRect );
            painter->setPen( Qt::red );
            painter->drawRect( r );
#endif
        }
        break;
    default:
        drawText = false;
        break;
    }

    Qt::Alignment ta;
    switch ( opt.displayPosition ) {
        case StyleOptionGanttItem::Left: ta = Qt::AlignLeft; break;
        case StyleOptionGanttItem::Right: ta = Qt::AlignRight; break;
        case StyleOptionGanttItem::Center: ta = Qt::AlignCenter; break;
        case StyleOptionGanttItem::Hidden: drawText = false; break;
    }
    if ( drawText ) {
        pen = painter->pen();
        pen.setColor(opt.palette.text().color());
        painter->setPen(pen);
        painter->drawText( boundingRect, ta | Qt::AlignVCenter, txt );
    }

    painter->restore();
}

static const qreal TURN = 10.;
static const qreal PW = 1.5;


QRectF ItemDelegate::constraintBoundingRect( const QPointF& start, const QPointF& end, const Constraint &constraint ) const
{
    QPolygonF poly;
    switch ( constraint.relationType() ) {
        case Constraint::FinishStart:
            poly = finishStartLine( start, end ) + finishStartArrow( start, end );
            break;
        case Constraint::FinishFinish:
            poly = finishFinishLine( start, end ) + finishFinishArrow( start, end );
            break;
        case Constraint::StartStart:
            poly = startStartLine( start, end ) + startStartArrow( start, end );
            break;
        case Constraint::StartFinish:
            poly = startFinishLine( start, end ) + startFinishArrow( start, end );
            break;
    }
    return poly.boundingRect().adjusted( -PW, -PW, PW, PW );
}



void ItemDelegate::paintConstraintItem( QPainter* painter, const QStyleOptionGraphicsItem& opt,
                                        const QPointF& start, const QPointF& end, const Constraint &constraint )
{
    //qDebug()<<"ItemDelegate::paintConstraintItem"<<start<<end<<constraint;
    switch ( constraint.relationType() ) {
        case Constraint::FinishStart:
            paintFinishStartConstraint( painter, opt, start, end, constraint );
            break;
        case Constraint::FinishFinish:
            paintFinishFinishConstraint( painter, opt, start, end, constraint );
            break;
        case Constraint::StartStart:
            paintStartStartConstraint( painter, opt, start, end, constraint );
            break;
        case Constraint::StartFinish:
            paintStartFinishConstraint( painter, opt, start, end, constraint );
            break;
    }
}

void ItemDelegate::paintFinishStartConstraint( QPainter* painter, const QStyleOptionGraphicsItem& opt, const QPointF& start, const QPointF& end, const Constraint &constraint )
{
    Q_UNUSED( opt );

    const QPen pen = d->constraintPen( start, end, constraint, opt );

    painter->setPen( pen );
    painter->setBrush( pen.color() );

    painter->drawPolyline( finishStartLine( start, end ) );
    painter->drawPolygon( finishStartArrow( start, end ) );
}

QPolygonF ItemDelegate::finishStartLine( const QPointF& start, const QPointF& end ) const
{
    QPolygonF poly;
    qreal midx = end.x() - TURN;
    qreal midy = ( end.y()-start.y() )/2. + start.y();

    if ( start.x() > end.x()-TURN ) {
        poly << start
                << QPointF( start.x()+TURN, start.y() )
                << QPointF( start.x()+TURN, midy )
                << QPointF( end.x()-TURN, midy )
                << QPointF( end.x()-TURN, end.y() )
                << end;
    } else {
        poly << start
                << QPointF( midx, start.y() )
                << QPointF( midx, end.y() )
                << end;
    }
    return poly;
}

QPolygonF ItemDelegate::finishStartArrow( const QPointF& start, const QPointF& end ) const
{
    Q_UNUSED(start);

    QPolygonF poly;
    poly << end
            << QPointF( end.x()-TURN/2., end.y()-TURN/2. )
            << QPointF( end.x()-TURN/2., end.y()+TURN/2. );
    return poly;
}

void ItemDelegate::paintFinishFinishConstraint( QPainter* painter, const QStyleOptionGraphicsItem& opt, const QPointF& start, const QPointF& end, const Constraint &constraint )
{
    Q_UNUSED( opt );

    const QPen pen = d->constraintPen( start, end, constraint, opt );

    painter->setPen( pen );
    painter->setBrush( pen.color() );

    painter->drawPolyline( finishFinishLine( start, end ) );
    painter->drawPolygon( finishFinishArrow( start, end ) );
}

QPolygonF ItemDelegate::finishFinishLine( const QPointF& start, const QPointF& end ) const
{
    QPolygonF poly;
    qreal midx = end.x() + TURN;
    qreal midy = ( end.y()-start.y() )/2. + start.y();

    if ( start.x() > end.x()+TURN ) {
        poly << start
                << QPointF( start.x()+TURN, start.y() )
                << QPointF( start.x()+TURN, end.y() )
                << end;
    } else {
        poly << start
                << QPointF( midx, start.y() )
                << QPointF( midx, midy )
                << QPointF( end.x()+TURN, midy )
                << QPointF( end.x()+TURN, end.y() )
                << end;
    }
    return poly;
}

QPolygonF ItemDelegate::finishFinishArrow( const QPointF& start, const QPointF& end ) const
{
    Q_UNUSED(start);

    QPolygonF poly;
    poly << end
            << QPointF( end.x()+TURN/2., end.y()-TURN/2. )
            << QPointF( end.x()+TURN/2., end.y()+TURN/2. );
    return poly;
}

void ItemDelegate::paintStartStartConstraint( QPainter* painter, const QStyleOptionGraphicsItem& opt, const QPointF& start, const QPointF& end, const Constraint &constraint )
{
    Q_UNUSED( opt );

    const QPen pen = d->constraintPen( start, end, constraint, opt );

    painter->setPen( pen );
    painter->setBrush( pen.color() );

    painter->drawPolyline( startStartLine( start, end ) );
    painter->drawPolygon( startStartArrow( start, end ) );

}

QPolygonF ItemDelegate::startStartLine( const QPointF& start, const QPointF& end ) const
{
    Q_UNUSED(start);

    QPolygonF poly;

    if ( start.x() > end.x() ) {
        poly << start
                << QPointF( end.x()-TURN, start.y() )
                << QPointF( end.x()-TURN, end.y() )
                << end;
    } else {
        poly << start
                << QPointF( start.x()-TURN, start.y() )
                << QPointF( start.x()-TURN, end.y() )
                << QPointF( end.x()-TURN, end.y() )
                << end;
    }
    return poly;
}

QPolygonF ItemDelegate::startStartArrow( const QPointF& start, const QPointF& end ) const
{
    Q_UNUSED(start);

    QPolygonF poly;
    poly << end
            << QPointF( end.x()-TURN/2., end.y()-TURN/2. )
            << QPointF( end.x()-TURN/2., end.y()+TURN/2. );
    return poly;
}

void ItemDelegate::paintStartFinishConstraint( QPainter* painter, const QStyleOptionGraphicsItem& opt, const QPointF& start, const QPointF& end, const Constraint &constraint )
{
    Q_UNUSED( opt );

    const QPen pen = d->constraintPen( start, end, constraint, opt);

    painter->setPen( pen );
    painter->setBrush( pen.color() );

    painter->drawPolyline( startFinishLine( start, end ) );
    painter->drawPolygon( startFinishArrow( start, end ) );
}

QPolygonF ItemDelegate::startFinishLine( const QPointF& start, const QPointF& end ) const
{
    Q_UNUSED(start);

    QPolygonF poly;
    qreal midx = end.x() + TURN;
    qreal midy = ( end.y()-start.y() )/2. + start.y();

    if ( start.x()-TURN > end.x()+TURN ) {
        poly << start
                << QPointF( midx, start.y() )
                << QPointF( midx, end.y() )
                << end;
    } else {
        poly << start
                << QPointF( start.x()-TURN, start.y() )
                << QPointF( start.x()-TURN, midy )
                << QPointF( midx, midy )
                << QPointF( end.x()+TURN, end.y() )
                << end;
    }
    return poly;
}

QPolygonF ItemDelegate::startFinishArrow( const QPointF& start, const QPointF& end ) const
{
    Q_UNUSED(start);

    QPolygonF poly;
    poly << end
            << QPointF( end.x()+TURN/2., end.y()-TURN/2. )
            << QPointF( end.x()+TURN/2., end.y()+TURN/2. );
    return poly;
}


#include "moc_kganttitemdelegate.cpp"
