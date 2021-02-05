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

#include "kganttgraphicsview.h"
#include "kganttgraphicsview_p.h"
#include "kganttabstractrowcontroller.h"
#include "kganttgraphicsitem.h"
#include "kganttconstraintmodel.h"
#include "kganttdatetimetimelinedialog.h"

#include <QMenu>
#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QScrollBar>
#include <QAbstractProxyModel>
#include <QPrinter>
#include <QItemSelectionModel>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>

#include <cassert>

#if defined KDAB_EVAL
#include "../evaldialog/evaldialog.h"
#endif

/*\class KGantt::HeaderWidget
 * \internal
 */

using namespace KGantt;

HeaderWidget::HeaderWidget( GraphicsView* parent )
    : QWidget( parent ), m_offset( 0. ), m_headerType( DateTimeGrid::NoHeader )
{
    assert( parent ); // Parent must be set
    setMouseTracking(true);
}

HeaderWidget::~HeaderWidget()
{
}

void HeaderWidget::scrollTo( int v )
{
    m_offset = v;
    // QWidget::scroll() wont work properly for me on Mac
    //scroll( static_cast<int>( old-v ), 0 );
    update();
}

void HeaderWidget::paintEvent( QPaintEvent* ev )
{
    QPainter p( this );
    view()->grid()->paintHeader( &p, rect(), ev->rect(), m_offset, this );
}

bool HeaderWidget::event( QEvent* event )
{
    if ( event->type() == QEvent::ToolTip ) {
        DateTimeGrid* const grid = qobject_cast< DateTimeGrid* >( view()->grid() );
        if ( grid ) {
            QHelpEvent *e = static_cast<QHelpEvent*>( event );
            QDateTime dt = grid->mapFromChart( view()->mapToScene( e->x(), 0 ).x() ).toDateTime();
            setToolTip( dt.toString() );
        }
    }
    return QWidget::event( event );
}

void HeaderWidget::mousePressEvent(QMouseEvent *event)
{
    DateTimeGrid* const grid = qobject_cast< DateTimeGrid* >( view()->grid() );
    int mousePosX = event->x();
    m_headerType = grid->sectionHandleAtPos( view()->mapToScene( event->x(), 0 ).x(), event->pos().y(), geometry() );
    if (m_headerType != DateTimeGrid::NoHeader) {
        bool hasCursor = testAttribute(Qt::WA_SetCursor);
        if (!hasCursor) {
            setCursor(QCursor(Qt::SplitHCursor));
        }
        m_mousePosX = mousePosX;
        event->accept();
        return;
    }
    QWidget::mousePressEvent( event );
}

void HeaderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if ( m_headerType > 0 ) {
        DateTimeGrid* const grid = qobject_cast< DateTimeGrid* >( view()->grid() );
        int mousePosX = view()->mapToScene( event->x(), 0 ).x();
        if ( grid->sectionHandleAtPos( mousePosX, event->pos().y(), geometry() ) == DateTimeGrid::NoHeader ) {
            bool hasCursor = testAttribute(Qt::WA_SetCursor);
            if (hasCursor) {
                unsetCursor();
            }
        }
        m_headerType = DateTimeGrid::NoHeader;
        m_mousePosX = event->x();
        QGuiApplication::restoreOverrideCursor();
    }
    QWidget::mouseReleaseEvent(event);
}

