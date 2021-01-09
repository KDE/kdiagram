/*
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "kganttgraphicsscene.h"
#include "kganttgraphicsscene_p.h"
#include "kganttgraphicsitem.h"
#include "kganttconstraint.h"
#include "kganttconstraintgraphicsitem.h"
#include "kganttitemdelegate.h"
#include "kganttabstractrowcontroller.h"
#include "kganttabstractgrid.h"
#include "kganttdatetimegrid.h"
#include "kganttsummaryhandlingproxymodel.h"
#include "kganttgraphicsview.h"
#include "kganttprintingcontext.h"

#include <QApplication>
#include <QGraphicsSceneHelpEvent>
#include <QPainter>
#include <QPrinter>
#include <QTextDocument>
#include <QToolTip>
#include <QSet>

#include <QDebug>

#include <functional>
#include <algorithm>
#include <cassert>

// defines HAVE_PRINTER if support for printing should be included
#ifdef _WIN32_WCE
    // There is no printer support under wince even if QT_NO_PRINTER is not set
#else
#ifndef QT_NO_PRINTER
    #define HAVE_PRINTER
#endif
#endif



using namespace KGantt;

GraphicsScene::Private::Private( GraphicsScene* _q )
    : q( _q ),
      dragSource( nullptr ),
      itemDelegate( new ItemDelegate( _q ) ),
      rowController( nullptr ),
      readOnly( false ),
      isPrinting( false ),
      drawColumnLabels( true ),
      labelsWidth( 0.0 ),
      summaryHandlingModel( new SummaryHandlingProxyModel( _q ) ),
      selectionModel( nullptr )
{
    default_grid.setStartDateTime( QDateTime::currentDateTime().addDays( -1 ) );
}

GraphicsScene::Private::~Private()
{
    delete grid;
}

void GraphicsScene::Private::clearConstraintItems()
{
    for(ConstraintGraphicsItem *citem : constraintItems) {
        // remove constraint from items first
        for(GraphicsItem *item : items) {
            item->removeStartConstraint(citem);
            item->removeEndConstraint(citem);
        }
        q->removeItem(citem);
        delete citem;
    }
    constraintItems.clear();
}

void GraphicsScene::Private::resetConstraintItems()
{
    clearConstraintItems();
    if ( constraintModel.isNull() ) return;
    const QList<Constraint> clst = constraintModel->constraints();
    for ( const Constraint& c : clst ) {
        createConstraintItem( c );
    }
    q->updateItems();
}

void GraphicsScene::Private::createConstraintItem( const Constraint& c )
{
    GraphicsItem* sitem = q->findItem( summaryHandlingModel->mapFromSource( c.startIndex() ) );
    GraphicsItem* eitem = q->findItem( summaryHandlingModel->mapFromSource( c.endIndex() ) );

    if ( sitem && eitem ) {
        ConstraintGraphicsItem* citem = new ConstraintGraphicsItem( c );
        sitem->addStartConstraint( citem );
        eitem->addEndConstraint( citem );
        constraintItems.append( citem );
        q->addItem( citem );
    }

    //q->insertConstraintItem( c, citem );
}

// Delete the constraint item, and clean up pointers in the start- and end item
void GraphicsScene::Private::deleteConstraintItem( ConstraintGraphicsItem *citem )
{
    //qDebug()<<"GraphicsScene::Private::deleteConstraintItem citem="<<citem;
    if ( citem == nullptr ) {
        return;
    }
    Constraint c = citem->constraint();
    GraphicsItem* item = items.value( summaryHandlingModel->mapFromSource( c.startIndex() ), nullptr );
    if ( item ) {
        item->removeStartConstraint( citem );
    }
    item = items.value( summaryHandlingModel->mapFromSource( c.endIndex() ), nullptr );
    if ( item ) {
        item->removeEndConstraint( citem );
    }
    constraintItems.removeAt(constraintItems.indexOf(citem));
    delete citem;
}

void GraphicsScene::Private::deleteConstraintItem( const Constraint& c )
{
    deleteConstraintItem( findConstraintItem( c ) );
}

ConstraintGraphicsItem* GraphicsScene::Private::findConstraintItem( const Constraint& c ) const
{
    GraphicsItem* item = items.value( summaryHandlingModel->mapFromSource( c.startIndex() ), nullptr );
    if ( item ) {
        const QList<ConstraintGraphicsItem*> clst = item->startConstraints();
        QList<ConstraintGraphicsItem*>::const_iterator it = clst.begin();
        for ( ; it != clst.end() ; ++it ) {
            if ( c.compareIndexes((*it)->constraint()) )
                break;
        }
        if ( it != clst.end() ) {
            return *it;
        }
    }
    item = items.value( summaryHandlingModel->mapFromSource( c.endIndex() ), nullptr );
    if ( item ) {
        const QList<ConstraintGraphicsItem*> clst = item->endConstraints();
        QList<ConstraintGraphicsItem*>::const_iterator it = clst.begin();
        for ( ; it != clst.end() ; ++it ) {
            if ( c.compareIndexes( (*it)->constraint() ) )
                break;
        }
        if ( it != clst.end() ) {
            return *it;
        }
    }
    return nullptr;
}

// NOTE: we might get here after indexes are invalidated, so cannot do any controlled cleanup
void GraphicsScene::Private::clearItems()
{
    for(GraphicsItem *item : items) {
        q->removeItem(item);
        delete item;
    }
    items.clear();
    // do last to avoid cleaning up items
    clearConstraintItems();
}

AbstractGrid *GraphicsScene::Private::getGrid()
{
    if (grid.isNull()) {
        return static_cast<AbstractGrid*>(&default_grid);
    }
    return grid.data();
}

const AbstractGrid *GraphicsScene::Private::getGrid() const
{
    if (grid.isNull()) {
        return static_cast<const AbstractGrid*>(&default_grid);
    }
    return grid.data();
}

GraphicsScene::GraphicsScene( QObject* parent )
    : QGraphicsScene( parent ), _d( new Private( this ) )
{
    init();
}

GraphicsScene::~GraphicsScene()
{
    qDeleteAll( items() );
    delete _d;
}

#define d d_func()

void GraphicsScene::init()
{
    setItemIndexMethod( QGraphicsScene::NoIndex );
    setConstraintModel( new ConstraintModel( this ) );
    connect( d->getGrid(), SIGNAL(gridChanged()), this, SLOT(slotGridChanged()) );
}

/* NOTE: The delegate should really be a property
 * of the view, but that doesn't really fit at
 * this time
 */
