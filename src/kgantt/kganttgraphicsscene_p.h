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

#ifndef KGANTTGRAPHICSSCENE_P_H
#define KGANTTGRAPHICSSCENE_P_H

#include <QPersistentModelIndex>
#include <QHash>
#include <QPointer>
#include <QItemSelectionModel>
#include <QAbstractProxyModel>

#include "kganttgraphicsscene.h"
#include "kganttconstraintmodel.h"
#include "kganttdatetimegrid.h"

namespace KGantt {
    class AbstractGrid;

    class Q_DECL_HIDDEN GraphicsScene::Private {
    public:
        explicit Private(GraphicsScene*);
        ~Private();

        void clearConstraintItems();
        void resetConstraintItems();
        void createConstraintItem( const Constraint& c );
        void deleteConstraintItem( ConstraintGraphicsItem* citem );
        void deleteConstraintItem( const Constraint& c );
        ConstraintGraphicsItem* findConstraintItem( const Constraint& c ) const;

	void recursiveUpdateMultiItem( const Span& span, const QModelIndex& idx );

        void clearItems();
        AbstractGrid *getGrid();
        const AbstractGrid *getGrid() const;

        GraphicsScene* q;

        QHash<QPersistentModelIndex,GraphicsItem*> items;
        QList<ConstraintGraphicsItem*> constraintItems;
        GraphicsItem* dragSource;

        QPointer<ItemDelegate> itemDelegate;
        AbstractRowController* rowController;
        DateTimeGrid           default_grid;
        QPointer<AbstractGrid> grid;
        bool readOnly;

        /* printing related members */
        bool isPrinting;
        bool drawColumnLabels;
        qreal labelsWidth;

        QPointer<QAbstractProxyModel> summaryHandlingModel;

        QPointer<ConstraintModel> constraintModel;

        QPointer<QItemSelectionModel> selectionModel;
    };

    GraphicsScene::GraphicsScene( GraphicsScene::Private* d ) : _d( d )
    {
        init();
    }
}

#endif /* KGANTTGRAPHICSSCENE_P_H */