void HeaderWidget::mouseMoveEvent(QMouseEvent *event)
{
    DateTimeGrid* const grid = qobject_cast< DateTimeGrid* >( view()->grid() );
    int mousePosX = event->x();
    qreal gridX = view()->mapToScene( event->x(), 0.0 ).x();
    switch ( m_headerType ) {
        case DateTimeGrid::UpperHeader:
        {
            if ( mousePosX > m_mousePosX )  {
                grid->setDayWidth( qMax<qreal>( 1.0, grid->dayWidth() * 1.05 ) );
            } else {
                grid->setDayWidth( qMax<qreal>( 1.0, grid->dayWidth() / 1.05 ) );
            }
            m_mousePosX = mousePosX;
            event->accept();
            return;
        }
        case DateTimeGrid::LowerHeader:
        {
            if ( mousePosX > m_mousePosX )  {
                grid->setDayWidth( qMax<qreal>( 1.0, grid->dayWidth() * 1.01 ) );
            } else {
                grid->setDayWidth( qMax<qreal>( 1.0, grid->dayWidth() / 1.01 ) );
            }
            m_mousePosX = mousePosX;
            event->accept();
            return;
        }
        default: {
            bool hasCursor = testAttribute(Qt::WA_SetCursor);
            DateTimeGrid::HeaderType type = grid->sectionHandleAtPos( gridX, event->pos().y(), geometry());
            if (type != DateTimeGrid::NoHeader) {
                if (!hasCursor) {
                    setCursor(QCursor(Qt::SplitHCursor));
                }
                event->accept();
                return;
            }
            if (hasCursor) {
                unsetCursor();
            }
            break;
        }
    }
    QWidget::mouseMoveEvent(event);
}

void HeaderWidget::wheelEvent( QWheelEvent *event )
{
    DateTimeGrid* const grid = qobject_cast< DateTimeGrid* >( view()->grid() );
    if ( event->angleDelta().y() > 0 ) {
        grid->setDayWidth( qMax<qreal>( 1.0, grid->dayWidth() * 1.1 ) );
    } else {
        grid->setDayWidth( qMax<qreal>( 1.0, grid->dayWidth() / 1.1 ) );
    }
    event->accept();
}