void GraphicsScene::setItemDelegate( ItemDelegate* delegate )
{
    if ( !d->itemDelegate.isNull() && d->itemDelegate->parent()==this ) delete d->itemDelegate;
    d->itemDelegate = delegate;
    update();
}

ItemDelegate* GraphicsScene::itemDelegate() const
{
    return d->itemDelegate;
}

QAbstractItemModel* GraphicsScene::model() const
{
    assert(!d->summaryHandlingModel.isNull());
    return d->summaryHandlingModel->sourceModel();
}

void GraphicsScene::setModel( QAbstractItemModel* model )
{
    assert(!d->summaryHandlingModel.isNull());
    d->summaryHandlingModel->setSourceModel(model);
    d->getGrid()->setModel( d->summaryHandlingModel );
    setSelectionModel( new QItemSelectionModel( model, this ) );
}

QAbstractProxyModel* GraphicsScene::summaryHandlingModel() const
{
    return d->summaryHandlingModel;
}

void GraphicsScene::setSummaryHandlingModel( QAbstractProxyModel* proxyModel )
{
    proxyModel->setSourceModel( model() );
    d->summaryHandlingModel = proxyModel;
}

void GraphicsScene::setRootIndex( const QModelIndex& idx )
{
    d->getGrid()->setRootIndex( idx );
}

QModelIndex GraphicsScene::rootIndex() const
{
    return d->getGrid()->rootIndex();
}

ConstraintModel* GraphicsScene::constraintModel() const
{
    return d->constraintModel;
}

void GraphicsScene::setConstraintModel( ConstraintModel* cm )
{
    if ( !d->constraintModel.isNull() ) {
        d->constraintModel->disconnect( this );
        d->clearConstraintItems();
    }
    d->constraintModel = cm;

    connect( cm, SIGNAL(constraintAdded(KGantt::Constraint)),
             this, SLOT(slotConstraintAdded(KGantt::Constraint)) );
    connect( cm, SIGNAL(constraintRemoved(KGantt::Constraint)),
             this, SLOT(slotConstraintRemoved(KGantt::Constraint)) );
    d->resetConstraintItems();
}

void GraphicsScene::setSelectionModel( QItemSelectionModel* smodel )
{
    if (d->selectionModel) {
        d->selectionModel->disconnect( this );
    }
    d->selectionModel = smodel;
    if (smodel) {
        connect(d->selectionModel, SIGNAL(modelChanged(QAbstractItemModel*)),
                this, SLOT(selectionModelChanged(QAbstractItemModel*)));
        connect( smodel, SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
                 this, SLOT(slotSelectionChanged(const QItemSelection&,const QItemSelection&)) );
    }
}

QItemSelectionModel* GraphicsScene::selectionModel() const
{
    return d->selectionModel;
}

void GraphicsScene::setRowController( AbstractRowController* rc )
{
    d->rowController = rc;
}

AbstractRowController* GraphicsScene::rowController() const
{
    return d->rowController;
}

AbstractGrid *GraphicsScene::takeGrid()
{
    AbstractGrid *grid = d->grid;
    grid->disconnect( this );
    d->grid = nullptr;
    if (grid) {
        // revert to the default_grid
        connect( &d->default_grid, SIGNAL(gridChanged()), this, SLOT(slotGridChanged()) );
    }
    return grid;
}

void GraphicsScene::setGrid( AbstractGrid* grid )
{
    QAbstractItemModel* model = nullptr;
    if ( d->getGrid() ) {
        d->getGrid()->disconnect( this );
        model = d->getGrid()->model();
    }
    delete d->grid;
    d->grid = grid;
    connect( d->getGrid(), SIGNAL(gridChanged()), this, SLOT(slotGridChanged()) );
    d->getGrid()->setModel( model );
    slotGridChanged();
}

// Returns the explicitly set grid
AbstractGrid* GraphicsScene::grid() const
{
    return d->grid;
}

// May also return the default_grid if a grid has not been set
const AbstractGrid *GraphicsScene::getGrid() const
{
    return d->getGrid();
}

void GraphicsScene::setReadOnly( bool ro )
{
    d->readOnly = ro;
}

bool GraphicsScene::isReadOnly() const
{
    return d->readOnly;
}

/* Returns the index with column=0 fromt the
 * same row as idx and with the same parent.
 * This is used to traverse the tree-structure
 * of the model
 */
