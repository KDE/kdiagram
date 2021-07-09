/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
    EntryDialog( const QAbstractItemModel* model, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags() );
    void initFrom( const QModelIndex& index, const KGantt::ConstraintModel* constraintModel );
    
    QString name() const;
    int type() const;
    QDateTime startDate() const;
    QDateTime endDate() const;
    int completion() const;
    bool readOnly() const;
    QModelIndex depends() const;
    QString legend() const;

private Q_SLOTS:
    void updateEndDate( const QDateTime& startDate );
    void disableEditing( bool disable );
    
private:
    void init();
    void addDependItem( const QAbstractItemModel* model, const QModelIndex& index, int indent = 0 );
    
    QList<QPersistentModelIndex> indexList;
    const QAbstractItemModel* model;
    Ui::EntryDialog* ui;
};

#endif /* ENTRYDIALOG_H */