void HeaderWidget::contextMenuEvent( QContextMenuEvent* event )
{
    QMenu contextMenu;

    DateTimeGrid* const grid = qobject_cast< DateTimeGrid* >( view()->grid() );
    QAction* actionScaleAuto = nullptr;
    QAction* actionScaleMonth = nullptr;
    QAction* actionScaleWeek = nullptr;
    QAction* actionScaleDay = nullptr;
    QAction* actionScaleHour = nullptr;
    QAction* actionZoomIn = nullptr;
    QAction* actionZoomOut = nullptr;
    QAction* actionTimeline = nullptr;
    if ( grid != nullptr )
    {
        QMenu* menuScale = new QMenu( tr( "Scale", "@title:menu" ), &contextMenu );
        QActionGroup* scaleGroup = new QActionGroup( &contextMenu );
        scaleGroup->setExclusive( true );

        actionScaleAuto = new QAction( tr( "Auto", "@item:inmenu Automatic scale" ), menuScale );
        actionScaleAuto->setCheckable( true );
        actionScaleAuto->setChecked( grid->scale() == DateTimeGrid::ScaleAuto );
        actionScaleMonth = new QAction( tr( "Month", "@item:inmenu" ), menuScale );
        actionScaleMonth->setCheckable( true );
        actionScaleMonth->setChecked( grid->scale() == DateTimeGrid::ScaleMonth );
        actionScaleWeek = new QAction( tr( "Week", "@item:inmenu" ), menuScale );
        actionScaleWeek->setCheckable( true );
        actionScaleWeek->setChecked( grid->scale() == DateTimeGrid::ScaleWeek );
        actionScaleDay = new QAction( tr( "Day", "@item:inmenu" ), menuScale );
        actionScaleDay->setCheckable( true );
        actionScaleDay->setChecked( grid->scale() == DateTimeGrid::ScaleDay );
        actionScaleHour = new QAction( tr( "Hour", "@item:inmenu" ), menuScale );
        actionScaleHour->setCheckable( true );
        actionScaleHour->setChecked( grid->scale() == DateTimeGrid::ScaleHour );

        scaleGroup->addAction( actionScaleAuto );
        menuScale->addAction( actionScaleAuto );

        scaleGroup->addAction( actionScaleMonth );
        menuScale->addAction( actionScaleMonth );

        scaleGroup->addAction( actionScaleWeek );
        menuScale->addAction( actionScaleWeek );

        scaleGroup->addAction( actionScaleDay );
        menuScale->addAction( actionScaleDay );

        scaleGroup->addAction( actionScaleHour );
        menuScale->addAction( actionScaleHour );

        contextMenu.addMenu( menuScale );

        contextMenu.addSeparator();

        actionZoomIn = new QAction( tr( "Zoom In", "@action:inmenu" ), &contextMenu );
        contextMenu.addAction( actionZoomIn );
        actionZoomOut = new QAction( tr( "Zoom Out", "@action:inmenu" ), &contextMenu );
        contextMenu.addAction( actionZoomOut );

        contextMenu.addSeparator();
        actionTimeline = new QAction( tr( "Timeline...", "@action:inmenu" ), &contextMenu );
        contextMenu.addAction( actionTimeline );
    }

    if ( contextMenu.isEmpty() )
    {
        event->ignore();
        return;
    }

    const QAction* const action = contextMenu.exec( event->globalPos() );
    if ( action == nullptr ) {}
    else if ( action == actionScaleAuto )
    {
        assert( grid != nullptr );
        grid->setScale( DateTimeGrid::ScaleAuto );
    }
    else if ( action == actionScaleMonth )
    {
        assert( grid != nullptr );
        grid->setScale( DateTimeGrid::ScaleMonth );
    }
    else if ( action == actionScaleWeek )
    {
        assert( grid != nullptr );
        grid->setScale( DateTimeGrid::ScaleWeek );
    }
    else if ( action == actionScaleDay )
    {
        assert( grid != nullptr );
        grid->setScale( DateTimeGrid::ScaleDay );
    }
    else if ( action == actionScaleHour )
    {
        assert( grid != nullptr );
        grid->setScale( DateTimeGrid::ScaleHour );
    }
    else if ( action == actionZoomIn )
    {
        assert( grid != nullptr );
        grid->setDayWidth( grid->dayWidth() * 1.25 );
    }
    else if ( action == actionZoomOut )
    {
        assert( grid != nullptr );
        // daywidth *MUST NOT* go below 1.0, it is used as an integer later on
        grid->setDayWidth( qMax<qreal>( 1.0, grid->dayWidth() * 0.8 ) );
    }
    else if ( action == actionTimeline )
    {
        assert( grid != nullptr );
        DateTimeTimeLineDialog dlg(grid->timeLine());
        dlg.exec();
    }
    event->accept();
}

GraphicsView::Private::Private( GraphicsView* _q )
  : q( _q ), rowcontroller(nullptr), headerwidget( _q )
{
}

GraphicsView::Private::~Private()
{
}

void GraphicsView::Private::updateHeaderGeometry()
{
    q->setViewportMargins(0,rowcontroller->headerHeight(),0,0);
    headerwidget.setGeometry( q->viewport()->x(),
                              q->viewport()->y() - rowcontroller->headerHeight(),
                              q->viewport()->width(),
                              rowcontroller->headerHeight() );
}

void GraphicsView::Private::slotGridChanged()
{
    updateHeaderGeometry();
    headerwidget.update();
    q->updateSceneRect();
    q->update();
}

void GraphicsView::Private::slotHorizontalScrollValueChanged( int val )
{
    const QRectF viewRect = q->transform().mapRect( q->sceneRect() );
    headerwidget.scrollTo( val-q->horizontalScrollBar()->minimum()+static_cast<int>( viewRect.left() ) );
}

void GraphicsView::Private::slotColumnsInserted( const QModelIndex& parent,  int start, int end )
{
    Q_UNUSED( start );
    Q_UNUSED( end );
    QModelIndex idx = scene.model()->index( 0, 0, scene.summaryHandlingModel()->mapToSource( parent ) );
    do {
        scene.updateRow( scene.summaryHandlingModel()->mapFromSource( idx ) );
    } while ( ( idx = rowcontroller->indexBelow( idx ) ) != QModelIndex() && rowcontroller->isRowVisible( idx ) );
        //} while ( ( idx = d->treeview.indexBelow( idx ) ) != QModelIndex() && d->treeview.visualRect(idx).isValid() );
     q->updateSceneRect();
}

