/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
