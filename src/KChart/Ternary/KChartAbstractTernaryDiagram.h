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

#ifndef KCHARTABSTRACTTERNARYDIAGRAM_H
#define KCHARTABSTRACTTERNARYDIAGRAM_H

#include "KChartAbstractDiagram.h"
#include "KChartTernaryAxis.h"

namespace KChart {

    class TernaryCoordinatePlane;
    class TernaryAxis;

    /**
      * @brief Base class for diagrams based on a ternary coordinate plane.
      */
    class KCHART_EXPORT AbstractTernaryDiagram : public AbstractDiagram
    {
        Q_OBJECT
        Q_DISABLE_COPY( AbstractTernaryDiagram )
        KCHART_DECLARE_DERIVED_DIAGRAM( AbstractTernaryDiagram,
                                         TernaryCoordinatePlane )

    public:
        explicit AbstractTernaryDiagram ( QWidget* parent = nullptr,
                                          TernaryCoordinatePlane* plane = nullptr );
        virtual ~AbstractTernaryDiagram();

        void paint (PaintContext *paintContext) Q_DECL_OVERRIDE;

        virtual void addAxis( TernaryAxis* axis );
        virtual void takeAxis( TernaryAxis* axis );
        virtual TernaryAxisList axes () const;

    protected:
        const QPair< QPointF, QPointF >  calculateDataBoundaries () const Q_DECL_OVERRIDE = 0;

    };

}

#endif