QModelIndex GraphicsScene::mainIndex( const QModelIndex& idx )
{
#if 0
    if ( idx.isValid() ) {
        return idx.model()->index( idx.row(), 0,idx.parent() );
    } else {
        return QModelIndex();
    }
#else
    return idx;
#endif
}


QModelIndex GraphicsScene::dataIndex( const QModelIndex& idx )
{
#if 0
    if ( idx.isValid() ) {
        const QAbstractItemModel* model = idx.model();
        return model->index( idx.row(), model->columnCount( idx.parent() )-1,idx.parent() );
    } else {
        return QModelIndex();
    }
#else
    return idx;
#endif
}


GraphicsItem* GraphicsScene::createItem( ItemType type ) const
{
#if 0
    TODO For 3.0
    assert(views().count() == 1);
    GraphicsView *v = qobject_cast<GraphicsView*>(views().first());
    assert(v);
    return v->createItem(type);
#else
    Q_UNUSED(type)
    return new GraphicsItem;
#endif
}

void GraphicsScene::Private::recursiveUpdateMultiItem( const Span& span, const QModelIndex& idx )
{
    //qDebug() << "recursiveUpdateMultiItem("<<span<<idx<<")";
    GraphicsItem* item = q->findItem( idx );
    const int itemtype = summaryHandlingModel->data( idx, ItemTypeRole ).toInt();
    if (!item) {
        item = q->createItem( static_cast<ItemType>( itemtype ) );
        item->setIndex( idx );
        q->insertItem( idx, item);
    }
    item->updateItem( span, idx );
    QModelIndex child;
    int cr = 0;
    while ( ( child = summaryHandlingModel->index( cr, 0, idx ) ).isValid() ) {
        recursiveUpdateMultiItem( span, child );
        ++cr;
    }
}

void GraphicsScene::updateRow( const QModelIndex& rowidx )
{
    //qDebug() << "GraphicsScene::updateRow("<<rowidx<<")" << rowidx.data( Qt::DisplayRole );
    if ( !rowidx.isValid() ) return;
#if !defined(NDEBUG)
    const QAbstractItemModel* model = rowidx.model(); // why const?
#endif
    assert( model );
    assert( rowController() );
    assert( model == summaryHandlingModel() );

    const QModelIndex sidx = summaryHandlingModel()->mapToSource( rowidx );
    Span rg = rowController()->rowGeometry( sidx );
    for ( QModelIndex treewalkidx = sidx; treewalkidx.isValid(); treewalkidx = treewalkidx.parent() ) {
        if ( treewalkidx.data( ItemTypeRole ).toInt() == TypeMulti
             && !rowController()->isRowExpanded( treewalkidx )) {
            rg = rowController()->rowGeometry( treewalkidx );
        }
    }

    bool blocked = blockSignals( true );
    for ( int col = 0; col < summaryHandlingModel()->columnCount( rowidx.parent() ); ++col ) {
        const QModelIndex idx = summaryHandlingModel()->index( rowidx.row(), col, rowidx.parent() );
        const QModelIndex sidx = summaryHandlingModel()->mapToSource( idx );
        const int itemtype = summaryHandlingModel()->data( idx, ItemTypeRole ).toInt();
        const bool isExpanded = rowController()->isRowExpanded( sidx );
        if ( itemtype == TypeNone ) {
            removeItem( idx );
            continue;
        }
        if ( itemtype == TypeMulti && !isExpanded ) {
            d->recursiveUpdateMultiItem( rg, idx );
        } else {
            if ( summaryHandlingModel()->data( rowidx.parent(), ItemTypeRole ).toInt() == TypeMulti && !isExpanded ) {
                //continue;
            }

            GraphicsItem* item = findItem( idx );
            if (!item) {
                item = createItem( static_cast<ItemType>( itemtype ) );
                item->setIndex( idx );
                insertItem(idx, item);
            }
            const Span span = rowController()->rowGeometry( sidx );
            item->updateItem( span, idx );
        }
    }
    blockSignals( blocked );
}

void GraphicsScene::insertItem( const QPersistentModelIndex& idx, GraphicsItem* item )
{
    if ( !d->constraintModel.isNull() ) {
        // Create items for constraints
        const QModelIndex sidx = summaryHandlingModel()->mapToSource( idx );
        const QList<Constraint> clst = d->constraintModel->constraintsForIndex( sidx );
        for ( const Constraint& c :  clst ) {
            QModelIndex other_idx;
            if ( c.startIndex() == sidx ) {
                other_idx = c.endIndex();
                GraphicsItem* other_item = d->items.value(summaryHandlingModel()->mapFromSource( other_idx ),nullptr);
                if ( !other_item ) continue;
                ConstraintGraphicsItem* citem = new ConstraintGraphicsItem( c );
                item->addStartConstraint( citem );
                other_item->addEndConstraint( citem );
                d->constraintItems.append( citem );
                addItem( citem );
            } else if ( c.endIndex() == sidx ) {
                other_idx = c.startIndex();
                GraphicsItem* other_item = d->items.value(summaryHandlingModel()->mapFromSource( other_idx ),nullptr);
                if ( !other_item ) continue;
                ConstraintGraphicsItem* citem = new ConstraintGraphicsItem( c );
                other_item->addStartConstraint( citem );
                item->addEndConstraint( citem );
                d->constraintItems.append( citem );
                addItem( citem );
            } else {
                assert( 0 ); // Impossible
            }
        }
    }
    d->items.insert( idx, item );
    addItem( item );
}

