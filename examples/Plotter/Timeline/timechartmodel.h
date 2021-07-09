/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef TIMECHARTMODEL_H
#define TIMECHARTMODEL_H

#include <QDateTime>
#include <QSortFilterProxyModel>
#include <QPair>

class TimeChartModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TimeChartModel( QObject* parent = nullptr );

    QPair< QDateTime, QDateTime > visibleRange() const;

    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;

public Q_SLOTS:
    void setVisibleRange( const QDateTime& start, const QDateTime& end );
    void setVisibleStart( const QDateTime& start );
    void setVisibleEnd( const QDateTime& end );

protected:
    bool filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const override;

private:
    QPair< QDateTime, QDateTime > range;
};

#endif
