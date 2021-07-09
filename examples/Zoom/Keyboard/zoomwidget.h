/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef ZOOMWIDGET_H
#define ZOOMWIDGET_H

#include <KChartWidget>

class ZoomWidget : public KChart::Widget
{
    Q_OBJECT

public:
    explicit ZoomWidget( QWidget* parent );

protected:
    QPointF findNewZoomCenter( const QPoint & pos );
    void mousePressEvent( QMouseEvent * e ) override;
    void wheelEvent( QWheelEvent* e ) override;
    void keyPressEvent( QKeyEvent* e ) override;
};


#endif /* ZOOMWIDGET_H */

