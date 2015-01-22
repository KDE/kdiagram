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

#ifndef KDCHARTTERNARYPOINTDIAGRAM_H
#define KDCHARTTERNARYPOINTDIAGRAM_H

#include "KDChartTernaryCoordinatePlane.h"
#include "KDChartAbstractTernaryDiagram.h"

namespace KDChart {

    /**
      * @brief A TernaryPointDiagram is a point diagram within a ternary coordinate plane
      */
    class KDCHART_EXPORT TernaryPointDiagram : public AbstractTernaryDiagram
    {
        Q_OBJECT
        Q_DISABLE_COPY( TernaryPointDiagram )
        KDCHART_DECLARE_DERIVED_DIAGRAM( TernaryPointDiagram, TernaryCoordinatePlane )

    public:
        explicit TernaryPointDiagram ( QWidget* parent = 0, TernaryCoordinatePlane* plane = 0 );
        virtual ~TernaryPointDiagram();

        virtual void resize (const QSizeF &area);
        virtual void paint (PaintContext *paintContext);

    protected:
        virtual const QPair< QPointF, QPointF >  calculateDataBoundaries () const;
    };

}

#endif
