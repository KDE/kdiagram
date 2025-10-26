/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTTERNARYPOINTDIAGRAM_H
#define KCHARTTERNARYPOINTDIAGRAM_H

#include "KChartAbstractTernaryDiagram.h"
#include "KChartTernaryCoordinatePlane.h"

namespace KChart
{

/**
 * @brief A TernaryPointDiagram is a point diagram within a ternary coordinate plane
 */
class KCHART_EXPORT TernaryPointDiagram : public AbstractTernaryDiagram
{
    Q_OBJECT
    Q_DISABLE_COPY(TernaryPointDiagram)
    KCHART_DECLARE_DERIVED_DIAGRAM(TernaryPointDiagram, TernaryCoordinatePlane)

public:
    explicit TernaryPointDiagram(QWidget *parent = nullptr, TernaryCoordinatePlane *plane = nullptr);
    ~TernaryPointDiagram() override;

    void resize(const QSizeF &area) override;
    void paint(PaintContext *paintContext) override;

protected:
    const QPair<QPointF, QPointF> calculateDataBoundaries() const override;
};

}

#endif
