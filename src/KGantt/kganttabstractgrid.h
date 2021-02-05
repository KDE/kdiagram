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



    /*!\class KGantt::AbstractGrid kganttabstractgrid.h KGanttAbstractGrid
     * \ingroup KGantt
     * \brief Abstract baseclass for grids. A grid is used to convert between
     * QModelIndex'es and gantt chart values (qreals) and to paint the
     * background and header of the view.
     *
     * \see KGantt::DateTimeGrid
     */
    class KGANTT_EXPORT AbstractGrid : public QObject {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( AbstractGrid )
	friend class GraphicsScene;
    public:
        /*! Constructor. Creates an AbstractGrid with parent \a parent.
         * The QObject parent is not used for anything internally. */
        AbstractGrid(QObject* parent = nullptr);


        /*! Destructor. Does nothing */
        virtual ~AbstractGrid();

        /*!\returns The QAbstractItemModel used by this grid */
        QAbstractItemModel* model() const;

        /*!\returns the current root index for this grid */
        QModelIndex rootIndex() const;

        /*!\fn virtual Span AbstractGrid::mapToChart( const QModelIndex& idx ) const
         * Implement this to map from the data in the model to the location of
         * the corresponding item in the view.
         */
        virtual Span mapToChart( const QModelIndex& idx ) const = 0;

        /*!\fn virtual bool AbstractGrid::mapFromChart( const Span& span, const QModelIndex& idx, const QList<Constraint>& constraints ) const
         * Implement this to update the model data based on the location of the item. Check
         * against the \a constraints list to make sure no hard constraints are violated by
         * writing back to the model.
         * \returns true if the update succeeded.
         */
        virtual bool mapFromChart( const Span& span, const QModelIndex& idx,
                                   const QList<Constraint>& constraints=QList<Constraint>() ) const = 0;

        /*!
        * Implement this to map from \a value to the corresponding location in the view.
        * Return a negative value if \a value cannot be mapped.
        * The default implementation returns -1.0.
        */
        virtual qreal mapToChart( const QVariant &value ) const;

        /*!
         * Implement this to map from \a x to the corresponding location in the view.
         * Return an invalid value if \a x cannot be mapped.
         */
        virtual QVariant mapFromChart( qreal x ) const;

        /*!\returns true if the startpoint is before the endpoint
         * of the constraint \a c.
         */
        bool isSatisfiedConstraint( const Constraint& c ) const;

        /*!\fn virtual void AbstractGrid::paintGrid( QPainter* painter, const QRectF& sceneRect, const QRectF& exposedRect, AbstractRowController* rowController=0, QWidget* widget=0 )
         *
         * Implement this to paint the background of the view -- typically
         * with some grid lines.
         * \param painter -- the QPainter to paint with.
         * \param sceneRect -- the total bounding rectangle of the scene.
         * \param exposedRect -- the rectangle that needs to be painted.
         * \param rowController -- the row controller used by the view -- may be 0.
         * \param widget -- the widget used by the view -- may be 0.
         */
        virtual void paintGrid( QPainter* painter, const QRectF& sceneRect, const QRectF& exposedRect,
                                AbstractRowController* rowController = nullptr, QWidget* widget = nullptr ) = 0;


        /*!\fn virtual void AbstractGrid::paintHeader( QPainter* painter, const QRectF& headerRect, const QRectF& exposedRect, qreal offset, QWidget* widget=0 )
         *
         * Implement this to paint the header part of the view.
         * \param painter -- the QPainter to paint with.
         * \param headerRect -- the total rectangle occupied by the header.
         * \param exposedRect -- the rectangle that needs to be painted.
         * \param offset -- the horizontal scroll offset of the view.
         * \param widget -- the widget used by the view -- may be 0.
         */
        virtual void paintHeader( QPainter* painter, const QRectF& headerRect, const QRectF& exposedRect,
                                  qreal offset, QWidget* widget = nullptr ) = 0;

    public Q_SLOTS:
        /*! Sets the QAbstractItemModel used by this grid implementation.
         * This is called by the view, you should never need to call this
         * from client code.  */
        /*internal*/ virtual void setModel( QAbstractItemModel* model );

        /*! Sets the root index used by this grid implementation.
         * This is called by the view, you should never need to call this
         * from client code.  */
        /*internal*/ virtual void setRootIndex( const QModelIndex& idx );
    Q_SIGNALS:
        void gridChanged();

    protected:
        /*!
        \todo document this function
        */
        virtual void drawBackground(QPainter* paint, const QRectF& rect);

        /*!
        \todo document this function
        */
        virtual void drawForeground(QPainter* paint, const QRectF& rect);
    };
}

#endif /* KGANTTABSTRACTGRID_H */