void GraphicsView::Private::slotColumnsRemoved( const QModelIndex& parent,  int start, int end )
{
    // TODO
    Q_UNUSED( start );
    Q_UNUSED( end );
    Q_UNUSED( parent );
    q->updateScene();
}

void GraphicsView::Private::slotDataChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight )
{
    //qDebug() << "GraphicsView::slotDataChanged("<<topLeft<<bottomRight<<")";
    const QModelIndex parent = topLeft.parent();
    for ( int row = topLeft.row(); row <= bottomRight.row(); ++row ) {
        scene.updateRow( scene.summaryHandlingModel()->index( row, 0, parent ) );
    }
}

void GraphicsView::Private::slotLayoutChanged()
{
    //qDebug() << "slotLayoutChanged()";
    q->updateScene();
}

void GraphicsView::Private::slotModelReset()
{
    //qDebug() << "slotModelReset()";
    q->updateScene();
}

void GraphicsView::Private::slotRowsInserted( const QModelIndex& parent,  int start, int end )
{
    Q_UNUSED( parent );
    Q_UNUSED( start );
    Q_UNUSED( end );
    q->updateScene(); // TODO: This might be optimised
}

void GraphicsView::Private::removeConstraintsRecursive( QAbstractProxyModel *summaryModel, const QModelIndex& index )
{
    if ( summaryModel->hasChildren( index ) ) {
        //qDebug() << "removing constraints from children of"<<index;
        for ( int row = 0; row < summaryModel->rowCount( index ); ++row ) {
            const QModelIndex child = summaryModel->index( row, index.column(), index );
            removeConstraintsRecursive( summaryModel, child );
        }
    }
    //qDebug() << "removing constraints from"<<index;
    // NOTE: Constraints are mapped to indexes in the summaryModel->sourceModel()
    const QList<Constraint> clst = scene.constraintModel()->constraintsForIndex( summaryModel->mapToSource( index ) );
    for ( const Constraint &c : clst ) {
        scene.constraintModel()->removeConstraint( c );
    }
}

void GraphicsView::Private::slotRowsAboutToBeRemoved( const QModelIndex& parent,  int start, int end )
{
    //qDebug() << "GraphicsView::Private::slotRowsAboutToBeRemoved("<<parent<<start<<end<<")";
    QAbstractProxyModel *summaryModel = scene.summaryHandlingModel();
    for ( int row = start; row <= end; ++row ) {
        for ( int col = 0; col < summaryModel->columnCount( parent ); ++col ) {
            const QModelIndex idx = summaryModel->index( row, col, parent );
            removeConstraintsRecursive( summaryModel, idx );
            scene.removeItem( idx );
        }
    }
}

void GraphicsView::Private::slotRowsRemoved( const QModelIndex& parent,  int start, int end )
{
    //qDebug() << "GraphicsView::Private::slotRowsRemoved("<<parent<<start<<end<<")";
    // TODO
    Q_UNUSED( parent );
    Q_UNUSED( start );
    Q_UNUSED( end );

    q->updateScene();
}

void GraphicsView::Private::slotItemClicked( const QModelIndex& idx )
{
    QModelIndex sidx = idx;//scene.summaryHandlingModel()->mapToSource( idx );
    Q_EMIT q->clicked( sidx );
    if (q->style()->styleHint(QStyle::SH_ItemView_ActivateItemOnSingleClick, nullptr, q))
        Q_EMIT q->activated( sidx );
}

