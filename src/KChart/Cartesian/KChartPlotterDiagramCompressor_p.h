/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef PLOTTERDIAGRAMCOMPRESSOR_P_H
#define PLOTTERDIAGRAMCOMPRESSOR_P_H

#include "KChartPlotterDiagramCompressor.h"

#include <QPointF>
#include <QDateTime>

typedef QPair< QPointF, QPointF > Boundaries;

namespace KChart
{

class Q_DECL_HIDDEN PlotterDiagramCompressor::Private : public QObject
{
    Q_OBJECT
public:
    Private( PlotterDiagramCompressor *parent );
    QModelIndexList mapToModel( const CachePosition& pos );
    void calculateDataBoundaries();    
    void setBoundaries( const Boundaries &bound );
    bool forcedBoundaries( Qt::Orientation orient ) const;
    bool inBoundaries( Qt::Orientation orient, const PlotterDiagramCompressor::DataPoint &dp ) const;
    PlotterDiagramCompressor *m_parent;
    QAbstractItemModel *m_model;
    qreal m_mergeRadius;
    qreal m_maxSlopeRadius;
    QVector< QVector< DataPoint > > m_bufferlist;
    Boundaries m_boundary;
    QPair< qreal, qreal > m_forcedXBoundaries;
    QPair< qreal, qreal > m_forcedYBoundaries;
    QDateTime m_timeOfLastInvalidation;
    PlotterDiagramCompressor::CompressionMode m_mode;
    QVector< qreal > m_accumulatedDistances;
    //QVector< PlotterDiagramCompressor::Iterator > exisitingIterators;
public Q_SLOTS:
    void rowsInserted( const QModelIndex& parent, int start, int end );
    void clearBuffer();
    void setModelToZero();
};

}

#endif // PLOTTERDIAGRAMCOMPRESSOR_P_H
