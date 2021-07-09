/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "entrydelegate.h"

#include "entrydialog.h"

#include <KGanttConstraintModel>
#include <KGanttGlobal>
#include <QEvent>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QPointer>

EntryDelegate::EntryDelegate( KGantt::ConstraintModel* constraintModel, QObject* parent )
    : QItemDelegate( parent )
{
    this->constraintModel = constraintModel;
}

bool EntryDelegate::editorEvent( QEvent* event, QAbstractItemModel *model, const QStyleOptionViewItem& option, const QModelIndex& index )
{
    if ( event->type() != QEvent::MouseButtonDblClick )
        return false;

    if ( !index.isValid() )
        return QItemDelegate::editorEvent( event, model, option, index );

    QPointer<EntryDialog> dialog = new EntryDialog( model );
    dialog->initFrom( index, constraintModel );
    dialog->setWindowTitle( tr( "Edit Entry" ) );
    dialog->exec();  
    if ( !dialog )
        return false;
    
    int row = index.row();
    const QModelIndex parent = index.parent();
    model->setData( model->index( row, 0, parent ), dialog->name() );
    model->setData( model->index( row, 1, parent ), dialog->type() );
    if ( dialog->type() != KGantt::TypeSummary ) {
        model->setData( model->index( row, 2, parent ), dialog->startDate(), KGantt::StartTimeRole );
        model->setData( model->index( row, 3, parent ), dialog->endDate(), KGantt::EndTimeRole );
    }
    model->setData( model->index( row, 4, parent ), dialog->completion() );
    model->setData( model->index( row, 5, parent ), dialog->legend() );
    
    addConstraint( dialog->depends(), model->index( row, 0, parent ) );
    setReadOnly( model->index( row, 0, parent ), dialog->readOnly() );

    delete dialog;
    return true;
}

void EntryDelegate::setReadOnly(const QModelIndex & index, bool readOnly)
{
    int row = index.row();
    QModelIndex parent = index.parent();
    QStandardItem* item;
    const QStandardItemModel* model = qobject_cast<const QStandardItemModel*>( index.model() );
    if ( !model )
        return;
    
    item = model->itemFromIndex( model->index( row, 0, parent ) );
    item->setFlags( readOnly ? item->flags() & ~Qt::ItemIsEditable : item->flags() | Qt::ItemIsEditable );
    
    item = model->itemFromIndex( model->index( row, 1, parent ) );
    item->setFlags( readOnly ? item->flags() & ~Qt::ItemIsEditable : item->flags() | Qt::ItemIsEditable );
    
    item = model->itemFromIndex( model->index( row, 2, parent ) );
    item->setFlags( readOnly ? item->flags() & ~Qt::ItemIsEditable : item->flags() | Qt::ItemIsEditable );
    
    item = model->itemFromIndex( model->index( row, 3, parent ) );
    item->setFlags( readOnly ? item->flags() & ~Qt::ItemIsEditable : item->flags() | Qt::ItemIsEditable );
    
    item = model->itemFromIndex( model->index( row, 4, parent ) );
    item->setFlags( readOnly ? item->flags() & ~Qt::ItemIsEditable : item->flags() | Qt::ItemIsEditable );
}

void EntryDelegate::addConstraint(const QModelIndex & index1, const QModelIndex & index2)
{
    if ( !index1.isValid() || !index2.isValid() )
        return;

    KGantt::Constraint c( index1, index2 );
    constraintModel->addConstraint( c );
}
