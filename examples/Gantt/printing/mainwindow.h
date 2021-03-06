/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef PRINTINGMAINWINDOW_H
#define PRINTINGMAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QDateTime>

#include <KGanttPrintingContext>

class QLineEdit;
class QCheckBox;
class QRadioButton;
class QPrinter;
class QDateTimeEdit;
class QLabel;
class QDoubleSpinBox;

namespace KGantt {
    class View;
}

class ProjectModel;

class SavePdfDialog : public QDialog
{
    Q_OBJECT
public:
    QLabel *m_fileLabel;
    QLineEdit *m_fileEdit;
    QPushButton *m_fileButton;
    QCheckBox *m_rowLabels;
    QCheckBox *m_columnLabels;
    QRadioButton *m_noFitting;
    QRadioButton *m_fitSingle;
    QRadioButton *m_fitVertical;
    QCheckBox *m_useStartTime;
    QCheckBox *m_useEndTime;
    QDateTimeEdit *m_startTime;
    QDateTimeEdit *m_endTime;
    QDoubleSpinBox *m_margin;
    
    SavePdfDialog(QWidget *parent = nullptr);
private Q_SLOTS:
    void fileButtonClicked();
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow( QWidget* parent = nullptr );

    QRectF calcSceneRect(const QDateTime &startDateTime, const QDateTime &endDateTime) const;
    bool optionsDialog(bool requireFile = false);

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
    KGantt::PrintingContext m_ctx;
    QDateTime m_startTime;
    QDateTime m_endTime;
    QString m_file;
    QMarginsF m_margins;
};
#endif /* PRINTINGMAINWINDOW_H */