void GraphicsScene::removeItem( const QModelIndex& idx )
{
    //qDebug() << "GraphicsScene::removeItem("<<idx<<")";
    QHash<QPersistentModelIndex,GraphicsItem*>::iterator it = d->items.find( idx );
    if ( it != d->items.end() ) {
        GraphicsItem* item = *it;
        assert( item );
        // We have to remove the item from the list first because
        // there is a good chance there will be reentrant calls
        d->items.erase( it );
        {
            // Remove any constraintitems attached
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
            // TODO remove when we depend on 5.14+
            const QSet<ConstraintGraphicsItem*> clst = QSet<ConstraintGraphicsItem*>::fromList( item->startConstraints() ) +
                                                       QSet<ConstraintGraphicsItem*>::fromList( item->endConstraints() );
#else
            const QList<ConstraintGraphicsItem*> lst1 = item->startConstraints();
            const QList<ConstraintGraphicsItem*> lst2 = item->endConstraints();
            const QSet<ConstraintGraphicsItem*> clst = QSet<ConstraintGraphicsItem*>( lst1.begin(), lst1.end() ) +
                                                       QSet<ConstraintGraphicsItem*>( lst2.begin(), lst2.end() );
#endif
            for ( ConstraintGraphicsItem* citem : clst ) {
                d->deleteConstraintItem( citem );
            }
        }
        // Get rid of the item
        delete item;
    }
}

GraphicsItem* GraphicsScene::findItem( const QModelIndex& idx ) const
{
    if ( !idx.isValid() ) return nullptr;
    assert( idx.model() == summaryHandlingModel() );
    QHash<QPersistentModelIndex,GraphicsItem*>::const_iterator it = d->items.find( idx );
    return ( it != d->items.end() )?*it:nullptr;
}

GraphicsItem* GraphicsScene::findItem( const QPersistentModelIndex& idx ) const
{
    if ( !idx.isValid() ) return nullptr;
    assert( idx.model() == summaryHandlingModel() );
    QHash<QPersistentModelIndex,GraphicsItem*>::const_iterator it = d->items.find( idx );
    return ( it != d->items.end() )?*it:nullptr;
}

void GraphicsScene::clearItems()
{
    d->clearItems();
}

void GraphicsScene::updateItems()
{
    for ( QHash<QPersistentModelIndex,GraphicsItem*>::iterator it = d->items.begin();
          it != d->items.end(); ++it ) {
        GraphicsItem* const item = it.value();
        const QPersistentModelIndex& idx = it.key();
        item->updateItem( Span( item->pos().y(), item->rect().height() ), idx );
    }
    invalidate( QRectF(), QGraphicsScene::BackgroundLayer );
}

void GraphicsScene::deleteSubtree( const QModelIndex& _idx )
{
    QModelIndex idx = dataIndex( _idx );
    if ( !idx.model() ) return;
    const QModelIndex parent( idx.parent() );
    const int colcount = idx.model()->columnCount( parent );
    {for ( int i = 0; i < colcount; ++i ) {
        removeItem( summaryHandlingModel()->index(idx.row(), i, parent ) );
    }}
    const int rowcount = summaryHandlingModel()->rowCount( _idx );
    {for ( int i = 0; i < rowcount; ++i ) {
        deleteSubtree( summaryHandlingModel()->index( i, summaryHandlingModel()->columnCount(_idx)-1, _idx ) );
    }}
}


ConstraintGraphicsItem* GraphicsScene::findConstraintItem( const Constraint& c ) const
{
    return d->findConstraintItem( c );
}

void GraphicsScene::slotConstraintAdded( const KGantt::Constraint& c )
{
    d->createConstraintItem( c );
}

void GraphicsScene::slotConstraintRemoved( const KGantt::Constraint& c )
{
    d->deleteConstraintItem( c );
}

void GraphicsScene::slotGridChanged()
{
    updateItems();
    update();
    Q_EMIT gridChanged();
}

void GraphicsScene::selectionModelChanged(QAbstractItemModel *model)
{
    Q_UNUSED(model)
}

void GraphicsScene::slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    for (const QModelIndex &idx : deselected.indexes()) {
        GraphicsItem *item = findItem(idx.model() == d->summaryHandlingModel ? idx : d->summaryHandlingModel->mapFromSource(idx));
        if (item) {
            item->setSelected(false);
        }
    }
    for (const QModelIndex &idx : selected.indexes()) {
        GraphicsItem *item = findItem(idx.model() == d->summaryHandlingModel ? idx : d->summaryHandlingModel->mapFromSource(idx));
        if (item) {
            item->setSelected(true);
        }
    }
    update();
}

void GraphicsScene::helpEvent( QGraphicsSceneHelpEvent *helpEvent )
{
#ifndef QT_NO_TOOLTIP
    QGraphicsItem *item = itemAt( helpEvent->scenePos(), QTransform() );
    if ( GraphicsItem* gitem = qgraphicsitem_cast<GraphicsItem*>( item ) ) {
        QToolTip::showText(helpEvent->screenPos(), gitem->ganttToolTip());
    } else if ( ConstraintGraphicsItem* citem = qgraphicsitem_cast<ConstraintGraphicsItem*>( item ) ) {
        QToolTip::showText(helpEvent->screenPos(), citem->ganttToolTip());
    } else {
        QGraphicsScene::helpEvent( helpEvent );
    }
#endif /* QT_NO_TOOLTIP */
}

