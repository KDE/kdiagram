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

#ifndef KCHART_TEXT_AREA_H
#define KCHART_TEXT_AREA_H

#include <QObject>

#include "KChartGlobal.h"
#include "KChartAbstractAreaBase.h"
#include "KChartLayoutItems.h"

namespace KChart {


/**
  * @class TextArea KChartTextArea.h
  * @brief A text area in the chart with a background, a frame, etc.
  *
  * TextArea is the base class for all text containing non-widget chart elements
  * that have a set of background attributes and frame attributes, such as
  * headers or footers.
  *
  * @note This class inherits AbstractAreaBase, TextLayoutItem, and QObject.
  * The reason for this triple inheritance is that neither AbstractAreaBase nor
  * TextLayoutItem inherit QObject.
  */
class KCHART_EXPORT TextArea : public QObject, public AbstractAreaBase, public TextLayoutItem
{
    Q_OBJECT

    Q_DISABLE_COPY( TextArea )
    KCHART_DECLARE_PRIVATE_DERIVED( TextArea )


public:
    virtual ~TextArea() ;

//    virtual TextArea * clone() const = 0;
    /**
      * @brief Draws the background and frame, then calls paint().
      *
      * In most cases there is no need to overwrite this method in a derived
      * class, but you would overwrite TextLayoutItem::paint() instead.
      */
    virtual void paintIntoRect( QPainter& painter, const QRect& rect );

    /**
      * Call paintAll, if you want the background and the frame to be drawn
      * before the normal paint() is invoked automatically.
      */
    void paintAll( QPainter& painter ) override;

protected:
    TextArea();
    QRect areaGeometry() const override;
    void positionHasChanged() override;

Q_SIGNALS:
    void positionChanged( TextArea * );

    //KCHART_DECLARE_PRIVATE_DERIVED(TextArea)
}; // End of class TextArea

}
#endif // KCHART_TEXT_AREA_H
