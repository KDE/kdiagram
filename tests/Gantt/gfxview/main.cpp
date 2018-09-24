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

#include <QApplication>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QPushButton>
#include <QPointer>

#include <stdlib.h>

#include <KGanttGraphicsView>
#include <KGanttAbstractRowController>
#include <KGanttStyleOptionGanttItem>

class MyRowController : public KGantt::AbstractRowController {
private:
    static const int ROW_HEIGHT;
    QPointer<QAbstractItemModel> m_model;
public:
    MyRowController()
    {
    }

    void setModel( QAbstractItemModel* model )
    {
        m_model = model;
    }

    /*reimp*/int headerHeight() const Q_DECL_OVERRIDE { return 40; }

    /*reimp*/ bool isRowVisible( const QModelIndex& ) const Q_DECL_OVERRIDE { return true;}
    /*reimp*/ bool isRowExpanded( const QModelIndex& ) const Q_DECL_OVERRIDE { return false; }
    /*reimp*/ KGantt::Span rowGeometry( const QModelIndex& idx ) const Q_DECL_OVERRIDE
    {
        qDebug() << "rowGeometry(" << idx.row()<<")";
        return KGantt::Span( idx.row()*ROW_HEIGHT, ROW_HEIGHT );
    }
    /*reimp*/ int maximumItemHeight() const Q_DECL_OVERRIDE {
        return ROW_HEIGHT/2;
    }
    /*reimp*/ int totalHeight() const Q_DECL_OVERRIDE {
        return m_model.isNull()?0:m_model->rowCount()*ROW_HEIGHT;
    }

    /*reimp*/ QModelIndex indexAt( int height ) const Q_DECL_OVERRIDE {
        return m_model->index( height/ROW_HEIGHT, 0 );
    }

    /*reimp*/ QModelIndex indexBelow( const QModelIndex& idx ) const Q_DECL_OVERRIDE {
        if ( !idx.isValid() )return QModelIndex();
        return idx.model()->index( idx.row()+1, idx.column(), idx.parent() );
    }
    /*reimp*/ QModelIndex indexAbove( const QModelIndex& idx ) const Q_DECL_OVERRIDE {
        if ( !idx.isValid() )return QModelIndex();
        return idx.model()->index( idx.row()-1, idx.column(), idx.parent() );
    }

};

const int MyRowController::ROW_HEIGHT = 30;

class MyStandardItemModel : public QStandardItemModel {
public:
    /*reimp*/bool setData( const QModelIndex& idx, const QVariant& value, int role ) Q_DECL_OVERRIDE
    {
        //qDebug() << "MyStandardItemModel::setData("<<idx<< value<<role<<")";
        return QStandardItemModel::setData( idx, value, role );
    }
};

static Qt::Alignment random_alignment()
{
    int r = (int) (3.0*rand()/(RAND_MAX+1.0));
    switch ( r ) {
    case 0: return Qt::AlignTop;
    case 1: return Qt::AlignBottom;
    case 2: return Qt::AlignCenter;
    }
    return Qt::Alignment();
}

static KGantt::StyleOptionGanttItem::Position random_position()
{
    int r = (int) (3.0*rand()/(RAND_MAX+1.0));
    switch ( r ) {
    case 0: return KGantt::StyleOptionGanttItem::Left;
    case 1: return KGantt::StyleOptionGanttItem::Right;
    case 2:
    default: return KGantt::StyleOptionGanttItem::Center;
    }
}

int main( int argc, char** argv ) {
    QApplication app( argc, argv );


    KGantt::GraphicsView* view = new KGantt::GraphicsView;
    MyRowController* rowController = new MyRowController;
    view->setReadOnly(true);
    view->setRowController( rowController );
    view->show();

    MyStandardItemModel model;
    for ( int i = 0; i < 10; ++i ) {
        QList<QStandardItem*> items;
        for ( int j = 0; j < 10; ++j ) {
            QStandardItem* item = new QStandardItem;
            //for ( int col = 0; col < 5; ++col ) {
            //  QStandardItem* colitem = new QStandardItem;
            item->setText( QString::fromLatin1( "Item %1" ).arg( i ) );
            item->setData( KGantt::TypeTask, KGantt::ItemTypeRole );
            item->setData( QDateTime::currentDateTime().addDays( 2*j ).addMSecs( 100000*i ), KGantt::StartTimeRole );
            item->setData( QDateTime::currentDateTime().addDays( 2*j+1 ).addMSecs( 100000*i ), KGantt::EndTimeRole );
            item->setData( qVariantFromValue<int>( random_alignment() ), Qt::TextAlignmentRole );
			item->setData( qVariantFromValue<int>( random_position()), KGantt::TextPositionRole );
            item->setFlags( item->flags() & ~Qt::ItemIsSelectable );
            //  item->appendColumn( QList<QStandardItem*>() << colitem );
            //}
            items.push_back( item );
        }
        model.appendRow( items );
    }
    qDebug() << &model;
    rowController->setModel( &model );
    view->setModel( &model );
#if 0
    QPushButton* pb = new QPushButton( QObject::tr( "Reset" ) );
    QObject::connect( pb, SIGNAL(clicked()),
                      &model, SIGNAL(modelReset()) );
    pb->show();
#endif
    return app.exec();
    //return 0;
}
