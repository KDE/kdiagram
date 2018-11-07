/*
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

#ifndef KCHARTABSTRACTAREAWIDGET_H
#define KCHARTABSTRACTAREAWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>

#include "KChartAbstractAreaBase.h"

namespace KChart {


/**
  * @class AbstractAreaWidget KChartAbstractArea.h
  * @brief An area in the chart with a background, a frame, etc.
  *
  * AbstractAreaWidget is the base for all widget classes that have
  * a set of background attributes and frame attributes, such as
  * KChart::Chart and KChart::Legend.
  */
class KCHART_EXPORT AbstractAreaWidget : public QWidget, public AbstractAreaBase
{
    Q_OBJECT

    Q_DISABLE_COPY( AbstractAreaWidget )
    KCHART_DECLARE_PRIVATE_DERIVED_QWIDGET( AbstractAreaWidget )

public:
    explicit AbstractAreaWidget( QWidget* parent = nullptr );

    /**
      * @brief Draws the background and frame, then calls paint().
      *
      * In most cases there is no need to overwrite this method in a derived
      * class, but you would overwrite paint() instead.
      * @sa paint
      */
    void paintEvent( QPaintEvent* event ) Q_DECL_OVERRIDE;

    /**
      * @brief Draws the background and frame, then calls paint().
      *
      * In most cases there is no need to overwrite this method in a derived
      * class, but you would overwrite paint() instead.
      */
    virtual void paintIntoRect( QPainter& painter, const QRect& rect );

    /**
      * Overwrite this to paint the inner contents of your widget.
      *
      * @note When overriding this method, please let your widget draw
      * itself at the top/left corner of the painter.  You should call rect()
      * (or width(), height(), resp.) to find the drawable area's size:
      * While the paint() method is being executed the frame of the widget
      * is outside of its rect(), so you can use all of rect() for
      * your custom drawing!
      * @sa paint, paintIntoRect
      */
    virtual void paint( QPainter* painter ) = 0;

    /**
      * Call paintAll, if you want the background and the frame to be drawn
      * before the normal paint() is invoked automatically.
      */
    void paintAll( QPainter& painter );

    /**
      * Call this to trigger an unconditional re-building of the widget's internals.
      */ 
    virtual void forceRebuild();

    /**
      * Call this to trigger an conditional re-building of the widget's internals.
      *
      * e.g. AbstractAreaWidget call this, before calling layout()->setGeometry()
      */ 
    virtual void needSizeHint();
    virtual void resizeLayout( const QSize& );

Q_SIGNALS:
    void positionChanged( AbstractAreaWidget * );

protected:
    virtual ~AbstractAreaWidget() ;
    QRect areaGeometry() const Q_DECL_OVERRIDE;
    void positionHasChanged() Q_DECL_OVERRIDE;
};

}
#endif // KCHARTABSTRACTAREAWIDGET_H
