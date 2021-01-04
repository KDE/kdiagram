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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include "../common/projectmodel.h"

#include <QAction>
#include <QApplication>
#include <QComboBox>
#include <QMenuBar>
#include <QMenu>
#include <QModelIndex>
#include <QItemSelectionModel>
#include <QTreeView>
#include <QDebug>
#include <QBrush>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QFileDialog>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileInfo>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDialogButtonBox>

#include <KGanttGlobal>
#include <KGanttView>
#include <KGanttItemDelegate>
#include <KGanttDateTimeGrid>
#include <KGanttStyleOptionGanttItem>
#include <KGanttConstraintModel>
#include <KGanttGraphicsView>
#include <KGanttDateTimeTimeLine>

// Define a printer friendly palette
#define VeryLightGray   "#f8f8f8"
#define LightLightGray  "#f0f0f0"
#define DarkDarkGray    "#b3b3b3"
#define VeryDarkGray    "#838383"
class PrintPalette {
public:
    PrintPalette() {
        orig = QApplication::palette();
        QPalette palette = orig;
        // define a palette that works when printing on white paper
        palette.setColor(QPalette::Window, Qt::white);
        palette.setColor(QPalette::WindowText, Qt::black);
        palette.setColor(QPalette::Base, Qt::white);
        palette.setColor(QPalette::AlternateBase, VeryLightGray);
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::black);
        palette.setColor(QPalette::Text, Qt::black);
        palette.setColor(QPalette::Button, Qt::lightGray);
        palette.setColor(QPalette::ButtonText, Qt::black);
        palette.setColor(QPalette::BrightText, Qt::white);
        palette.setColor(QPalette::Link, Qt::blue);
        palette.setColor(QPalette::Highlight, Qt::blue);
        palette.setColor(QPalette::HighlightedText, Qt::white);
        palette.setColor(QPalette::Light, QColor(VeryLightGray));
        palette.setColor(QPalette::Midlight, QColor(LightLightGray));
        palette.setColor(QPalette::Dark, QColor(DarkDarkGray));
        palette.setColor(QPalette::Mid, QColor(VeryDarkGray));
        palette.setColor(QPalette::Shadow, Qt::black);
        QApplication::setPalette(palette);
    }
    ~PrintPalette() {
        QApplication::setPalette(orig);
    }
    QPalette orig;
};


class ItemTypeComboBox : public QComboBox {
    Q_OBJECT
    Q_PROPERTY( KGantt::ItemType itemType READ itemType WRITE setItemType )
public:
    explicit ItemTypeComboBox( QWidget* parent = nullptr );

    KGantt::ItemType itemType() const;
public Q_SLOTS:
    void setItemType( KGantt::ItemType typ );
};

ItemTypeComboBox::ItemTypeComboBox( QWidget* parent )
    : QComboBox( parent )
{
    addItem( tr( "Task" ), QVariant( KGantt::TypeTask ) );
    addItem( tr( "Event" ), QVariant( KGantt::TypeEvent ) );
    addItem( tr( "Summary" ), QVariant( KGantt::TypeSummary ) );
}

KGantt::ItemType ItemTypeComboBox::itemType() const
{
    return static_cast<KGantt::ItemType>( itemData( currentIndex() ).toInt() );
}

void ItemTypeComboBox::setItemType( KGantt::ItemType typ )
{
    setCurrentIndex( typ-1 );
}

class MyItemDelegate : public KGantt::ItemDelegate {
public:
    explicit MyItemDelegate( QObject* parent = nullptr );

    /*reimp*/ QWidget* createEditor( QWidget* parent,
                                     const QStyleOptionViewItem& option,
                                     const QModelIndex& idx ) const override;
    /*reimp*/ void setEditorData( QWidget* editor, const QModelIndex& index ) const override;
    /*reimp*/ void setModelData( QWidget* editor, QAbstractItemModel* model,
                                  const QModelIndex & index ) const override;
};

MyItemDelegate::MyItemDelegate( QObject* parent )
    : KGantt::ItemDelegate( parent )
{
}

