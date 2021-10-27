/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTGRAPHICSITEM_H
#define KGANTTGRAPHICSITEM_H

#include "kganttglobal.h"
#include "kganttstyleoptionganttitem.h"

#include <QGraphicsItem>
#include <QDateTime>
#include <QPersistentModelIndex>

QT_BEGIN_NAMESPACE
class QGraphicsLineItem;
QT_END_NAMESPACE

namespace KGantt {
    class GraphicsScene;
    class ConstraintGraphicsItem;

    /* Can we fit every kind of item into one gfxitem class? */

    /*!\class KGantt::GraphicsItem
     * \internal
     */
    class KGANTT_EXPORT GraphicsItem : public QGraphicsItem {
    public:
        enum { Type = UserType + 42 };

        explicit GraphicsItem( QGraphicsItem* parent = nullptr, GraphicsScene* scene = nullptr );
        explicit GraphicsItem( const QModelIndex& idx, QGraphicsItem* parent = nullptr, GraphicsScene* scene = nullptr );
        ~GraphicsItem() override;

        /*reimp*/int type() const override;
        /*reimp (non-virtual)*/ GraphicsScene* scene() const;

        void updateItem( const Span& rowgeometry, const QPersistentModelIndex& idx );

        //virtual ItemType itemType() const = 0;

        //qreal dateTimeToSceneX( const QDateTime& dt ) const;
        //QDateTime sceneXtoDateTime( qreal x ) const;

        QRectF rect() const { return m_rect; }
        void setRect( const QRectF& r );
        void setBoundingRect( const QRectF& r );

        virtual QString ganttToolTip() const;

        const QPersistentModelIndex& index() const { return m_index; }
        void setIndex( const QPersistentModelIndex& idx );

        bool isEditable() const;
        bool isUpdating() const { return m_isupdating; }

        void addStartConstraint( ConstraintGraphicsItem* );
        void addEndConstraint( ConstraintGraphicsItem* );
        void removeStartConstraint( ConstraintGraphicsItem* );
        void removeEndConstraint( ConstraintGraphicsItem* );
        QList<ConstraintGraphicsItem*> startConstraints() const { return m_startConstraints; }
        QList<ConstraintGraphicsItem*> endConstraints() const { return m_endConstraints; }

        /*reimp*/ QRectF boundingRect() const override;
        /*reimp*/ void paint( QPainter* painter, const QStyleOptionGraphicsItem* option,
                              QWidget* widget = nullptr ) override;

        /*reimp*/ QVariant itemChange( GraphicsItemChange, const QVariant& value ) override;
    protected:
        /*reimp*/ void focusInEvent( QFocusEvent* event ) override;
        /*reimp*/ void hoverMoveEvent( QGraphicsSceneHoverEvent* ) override;
        /*reimp*/ void hoverLeaveEvent( QGraphicsSceneHoverEvent* ) override;
        /*reimp*/ void mousePressEvent( QGraphicsSceneMouseEvent* ) override;
        /*reimp*/ void mouseReleaseEvent( QGraphicsSceneMouseEvent* ) override;
        /*reimp*/ void mouseDoubleClickEvent( QGraphicsSceneMouseEvent* ) override;
        /*reimp*/ void mouseMoveEvent( QGraphicsSceneMouseEvent* ) override;

    private:
        void init();

        QPointF startConnector( int relationType ) const;
        QPointF endConnector( int relationType ) const;
        void updateConstraintItems();
        StyleOptionGanttItem getStyleOption() const;
        void updateModel();
        void updateItemFromMouse( const QPointF& scenepos );
        void constraintsChanged();

        QRectF m_rect;
        QRectF m_boundingrect;
        QPersistentModelIndex m_index;
        bool m_isupdating;
        int m_istate;
        QPointF m_presspos;
        QPointF m_pressscenepos;
        QGraphicsLineItem* m_dragline;
        GraphicsItem* m_dragtarget;
        QList<ConstraintGraphicsItem*> m_startConstraints;
        QList<ConstraintGraphicsItem*> m_endConstraints;
    };
}

#endif /* KGANTTGRAPHICSITEM_H */

