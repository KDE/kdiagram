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

#include "kganttview.h"
#include "kganttview_p.h"

#include "kganttitemdelegate.h"
#include "kganttgraphicsitem.h"
#include "kganttsummaryhandlingproxymodel.h"

#include <QAbstractItemModel>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QScrollBar>
#include <QPaintEvent>

#include <QDebug>

#include <cassert>

#if defined KDAB_EVAL
#include "../evaldialog/evaldialog.h"
#endif

using namespace KGantt;

namespace {
    class HeaderView : public QHeaderView {
    public:
        explicit HeaderView( QWidget* parent=nullptr ) : QHeaderView( Qt::Horizontal, parent ) {
        }

        QSize sizeHint() const override { QSize s = QHeaderView::sizeHint(); s.rheight() *= 2; return s; }
    };
}

KGanttTreeView::KGanttTreeView( QAbstractProxyModel* proxy, QWidget* parent )
    : QTreeView( parent ),
      m_controller( this, proxy )
{
    setHeader( new HeaderView );
}

KGanttTreeView::~KGanttTreeView()
{
}

void KGanttTreeView::expandAll(QModelIndex index)
{
    for (int i = 0; i < model()->rowCount(index); i++) {
        QModelIndex indexAt = model()->index(i, 0, index);
        if (model()->hasChildren(indexAt))
            expandAll(indexAt);
        if (isExpanded(indexAt))
            continue;
        expand(indexAt);
    }
}

void KGanttTreeView::collapseAll(QModelIndex index)
{
    for (int i = 0; i < model()->rowCount(index); i++) {
        QModelIndex indexAt = model()->index(i, 0, index);
        if (model()->hasChildren(indexAt))
            collapseAll(indexAt);
        if (!isExpanded(indexAt))
            continue;
        collapse(indexAt);
    }
}

View::Private::Private(View* v)
    : q(v),
      splitter(v),
      rowController(nullptr),
      gfxview( new GraphicsView( &splitter ) ),
      model(nullptr)
{
    //init();
}

View::Private::~Private()
{
    delete gfxview;
}

void View::Private::init()
{
    KGanttTreeView* tw = new KGanttTreeView( &ganttProxyModel, &splitter );
    tw->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tw->setVerticalScrollMode( QAbstractItemView::ScrollPerPixel );

    q->setLeftView( tw );
    q->setRowController( tw->rowController() );

    //gfxview.setRenderHints( QPainter::Antialiasing );

    tw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QVBoxLayout* layout = new QVBoxLayout(q);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(&splitter);
    q->setLayout(layout);

    constraintProxy.setProxyModel( &ganttProxyModel );
    constraintProxy.setDestinationModel( &mappedConstraintModel );
    setupGraphicsView();
}

void View::Private::setupGraphicsView()
{
    gfxview->setParent( &splitter );
    gfxview->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    gfxview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    gfxview->setSelectionModel( leftWidget->selectionModel() );
    gfxview->setConstraintModel( &mappedConstraintModel );
    q->setLeftView( leftWidget );
    q->setRowController( rowController );
    updateScene();
}

void View::Private::updateScene()
{
    gfxview->clearItems();
    if ( !model) return;

    if ( QTreeView* tw = qobject_cast<QTreeView*>(leftWidget)) {
      QModelIndex idx = ganttProxyModel.mapFromSource( model->index( 0, 0, leftWidget->rootIndex() ) );
      do {
        gfxview->updateRow( idx );
      } while ( ( idx = tw->indexBelow( idx ) ) != QModelIndex() &&
		gfxview->rowController()->isRowVisible(idx) );
      gfxview->updateSceneRect();
    } else {
      const QModelIndex rootidx = ganttProxyModel.mapFromSource( leftWidget->rootIndex() );
      for ( int r = 0; r < ganttProxyModel.rowCount(rootidx); ++r ) {
	gfxview->updateRow( ganttProxyModel.index( r, 0, rootidx ) );
      }
    }
}

