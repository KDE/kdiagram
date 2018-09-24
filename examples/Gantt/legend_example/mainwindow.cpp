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

#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "entrydelegate.h"
#include "entrydialog.h"

#include <algorithm>

#include <KGanttConstraintModel>
#include <KGanttDateTimeGrid>
#include <KGanttGraphicsView>
#include <KGanttLegend>
#include <QAbstractItemView>
#include <QDebug>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QTreeView>
#include <QCloseEvent>
#include <QPointer>
#include <QScrollBar>

class MyStandardItem : public QStandardItem {
public:
  MyStandardItem( const QVariant& v ) : QStandardItem()
  {
    setData( v, Qt::DisplayRole );
  }
  MyStandardItem( const QString& v ) : QStandardItem()
  {
    setData( v, Qt::DisplayRole );
  }
};

MainWindow::MainWindow( QWidget* parent, Qt::WindowFlags flags )
    : QMainWindow( parent, flags ),
      smallLegend( 0 ),
      detailedLegend( 0 ),
      ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    initModel();
    initActions();
    initItemDelegate();
    initGrid();

    QTreeView* leftView = qobject_cast<QTreeView*>( ui->ganttView->leftView() );
    Q_ASSERT( leftView );
    leftView->setColumnHidden( 1, true );
    leftView->setColumnHidden( 2, true );
    leftView->setColumnHidden( 3, true );
    leftView->setColumnHidden( 4, true );
    leftView->setColumnHidden( 5, true );
    leftView->header()->setStretchLastSection( true );

    connect( ui->ganttView->leftView(), SIGNAL(customContextMenuRequested(QPoint)),
             this, SLOT(showContextMenu(QPoint)) );
    connect( ui->ganttView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
             this, SLOT(enableActions(QItemSelection)) );
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    delete smallLegend;
    delete detailedLegend;
    event->accept();
}

void MainWindow::initModel()
{
    model = new QStandardItemModel( 0, 6, this );
    model->setHeaderData( 0, Qt::Horizontal, tr( "Tree View of Entries" ) );
    ui->ganttView->setModel( model );

    QStandardItemModel* lmodel = new QStandardItemModel;
    lmodel->appendRow( QList<QStandardItem*>()
        << new MyStandardItem( QVariant() )
        << new MyStandardItem( KGantt::TypeEvent )
        << new MyStandardItem( QVariant() )
        << new MyStandardItem( QVariant() )
        << new MyStandardItem( QVariant() )
        << new MyStandardItem( QString::fromLatin1("Event") ) );
    lmodel->appendRow( QList<QStandardItem*>()
        << new MyStandardItem( QVariant() )
        << new MyStandardItem( KGantt::TypeTask )
        << new MyStandardItem( QVariant() )
        << new MyStandardItem( QVariant() )
        << new MyStandardItem( QVariant() )
        << new MyStandardItem( QString::fromLatin1("Task") ) );
    lmodel->appendRow( QList<QStandardItem*>()
        << new MyStandardItem( QVariant() )
        << new MyStandardItem( KGantt::TypeSummary )
        << new MyStandardItem( QVariant() )
        << new MyStandardItem( QVariant() )
        << new MyStandardItem( QVariant() )
        << new MyStandardItem( QString::fromLatin1("Summary") ) );

    smallLegend = new KGantt::Legend();
    smallLegend->setWindowTitle( tr( "Legend" ) );
    smallLegend->show();
    smallLegend->setModel( lmodel );

    detailedLegend = new KGantt::Legend();
    detailedLegend->setWindowTitle( tr( "List" ) );
    detailedLegend->show();
    detailedLegend->setModel( model );

    constraintModel = new KGantt::ConstraintModel( this );
    ui->ganttView->setConstraintModel( constraintModel );
}