void GraphicsScene::drawBackground( QPainter* painter, const QRectF& _rect )
{
    QRectF scn( sceneRect() );
    QRectF rect( _rect );
    if ( d->isPrinting && d->drawColumnLabels ) {
        QRectF headerRect( scn.topLeft()+QPointF( d->labelsWidth, 0 ),
                           QSizeF( scn.width()-d->labelsWidth, d->rowController->headerHeight() ));

        d->getGrid()->paintHeader( painter, headerRect, rect, 0, nullptr );

#if 0
        /* We have to blank out the part of the header that is invisible during
        * normal rendering when we are printing.
        */
        QRectF labelsTabRect( scn.topLeft(), QSizeF( d->labelsWidth, headerRect.height() ) );

        QStyleOptionHeader opt;
        opt.rect = labelsTabRect.toRect();
        opt.text = QLatin1String("");
        opt.textAlignment = Qt::AlignCenter;
        style()->drawControl(QStyle::CE_Header, &opt, painter, 0);
#endif

        scn.setTop( headerRect.bottom() );
        scn.setLeft( headerRect.left() );
        rect = rect.intersected( scn );
    }
    d->getGrid()->paintGrid( painter, scn, rect, d->rowController );

    d->getGrid()->drawBackground(painter, rect);
}

void GraphicsScene::drawForeground( QPainter* painter, const QRectF& rect )
{
    d->getGrid()->drawForeground(painter, rect);
}

void GraphicsScene::itemEntered( const QModelIndex& idx )
{
    Q_EMIT entered( idx );
}

void GraphicsScene::itemPressed( const QModelIndex& idx, QGraphicsSceneMouseEvent *event )
{
    if (event->button() == Qt::LeftButton) {
        QItemSelectionModel::SelectionFlags flags;
        if (event->modifiers() & Qt::ControlModifier) {
            flags |= QItemSelectionModel::Toggle;
        } else {
            flags |= QItemSelectionModel::ClearAndSelect;
        }
        d->selectionModel->select(d->summaryHandlingModel->mapToSource(idx), flags);
    }
    Q_EMIT pressed( idx );
}

void GraphicsScene::itemClicked( const QModelIndex& idx )
{
    Q_EMIT clicked( idx );
}

void GraphicsScene::itemDoubleClicked( const QModelIndex& idx )
{
    Q_EMIT qrealClicked( idx );
}

void GraphicsScene::setDragSource( GraphicsItem* item )
{
    d->dragSource = item;
}

GraphicsItem* GraphicsScene::dragSource() const
{
    return d->dragSource;
}


void GraphicsScene::print( QPrinter* printer, bool drawRowLabels, bool drawColumnLabels )
{
#ifndef HAVE_PRINTER
    Q_UNUSED( printer );
    Q_UNUSED( drawRowLabels );
    Q_UNUSED( drawColumnLabels );
#else
    QPainter painter( printer );
    doPrint( &painter, printer->pageRect(), sceneRect().left(), sceneRect().right(), printer, drawRowLabels, drawColumnLabels );
#endif
}


void GraphicsScene::print( QPrinter* printer, qreal start, qreal end, bool drawRowLabels, bool drawColumnLabels )
{
#ifndef HAVE_PRINTER
    Q_UNUSED( printer );
    Q_UNUSED( start );
    Q_UNUSED( end );
    Q_UNUSED( drawRowLabels );
    Q_UNUSED( drawColumnLabels );
#else
    QPainter painter( printer );
    doPrint( &painter, printer->pageRect(), start, end, printer, drawRowLabels, drawColumnLabels );
#endif
}


void GraphicsScene::print( QPainter* painter, const QRectF& _targetRect, bool drawRowLabels, bool drawColumnLabels )
{
    QRectF targetRect( _targetRect );
    if ( targetRect.isNull() ) {
        targetRect = sceneRect();
    }

    doPrint( painter, targetRect, sceneRect().left(), sceneRect().right(), nullptr, drawRowLabels, drawColumnLabels );
}


void GraphicsScene::print( QPainter* painter, qreal start, qreal end,
                           const QRectF& _targetRect, bool drawRowLabels, bool drawColumnLabels )
{
    QRectF targetRect( _targetRect );
    if ( targetRect.isNull() ) {
        targetRect = sceneRect();
    }

    doPrint( painter, targetRect, start, end, nullptr, drawRowLabels, drawColumnLabels );
}

void GraphicsScene::printDiagram( QPrinter *printer, const PrintingContext &context )
{
#ifndef HAVE_PRINTER
    Q_UNUSED( printer );
    Q_UNUSED( context );
#else
    PrintingContext ctx( context );
    if (ctx.sceneRect().isNull()) {
        ctx.setSceneRect(sceneRect());
    }
    QRectF targetRect = printer->pageRect( QPrinter::DevicePixel );
    if ( printer->fullPage() ) {
        // Handle margins
        QPageLayout pl = printer->pageLayout();
        targetRect = targetRect.marginsRemoved( pl.marginsPixels( printer->resolution() ) );
    }
    QPainter painter( printer );
    doPrintScene( printer, &painter, targetRect, ctx );
#endif
}

