/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <QApplication>
#include <QStandardItemModel>
#include <QTreeView>
#include <QTimer>
#include <QWidget>
#include <QSplitter>
#include <QPushButton>

#include <math.h>

#include <KChartChart>
#include <KChartPlotter>

#include "timeaxis.h"
#include "timechartmodel.h"

class ChartWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChartWidget(QWidget* parent = nullptr) : QWidget(parent), m_counter(0) {
        QSplitter* splitter = new QSplitter(this);
        QHBoxLayout* l = new QHBoxLayout(this);
        setLayout(l);
        l->addWidget( splitter );

        QWidget* leftWidget = new QWidget( splitter );
        QVBoxLayout* leftLayout = new QVBoxLayout(leftWidget);
        leftWidget->setLayout(leftLayout);
        
        QPushButton* button = new QPushButton("Animate", leftWidget);
        leftLayout->addWidget( button );
        button->setCheckable( true );
        connect( button, SIGNAL(toggled(bool)), this, SLOT(buttonToggled(bool)) );

        QTreeView* tv = new QTreeView( leftWidget );
        leftLayout->addWidget( tv );

        m_chart = new KChart::Chart( splitter );
        
        m_model = new QStandardItemModel( 365, 2, this );
        for ( int i = 0; i < 365; ++i ) {
            const QDateTime dt = QDateTime( QDate( 2010, 1, 1 ), QTime() );
            m_model->setData( m_model->index( i, 0 ), dt.addDays( i ) );
            m_model->setData( m_model->index( i, 1 ), sin( i / 10.0 ) * 10 );
        }

        TimeChartModel* proxy = new TimeChartModel( this );
        proxy->setSourceModel( m_model );
        proxy->setVisibleRange( QDateTime( QDate( 2010, 2, 1 ), QTime() ),
                                QDateTime( QDate( 2010, 3, 31 ), QTime() ) );

        KChart::Plotter* plotter = new KChart::Plotter;
        m_chart->coordinatePlane()->replaceDiagram( plotter );

        tv->setModel( proxy );
        tv->show();

        TimeAxis* axis = new TimeAxis( plotter );
        axis->setPosition( TimeAxis::Bottom );
        plotter->addAxis( axis );

        plotter->setModel( proxy );

        connect( proxy, SIGNAL(rowsInserted(QModelIndex,int,int)),
                 m_chart->coordinatePlane(), SLOT(adjustRangesToData()) );
        connect( proxy, SIGNAL(rowsRemoved(QModelIndex,int,int)),
                 m_chart->coordinatePlane(), SLOT(adjustRangesToData()) );

        proxy->setVisibleRange( QDateTime( QDate( 2010, 3, 15 ), QTime() ),
                                QDateTime( QDate( 2010, 5, 18 ), QTime() ) );
        qobject_cast< KChart::CartesianCoordinatePlane* >( m_chart->coordinatePlane() )->adjustRangesToData();

        m_timer = new QTimer(this);
        connect( m_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()) );
    }
private Q_SLOTS:
    void slotTimeout() {

        // An ugly hack to prevent the QAbstractItemModel from emitting dataChanged
        // for every single call to setData which would result in a full relayout
        // every time. That is horrible for performance and what we do is we prevent
        // QAbstractItemModel from emitting dataChanged, we collect what data changed and
        // we emit the signal at the end ourself.
        m_model->blockSignals(true);
        QModelIndexList indexes;

        for ( int i = 0; i < 365; ++i ) {
            QModelIndex idx = m_model->index( i, 1 );
            indexes.append(idx);
            m_model->setData( idx, sin( i / 10.0 + m_counter ) * 10 );
        }

        m_model->blockSignals(false);
        if (!indexes.isEmpty()) {
            m_model->metaObject()->invokeMethod(m_model, "dataChanged", Qt::DirectConnection, Q_ARG(QModelIndex,indexes.first()), Q_ARG(QModelIndex,indexes.last()));
        }

        m_counter += 0.02;
    }
    void buttonToggled(bool checked) {
        if (checked)
            m_timer->start( 200 );
        else
            m_timer->stop();
    }
private:
    KChart::Chart* m_chart;
    QStandardItemModel* m_model;
    QTimer* m_timer;
    qreal m_counter;
};

/**
 * This example demonstrates how to use time-based plots with timestamp-value data points
 * based on seconds and how to use a proxy model for defining the plotted "window" of the
 * measurement data.
 */
int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    
    ChartWidget w;
    w.show();

    return app.exec();
}

#include "main.moc"
