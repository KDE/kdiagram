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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KGANTTITEMDELEGATE_H
#define KGANTTITEMDELEGATE_H

#include <QItemDelegate>
#include <QBrush>
#include <QPen>
#include <QDebug>

#include "kganttglobal.h"

namespace KGantt {
    class StyleOptionGanttItem;
    class Constraint;

    class KGANTT_EXPORT ItemDelegate : public QItemDelegate {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( ItemDelegate )
    public:
        enum InteractionState { State_None = 0,
                                State_Move,
                                State_ExtendLeft,
                                State_ExtendRight,
                                State_DragConstraint
        };

        explicit ItemDelegate( QObject* parent = nullptr );
        virtual ~ItemDelegate();

        void setDefaultBrush( ItemType type, const QBrush& brush );
        QBrush defaultBrush( ItemType type ) const;

        void setDefaultPen( ItemType type, const QPen& pen );
        QPen defaultPen( ItemType type ) const;

        virtual Span itemBoundingSpan(const StyleOptionGanttItem& opt, const QModelIndex& idx) const;
        virtual QRectF constraintBoundingRect( const QPointF& start, const QPointF& end, const Constraint &constraint ) const;
        virtual InteractionState interactionStateFor( const QPointF& pos,
						      const StyleOptionGanttItem& opt,
						      const QModelIndex& idx ) const;

        virtual void paintGanttItem( QPainter* p, const StyleOptionGanttItem& opt, const QModelIndex& idx );
        virtual void paintConstraintItem( QPainter* p, const QStyleOptionGraphicsItem& opt,
                                          const QPointF& start, const QPointF& end, const Constraint &constraint );
        
        virtual QString toolTip( const QModelIndex &idx ) const;

    protected:
        void paintFinishStartConstraint( QPainter* p, const QStyleOptionGraphicsItem& opt,
                const QPointF& start, const QPointF& end, const Constraint &constraint );
        QPolygonF finishStartLine( const QPointF& start, const QPointF& end ) const;
        QPolygonF finishStartArrow( const QPointF& start, const QPointF& end ) const;

        void paintFinishFinishConstraint( QPainter* p, const QStyleOptionGraphicsItem& opt,
                const QPointF& start, const QPointF& end, const Constraint &constraint );
        QPolygonF finishFinishLine( const QPointF& start, const QPointF& end ) const;
        QPolygonF finishFinishArrow( const QPointF& start, const QPointF& end ) const;
        
        void paintStartStartConstraint( QPainter* p, const QStyleOptionGraphicsItem& opt,
                const QPointF& start, const QPointF& end, const Constraint &constraint );
        QPolygonF startStartLine( const QPointF& start, const QPointF& end ) const;
        QPolygonF startStartArrow( const QPointF& start, const QPointF& end ) const;
        
        void paintStartFinishConstraint( QPainter* p, const QStyleOptionGraphicsItem& opt,
                const QPointF& start, const QPointF& end, const Constraint &constraint );
        QPolygonF startFinishLine( const QPointF& start, const QPointF& end ) const;
        QPolygonF startFinishArrow( const QPointF& start, const QPointF& end ) const;

        
    };
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<( QDebug dbg, KGantt::ItemDelegate::InteractionState );
#endif

#endif /* KGANTTITEMDELEGATE_H */

