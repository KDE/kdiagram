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

#ifndef KGANTTABSTRACTGRID_H
#define KGANTTABSTRACTGRID_H

#include "kganttglobal.h"
#include "kganttconstraint.h"

QT_BEGIN_NAMESPACE
class QPainter;
class QRectF;
class QAbstractItemModel;
class QModelIndex;
QT_END_NAMESPACE

namespace KGantt {
    class AbstractRowController;
    class Span;

    class KGANTT_EXPORT AbstractGrid : public QObject {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( AbstractGrid )
	friend class GraphicsScene;
    public:

        AbstractGrid(QObject* parent = nullptr);
        virtual ~AbstractGrid();

        QAbstractItemModel* model() const;
        QModelIndex rootIndex() const;

        virtual Span mapToChart( const QModelIndex& idx ) const = 0;
        virtual bool mapFromChart( const Span& span, const QModelIndex& idx,
                                   const QList<Constraint>& constraints=QList<Constraint>() ) const = 0;
        virtual qreal mapToChart( const QVariant &value ) const;
        virtual QVariant mapFromChart( qreal x ) const;
        bool isSatisfiedConstraint( const Constraint& c ) const;

        virtual void paintGrid( QPainter* painter, const QRectF& sceneRect, const QRectF& exposedRect,
                                AbstractRowController* rowController = nullptr, QWidget* widget = nullptr ) = 0;
        virtual void paintHeader( QPainter* painter, const QRectF& headerRect, const QRectF& exposedRect,
                                  qreal offset, QWidget* widget = nullptr ) = 0;

    public Q_SLOTS:
        /*internal*/ virtual void setModel( QAbstractItemModel* model );
        /*internal*/ virtual void setRootIndex( const QModelIndex& idx );
    Q_SIGNALS:
        void gridChanged();

    protected:
        virtual void drawBackground(QPainter* paint, const QRectF& rect);
        virtual void drawForeground(QPainter* paint, const QRectF& rect);
    };
}

#endif /* KGANTTABSTRACTGRID_H */