void GraphicsScene::doPrint( QPainter* painter, const QRectF& targetRect,
                             qreal start, qreal end,
                             QPrinter* printer, bool drawRowLabels, bool drawColumnLabels )
{
    assert( painter );
    PrintingContext ctx;
    ctx.setFitting(PrintingContext::FitPageHeight); // keep old behavior (?)
    ctx.setDrawRowLabels( drawRowLabels );
    ctx.setDrawColumnLabels( drawColumnLabels );
    ctx.setSceneRect( sceneRect() );
    ctx.setLeft( start );
    ctx.setRight( end );
    doPrintScene( printer, painter, targetRect, ctx );
}

void GraphicsScene::doPrintScene( QPrinter *printer, QPainter *painter, const QRectF &targetRect, const PrintingContext &context )
{
    assert( painter );

    bool b = blockSignals( true );

    d->isPrinting = true;
    d->drawColumnLabels = context.drawColumnLabels();
    d->labelsWidth = 0.0;

    QFont sceneFont( font() );
#ifdef HAVE_PRINTER
    if ( printer ) {
        sceneFont = QFont( font(), printer );
        if ( font().pointSizeF() >= 0.0 )
            sceneFont.setPointSizeF( font().pointSizeF() );
        else if ( font().pointSize() >= 0 )
            sceneFont.setPointSize( font().pointSize() );
        else
            sceneFont.setPixelSize( font().pixelSize() );
    }
#endif

    QGraphicsTextItem dummyTextItem( QLatin1String("X") );
    dummyTextItem.adjustSize();
    QFontMetrics fm(dummyTextItem.font());
    sceneFont.setPixelSize( fm.height() );

    const QRectF oldScnRect( sceneRect() );
    QRectF scnRect( oldScnRect );
    QRectF sceneHeaderRect;
    QRectF labelsHeaderRect;
    QRectF labelsRect;

    /* column labels */
    qreal headerHeight = 0.0;
    if ( context.drawColumnLabels() ) {
        headerHeight = d->rowController->headerHeight();
        sceneHeaderRect = context.sceneRect();
        sceneHeaderRect.setLeft( context.left() );
        sceneHeaderRect.setTop( -headerHeight );
        sceneHeaderRect.setHeight( headerHeight );
        scnRect.setTop(scnRect.top() - headerHeight);
    }

    /* row labels */
    QVector<QGraphicsTextItem*> textLabels;
    if ( context.drawRowLabels() ) {
        qreal textWidth = 0.;
        qreal charWidth = QFontMetricsF(sceneFont).boundingRect( QString::fromLatin1( "X" ) ).width();
        QModelIndex sidx = summaryHandlingModel()->mapToSource( summaryHandlingModel()->index( 0, 0, rootIndex()) );
        do {
            QModelIndex idx = summaryHandlingModel()->mapFromSource( sidx );
            const Span rg=rowController()->rowGeometry( sidx );
            const QString txt = idx.data( Qt::DisplayRole ).toString();
            QGraphicsTextItem* item = new QGraphicsTextItem( txt );
            addItem( item );
            textLabels << item;
            item->setTextWidth( QFontMetricsF(sceneFont).boundingRect( txt ).width() + charWidth );
            textWidth = qMax( item->textWidth(), textWidth );
            item->setPos( 0, rg.start() );
        } while ( ( sidx = rowController()->indexBelow( sidx ) ).isValid() );
        d->labelsWidth = textWidth;
        scnRect.setLeft( scnRect.left() - textWidth );
        for( QGraphicsTextItem* item : textLabels ) {
            item->setPos( scnRect.left(), item->y() );
            item->show();
        }
        if ( context.drawColumnLabels() ) {
            labelsHeaderRect = sceneHeaderRect;
            labelsHeaderRect.translate( -textWidth, 0.0 );
            labelsHeaderRect.setWidth( textWidth );
        }
        labelsRect = QRectF( scnRect.left(), context.top(), textWidth, context.sceneRect().height() );
    }
    setSceneRect( scnRect );
    scnRect.setRight( context.right() );

    // The scene looks like this:
    //  Labels   Do not print    Print        Behind end
    // 1       2               3            4
    // !-------!---------------!------------!-----------
    // sceneWidth is 1 to 2 + 3 to 4
    qreal sceneWidth = d->labelsWidth + context.right() - context.left();
    qreal sceneHeight = context.sceneRect().height() + sceneHeaderRect.height();
    // qInfo()<<Q_FUNC_INFO<<targetRect<<scnRect<<sceneWidth;

    int horPages = 1;
    int vertPages = 1;
    qreal scaleFactor = targetRect.height() / scnRect.height(); // FitPageHeight (default)
    if ( printer ) {
        if ( context.fitting() & PrintingContext::NoFitting ) {
            scaleFactor = printer->logicalDpiX() / views().at(0)->logicalDpiX(); // always have only one view
            vertPages = qRound( ( sceneHeight * scaleFactor / targetRect.height() ) + 0.5 );
            horPages = qRound( ( sceneWidth * scaleFactor / targetRect.width() ) + 0.5 );
        } else if ( context.fitting() & PrintingContext::FitSinglePage ) {
            scaleFactor = std::min( scaleFactor, targetRect.width() / sceneWidth );
        } else /*FitPageHeight (default)*/ {
            horPages = qRound( ( sceneWidth * scaleFactor / targetRect.width() ) + 0.5 );
        }
    } else {
        // paint device has no pages so just fit inside the target
        scaleFactor = std::min( scaleFactor, targetRect.width() / sceneWidth );
    }
    // qInfo()<<Q_FUNC_INFO<<"labels header:"<<labelsHeaderRect<<"labels:"<<labelsRect<<"scene header:"<<sceneHeaderRect<<"scene:"<<scnRect<<"scaleFactor:"<<scaleFactor;
    painter->save();
    painter->setFont( sceneFont );

    // qInfo()<<Q_FUNC_INFO<<'s'<<scaleFactor<<"pages="<<((sceneWidth * scaleFactor)/targetRect.width())<<'h'<<horPages<<'v'<<vertPages<<'s'<<scnRect<<'t'<<(targetRect.size()/scaleFactor);
    qreal yPos = labelsRect.top();
    for ( int vpage = 0; vpage < vertPages && yPos < context.bottom(); ++vpage ) {
        // qInfo()<<Q_FUNC_INFO<<"print vertical page"<<vpage;
        // Disable painting of noInformation during labels printing
        // or else labels might be painted over
        QBrush noInfoBrush;
        DateTimeGrid *dateTimeGrid = qobject_cast<DateTimeGrid*>(grid());
        if (dateTimeGrid) {
            noInfoBrush = dateTimeGrid->noInformationBrush();
            dateTimeGrid->setNoInformationBrush(QBrush());
        }
        int hpage = 0;
        qreal targetLabelsOffset = 0.0;
        qreal labelsOffsetX = 0.0;
        while ( labelsOffsetX < labelsHeaderRect.width() ) {
            // qInfo()<<Q_FUNC_INFO<<"print labels"<<"vert page:"<<vpage<<','<<hpage<<"yPos"<<yPos<<"label x:"<<labelsOffsetX;
            // print labels, they might span multiple pages
            QRectF target = targetRect;
            target.setWidth(std::min(target.width(), (labelsHeaderRect.width() - labelsOffsetX) * scaleFactor) );
            if ( vpage == 0 && headerHeight > 0.0 ) {
                QRectF sourceHeader = labelsHeaderRect;
                sourceHeader.translate( labelsOffsetX, 0.0 );
                QRectF targetHeader = target;
                targetHeader.setSize( sourceHeader.size() * scaleFactor );
                drawLabelsHeader( painter, sourceHeader, targetHeader );
                target.adjust( 0.0, targetHeader.height(), 0.0, 0.0 );
            }
            QRectF rect = labelsRect;
            rect.setLeft( rect.left() + labelsOffsetX );
            rect.setTop( yPos );
            rect.setHeight( std::min(rect.height(), target.height() / scaleFactor ) );
            painter->setClipRect(target);
            // disable header, it has been drawn above
            bool drawColumnLabels = d->drawColumnLabels;
            d->drawColumnLabels = false;
            // qInfo()<<Q_FUNC_INFO<<"print labels"<<"vert page:"<<vpage<<','<<hpage<<"scene rect:"<<rect<<"target:"<<target;
            render( painter, target, rect );
            d->drawColumnLabels = drawColumnLabels;
            labelsOffsetX += rect.width();
            if ( targetRect.right() <= target.right() ) {
                // we have used the whole page
                ++hpage;
#ifdef HAVE_PRINTER
                if ( printer ) {
                    printer->newPage();
                }
#endif
            } else {
                // labels might take part of the page
                targetLabelsOffset = target.width();
                // qInfo()<<Q_FUNC_INFO<<"print labels finished"<<"vert page:"<<vpage<<"hor page:"<<hpage<<"target offset:"<<targetLabelsOffset;
                break;
            }
        }
        if (dateTimeGrid) {
            dateTimeGrid->setNoInformationBrush(noInfoBrush);
        }
        qreal xPos = context.left();
        // qInfo()<<Q_FUNC_INFO<<"print diagram"<<"page:"<<vpage<<','<<hpage<<"xPos"<<xPos<<"yPos:"<<yPos;
        for ( ; hpage < horPages && xPos < context.right(); ++hpage ) {
            // Adjust for row labels (first time only)
            QRectF target = targetRect.adjusted(targetLabelsOffset, 0., 0., 0.);
            targetLabelsOffset = 0.0;
            if (!sceneHeaderRect.isNull() && vpage == 0) {
                // draw header
                QRectF rect = sceneHeaderRect;
                rect.setLeft( xPos );
                QRectF targetHeader = target;
                targetHeader.setHeight( rect.height() * scaleFactor );
                rect.setWidth( std::min( rect.width(), target.width() / scaleFactor) );
                // qInfo()<<Q_FUNC_INFO<<"scene header:"<<"page:"<<vpage<<','<<hpage<<"source:"<<rect<<"target:"<<targetHeader;
                render( painter, targetHeader, rect );
                target.adjust( 0.0, targetHeader.height(), 0.0, 0.0 );
            }
            QRectF rect = context.sceneRect();
            rect.setLeft( xPos );
            rect.setTop( yPos );
            rect.setWidth( std::min( rect.width(), target.width() / scaleFactor) );
            rect.setHeight( std::min( rect.height(), target.height() / scaleFactor ) );
            target.setWidth( rect.width() * scaleFactor );
            painter->setClipRect( target );
            // disable header, it has been drawn above
            bool drawColumnLabels = d->drawColumnLabels;
            d->drawColumnLabels = false;
            // qInfo()<<Q_FUNC_INFO<<"scene:"<<"page:"<<vpage<<','<<hpage<<"source:"<<rect<<"target:"<<target;
            render( painter, target, rect );
            d->drawColumnLabels = drawColumnLabels;

            xPos += rect.width();
            // qInfo()<<Q_FUNC_INFO<<context<<"xPos:"<<xPos;
            if ( printer && xPos < context.right() ) {
#ifdef HAVE_PRINTER
                printer->newPage();
#endif
            } else {
                // qInfo()<<Q_FUNC_INFO<<"print horizontal finished if"<<xPos<<">="<<scnRect.right();
                break;
            }
        }
        yPos += targetRect.height() / scaleFactor;
        if ( vpage == 0 ) {
            yPos -= headerHeight;
        }
        // qInfo()<<Q_FUNC_INFO<<"yPos:"<<yPos<<"bottom:"<<context.bottom();
        if ( printer && yPos < context.bottom() ) {
#ifdef HAVE_PRINTER
            // next vertical page
            printer->newPage();
#endif
        }
        // qInfo()<<Q_FUNC_INFO<<"next vertical page if"<<yPos<<'<'<<scnRect.bottom();
    }

    d->isPrinting = false;
    d->drawColumnLabels = true;
    d->labelsWidth = 0.0;
    qDeleteAll( textLabels );
    blockSignals( b );
    setSceneRect( oldScnRect );
    painter->restore();
}