QWidget* MyItemDelegate::createEditor( QWidget* parent,
                                       const QStyleOptionViewItem& option,
                                       const QModelIndex& idx ) const
{
    qDebug() << "MyItemDelegate::createEditor("<<parent<<idx<<")";
    if ( idx.isValid() && idx.column() == 1 )
      return new ItemTypeComboBox(parent);
    return ItemDelegate::createEditor( parent, option, idx );
}

void MyItemDelegate::setEditorData ( QWidget* editor, const QModelIndex& index ) const
{
  ItemTypeComboBox* c;
  if ( (c = qobject_cast<ItemTypeComboBox*>(editor)) && index.isValid() ) {
      c->setItemType(static_cast<KGantt::ItemType>(index.data(Qt::EditRole).toInt()));
  } else {
      ItemDelegate::setEditorData(editor,index);
  }
}

void MyItemDelegate::setModelData ( QWidget* editor, QAbstractItemModel* model,
                                  const QModelIndex & index ) const
{
  ItemTypeComboBox* c;
  if ( (c = qobject_cast<ItemTypeComboBox*>(editor)) && index.isValid() ) {
      model->setData(index,c->itemType());
  } else {
      ItemDelegate::setModelData(editor,model,index);
  }
}

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent ),
      m_model( new ProjectModel( this ) ),
      m_view( new KGantt::View )
{
    m_view->setModel( m_model );

    m_view->leftView()->setItemDelegateForColumn( 1, new MyItemDelegate( this ) );

    KGantt::DateTimeGrid *grid = new KGantt::DateTimeGrid();
    grid->timeLine()->setPen(QPen(Qt::red));
    grid->timeLine()->setOptions(KGantt::DateTimeTimeLine::UseCustomPen);
    grid->timeLine()->setInterval(5000);
    grid->setRowSeparators(true);
    m_view->setGrid(grid);


    setCentralWidget( m_view );

    QMenuBar* mb = menuBar();

    QMenu* fileMenu = new QMenu( tr( "&File" ) );

#ifndef QT_NO_PRINTER
    fileMenu->addAction( tr( "&Save as PDF..." ), this, SLOT(slotFileSavePdf()) );
    fileMenu->addAction( tr( "&Print Preview..." ), this, SLOT(slotFilePrintPreview()) );
    fileMenu->addAction( tr( "&Print..." ), this, SLOT(slotFilePrint()) );
#endif

    fileMenu->addSeparator();
    fileMenu->addAction( tr( "&Quit" ), this, SLOT(slotFileQuit()) );

    mb->addMenu( fileMenu );

    QMenu* toolsMenu = new QMenu( tr( "&Tools" ) );

    toolsMenu->addAction( tr( "&New Item" ), this, SLOT(slotToolsNewItem()) );
    toolsMenu->addAction( tr( "&Add Item" ), this, SLOT(slotToolsAppendItem()) );
    toolsMenu->addSeparator();
    QMenu *alignMenu = toolsMenu->addMenu( tr( "Ali&gn" ) );
    alignMenu->addAction( tr( "&Left" ), this, SLOT(slotAlignLeft()) );
    alignMenu->addAction( tr( "&Center" ), this, SLOT(slotAlignCenter()) );
    alignMenu->addAction( tr( "&Right" ), this, SLOT(slotAlignRight()) );
    alignMenu->addAction( tr( "&Hidden" ), this, SLOT(slotAlignHidden()) );
    toolsMenu->addSeparator();
    toolsMenu->addAction( tr( "&Collapse All" ), this, SLOT(slotCollapseAll()) );
    toolsMenu->addAction( tr( "&Expand All" ), this, SLOT(slotExpandAll()) );

    mb->addMenu( toolsMenu );

    // define some items with different properties
    slotToolsAppendItem();
    slotToolsAppendItem();
    slotToolsAppendItem();
    for (int i = 0; i < 3; ++i) {
        m_model->setData(m_model->index(i,2,QModelIndex()), QVariant::fromValue(QDateTime::currentDateTime().addDays(i)), KGantt::StartTimeRole);
        m_model->setData(m_model->index(i,3,QModelIndex()), QVariant::fromValue(QDateTime::currentDateTime().addDays(i+1)), KGantt::EndTimeRole);
    }
    slotToolsAppendItem();
    m_model->setData(m_model->index(3,2,QModelIndex()), QVariant::fromValue(QDateTime::currentDateTime()), KGantt::StartTimeRole);
    m_model->setData(m_model->index(3,3,QModelIndex()), QVariant::fromValue(QDateTime::currentDateTime().addDays(1)), KGantt::EndTimeRole);
    m_model->setData(m_model->index(3,4,QModelIndex()), QVariant::fromValue(50), KGantt::TaskCompletionRole);

    m_view->setConstraintModel(new KGantt::ConstraintModel(m_view));
    m_view->constraintModel()->addConstraint(KGantt::Constraint(m_model->index(0,0,QModelIndex()),m_model->index(1,0,QModelIndex())));
    m_view->constraintModel()->addConstraint(KGantt::Constraint(m_model->index(1,0,QModelIndex()),m_model->index(2,0,QModelIndex())));
    // invalid contraint
    m_view->constraintModel()->addConstraint(KGantt::Constraint(m_model->index(2,0,QModelIndex()),m_model->index(3,0,QModelIndex())));

    // no info
    slotToolsAppendItem();
    m_model->setData(m_model->index(4,2,QModelIndex()), QVariant::fromValue(QDateTime()), KGantt::StartTimeRole);
    m_model->setData(m_model->index(4,3,QModelIndex()), QVariant::fromValue(QDateTime()), KGantt::EndTimeRole);
}