void MainWindow::initActions()
{
    newEntryAction = new QAction( tr( "New entry" ), this );
    newEntryAction->setShortcut( QKeySequence::New );
    connect( newEntryAction, SIGNAL(triggered()), this, SLOT(addNewEntry()) );

    removeEntryAction = new QAction( tr( "Remove entry" ), this );
    removeEntryAction->setShortcut( QKeySequence::Delete );
    connect( removeEntryAction, SIGNAL(triggered()), this, SLOT(removeEntry()) );

    zoomInAction = new QAction( tr( "Zoom In" ), this );
    zoomInAction->setShortcut( QKeySequence::ZoomIn );
    connect( zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()) );

    zoomOutAction = new QAction( tr( "Zoom Out" ), this );
    zoomOutAction->setShortcut( QKeySequence::ZoomOut );
    connect( zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()) );

    zoomFitAction = new QAction( tr( "Zoom to Fit" ), this );
    connect( zoomFitAction, SIGNAL(triggered()), this, SLOT(zoomFit()) );

    ui->ganttView->leftView()->setContextMenuPolicy( Qt::CustomContextMenu );
    ui->ganttView->leftView()->addAction( newEntryAction );
    ui->ganttView->leftView()->addAction( removeEntryAction );

    QMenu* entryMenu = menuBar()->addMenu( tr( "Entry" ) );
    entryMenu->addAction( newEntryAction );
    entryMenu->addAction( removeEntryAction );

    QMenu* zoomMenu = menuBar()->addMenu( tr( "Zoom" ) );
    zoomMenu->addAction( zoomInAction );
    zoomMenu->addAction( zoomOutAction );
    zoomMenu->addAction( zoomFitAction );
    
    QMenu* scaleMenu = menuBar()->addMenu( tr( "Scale" ) );
    
    scaleMenu->addAction( tr( "Auto" ), this, SLOT(scaleAuto()) );
    scaleMenu->addAction( tr( "Hour" ), this, SLOT(scaleHour()) );
    scaleMenu->addAction( tr( "Day" ), this, SLOT(scaleDay()) );
    scaleMenu->addAction( tr( "Week" ), this, SLOT(scaleWeek()) );
    scaleMenu->addAction( tr( "Month" ), this, SLOT(scaleMonth()) );

    enableActions( QItemSelection() );
}

void MainWindow::initItemDelegate()
{
    EntryDelegate* delegate = new EntryDelegate( constraintModel, this );
    ui->ganttView->leftView()->setItemDelegate( delegate );
}

void MainWindow::initGrid()
{
    grid = new KGantt::DateTimeGrid();
    grid->setDayWidth( 70 );
    ui->ganttView->setGrid( grid );
}

void MainWindow::showContextMenu( const QPoint& pos )
{
    if ( !ui->ganttView->leftView()->indexAt( pos ).isValid() )
        ui->ganttView->selectionModel()->clearSelection();

    QMenu menu( ui->ganttView->leftView() );
    menu.addAction( newEntryAction );
    menu.addAction( removeEntryAction );
    menu.exec( ui->ganttView->leftView()->viewport()->mapToGlobal( pos ) );
}

void MainWindow::enableActions(const QItemSelection & selected)
{
    if ( selected.indexes().isEmpty() ) {
        newEntryAction->setEnabled( true );
        removeEntryAction->setEnabled( false );
        return;
    }

    QModelIndex selectedIndex = selected.indexes()[0];

    if ( model->data( model->index( selectedIndex.row(), 1 ) ) == KGantt::TypeEvent ||
        model->data( model->index( selectedIndex.row(), 1 ) ) == KGantt::TypeTask ) {
        newEntryAction->setEnabled( false );
        removeEntryAction->setEnabled( true );
        return;
    }

    newEntryAction->setEnabled( true );
    removeEntryAction->setEnabled( true );
}

void MainWindow::addNewEntry()
{
    QPointer<EntryDialog> dialog = new EntryDialog( model );
    dialog->setWindowTitle( tr( "New Entry") );
    if ( dialog->exec() == QDialog::Rejected || !dialog ) {
        delete dialog;
        return;
    }

    QModelIndexList selectedIndexes = ui->ganttView->selectionModel()->selectedIndexes();
    const QModelIndex parent = selectedIndexes.value( 0 );

    if ( !model->insertRow( model->rowCount( parent ), parent ) )
        return;

    int row = model->rowCount( parent ) - 1;
    if ( row == 0 && parent.isValid() )
        model->insertColumns( model->columnCount( parent ), 5, parent );

    model->setData( model->index( row, 0, parent ), dialog->name() );
    model->setData( model->index( row, 1, parent ), dialog->type() );
    if ( dialog->type() != KGantt::TypeSummary ) {
        model->setData( model->index( row, 2, parent ), dialog->startDate(), KGantt::StartTimeRole );
        model->setData( model->index( row, 3, parent ), dialog->endDate(), KGantt::EndTimeRole );
    }
    model->setData( model->index( row, 4, parent ), dialog->completion() );
    const QString legend( dialog->legend() );
    if ( ! legend.isEmpty() )
        model->setData( model->index( row, 5, parent ), legend );

    addConstraint( dialog->depends(), model->index( row, 0, parent ) );
    setReadOnly( model->index( row, 0, parent ), dialog->readOnly() );

    delete dialog;
}

