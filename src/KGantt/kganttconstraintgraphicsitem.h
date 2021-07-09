/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTCONSTRAINTGRAPHICSITEM_H
#define KGANTTCONSTRAINTGRAPHICSITEM_H

#include <QGraphicsItem>

#include "kganttconstraint.h"

namespace KGantt {
    class GraphicsScene;



    /*!\class KGantt::ConstraintGraphicsItem
     * \internal
     */
    class KGANTT_EXPORT ConstraintGraphicsItem : public QGraphicsItem {
    public:
        enum { Type = UserType + 43 };

        explicit ConstraintGraphicsItem( const Constraint& c,
                                         QGraphicsItem* parent = nullptr, GraphicsScene* scene = nullptr );
        virtual ~ConstraintGraphicsItem();

        /*reimp*/ int type() const override;
        /*reimp (non virtual)*/GraphicsScene* scene() const;

        /*reimp*/ QString ganttToolTip() const;

        /*reimp*/ QRectF boundingRect() const override;
        /*reimp*/ void paint( QPainter* painter, const QStyleOptionGraphicsItem* option,
                              QWidget* widget = nullptr ) override;

        inline const Constraint& constraint() const { return m_constraint; }
        Constraint proxyConstraint() const;

        void setStart( const QPointF& start );
        inline QPointF start() const { return m_start; }
        void setEnd( const QPointF& end );
        inline QPointF end() const { return m_end; }

        void updateItem( const QPointF& start,const QPointF& end );
    private:
        Constraint m_constraint;
        QPointF m_start;
        QPointF m_end;
    };
}

#endif /* KGANTTCONSTRAINTGRAPHICSITEM_H */

