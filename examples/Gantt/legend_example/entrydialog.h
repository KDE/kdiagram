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

#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include <QDateTime>
#include <QDialog>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
namespace Ui {
    class EntryDialog;
}
QT_END_NAMESPACE

namespace KGantt {
    class ConstraintModel;
}

class EntryDialog : public QDialog {
    Q_OBJECT

public:
    explicit EntryDialog( const QAbstractItemModel* model, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags() );
    void initFrom( const QModelIndex& index, const KGantt::ConstraintModel* constraintModel );
    
    QString name() const;
    int type() const;
    QDateTime startDate() const;
    QDateTime endDate() const;
    int completion() const;
    bool readOnly() const;
    QModelIndex depends() const;
    QString legend() const;

private slots:
    void updateEndDate( const QDateTime& startDate );
    void disableEditing( bool disable );
    void typeChanged( int index );
    
private:
    void init();
    void addDependItem( const QAbstractItemModel* model, const QModelIndex& index, int indent = 0 );
    
    QList<QPersistentModelIndex> indexList;
    const QAbstractItemModel* model;
    Ui::EntryDialog* ui;
};

#endif /* ENTRYDIALOG_H */
