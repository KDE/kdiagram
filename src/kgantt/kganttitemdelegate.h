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

    /*!\class KGantt::ItemDelegate kganttitemdelegate.h KGanttItemDelegate
     *\ingroup KGantt
     *\brief Class used to render gantt items in a KGantt::GraphicsView
     *
     */
    class KGANTT_EXPORT ItemDelegate : public QItemDelegate {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( ItemDelegate )
    public:
        /*!\enum KGantt::ItemDelegate::InteractionState
         * This enum is used for communication between the view and
         * the delegate about user interaction with gantt items.
         *
         * \see KGantt::ItemDelegate::interactionStateFor
         */
        enum InteractionState { State_None = 0,
                                State_Move,
                                State_ExtendLeft,
                                State_ExtendRight,
                                State_DragConstraint
        };

        /*! Constructor. Creates an ItemDelegate with parent \a parent */
        explicit ItemDelegate( QObject* parent = nullptr );

        /*! Destructor */
        virtual ~ItemDelegate();

        /*! Sets the default brush used for items of type \a type to
         * \a brush. The default brush is used in the case when the model
         * does not provide an explicit brush.
         *
         * \todo Move this to GraphicsView to make delegate stateless.
         */
        void setDefaultBrush( ItemType type, const QBrush& brush );

        /*!\returns The default brush for item type \a type
         *
         * \todo Move this to GraphicsView to make delegate stateless.
         */
        QBrush defaultBrush( ItemType type ) const;

        /*! Sets the default pen used for items of type \a type to
         * \a pen. The default pen is used in the case when the model
         * does not provide an explicit pen.
         *
         * \todo Move this to GraphicsView to make delegate stateless.
         */
        void setDefaultPen( ItemType type, const QPen& pen );

        /*!\returns The default pen for item type \a type
         *
         * \todo Move this to GraphicsView to make delegate stateless.
         */
        QPen defaultPen( ItemType type ) const;

        /*! \returns The bounding Span for the item identified by \a idx
         * when rendered with options \a opt. This is often the same as the
         * span given by the AbstractGrid for \a idx, but it might be larger
         * in case there are additional texts or decorations on the item.
         *
         * Override this to implement new itemtypes or to change the look
         * of the existing ones.
         */
        virtual Span itemBoundingSpan(const StyleOptionGanttItem& opt, const QModelIndex& idx) const;

        /*! \return The bounding rectangle for the graphics used to represent
         * a constraint between points \a start and \a end (typically an
         * arrow)
         */
        virtual QRectF constraintBoundingRect( const QPointF& start, const QPointF& end, const Constraint &constraint ) const;

        /*! \returns The interaction state for position \a pos on item \a idx
         * when rendered with options \a opt. This is used to tell the view
         * about how the item should react to mouse click/drag.
         *
         * Override to implement new items or interactions.
         */
        virtual InteractionState interactionStateFor( const QPointF& pos,
                                                      const StyleOptionGanttItem& opt,
                                                      const QModelIndex& idx ) const;

        /*! Paints the gantt item \a idx using \a painter and \a opt
         */
        virtual void paintGanttItem( QPainter* p, const StyleOptionGanttItem& opt, const QModelIndex& idx );

        /*! Paints the \a constraint between points \a start and \a end
         * using \a painter and \a opt.
         *
         * \todo Review \a opt's type
         */
        virtual void paintConstraintItem( QPainter* p, const QStyleOptionGraphicsItem& opt,
                                          const QPointF& start, const QPointF& end, const Constraint &constraint );
        

        /*!\returns The tooltip for index \a idx
         */
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

