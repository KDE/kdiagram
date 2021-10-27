/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTPERCENTLYINGBARDIAGRAM_P_H
#define KCHARTPERCENTLYINGBARDIAGRAM_P_H

#include "KChartBarDiagram_p.h"

namespace KChart {

    class PercentLyingBarDiagram : public BarDiagram::BarDiagramType
    {
    public:
        explicit PercentLyingBarDiagram( BarDiagram* );
        ~PercentLyingBarDiagram() override {}
        BarDiagram::BarType type() const override;
        const QPair<QPointF,  QPointF> calculateDataBoundaries() const override;
        void paint( PaintContext* ctx ) override;
    };

}

#endif
