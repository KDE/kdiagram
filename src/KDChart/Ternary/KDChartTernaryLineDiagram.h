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

#ifndef KDCHARTTERNARYLINEDIAGRAM_H
#define KDCHARTTERNARYLINEDIAGRAM_H

#include "KDChartTernaryCoordinatePlane.h"
#include "KDChartAbstractTernaryDiagram.h"


namespace KDChart {

    /**
      * @brief A TernaryLineDiagram is a line diagram with a ternary coordinate plane
      */
    class KDE_KDCHART_EXPORT TernaryLineDiagram : public AbstractTernaryDiagram
    {
        Q_OBJECT
        Q_DISABLE_COPY( TernaryLineDiagram )
        KDCHART_DECLARE_DERIVED_DIAGRAM( TernaryLineDiagram, TernaryCoordinatePlane )

    public:
        explicit TernaryLineDiagram ( QWidget* parent = 0, TernaryCoordinatePlane* plane = 0 );
        virtual ~TernaryLineDiagram();

        void resize (const QSizeF &area);
        void paint (PaintContext *paintContext);

    protected:
        const QPair< QPointF, QPointF > calculateDataBoundaries () const;

    };
}

#endif