void GraphicsView::Private::slotItemDoubleClicked( const QModelIndex& idx )
{
    QModelIndex sidx = idx;//scene.summaryHandlingModel()->mapToSource( idx );
    Q_EMIT q->qrealClicked( sidx );
    if (!q->style()->styleHint(QStyle::SH_ItemView_ActivateItemOnSingleClick, nullptr, q))
        Q_EMIT q->activated( sidx );
}

void GraphicsView::Private::slotHeaderContextMenuRequested( const QPoint& pt )
{
    Q_EMIT q->headerContextMenuRequested( headerwidget.mapToGlobal( pt ) );
}

GraphicsView::GraphicsView( QWidget* parent )
    : QGraphicsView( parent ), _d( new Private( this ) )
{
#if defined KDAB_EVAL
  EvalDialog::checkEvalLicense( "KD Gantt" );
#endif
    connect( horizontalScrollBar(), SIGNAL(valueChanged(int)),
             this, SLOT(slotHorizontalScrollValueChanged(int)) );
    connect( &_d->scene, SIGNAL(gridChanged()),
             this, SLOT(slotGridChanged()) );
    connect( &_d->scene, SIGNAL(entered(QModelIndex)),
             this, SIGNAL(entered(QModelIndex)) );
    connect( &_d->scene, SIGNAL(pressed(QModelIndex)),
             this, SIGNAL(pressed(QModelIndex)) );
    connect( &_d->scene, SIGNAL(clicked(QModelIndex)),
             this, SLOT(slotItemClicked(QModelIndex)) );
    connect( &_d->scene, SIGNAL(qrealClicked(QModelIndex)),
             this, SLOT(slotItemDoubleClicked(QModelIndex)) );
    connect( &_d->scene, SIGNAL(sceneRectChanged(QRectF)),
             this, SLOT(updateSceneRect()) );
    connect( &_d->headerwidget, SIGNAL(customContextMenuRequested(QPoint)),
             this, SLOT(slotHeaderContextMenuRequested(QPoint)) );
    setScene( &_d->scene );

    // HACK!
    setSummaryHandlingModel( _d->scene.summaryHandlingModel() );

    // So that AbstractGrid::drawBackground() and AbstractGrid::drawForeground()
    // works properly
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    //setCacheMode( CacheBackground );
}


GraphicsView::~GraphicsView()
{
    delete _d;
}

#define d d_func()


void GraphicsView::setModel( QAbstractItemModel* model )
{
    if ( d->scene.model() ) {
        disconnect( d->scene.model() );
    }

    d->scene.setModel( model );
    if (model) {
        connect( model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                this, SLOT(updateSceneRect()) );
    }
    updateScene();
}


QAbstractItemModel* GraphicsView::model() const
{
    return d->scene.model();
}

void GraphicsView::setSummaryHandlingModel( QAbstractProxyModel* proxyModel )
{
    disconnect( d->scene.summaryHandlingModel() );
    d->scene.setSummaryHandlingModel( proxyModel );

    /* Connections. We have to rely on the treeview
     * to receive the signals before we do(!)
     */
    connect( proxyModel, SIGNAL(columnsInserted(QModelIndex,int,int)),
             this,  SLOT(slotColumnsInserted(QModelIndex,int,int)) );
    connect( proxyModel, SIGNAL(columnsRemoved(QModelIndex,int,int)),
             this,  SLOT(slotColumnsRemoved(QModelIndex,int,int)) );
    connect( proxyModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
             this,  SLOT(slotDataChanged(QModelIndex,QModelIndex)) );
    connect( proxyModel, SIGNAL(layoutChanged()),
             this,  SLOT(slotLayoutChanged()) );
    connect( proxyModel, SIGNAL(modelReset()),
             this,  SLOT(slotModelReset()) );
    connect( proxyModel, SIGNAL(rowsInserted(QModelIndex,int,int)),
             this,  SLOT(slotRowsInserted(QModelIndex,int,int)) );
    connect( proxyModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
             this,  SLOT(slotRowsAboutToBeRemoved(QModelIndex,int,int)) );
    connect( proxyModel, SIGNAL(rowsRemoved(QModelIndex,int,int)),
             this,  SLOT(slotRowsRemoved(QModelIndex,int,int)) );

    updateScene();
}


