/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

class QLineEdit;
class QCheckBox;
class QPrinter;

namespace KGantt {
    class View;
}

class ProjectModel;

class SavePdfDialog : public QDialog
{
    Q_OBJECT
public:
    QLineEdit *m_fileEdit;
    QCheckBox *m_rowLabels;
    QCheckBox *m_columnLabels;
    SavePdfDialog(QWidget *parent = nullptr);
private Q_SLOTS:
    void fileButtonClicked();
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow( QWidget* parent = nullptr );

private Q_SLOTS:
    void slotFileSavePdf();
    void slotFilePrint();
    void slotFilePrintPreview();
    void slotPrintPreviewPaintRequest(QPrinter *printer);
    void slotFileQuit();
    void slotToolsNewItem();
    void slotToolsAppendItem();
    void slotCollapseAll();
    void slotExpandAll();

    void slotAlignLeft();
    void slotAlignCenter();
    void slotAlignRight();
    void slotAlignHidden();
    
private:
    ProjectModel* m_model;
    KGantt::View* m_view;
};
#endif /* MAINWINDOW_H */

