/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
     * changes and deletion and emits corresponding signals.
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
        void diagramDestroyed( KChart::AbstractDiagram* diagram );
        /** Emitted when a diagram is being destroyed, but before its data is invalidated **/
        void diagramAboutToBeDestroyed( KChart::AbstractDiagram* diagram );
        /** This signal is emitted whenever the data of the diagram changes. */
        void diagramDataChanged( KChart::AbstractDiagram* diagram );
        /** This signal is emitted whenever any of the data of the diagram was set (un)hidden. */
        void diagramDataHidden( KChart::AbstractDiagram* diagram );
        /** This signal is emitted whenever the attributes of the diagram change. */
        void diagramAttributesChanged( KChart::AbstractDiagram* diagram );

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
