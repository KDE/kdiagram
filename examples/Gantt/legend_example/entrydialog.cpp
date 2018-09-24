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

#include "entrydialog.h"

#include "ui_entrydialog.h"

#include <KGanttConstraintModel>
#include <KGanttGlobal>
#include <QAbstractItemModel>
#include <QDateTime>
#include <QPersistentModelIndex>

Q_DECLARE_METATYPE( QPersistentModelIndex )

EntryDialog::EntryDialog( const QAbstractItemModel* model, QWidget* parent, Qt::WindowFlags f )
    : QDialog( parent, f ),
      indexList( QList<QPersistentModelIndex>() ),
      ui( new Ui::EntryDialog )
{
    ui->setupUi( this );
    this->model = model;
    init();
}

void EntryDialog::init()
{
    ui->type->addItem( tr( "Event" ), KGantt::TypeEvent );
    ui->type->addItem( tr( "Task" ), KGantt::TypeTask );
    ui->type->addItem( tr( "Summary" ), KGantt::TypeSummary );
    ui->type->addItem( tr( "Multi" ), KGantt::TypeMulti );
    
    for (int row = 0; row < model->rowCount(); ++row )
        addDependItem( model, model->index( row, 0 ) );
    
    connect( ui->startDate, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(updateEndDate(QDateTime)) );
    connect( ui->readOnly, SIGNAL(toggled(bool)), this, SLOT(disableEditing(bool)) );
    connect( ui->type, SIGNAL(currentIndexChanged(int)), this, SLOT(typeChanged(int)) );
    
    ui->startDate->setDateTime( QDateTime::currentDateTime() );
    typeChanged( 0 );
}

void EntryDialog::initFrom( const QModelIndex & index, const KGantt::ConstraintModel* constraintModel )
{
    int row = index.row();
    const QModelIndex parent = index.parent();
    
    ui->name->setText( model->data( model->index( row, 0, parent ) ).toString() );
    ui->legend->setText( model->data( model->index( row, 5, parent ) ).toString() );
    int idx = ui->type->findData( model->data( model->index( row, 1, parent ) ).toInt() );
    ui->type->setCurrentIndex( idx );
    ui->startDate->setDateTime( model->data( model->index( row, 2, parent ), KGantt::StartTimeRole ).toDateTime() );
    ui->endDate->setDateTime( model->data( model->index( row, 3, parent ), KGantt::EndTimeRole ).toDateTime() );
    ui->completion->setValue( model->data( model->index( row, 4, parent ) ).toInt() );
    ui->readOnly->setChecked( !(model->flags( model->index( row, 0, parent ) ) & Qt::ItemIsEditable) );
    
    QList<KGantt::Constraint> constraints = constraintModel->constraintsForIndex( model->index( row, 0, parent ) );
    if ( constraints.isEmpty() )
        return;
    
    QModelIndex constraintIndex;
    for ( int i = 0; i < constraints.size(); ++i ) {
        KGantt::Constraint constraint = constraints[i];
        if ( constraint.endIndex() == index ) {
            constraintIndex = constraint.startIndex();
            break;
        }
    }
    
    if ( !constraintIndex.isValid() )
        return;
    
    ui->depends->setCurrentIndex( indexList.indexOf( constraintIndex ) + 1 );
}

void EntryDialog::addDependItem( const QAbstractItemModel* model, const QModelIndex & index, int indent)
{
    indexList << QPersistentModelIndex( index );
    QString str = QString( "%1%2" ).arg( QString().fill( ' ', indent ) ).arg( model->data( index ).toString() );
    ui->depends->addItem( str );
    
    for (int row = 0; row < model->rowCount( index ); ++row )
        addDependItem( model, model->index( row, 0, index ), indent + 2 );
}

QString EntryDialog::name() const
{
    return ui->name->text();
}

int EntryDialog::type() const
{
    return ui->type->itemData( ui->type->currentIndex() ).toInt();
}

QDateTime EntryDialog::startDate() const
{
    return ui->startDate->dateTime();
}

QDateTime EntryDialog::endDate() const
{
    return ui->endDate->dateTime();
}

int EntryDialog::completion() const
{
    return ui->completion->value();
}

void EntryDialog::updateEndDate(const QDateTime & startDate)
{
    ui->endDate->setMinimumDate( startDate.date() );
    ui->endDate->setMinimumTime( startDate.time() );
}

bool EntryDialog::readOnly() const
{
    return ui->readOnly->isChecked();
}

QModelIndex EntryDialog::depends() const
{
    if ( ui->depends->currentIndex() == 0 )
        return QModelIndex();

    QPersistentModelIndex index = indexList[ ui->depends->currentIndex() - 1 ];
    if ( index.isValid() )
        return index;
    
    return QModelIndex();
}

QString EntryDialog::legend() const
{
    return ui->legend->text();
}

void EntryDialog::disableEditing(bool disable)
{
    ui->name->setEnabled( !disable );
    ui->type->setEnabled( !disable );
    ui->completion->setEnabled( !disable );
    ui->startDate->setEnabled( !disable );
    ui->endDate->setEnabled( !disable );
    ui->depends->setEnabled( !disable );
}

void EntryDialog::typeChanged(int index)
{
    if ( ! index ) {
        ui->label_EndDate->hide();
        ui->endDate->hide();
    } else {
        ui->label_EndDate->show();
        ui->endDate->show();
    }
}
