/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>

namespace KChart {
    class Chart;
}


class FrameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FrameWidget( QWidget * parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags() );

    void paintEvent( QPaintEvent* ) override;

    void setChart( KChart::Chart* chart );

private:
    KChart::Chart* mChart;
};


#endif /* FRAMEWIDGET_H */

