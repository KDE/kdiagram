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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

class QLineEdit;
class QCheckBox;

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
private slots:
    void fileButtonClicked();
};
        
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow( QWidget* parent = nullptr );

private slots:
    void slotFileSavePdf();
    void slotFilePrint();
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