SavePdfDialog::SavePdfDialog(QWidget *parent)
    : QDialog(parent)
{
    setModal(true);
    setWindowTitle(tr("Save as PDF"));
    QVBoxLayout *l = new QVBoxLayout(this);
    setLayout(l);

    QHBoxLayout *fileLayout = new QHBoxLayout(this);
    l->addLayout(fileLayout);
    QLabel *fileLabel = new QLabel(tr("File:"), this);
    fileLayout->addWidget(fileLabel);
    m_fileEdit = new QLineEdit(this);
    fileLabel->setBuddy(m_fileEdit);
    m_fileEdit->setText(QFileInfo(QDir::homePath(), "gantt.pdf").absoluteFilePath());
    fileLayout->addWidget(m_fileEdit);
    QPushButton *m_fileButton = new QPushButton("...", this);
    connect(m_fileButton, SIGNAL(clicked()), this, SLOT(fileButtonClicked()));
    fileLayout->addWidget(m_fileButton);

    m_rowLabels = new QCheckBox(tr("Row Header"), this);
    m_rowLabels->setChecked(true);
    l->addWidget(m_rowLabels);

    m_columnLabels = new QCheckBox(tr("Column Header"), this);
    m_columnLabels->setChecked(true);
    l->addWidget(m_columnLabels);

    QDialogButtonBox *btnBox = new QDialogButtonBox(this);
    btnBox->setStandardButtons(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    connect(btnBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));
    l->addWidget(btnBox);

    resize(QSize(400, 100).expandedTo(minimumSizeHint()));
}

void SavePdfDialog::fileButtonClicked()
{
    const QString file = QFileDialog::getSaveFileName(this, tr("Choose PDF File..."), QString(), tr("PDF files (*.pdf)"));
    if (!file.isEmpty())
        m_fileEdit->setText(file);
}

void MainWindow::slotFileSavePdf()
{
#ifndef QT_NO_PRINTER
    SavePdfDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;

    const QString file = dialog.m_fileEdit->text();
    if (file.isEmpty())
        return;

    const bool drawRowLabels = dialog.m_rowLabels->isChecked();
    const bool drawColumnLabels = dialog.m_columnLabels->isChecked();

    QPrinter printer(QPrinter::HighResolution);
    printer.setOrientation(QPrinter::Landscape);
    printer.setColorMode(QPrinter::Color);
    printer.setPageMargins(0.2, 0.2, 0.2, 0.2, QPrinter::Point);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file);
    PrintPalette p;
    m_view->print(&printer, drawRowLabels, drawColumnLabels);
