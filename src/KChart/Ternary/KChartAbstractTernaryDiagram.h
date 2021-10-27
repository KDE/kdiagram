/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
        ~AbstractTernaryDiagram() override;

        void paint (PaintContext *paintContext) override;

        virtual void addAxis( TernaryAxis* axis );
        virtual void takeAxis( TernaryAxis* axis );
        virtual TernaryAxisList axes () const;

    protected:
        const QPair< QPointF, QPointF >  calculateDataBoundaries () const override = 0;

    };

}

#endif
