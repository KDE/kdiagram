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

#ifndef __KCHARTDIAGRAMOBSERVER_H_
#define __KCHARTDIAGRAMOBSERVER_H_

#include "KChartGlobal.h"

#include <QObject>
#include <QPointer>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

namespace KChart {

    class AbstractDiagram;

    /**
     * \brief A DiagramObserver watches the associated diagram for
     * changes and deletion and emits corresponsing signals.
     */
    class KCHART_EXPORT DiagramObserver : public QObject
    {
        Q_OBJECT
    public:
       /**
         * Constructs a new observer observing the given diagram.
         */
        explicit DiagramObserver( AbstractDiagram * diagram, QObject* parent = nullptr );
        ~DiagramObserver();

        const AbstractDiagram* diagram() const;
        AbstractDiagram* diagram();

    Q_SIGNALS:
        /** This signal is emitted immediately before the diagram is
          * being destroyed. */
        void diagramDestroyed( AbstractDiagram* diagram );
        /** Emitted when a diagram is being destroyed, but before its data is invalidated **/
        void diagramAboutToBeDestroyed( AbstractDiagram* diagram );
        /** This signal is emitted whenever the data of the diagram changes. */
        void diagramDataChanged( AbstractDiagram* diagram );
        /** This signal is emitted whenever any of the data of the diagram was set (un)hidden. */
        void diagramDataHidden( AbstractDiagram* diagram );
        /** This signal is emitted whenever the attributes of the diagram change. */
        void diagramAttributesChanged( AbstractDiagram* diagram );

    private Q_SLOTS:
        void slotDestroyed(QObject*);
        void slotAboutToBeDestroyed();
        void slotHeaderDataChanged(Qt::Orientation,int,int);
        void slotDataChanged(QModelIndex,QModelIndex);
        void slotDataChanged();
        void slotDataHidden();
        void slotAttributesChanged();
        void slotAttributesChanged(QModelIndex,QModelIndex);
        void slotModelsChanged();

    private:
        void init();

        AbstractDiagram*    m_diagram;
        QPointer<QAbstractItemModel> m_model;
        QPointer<QAbstractItemModel> m_attributesmodel;
   };
}

#endif // KChartDiagramObserver_H
