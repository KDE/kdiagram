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

#ifndef PAINTCONTEXT_H
#define PAINTCONTEXT_H

#include <QRectF>
#include "KChartGlobal.h"

QT_BEGIN_NAMESPACE
class QPainter;
QT_END_NAMESPACE

namespace KChart {

    class AbstractCoordinatePlane;

    /**
      * @brief Stores information about painting diagrams
      * \internal
      */
    class KCHART_EXPORT PaintContext
    {
    public:
        PaintContext();
        ~PaintContext();

        const QRectF rectangle () const;
        void setRectangle( const QRectF& rect );

        QPainter* painter() const;
        void setPainter( QPainter* painter );

        AbstractCoordinatePlane* coordinatePlane() const;
        void setCoordinatePlane( AbstractCoordinatePlane* plane );

    private:
        class Private;
        Private * _d;
        Private * d_func() { return _d; }
        const Private * d_func() const { return _d; }
    };

}

#endif /* PAINTCONTEXT_H */

