/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef DIAGRAMTYPEDIALOG_H
#define DIAGRAMTYPEDIALOG_H

#include <QDialog>
#include <QHash>

class QAbstractItemModel;
namespace KChart
{
    class Chart;
}

class DiagramTypeDialog : public QDialog
{
    Q_OBJECT
public:
    enum DiagramType{ Bar, LyingBar, Line, Plotter, Pie };
    enum Subtype{ Normal, Percent, Stacked };
    explicit DiagramTypeDialog( KChart::Chart *chart, QWidget *parent = nullptr );
    ~DiagramTypeDialog();

    void setDefaultModels( QHash< DiagramType, QAbstractItemModel* > models );

Q_SIGNALS:
    void diagramTypeChanged( DiagramTypeDialog::DiagramType, DiagramTypeDialog::Subtype );

private:
    class Private;
    Private *d;
};

#endif // DIAGRAMTYPEDIALOG_H
