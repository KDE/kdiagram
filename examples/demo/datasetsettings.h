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

#ifndef DATASETSETTINGS_H
#define DATASETSETTINGS_H

#include <QWidget>

namespace KChart{
    class Chart;
}

class DatasetSettings : public QWidget
{
    Q_OBJECT
    Q_PROPERTY( int datasetCount READ datasetCount WRITE setDatasetCount NOTIFY datasetCountChanged() )

public:
    explicit DatasetSettings( KChart::Chart *chart, QWidget *parent = nullptr );
    ~DatasetSettings();
    int datasetCount() const;
public Q_SLOTS:
    void setDatasetCount( int value );
    void indexChanged( int index );
    void diagramTypeChanged();

Q_SIGNALS:
    void datasetCountChanged();

private:
    class Private;
    Private *d;
};

#endif // DATASETSETTINGS_H
