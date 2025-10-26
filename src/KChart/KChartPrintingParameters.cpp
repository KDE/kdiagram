/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartPrintingParameters.h"

using namespace KChart;

PrintingParameters::PrintingParameters()
    : m_scaleFactor(1.0)
{
}

PrintingParameters *PrintingParameters::instance()
{
    static PrintingParameters instance;
    return &instance;
}

qreal PrintingParameters::scaleFactor()
{
    return instance()->m_scaleFactor;
}

void PrintingParameters::setScaleFactor(const qreal scaleFactor)
{
    instance()->m_scaleFactor = scaleFactor;
}

void PrintingParameters::resetScaleFactor()
{
    instance()->m_scaleFactor = 1.0;
}

QPen PrintingParameters::scalePen(const QPen &pen)
{
    if (instance()->m_scaleFactor == 1.0)
        return pen;

    QPen resultPen = pen;
    resultPen.setWidthF(resultPen.widthF() * instance()->m_scaleFactor);
    if (resultPen.widthF() == 0.0)
        resultPen.setWidthF(instance()->m_scaleFactor);

    return resultPen;
}
