/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef ENTRYDELEGATE_H
#define ENTRYDELEGATE_H

#include <QItemDelegate>

namespace KGantt {
    class ConstraintModel;
}

class EntryDelegate : public QItemDelegate {
public:
    EntryDelegate( KGantt::ConstraintModel* constraintModel, QObject* parent = nullptr );
    
    bool editorEvent( QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index ) override;
    
private:
    void addConstraint(const QModelIndex & index1, const QModelIndex & index2);
    void setReadOnly(const QModelIndex & index, bool readOnly);
    
    KGantt::ConstraintModel* constraintModel;
};

#endif /* ENTRYDELEGATE_H */
