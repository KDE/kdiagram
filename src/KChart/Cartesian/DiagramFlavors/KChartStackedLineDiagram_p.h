/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTSTACKEDLINEDIAGRAM_P_H
#define KCHARTSTACKEDLINEDIAGRAM_P_H

#include "KChartLineDiagram_p.h"

namespace KChart {

    class StackedLineDiagram : public LineDiagram::LineDiagramType
    {
    public:
        explicit StackedLineDiagram( LineDiagram* );
        virtual ~StackedLineDiagram() {}
        LineDiagram::LineType type() const override;
        const QPair<QPointF,  QPointF> calculateDataBoundaries() const override;
        void paint( PaintContext* ctx ) override;
    };

}

#endif