void View::Private::slotCollapsed(const QModelIndex& _idx)
{
    QTreeView* tw = qobject_cast<QTreeView*>(leftWidget);
    if (!tw) return;

    bool blocked = gfxview->blockSignals( true );

    QModelIndex idx( _idx );
    const QAbstractItemModel* model = leftWidget->model();
    const QModelIndex pidx = ganttProxyModel.mapFromSource(idx);
    bool isMulti = false;
    for ( QModelIndex treewalkidx = pidx; treewalkidx.isValid(); treewalkidx = treewalkidx.parent() ) {
        if ( treewalkidx.data( ItemTypeRole ).toInt() == TypeMulti
             && !gfxview->rowController()->isRowExpanded( treewalkidx ) ) {
            isMulti = true;
            break;
        }
    }

    if ( !isMulti ) {
        for ( int i = 0; i < model->rowCount( idx ); ++i ) {
            gfxview->deleteSubtree( ganttProxyModel.index( i, 0, pidx ) );
        }
    } else {
        gfxview->updateRow(pidx);
    }
    //qDebug() << "Looking to update from " << idx;
    while ( ( idx=tw->indexBelow( idx ) ) != QModelIndex() &&
            gfxview->rowController()->isRowVisible( ganttProxyModel.mapFromSource(idx) ) ) {
        const QModelIndex proxyidx( ganttProxyModel.mapFromSource( idx ) );
        gfxview->updateRow(proxyidx);
    }
    gfxview->blockSignals( blocked );
    gfxview->updateSceneRect();
}

void View::Private::slotExpanded(const QModelIndex& _idx)
{
    QModelIndex idx( ganttProxyModel.mapFromSource( _idx ) );
    do {
        //qDebug() << "Updating row" << idx << idx.data( Qt::DisplayRole ).toString();
        gfxview->updateRow(idx);
    } while ( ( idx=gfxview->rowController()->indexBelow( idx ) ) != QModelIndex()
             && gfxview->rowController()->isRowVisible( idx ) );
    gfxview->updateSceneRect();
}

void View::Private::slotVerticalScrollValueChanged( int val )
{
#if 0
    qDebug() << "View::Private::slotVerticalScrollValueChanged("<<val<<")="
             << val/gfxview->verticalScrollBar()->singleStep();
#endif
    leftWidget->verticalScrollBar()->setValue( val/gfxview->verticalScrollBar()->singleStep() );
}

void View::Private::slotLeftWidgetVerticalRangeChanged(int min, int max )
{
    //qDebug() << "View::Private::slotLeftWidgetVerticalRangeChanged("<<min<<max<<")";
    // In some cases the gfxview has already been deleted when this signal arrive
    if (!gfxview.isNull()) {
        gfxview->verticalScrollBar()->setRange( min, max );
        gfxview->updateSceneRect();
    }
}

void View::Private::slotGfxViewVerticalRangeChanged( int min, int max )
{
    //qDebug() << "View::Private::slotGfxViewVerticalRangeChanged("<<min<<max<<")";
    if ( !leftWidget.isNull() && !gfxview.isNull() ) {
        int leftMin = leftWidget->verticalScrollBar()->minimum();
        int leftMax = leftWidget->verticalScrollBar()->maximum();
        bool blocked = gfxview->verticalScrollBar()->blockSignals( true );
        gfxview->verticalScrollBar()->setRange( qMax( min, leftMin ), qMax( max, leftMax ) );
        gfxview->verticalScrollBar()->blockSignals( blocked );
    }
}




View::View(QWidget* parent)
    : QWidget(parent),
      _d(new Private(this))
{
#if defined KDAB_EVAL
   EvalDialog::checkEvalLicense( "KD Gantt" );
#endif
   _d->init();
}

View::~View()
{
    delete _d;
}

#define d d_func()


