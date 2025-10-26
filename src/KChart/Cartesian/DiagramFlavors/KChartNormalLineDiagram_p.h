/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTNORMALLINEDIAGRAM_P_H
#define KCHARTNORMALLINEDIAGRAM_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the KD Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//
#include "KChartLineDiagram_p.h"

namespace KChart
{

class NormalLineDiagram : public LineDiagram::LineDiagramType
{
public:
    explicit NormalLineDiagram(LineDiagram *);
    ~NormalLineDiagram() override
    {
    }
    LineDiagram::LineType type() const override;
    const QPair<QPointF, QPointF> calculateDataBoundaries() const override;
    void paint(PaintContext *ctx) override;
};

}

#endif
