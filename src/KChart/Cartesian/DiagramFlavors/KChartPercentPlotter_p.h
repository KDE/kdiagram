/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTPERCENTPLOTTER_P_H
#define KCHARTPERCENTPLOTTER_P_H

#include "KChartPlotter_p.h"

namespace KChart {

    class PercentPlotter : public Plotter::PlotterType
    {
    public:
        explicit PercentPlotter( Plotter* );
        ~PercentPlotter() override {}
        Plotter::PlotType type() const override;
        const QPair< QPointF,  QPointF > calculateDataBoundaries() const override;
        void paint( PaintContext* ctx ) override;
    };
}

#endif
