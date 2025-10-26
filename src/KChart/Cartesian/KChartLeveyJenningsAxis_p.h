/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTLEVEYJENNINGSAXIS_P_H
#define KCHARTLEVEYJENNINGSAXIS_P_H

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

#include "KChartCartesianAxis_p.h"
#include "KChartLeveyJenningsAxis.h"
#include "KChartLeveyJenningsDiagram.h"
#include "KChartMath_p.h"

namespace KChart
{

/**
 * \internal
 */
class Q_DECL_HIDDEN LeveyJenningsAxis::Private : public CartesianAxis::Private
{
    friend class LeveyJenningsAxis;

public:
    Private(LeveyJenningsDiagram *diagram, LeveyJenningsAxis *axis)
        : CartesianAxis::Private(diagram, axis)
        , type(LeveyJenningsGridAttributes::Expected)
        , format(Qt::ISODate)
    {
    }
    ~Private() override
    {
    }

private:
    LeveyJenningsGridAttributes::GridType type;
    Qt::DateFormat format;
};

inline LeveyJenningsAxis::LeveyJenningsAxis(Private *p, AbstractDiagram *diagram)
    : CartesianAxis(p, diagram)
{
    init();
}
inline LeveyJenningsAxis::Private *LeveyJenningsAxis::d_func()
{
    return static_cast<Private *>(CartesianAxis::d_func());
}
inline const LeveyJenningsAxis::Private *LeveyJenningsAxis::d_func() const
{
    return static_cast<const Private *>(CartesianAxis::d_func());
}

}

#endif
