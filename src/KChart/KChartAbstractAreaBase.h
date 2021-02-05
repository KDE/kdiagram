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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef KCHARTABSTRACTAREABASE_H
#define KCHARTABSTRACTAREABASE_H

#include <QPointF>
#include <QSizeF>
#include <QRectF>

#include "KChartGlobal.h"
#include "KChartLayoutItems.h"
#include "KChartRelativePosition.h"
#include "KChartAbstractAreaBase.h"


QT_BEGIN_NAMESPACE
class QPainter;
class QString;
QT_END_NAMESPACE

namespace KChart {
    class TextAttributes;
    class BackgroundAttributes;
    class FrameAttributes;
    class PaintContext;


/**
  * @class AbstractAreaBase KChartAbstractAreaBase.h
  * @brief Base class for AbstractArea and AbstractAreaWidget: An area
  * in the chart with a background, a frame, etc.
  *
  * AbstractAreaBase is the base class for all chart elements that have
  * a set of background attributes and frame attributes, such as
  * legends or axes.
  *
  * @note Normally you should not use AbstractAreaBase directly, but
  * derive your classes from AbstractArea or AbstractAreaWidget.
  *
  * @note This classis not a QObject, so it is easier to inherit from
  * it, if your are inheriting from a QObject too like AbstractAreaWidget does it.
  *
  * @sa AbstractArea, AbstractAreaWidget
  */
class KCHART_EXPORT AbstractAreaBase
{
    Q_DISABLE_COPY( AbstractAreaBase )
    KCHART_DECLARE_PRIVATE_BASE_POLYMORPHIC( AbstractAreaBase )

protected:
    AbstractAreaBase();
    virtual ~AbstractAreaBase() ;

public:
   /**
     * Returns true if both areas have the same settings.
     */
    bool compare( const AbstractAreaBase* other ) const;

    void alignToReferencePoint( const RelativePosition& position );

    void setFrameAttributes( const FrameAttributes &a );
    FrameAttributes frameAttributes() const;

    void setBackgroundAttributes( const BackgroundAttributes &a );
    BackgroundAttributes backgroundAttributes() const;

    virtual void paintBackground( QPainter& painter, const QRect& rectangle );
    virtual void paintFrame( QPainter& painter, const QRect& rectangle );

    static void paintBackgroundAttributes( QPainter& painter, const QRect& rectangle,
        const KChart::BackgroundAttributes& attributes );
    static void paintFrameAttributes( QPainter& painter, const QRect& rectangle,
        const KChart::FrameAttributes& attributes );

    /** \internal
      * \note Normally you should not call this method, but derive your classes
      * from AbstractArea or AbstractAreaWidget.
      * \sa AbstractArea, AbstractAreaWidget
      */
    void getFrameLeadings(int& left, int& top, int& right, int& bottom ) const;


protected:
    /** \internal
      * \note Normally you should not call this method, but derive your classes
      * from AbstractArea or AbstractAreaWidget.
      * \sa AbstractArea, AbstractAreaWidget
      */
    QRect innerRect() const;

    /** \internal
      * This internal method is used by AbstractArea and AbstractAreaWidget
      * to find out the real widget size.
      * \sa AbstractArea, AbstractAreaWidget
      */
    virtual QRect areaGeometry() const = 0;

    /** \internal
      * This internal method can be overwritten by derived classes,
      * if they want to emit a signal (or perform other actions, resp.)
      * when the Position of the area has been changed.
      * The default implementation does nothing.
      */
    virtual void positionHasChanged();

}; // End of class AbstractAreaBase

}
#endif // KCHARTABSTRACTAREABASE_H