void GraphicsView::setConstraintModel( ConstraintModel* cmodel )
{
    d->scene.setConstraintModel( cmodel );
}


ConstraintModel* GraphicsView::constraintModel() const
{
    return d->scene.constraintModel();
}


QAbstractProxyModel* GraphicsView::summaryHandlingModel() const
{
    return d->scene.summaryHandlingModel();
}


void GraphicsView::setRootIndex( const QModelIndex& idx )
{
    d->scene.setRootIndex( idx );
}


QModelIndex GraphicsView::rootIndex() const
{
    return d->scene.rootIndex();
}


void GraphicsView::setSelectionModel( QItemSelectionModel* model )
{
    d->scene.setSelectionModel( model );
}


QItemSelectionModel* GraphicsView::selectionModel() const
{
    return d->scene.selectionModel();
}


void GraphicsView::setItemDelegate( ItemDelegate* delegate )
{
    d->scene.setItemDelegate( delegate );
}


ItemDelegate* GraphicsView::itemDelegate() const
{
    return d->scene.itemDelegate();
}


void GraphicsView::setRowController( AbstractRowController* rowcontroller )
{
    d->rowcontroller = rowcontroller;
    d->scene.setRowController( rowcontroller );
    updateScene();
}


AbstractRowController* GraphicsView::rowController() const
{
    return d->rowcontroller;
}


void GraphicsView::setGrid( AbstractGrid* grid )
{
    d->scene.setGrid( grid );
    d->slotGridChanged();
}


AbstractGrid* GraphicsView::grid() const
{
    return d->scene.grid();
}


AbstractGrid* GraphicsView::takeGrid()
{
    return d->scene.takeGrid();
}


void GraphicsView::setReadOnly( bool ro )
{
    d->scene.setReadOnly( ro );
}


bool GraphicsView::isReadOnly() const
{
    return d->scene.isReadOnly();
}


void GraphicsView::setHeaderContextMenuPolicy( Qt::ContextMenuPolicy p )
{
    d->headerwidget.setContextMenuPolicy( p );
}


Qt::ContextMenuPolicy GraphicsView::headerContextMenuPolicy() const
{
    return d->headerwidget.contextMenuPolicy();
}


void GraphicsView::addConstraint( const QModelIndex& from,
                                  const QModelIndex& to,
                                  Qt::KeyboardModifiers modifiers )
{
    if ( isReadOnly() ) return;
    ConstraintModel* cmodel = constraintModel();
    assert( cmodel );
    Constraint c( from, to, ( modifiers&Qt::ShiftModifier )?Constraint::TypeHard:Constraint::TypeSoft );
    if ( cmodel->hasConstraint( c ) ) cmodel->removeConstraint( c );
    else cmodel->addConstraint( c );
}

void GraphicsView::resizeEvent( QResizeEvent* ev )
{
    d->updateHeaderGeometry();
    QRectF r = scene()->itemsBoundingRect();
    // To scroll more to the left than the actual item start, bug #4516
    r.setLeft( qMin<qreal>( 0.0, r.left() ) );
    // TODO: take scrollbars into account (if not always on)
    // The scene should be at least the size of the viewport
    QSizeF size = viewport()->size();
    //TODO: why -2 below? size should be ex. frames etc?
    if ( size.width() > r.width() ) {
        r.setWidth( size.width() - 2 );
    }
    if ( size.height() > r.height() ) {
        r.setHeight( size.height() - 2 );
    }
    const int totalh = rowController()->totalHeight();
    if ( r.height() < totalh ) {
        r.setHeight( totalh );
    }

    scene()->setSceneRect( r );

    QGraphicsView::resizeEvent( ev );
}


