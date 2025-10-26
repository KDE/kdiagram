/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTTHREEDBARATTRIBUTES_P_H
#define KCHARTTHREEDBARATTRIBUTES_P_H

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

#include <KChartAbstractThreeDAttributes_p.h>
#include <KChartThreeDBarAttributes.h>

#include "KChartMath_p.h"

namespace KChart
{

/**
 * \internal
 */
class Q_DECL_HIDDEN ThreeDBarAttributes::Private : public AbstractThreeDAttributes::Private
{
    friend class ThreeDBarAttributes;

public:
    Private();

private:
    bool useShadowColors;
    uint angle;
};

KCHART_DERIVED_PRIVATE_FOOTER(ThreeDBarAttributes, AbstractThreeDAttributes)

}

#endif // KCHARTTHREEDBARATTRIBUTES_P_H
