/**
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QAbstractItemModel>

class ProjectModel : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit ProjectModel( QObject* parent = 0 );
    virtual ~ProjectModel();

    /*reimp*/ int rowCount( const QModelIndex& idx ) const;
    /*reimp*/ int columnCount( const QModelIndex& idx ) const;

    /*reimp*/ QModelIndex index( int row, int col, const QModelIndex& parent = QModelIndex() ) const;
    /*reimp*/ QModelIndex parent( const QModelIndex& idx ) const;

    /*reimp*/QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    /*reimp*/ QVariant data( const QModelIndex& idx, int role = Qt::DisplayRole ) const;
    /*reimp*/ bool setData( const QModelIndex& idx,  const QVariant& value,
                            int role = Qt::DisplayRole );

    /*reimp*/ bool insertRows( int row, int count, const QModelIndex& parent = QModelIndex() );

    /*reimp*/ Qt::ItemFlags flags( const QModelIndex& ) const;

    bool load( const QString& filename );
    bool save( const QString& filename );

private:
    class Node;

    Node* m_root;
};

#endif /* PROJECTMODEL_H */