void View::setLeftView( QAbstractItemView* aiv )
{
    assert( aiv );
    if ( aiv==d->leftWidget ) return;
    if ( !d->leftWidget.isNull() ) {
        d->leftWidget->disconnect( this );
        d->leftWidget->hide();
        d->leftWidget->verticalScrollBar()->disconnect( d->gfxview->verticalScrollBar() );
        d->gfxview->verticalScrollBar()->disconnect( d->leftWidget->verticalScrollBar() );
    }

    d->leftWidget = aiv;
    d->splitter.insertWidget( 0, d->leftWidget );

    if ( qobject_cast<QTreeView*>(d->leftWidget) ) {
      connect( d->leftWidget,  SIGNAL(collapsed(QModelIndex)),
	       this, SLOT(slotCollapsed(QModelIndex)) );
      connect( d->leftWidget,  SIGNAL(expanded(QModelIndex)),
	       this, SLOT(slotExpanded(QModelIndex)) );
    }

    connect( d->gfxview->verticalScrollBar(), SIGNAL(valueChanged(int)),
             d->leftWidget->verticalScrollBar(), SLOT(setValue(int)) );
    connect( d->leftWidget->verticalScrollBar(), SIGNAL(valueChanged(int)),
             d->gfxview->verticalScrollBar(), SLOT(setValue(int)) );
    connect( d->leftWidget->verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
             this, SLOT(slotLeftWidgetVerticalRangeChanged(int,int)) );
    connect( d->gfxview->verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
             this, SLOT(slotGfxViewVerticalRangeChanged(int,int)) );
}


void View::setRowController( AbstractRowController* ctrl )
{
    if ( ctrl == d->rowController && d->gfxview->rowController() == ctrl ) return;
    d->rowController = ctrl;
    d->gfxview->setRowController( d->rowController );
}


AbstractRowController* View::rowController()
{
    return d->rowController;
}


const AbstractRowController* View::rowController() const
{
    return d->rowController;
}


const QAbstractItemView* View::leftView() const
{
    return d->leftWidget;
}


QAbstractItemView* View::leftView()
{
    return d->leftWidget;
}


void View::setGraphicsView( GraphicsView* gv )
{
    if ( gv != d->gfxview ) {
        GraphicsView* old = d->gfxview;
        AbstractGrid *grid = old->takeGrid();
        d->gfxview = gv;
        d->gfxview->setModel(old->model()); // use the old ForwardingProxyModel
        d->setupGraphicsView();
        d->gfxview->setGrid( grid );
        delete old;
    }
}


const GraphicsView* View::graphicsView() const
{
    return d->gfxview;
}


GraphicsView* View::graphicsView()
{
    return d->gfxview;
}


const QSplitter* View::splitter() const
{
    return &d->splitter;
}


QSplitter* View::splitter()
{
    return &d->splitter;
}



QAbstractItemModel* View::model() const
{
    return leftView()->model();
}


void View::setModel( QAbstractItemModel* model )
{
    leftView()->setModel( model );
    d->ganttProxyModel.setSourceModel( model );
    d->gfxview->setModel( &d->ganttProxyModel );
}


QItemSelectionModel* View::selectionModel() const
{
    return leftView()->selectionModel();
}


void View::setSelectionModel( QItemSelectionModel* smodel )
{
    leftView()->setSelectionModel( smodel );
    d->gfxview->setSelectionModel( new QItemSelectionModel( &( d->ganttProxyModel ),this ) );
}


void View::setGrid( AbstractGrid* grid )
{
    d->gfxview->setGrid( grid );
}

void View::expandAll( QModelIndex index )
{
    // FIXME:
    // It is legal to call setLeftView() with any QAbstractItemView,
    // so expandAll should be reimplemented to work with that.
    KGanttTreeView* tw = qobject_cast<KGanttTreeView*>(leftView());
    if (tw) {
        tw->expandAll(index);
    }
}

void View::collapseAll( QModelIndex index )
{
    // FIXME:
    // It is legal to call setLeftView() with any QAbstractItemView,
    // so expandAll should be reimplemented to work with that.
    KGanttTreeView* tw = qobject_cast<KGanttTreeView*>(leftView());
    if (tw) {
        tw->collapseAll(index);
    }
}


AbstractGrid* View::grid() const
{
    return d->gfxview->grid();
}


QModelIndex View::rootIndex() const
{
    return leftView()->rootIndex();
}


void View::setRootIndex( const QModelIndex& idx )
{
    leftView()->setRootIndex( idx );
    d->gfxview->setRootIndex( idx );
}


