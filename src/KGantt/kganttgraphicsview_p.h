/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTGRAPHICSVIEW_P_H
#define KGANTTGRAPHICSVIEW_P_H

#include "kganttgraphicsview.h"
#include "kganttgraphicsscene.h"
#include "kganttdatetimegrid.h"

#include <QPointer>

namespace KGantt {
    class HeaderWidget : public QWidget {
        Q_OBJECT
    public:
        explicit HeaderWidget( GraphicsView* parent );
        virtual ~HeaderWidget();

        GraphicsView* view() const { return qobject_cast<GraphicsView*>( parent() );}

    public Q_SLOTS:
        void scrollTo( int );
    protected:
        /*reimp*/ bool event( QEvent* ev ) override;
        /*reimp*/ void paintEvent( QPaintEvent* ev ) override;
        /*reimp*/ void mousePressEvent(QMouseEvent *event) override;
        /*reimp*/ void mouseReleaseEvent(QMouseEvent *event) override;
        /*reimp*/ void mouseMoveEvent(QMouseEvent *event) override;
        /*reimp*/ void wheelEvent(QWheelEvent *event) override;
        /*reimp*/ void contextMenuEvent( QContextMenuEvent* ev ) override;
    private:
        qreal m_offset;
        DateTimeGrid::HeaderType m_headerType;
        int m_mousePosX;
    };

    class Q_DECL_HIDDEN GraphicsView::Private {
        Q_DISABLE_COPY( Private )
    public:
        explicit Private(GraphicsView* _q);
        ~Private();

        void updateHeaderGeometry();

        void slotGridChanged();
        void slotHorizontalScrollValueChanged( int val );

        /* slots for QAbstractItemModel signals */
        void slotColumnsInserted( const QModelIndex& parent,  int start, int end );
        void slotColumnsRemoved( const QModelIndex& parent,  int start, int end );
        void slotDataChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight );
        void slotLayoutChanged();
        void slotModelReset();
        void slotRowsInserted( const QModelIndex& parent,  int start, int end );
        void slotRowsAboutToBeRemoved( const QModelIndex& parent,  int start, int end );
        void slotRowsRemoved( const QModelIndex& parent,  int start, int end );

        void slotItemClicked( const QModelIndex& idx );
        void slotItemDoubleClicked( const QModelIndex& idx );

        void slotHeaderContextMenuRequested( const QPoint& pt );

        void removeConstraintsRecursive( QAbstractProxyModel *summaryModel, const QModelIndex& index );

        GraphicsView* q;
        AbstractRowController* rowcontroller;
        HeaderWidget headerwidget;
        GraphicsScene scene;
    };
}

#endif /* KGANTTGRAPHICSVIEW_P_H */