QModelIndex GraphicsView::indexAt( const QPoint& pos ) const
{
    QGraphicsItem* item = itemAt( pos );
    if ( GraphicsItem* gitem = qgraphicsitem_cast<GraphicsItem*>( item ) ) {
        return d->scene.summaryHandlingModel()->mapToSource( gitem->index() );
    } else {
        return QModelIndex();
    }
}


void GraphicsView::clearItems()
{
    d->scene.clearItems();
}


void GraphicsView::updateRow( const QModelIndex& idx )
{
    d->scene.updateRow( d->scene.summaryHandlingModel()->mapFromSource( idx ) );
}


void GraphicsView::updateSceneRect()
{
    /* What to do with this? We need to shrink the view to
     * make collapsing items work
     */
    qreal range = horizontalScrollBar()->maximum()-horizontalScrollBar()->minimum();
    const qreal hscroll = horizontalScrollBar()->value()/( range>0?range:1 );
    QRectF r = d->scene.itemsBoundingRect();
    // To scroll more to the left than the actual item start, bug #4516
    r.setTop( 0. );
    r.setLeft( qMin<qreal>( 0.0, r.left() ) );
    r.setSize( r.size().expandedTo( viewport()->size() ) );
    const int totalh = rowController()->totalHeight();
    if ( r.height() < totalh ) r.setHeight( totalh );
    d->scene.setSceneRect( r );

    /* set scrollbar to keep the same time in view */
    range = horizontalScrollBar()->maximum()-horizontalScrollBar()->minimum();
    if ( range>0 ) {
        horizontalScrollBar()->setValue( qRound( hscroll*range ) );
    } else {
        // keep header in sync with scene
        d->headerwidget.scrollTo(r.left());
    }
    /* We have to update here to adjust for any rows with no
     * information because they are painted with a different
     * background brush
     */
    d->scene.invalidate( QRectF(), QGraphicsScene::BackgroundLayer );
}


void GraphicsView::updateScene()
{
    clearItems();
    if ( !model()) return;
    if ( !rowController()) return;
    QModelIndex idx = model()->index( 0, 0, rootIndex() );
    do {
        updateRow( idx );
    } while ( ( idx = rowController()->indexBelow( idx ) ) != QModelIndex() && rowController()->isRowVisible(idx) );
    //constraintModel()->cleanup();
    //qDebug() << constraintModel();
    updateSceneRect();
    if ( scene() ) scene()->invalidate( QRectF(), QGraphicsScene::BackgroundLayer );
}

#if 0
TODO: For 3.0

GraphicsItem* GraphicsView::createItem( ItemType type ) const
{
    Q_UNUSED(type)
    return new GraphicsItem;
}
#endif


void GraphicsView::deleteSubtree( const QModelIndex& idx )
{
    d->scene.deleteSubtree( d->scene.summaryHandlingModel()->mapFromSource( idx ) );
}


void GraphicsView::print( QPrinter* printer, bool drawRowLabels, bool drawColumnLabels )
{
    d->scene.print( printer, drawRowLabels, drawColumnLabels );
}


void GraphicsView::print( QPrinter* printer,  qreal start, qreal end, bool drawRowLabels, bool drawColumnLabels )
{
    d->scene.print( printer, start, end, drawRowLabels, drawColumnLabels );
}


void GraphicsView::print( QPainter* painter, const QRectF& targetRect, bool drawRowLabels, bool drawColumnLabels )
{
  d->scene.print(painter, targetRect, drawRowLabels, drawColumnLabels);
}


void GraphicsView::print( QPainter* painter, qreal start, qreal end,
                          const QRectF& targetRect, bool drawRowLabels, bool drawColumnLabels )
{
  d->scene.print(painter, start, end, targetRect, drawRowLabels, drawColumnLabels);
}

void GraphicsView::printDiagram( QPrinter *printer, const PrintingContext &context )
{
    d->scene.printDiagram( printer, context );
}

#include "moc_kganttgraphicsview.cpp"