ItemDelegate* View::itemDelegate() const
{
    return d->gfxview->itemDelegate();
}


void View::setItemDelegate( ItemDelegate* delegate )
{
    leftView()->setItemDelegate( delegate );
    d->gfxview->setItemDelegate( delegate );
}


void View::setConstraintModel( ConstraintModel* cm )
{
    d->constraintProxy.setSourceModel( cm );
    d->gfxview->setConstraintModel( &d->mappedConstraintModel );
}


ConstraintModel* View::constraintModel() const
{
    return d->constraintProxy.sourceModel();
}

const QAbstractProxyModel* View::ganttProxyModel() const
{
    return &( d->ganttProxyModel );
}

QAbstractProxyModel* View::ganttProxyModel()
{
    return &( d->ganttProxyModel );
}

void View::ensureVisible(const QModelIndex& index)
{
    QGraphicsView* view = graphicsView();
    KGantt::GraphicsScene* scene = static_cast<KGantt::GraphicsScene*>(view->scene());
    if (!scene)
        return;

    KGantt::SummaryHandlingProxyModel* model = static_cast<KGantt::SummaryHandlingProxyModel*>(scene->summaryHandlingModel());

    const QModelIndex pidx = d->ganttProxyModel.mapFromSource(index);
    const QModelIndex idx = model->mapFromSource( pidx );
    QGraphicsItem* item = scene->findItem(idx);
    view->ensureVisible(item);
}

void View::resizeEvent(QResizeEvent*ev)
{
    QWidget::resizeEvent(ev);
}


QModelIndex View::indexAt( const QPoint& pos ) const
{
    return d->gfxview->indexAt( pos );
}


void View::print( QPrinter* printer, bool drawRowLabels, bool drawColumnLabels )
{
    graphicsView()->print( printer, drawRowLabels, drawColumnLabels );
}


void View::print( QPrinter* printer, qreal start, qreal end, bool drawRowLabels, bool drawColumnLabels )
{
    graphicsView()->print( printer, start, end, drawRowLabels, drawColumnLabels );
}


void View::print( QPainter* painter, const QRectF& target, bool drawRowLabels, bool drawColumnLabels)
{
    d->gfxview->print( painter,
		      target,
		      drawRowLabels,
              drawColumnLabels);
}


void View::print( QPainter* painter, qreal start, qreal end, const QRectF& target, bool drawRowLabels, bool drawColumnLabels)
{
    d->gfxview->print( painter,
                      start, end,
		      target,
		      drawRowLabels,
              drawColumnLabels);
}

void View::printDiagram( QPrinter *printer, const PrintingContext &context )
{
    graphicsView()->printDiagram( printer, context );
}

#include "moc_kganttview.cpp"

#ifndef KDAB_NO_UNIT_TESTS
#include "unittest/test.h"

#include "kganttlistviewrowcontroller.h"
#include <QApplication>
#include <QTimer>
#include <QPixmap>
#include <QListView>

KDAB_SCOPED_UNITTEST_SIMPLE( KGantt, View, "test" ) {
    View view( nullptr );
#if 0 // GUI tests do not work well on the server
    QTimer::singleShot( 1000, qApp, SLOT(quit()) );
    view.show();

    qApp->exec();
    QPixmap screenshot1 = QPixmap::grabWidget( &view );

    QTreeView* tv = new QTreeView;
    view.setLeftView( tv );
    view.setRowController( new TreeViewRowController(tv,view.ganttProxyModel()) );

    QTimer::singleShot( 1000, qApp, SLOT(quit()) );

    qApp->exec();
    QPixmap screenshot2 = QPixmap::grabWidget( &view );

    assertEqual( screenshot1.toImage(),  screenshot2.toImage() );

    QListView* lv = new QListView;
    view.setLeftView(lv);
    view.setRowController( new ListViewRowController(lv,view.ganttProxyModel()));
    view.show();
    QTimer::singleShot( 1000, qApp, SLOT(quit()) );
    qApp->exec();
#endif
}
#endif /* KDAB_NO_UNIT_TESTS */
