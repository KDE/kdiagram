/**
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

#ifndef ENTRYDELEGATE_H
#define ENTRYDELEGATE_H

#include <QItemDelegate>

namespace KDGantt {
    class ConstraintModel;
}

class EntryDelegate : public QItemDelegate {
public:
    explicit EntryDelegate( KDGantt::ConstraintModel* constraintModel, QObject* parent = 0 );
    
    bool editorEvent( QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index );
    
private:
    void addConstraint(const QModelIndex & index1, const QModelIndex & index2);
    void setReadOnly(const QModelIndex & index, bool readOnly);
    
    KDGantt::ConstraintModel* constraintModel;
};

#endif /* ENTRYDELEGATE_H */
