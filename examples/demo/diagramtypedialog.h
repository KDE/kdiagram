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
    explicit DiagramTypeDialog( KChart::Chart *chart, QWidget *parent = 0 );
    ~DiagramTypeDialog();

    void setDefaultModels( QHash< DiagramType, QAbstractItemModel* > models );

Q_SIGNALS:
    void diagramTypeChanged( DiagramType, Subtype );

private:
    class Private;
    Private *d;
};

#endif // DIAGRAMTYPEDIALOG_H
