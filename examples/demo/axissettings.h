/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef AXISSETTINGS_H
#define AXISSETTINGS_H

#include <QWidget>

namespace KChart
{
    class Chart;
}

class AxisSettings : public QWidget
{
    Q_OBJECT

public:
    explicit AxisSettings( KChart::Chart *chart, QWidget *parent = nullptr );
    ~AxisSettings();

public Q_SLOTS:
    void diagramTypeChanged();

private:
    class Private;
    Private *d;
};

#endif // AXISSETTINGS_H
