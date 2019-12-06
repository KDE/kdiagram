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

#ifndef KCHARTABSTRACTAREA_H
#define KCHARTABSTRACTAREA_H

#include <QObject>

#include "KChartGlobal.h"
#include "KChartAbstractAreaBase.h"
#include "KChartLayoutItems.h"

namespace KChart {


/**
  * @class AbstractArea KChartAbstractArea.h
  * @brief An area in the chart with a background, a frame, etc.
  *
  * AbstractArea is the base class for all non-widget chart elements that have
  * a set of background attributes and frame attributes, such as
  * coordinate planes or axes.
  *
  * @note This class inherits from AbstractAreaBase, AbstractLayoutItem, QObject.
  * The reason for this triple inheritance is that neither AbstractAreaBase nor
  * AbstractLayoutItem are QObject.
  */
class KCHART_EXPORT AbstractArea : public QObject,
                                    public AbstractAreaBase,
                                    public AbstractLayoutItem
{
    Q_OBJECT

    Q_DISABLE_COPY( AbstractArea )
    KCHART_DECLARE_PRIVATE_DERIVED( AbstractArea )

public:
    virtual ~AbstractArea() ;

    /**
      * @brief Draws the background and frame, then calls paint().
      *
      * In most cases there is no need to overwrite this method in a derived
      * class, but you would overwrite AbstractLayoutItem::paint() instead.
      */
    virtual void paintIntoRect( QPainter& painter, const QRect& rect );

    /**
      * Call paintAll, if you want the background and the frame to be drawn
      * before the normal paint() is invoked automatically.
      */
    void paintAll( QPainter& painter ) override;

    /**
     * This is called at layout time by KChart::AutoSpacerLayoutItem::sizeHint().
     *
     * The method triggers AbstractArea::sizeHint() to find out the
     * amount of overlap at the left edge of the area.
     *
     * \note The default implementation is not using any caching,
     * it might make sense to implement a more sophisticated solution
     * for derived classes that have complex work to do in sizeHint().
     * All we have here is a primitive flag to be set by the caller
     * if it is sure that no sizeHint() needs to be called.
     */
    virtual int leftOverlap( bool doNotRecalculate=false ) const;
    /**
     * This is called at layout time by KChart::AutoSpacerLayoutItem::sizeHint().
     *
     * The method triggers AbstractArea::sizeHint() to find out the
     * amount of overlap at the right edge of the area.
     *
     * \note The default implementation is not using any caching,
     * it might make sense to implement a more sophisticated solution
     * for derived classes that have complex work to do in sizeHint().
     * All we have here is a primitive flag to be set by the caller
     * if it is sure that no sizeHint() needs to be called.
     */
    virtual int rightOverlap( bool doNotRecalculate=false ) const;
    /**
     * This is called at layout time by KChart::AutoSpacerLayoutItem::sizeHint().
     *
     * The method triggers AbstractArea::sizeHint() to find out the
     * amount of overlap at the top edge of the area.
     *
     * \note The default implementation is not using any caching,
     * it might make sense to implement a more sophisticated solution
     * for derived classes that have complex work to do in sizeHint().
     * All we have here is a primitive flag to be set by the caller
     * if it is sure that no sizeHint() needs to be called.
     */
    virtual int topOverlap( bool doNotRecalculate=false ) const;
    /**
     * This is called at layout time by KChart:AutoSpacerLayoutItem::sizeHint().
     *
     * The method triggers AbstractArea::sizeHint() to find out the
     * amount of overlap at the bottom edge of the area.
     *
     * \note The default implementation is not using any caching,
     * it might make sense to implement a more sophisticated solution
     * for derived classes that have complex work to do in sizeHint().
     * All we have here is a primitive flag to be set by the caller
     * if it is sure that no sizeHint() needs to be called.
     */
    virtual int bottomOverlap( bool doNotRecalculate=false ) const;

protected:
    AbstractArea();
    QRect areaGeometry() const override;
    void positionHasChanged() override;

Q_SIGNALS:
    void positionChanged( AbstractArea * );
}; // End of class AbstractArea

}
#endif // KCHARTABSTRACTAREA_H
