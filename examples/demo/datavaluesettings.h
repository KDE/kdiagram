/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef DATAVALUESETTINGS_H
#define DATAVALUESETTINGS_H

#include <QWidget>

namespace KChart {
    class Chart;
}

class DataValueSettings : public QWidget
{
    Q_OBJECT

public:
    DataValueSettings( KChart::Chart *chart, QWidget* parent = nullptr );
    ~DataValueSettings() override;

public Q_SLOTS:
    void refresh();

private:
    class Private;
    Private *d;

};


#endif /* MAINWINDOW_H */