#endif
}

void MainWindow::slotFilePrint()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    printer.setOrientation(QPrinter::Landscape);
    printer.setColorMode(QPrinter::Color);
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() != QDialog::Accepted) {
        return;
    }
    PrintPalette p;
    m_view->print(&printer);
#endif
}

void MainWindow::slotFilePrintPreview()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOrientation(QPrinter::Landscape);
    printer.setColorMode(QPrinter::Color);
    QPrintPreviewDialog preview(&printer);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(slotPrintPreviewPaintRequest(QPrinter*)));
    preview.exec();
}

void MainWindow::slotPrintPreviewPaintRequest(QPrinter *printer)
{
    PrintPalette p;
    m_view->print(printer);
}

void MainWindow::slotFileQuit()
{
    // TODO
    QApplication::instance()->quit();
}

void MainWindow::slotToolsNewItem()
{
    QModelIndex idx = m_view->selectionModel()->currentIndex();
    if ( idx.isValid() ) {
        qDebug() << "MainWindow::slotToolsNewItem" << idx;
        m_model->insertRows( 0, 1, m_model->index( idx.row(),0,idx.parent() ) );
    } else {
        m_model->insertRows( 0, 1, m_view->rootIndex() );
    }
}

void MainWindow::slotToolsAppendItem()
{
    QModelIndex idx = m_view->selectionModel()->currentIndex();
    if ( idx.isValid() ) {
        qDebug() << "MainWindow::slotToolsAppendItem" << idx;
        m_model->insertRows( m_model->rowCount( idx ), 1, m_model->index( idx.row(),0,idx.parent() ) );
    } else {
        m_model->insertRows( m_model->rowCount( m_view->rootIndex() ), 1, m_view->rootIndex() );
    }
}

void MainWindow::slotCollapseAll()
{
    // don't use the treeview's collapseAll/expandAll methods but use the one provided by the
    // view cause that one will take care to update everyt6hing as needed.
    //QTreeView* view = qobject_cast<QTreeView*>( m_view->leftView() );
    //view->collapseAll();

    QModelIndex idx = m_view->selectionModel()->currentIndex();
    if ( idx.isValid() )
        m_view->collapseAll();
}

void MainWindow::slotExpandAll()
{
    // don't use the treeview's collapseAll/expandAll methods but use the one provided by the
    // view cause that one will take care to update everyt6hing as needed.
    //QTreeView* view = qobject_cast<QTreeView*>( m_view->leftView() );
    //view->expandAll();

    QModelIndex idx = m_view->selectionModel()->currentIndex();
    if ( idx.isValid() )
        m_view->expandAll();
}

void MainWindow::slotAlignLeft()
{
    QModelIndex idx = m_view->selectionModel()->currentIndex();
    if ( idx.isValid() ) {
        m_model->setData( idx, KGantt::StyleOptionGanttItem::Left, KGantt::TextPositionRole );
    }
}

void MainWindow::slotAlignCenter()
{
    QModelIndex idx = m_view->selectionModel()->currentIndex();
    if ( idx.isValid() ) {
        m_model->setData( idx, KGantt::StyleOptionGanttItem::Center, KGantt::TextPositionRole );
    }
}

void MainWindow::slotAlignRight()
{
    QModelIndex idx = m_view->selectionModel()->currentIndex();
    if ( idx.isValid() ) {
        m_model->setData( idx, KGantt::StyleOptionGanttItem::Right, KGantt::TextPositionRole );
    }
}

void MainWindow::slotAlignHidden()
{
    QModelIndex idx = m_view->selectionModel()->currentIndex();
    if ( idx.isValid() ) {
        m_model->setData( idx, KGantt::StyleOptionGanttItem::Hidden, KGantt::TextPositionRole );
    }
}

#include "mainwindow.moc"