void GraphicsScene::drawLabelsHeader( QPainter *painter, const QRectF &sourceRect, const QRectF &targetRect )
{
    // qInfo()<<Q_FUNC_INFO<<"header:"<<sourceRect<<targetRect;
    // TODO This should paint itemview header
    painter->setClipRect( targetRect );
    render( painter, targetRect, sourceRect );
}

#include "moc_kganttgraphicsscene.cpp"


#ifndef KDAB_NO_UNIT_TESTS
#include "unittest/test.h"

#include <QGraphicsLineItem>
#include <QPointer>
#include <QStandardItemModel>

#include "kganttgraphicsview.h"

class SceneTestRowController : public KGantt::AbstractRowController {
private:
    static const int ROW_HEIGHT;
    QPointer<QAbstractItemModel> m_model;

public:
    SceneTestRowController()
    {
    }

    void setModel( QAbstractItemModel* model )
    {
        m_model = model;
    }

    /*reimp*/int headerHeight() const override { return 40; }

    /*reimp*/ bool isRowVisible( const QModelIndex& ) const override { return true;}
    /*reimp*/ bool isRowExpanded( const QModelIndex& ) const override { return false; }
    /*reimp*/ KGantt::Span rowGeometry( const QModelIndex& idx ) const override
    {
        return KGantt::Span( idx.row() * ROW_HEIGHT, ROW_HEIGHT );
    }
    /*reimp*/ int maximumItemHeight() const override {
        return ROW_HEIGHT/2;
    }
    /*reimp*/int totalHeight() const override {
        return m_model->rowCount()* ROW_HEIGHT;
    }

