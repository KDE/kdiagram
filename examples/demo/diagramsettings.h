/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef DIAGRAMSETTINGS_H
#define DIAGRAMSETTINGS_H

#include <QWidget>

namespace KChart{
    class Chart;
}

class DiagramSettings : public QWidget
{
    Q_OBJECT

public:
    explicit DiagramSettings( KChart::Chart* chart, QWidget *parent = nullptr );
    ~DiagramSettings();

public Q_SLOTS:
    void refreshSettings();

private:
    class Private;
    Private *d;
};

#endif // DIAGRAMSETTINGS_H