void MainWindow::setReadOnly(const QModelIndex & index, bool readOnly)
{
    int row = index.row();
    const QModelIndex parent = index.parent();
    QStandardItem* item;

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

void MainWindow::addConstraint(const QModelIndex & index1, const QModelIndex & index2)
{
    if ( !index1.isValid() || !index2.isValid() )
        return;

    KGantt::Constraint c( index1, index2 );
    ui->ganttView->constraintModel()->addConstraint( c );
}

void MainWindow::removeEntry()
{
    QModelIndexList selectedIndexes = ui->ganttView->selectionModel()->selectedIndexes();
    QModelIndex index = selectedIndexes.value( 0 );

    if ( !index.isValid() )
        return;

    model->removeRow( index.row(), index.parent() );
}

void MainWindow::zoomIn()
{
    qreal dayWidth = grid->dayWidth() + 10;
    if ( dayWidth > 400 )
        grid->setScale( KGantt::DateTimeGrid::ScaleHour );

    grid->setDayWidth( dayWidth );
}

void MainWindow::zoomOut()
{
    qreal dayWidth = grid->dayWidth() - 10;
    if ( dayWidth < 10 )
        dayWidth = 10;

    if ( dayWidth <= 400 )
        grid->setScale( KGantt::DateTimeGrid::ScaleDay );

    grid->setDayWidth( dayWidth );
}

void MainWindow::zoomFit()
{
    QModelIndexList selectedIndexes = ui->ganttView->selectionModel()->selectedIndexes();

    if ( selectedIndexes.isEmpty() ) {
        return;
    }

    KGantt::Span span;
    Q_FOREACH( QModelIndex idx, selectedIndexes ) {
        const KGantt::Span s = grid->mapToChart( grid->model()->index( idx.row(), 0 ) );
        if ( span.isValid() ) {
            span = span.expandedTo( s );
        } else {
            span = s;
        }
    }

    span.setLength( span.length()+20 );
    span.setStart( span.start()-10 );

    qDebug() << selectedIndexes << span;

    const qreal view_width = ui->ganttView->graphicsView()->viewport()->width();
    const QDateTime start = grid->mapFromChart( span.start() ).value<QDateTime>();
    const QDateTime end = grid->mapFromChart( span.end() ).value<QDateTime>();

    qreal delta = start.date().daysTo(end.date());
    delta += start.time().msecsTo(end.time())/( 1000.*24.*60.*60. );

    qDebug() << view_width << "/" << delta;
    grid->setDayWidth( view_width/( std::max( 1., delta ) ) );
    qDebug() << "daywidth set to" << grid->dayWidth();
    qDebug() << "start scroll to" << grid->mapToChart( start );
    ui->ganttView->graphicsView()->horizontalScrollBar()->setValue( grid->mapToChart( start ) );
}

void MainWindow::scaleAuto()
{
    KGantt::DateTimeGrid* grid = static_cast<KGantt::DateTimeGrid*>(ui->ganttView->grid());
    grid->setScale( KGantt::DateTimeGrid::ScaleAuto );
}

void MainWindow::scaleHour()
{
    KGantt::DateTimeGrid* grid = static_cast<KGantt::DateTimeGrid*>(ui->ganttView->grid());
    grid->setScale( KGantt::DateTimeGrid::ScaleHour );
}

void MainWindow::scaleDay()
{
    KGantt::DateTimeGrid* grid = static_cast<KGantt::DateTimeGrid*>(ui->ganttView->grid());
    grid->setScale( KGantt::DateTimeGrid::ScaleDay );
}

void MainWindow::scaleWeek()
{
    KGantt::DateTimeGrid* grid = static_cast<KGantt::DateTimeGrid*>(ui->ganttView->grid());
    grid->setScale( KGantt::DateTimeGrid::ScaleWeek );
}

void MainWindow::scaleMonth()
{
    KGantt::DateTimeGrid* grid = static_cast<KGantt::DateTimeGrid*>(ui->ganttView->grid());
    grid->setScale( KGantt::DateTimeGrid::ScaleMonth );
}
    
