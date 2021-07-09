/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>
#include <QTimer>
#include <QVector>

class Model : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Function {
        SineFunction = 0,
        TriangleFunction,
        SquareFunction,
        NoiseFunction,
        OneDivSineFunction,
        SineOneDivFunction
    };
    Model();

    int columnCount( const QModelIndex& parent ) const override;
    int rowCount( const QModelIndex& parent ) const override;

    QModelIndex index( int row, int column, const QModelIndex& parent ) const override;
    QModelIndex parent( const QModelIndex& index ) const override;

    QVariant data( const QModelIndex& index, int role ) const override;

    void setFunction( Function f );

    void appendPoints( int numPoints );

public Q_SLOTS:
    void setRunning( bool );

private Q_SLOTS:
    void appendPoint();

private:
    qreal nextFunctionValue();

    qreal m_x;
    Function m_function;
    QVector< qreal > m_data;
    QTimer m_appendTimer;
};

#endif
