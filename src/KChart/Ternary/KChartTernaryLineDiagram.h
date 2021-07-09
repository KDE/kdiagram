/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTTERNARYLINEDIAGRAM_H
#define KCHARTTERNARYLINEDIAGRAM_H

#include "KChartTernaryCoordinatePlane.h"
#include "KChartAbstractTernaryDiagram.h"


namespace KChart {

    /**
      * @brief A TernaryLineDiagram is a line diagram with a ternary coordinate plane
      */
    class KCHART_EXPORT TernaryLineDiagram : public AbstractTernaryDiagram
    {
        Q_OBJECT
        Q_DISABLE_COPY( TernaryLineDiagram )
        KCHART_DECLARE_DERIVED_DIAGRAM( TernaryLineDiagram, TernaryCoordinatePlane )

    public:
        explicit TernaryLineDiagram ( QWidget* parent = nullptr, TernaryCoordinatePlane* plane = nullptr );
        virtual ~TernaryLineDiagram();

        void resize (const QSizeF &area) override;
        void paint (PaintContext *paintContext) override;

    protected:
        const QPair< QPointF, QPointF > calculateDataBoundaries () const override;

    };
}

#endif
