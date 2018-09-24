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
