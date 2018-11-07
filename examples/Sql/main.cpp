/**
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KD Chart library.
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

#include <QAbstractProxyModel>

#include <QApplication>

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <KChartChart>
#include <KChartBarDiagram>
#include <KChartHeaderFooter>
#include <KChartPosition>
#include <KChartBackgroundAttributes>
#include <KChartFrameAttributes>

#include <QPixmap>

using namespace KChart;

/**
 * Proxymodel that transposes columns and rows.
 */
class TransposeProxyModel : public QAbstractProxyModel{
public:
  explicit TransposeProxyModel(QObject* parent = nullptr) : QAbstractProxyModel(parent) {}
  virtual ~TransposeProxyModel() {}
  QModelIndex mapFromSource ( const QModelIndex & sourceIndex ) const Q_DECL_OVERRIDE { return index(sourceIndex.column(), sourceIndex.row()); }
  QModelIndex mapToSource ( const QModelIndex & proxyIndex ) const Q_DECL_OVERRIDE { return sourceModel()->index(proxyIndex.column(), proxyIndex.row()); }
  QModelIndex index(int r, int c, const QModelIndex &ind=QModelIndex()) const Q_DECL_OVERRIDE { Q_UNUSED(ind) return createIndex(r,c); }
  QModelIndex parent(const QModelIndex&) const Q_DECL_OVERRIDE { return QModelIndex(); }
  int rowCount(const QModelIndex &) const Q_DECL_OVERRIDE { return sourceModel()->columnCount(); }
  int columnCount(const QModelIndex &) const Q_DECL_OVERRIDE { return sourceModel()->rowCount(); }
  QVariant data(const QModelIndex &ind, int role) const Q_DECL_OVERRIDE { return sourceModel()->data(mapToSource(ind), role); }
};

/**
 * The example that creates the SQL-model, adds data to it and display the data in a model.
 */
class ChartWidget : public QWidget {
  Q_OBJECT
public:
  explicit ChartWidget(QWidget* parent = nullptr)
    : QWidget(parent)
    , m_model(nullptr)
  {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName(":memory:"); // in memory rather then in a file
    //db.setUserName("");
    //db.setPassword("");
    bool ok = db.open();
    Q_ASSERT(ok);
    Q_UNUSED(ok) // release mode

    QSqlQuery createTableQuery = db.exec("CREATE TABLE IF NOT EXISTS MyTable (col1 INT NOT NULL PRIMARY KEY, col2 INT);");
    Q_ASSERT(!createTableQuery.lastError().isValid());

    m_model = new QSqlTableModel(this, db);
    m_model->setTable("MyTable");
    m_model->setEditStrategy(QSqlTableModel::OnRowChange);
    m_model->setSort(0, Qt::AscendingOrder);

    ok = m_model->select();
    Q_ASSERT(ok);

    m_model->setHeaderData(0, Qt::Horizontal, tr("Column 1"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("Column 2"));

    for (int row = 0; row < 3; ++row) {
        QSqlRecord rec;
        for (int column = 0; column < 2; ++column) {
            QSqlField field(column==0?"col1":"col2",QVariant::Int);
            field.setValue(row+1 * column);
            rec.append(field);
        }
        ok = m_model->insertRecord(-1, rec);
        Q_ASSERT(ok);
    }

    BarDiagram* diagram = new BarDiagram;

    TransposeProxyModel* proxymodel = new TransposeProxyModel(this);
    proxymodel->setSourceModel(m_model);
    diagram->setModel(proxymodel);

    m_chart.coordinatePlane()->replaceDiagram(diagram);

    // Add at one Header and set it up
    HeaderFooter* header = new HeaderFooter( &m_chart );
    header->setPosition( Position::North );
    header->setText( "A Simple Bar Chart" );
    m_chart.addHeaderFooter( header );

    // Configure the plane Frame attributes
    FrameAttributes pfa;
    pfa.setPen( QPen ( QBrush( Qt::blue ), 2 ) );
    pfa.setVisible( true );
    diagram->coordinatePlane()->setFrameAttributes(  pfa );

    // Configure the header Frame attributes
    FrameAttributes hfa;
    hfa.setPen( QPen ( QBrush( Qt::darkGray ), 2 ) );
    hfa.setPadding( 2 );
    hfa.setVisible( true );
    header->setFrameAttributes(  hfa );

    QVBoxLayout* l = new QVBoxLayout(this);
    l->addWidget(&m_chart);
    setLayout(l);
  }

private:
  Chart m_chart;
  QSqlTableModel *m_model;
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    ChartWidget w;
    w.show();

    return app.exec();
}

#include "main.moc"
