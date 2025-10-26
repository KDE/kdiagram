/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHART_PIE_ATTRIBUTES_P_H
#define KCHART_PIE_ATTRIBUTES_P_H

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

#include "KChartMath_p.h"
#include <KChartPieAttributes.h>

namespace KChart
{

/**
 * \internal
 */
class Q_DECL_HIDDEN PieAttributes::Private
{
    friend class PieAttributes;

public:
    Private();

    qreal explodeFactor;
    qreal tangentialGapFactor;
    qreal radialGapFactor;
};

}

#endif // KCHART_PIE_ATTRIBUTES_P_H