    /*reimp*/ QModelIndex indexAt( int height ) const override {
        return m_model->index( height/ROW_HEIGHT, 0 );
    }

    /*reimp*/ QModelIndex indexBelow( const QModelIndex& idx ) const override {
        if ( !idx.isValid() )return QModelIndex();
        return idx.model()->index( idx.row()+1, idx.column(), idx.parent() );
    }
    /*reimp*/ QModelIndex indexAbove( const QModelIndex& idx ) const override {
        if ( !idx.isValid() )return QModelIndex();
        return idx.model()->index( idx.row()-1, idx.column(), idx.parent() );
    }

};

class TestLineItem : public QGraphicsLineItem
{
public:
    TestLineItem( bool *destroyedFlag )
         : QGraphicsLineItem( 0, 0, 10, 10 ), // geometry doesn't matter
           m_destroyedFlag( destroyedFlag )
    {}

    ~TestLineItem()
    { *m_destroyedFlag = true; }

private:
    bool *m_destroyedFlag;
};

const int SceneTestRowController::ROW_HEIGHT = 30;

KDAB_SCOPED_UNITTEST_SIMPLE( KGantt, GraphicsView, "test" ) {
    QStandardItemModel model;

    QStandardItem* item = new QStandardItem();
    item->setData( KGantt::TypeTask, KGantt::ItemTypeRole );
    item->setData( QString::fromLatin1( "Decide on new product" ) );
    item->setData( QDateTime( QDate( 2007, 3, 1 ), QTime() ), KGantt::StartTimeRole );
    item->setData( QDateTime( QDate( 2007, 3, 3 ), QTime() ), KGantt::EndTimeRole );

    QStandardItem* item2 = new QStandardItem();
    item2->setData( KGantt::TypeTask, KGantt::ItemTypeRole );
    item2->setData( QString::fromLatin1( "Educate personnel" ) );
    item2->setData( QDateTime( QDate( 2007, 3, 3 ), QTime() ), KGantt::StartTimeRole );
    item2->setData( QDateTime( QDate( 2007, 3, 6 ), QTime() ), KGantt::EndTimeRole );

    model.appendRow( item );
    model.appendRow( item2 );

    SceneTestRowController rowController;
    rowController.setModel( &model );

    KGantt::GraphicsView graphicsView;
    graphicsView.setRowController( &rowController );
    graphicsView.setModel( &model );

    // Now the interesting stuff - the items above are just for a "realistic environment"

    bool foreignItemDestroyed = false;
    TestLineItem *foreignItem = new TestLineItem( &foreignItemDestroyed );
    graphicsView.scene()->addItem( foreignItem );

    assertFalse( foreignItemDestroyed );
    graphicsView.updateScene();
    assertFalse( foreignItemDestroyed );
}
#endif /* KDAB_NO_UNIT_TESTS */
