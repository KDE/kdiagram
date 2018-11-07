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

#ifndef PLOTTERDIAGRAMCOMPRESSOR_H
#define PLOTTERDIAGRAMCOMPRESSOR_H

#include <QObject>
#include <QAbstractItemModel>
#include <QPointer>
#include <QVector>
#include <QDateTime>

#include <cmath>
#include <limits>

namespace KChart
{


class PlotterDiagramCompressor : public QObject
{
    Q_OBJECT
    Q_ENUMS( CompressionMode )
public:

    enum CompressionMode{ SLOPE = 0, DISTANCE, BOTH };
    class DataPoint {
    public:
        DataPoint()
            : key( std::numeric_limits< qreal >::quiet_NaN() ),
              value( std::numeric_limits< qreal >::quiet_NaN() ),
              hidden( false )
              {}
        inline qreal distance( const DataPoint &other )
        {
            const qreal dx = key - other.key;
            const qreal dy = value - other.value;
            return std::sqrt( dx * dx + dy * dy );
        }

        inline bool operator==( const DataPoint &other )
        {
            return key == other.key && value == other.value;
        }

        inline bool operator!=( const DataPoint &other )
        {
            return !( *this == other );
        }

        qreal key;
        qreal value;
        bool hidden;
        QModelIndex index;
    };

    class Iterator
    {
        friend class PlotterDiagramCompressor;
    public:
        Iterator( int dataSet, PlotterDiagramCompressor *parent );
        ~Iterator();
        bool isValid() const;
        Iterator& operator++();
        Iterator operator++( int );
        Iterator& operator += ( int value );
        Iterator& operator--();
        Iterator operator--( int );
        Iterator& operator-=( int value );
        DataPoint operator*();
        bool operator==( const Iterator &other ) const;
        bool operator!=( const Iterator &other ) const;
        void invalidate();
    protected:
        Iterator( int dataSet, PlotterDiagramCompressor *parent, QVector< DataPoint > buffer );
    private:
        void handleSlopeForward( const DataPoint &dp );
        QPointer< PlotterDiagramCompressor > m_parent;
        QVector< DataPoint > m_buffer;
        int m_index;
        int m_dataset;
        int m_bufferIndex;
        int m_rebuffer;
        QDateTime m_timeOfCreation;
    };

    typedef QVector<DataPoint> DataPointVector;
    class CachePosition {
    public:
        CachePosition()
            : first( -1 ),
              second( -1 )
              {}
        CachePosition( int first, int second )
            : first( first ),
              second( second )
              {}
        int first;
        int second;

        bool operator==( const CachePosition& rhs ) const
        {
            return first == rhs.first &&
                   second == rhs.second;
        }
    };
    explicit PlotterDiagramCompressor(QObject *parent = nullptr);
    ~PlotterDiagramCompressor();
    Iterator begin( int dataSet );
    Iterator end( int dataSet );    
    void setMergeRadius( qreal radius );
    void setMergeRadiusPercentage( qreal radius );
    void setModel( QAbstractItemModel *model );
    QAbstractItemModel* model() const;
    DataPoint data( const CachePosition& pos ) const;
    int rowCount() const;
    int datasetCount() const;
    void setCompressionModel( CompressionMode value );
    void setMaxSlopeChange( qreal value );
    qreal maxSlopeChange() const;
    void cleanCache();
    QPair< QPointF, QPointF > dataBoundaries() const;
    void setForcedDataBoundaries( const QPair< qreal, qreal > &bounds, Qt::Orientation direction );
Q_SIGNALS:
    void boundariesChanged();
    void rowCountChanged();

private:
    class Private;
    Private *d;
};

}

#endif // PLOTTERDIAGRAMCOMPRESSOR_H
