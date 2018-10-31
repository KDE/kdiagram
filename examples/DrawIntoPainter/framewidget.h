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
    explicit FrameWidget( QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

    void paintEvent( QPaintEvent* ) Q_DECL_OVERRIDE;

    void setChart( KChart::Chart* chart );

private:
    KChart::Chart* mChart;
};


#endif /* FRAMEWIDGET_H */

