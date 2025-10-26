/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTTHREEDLINEATTRIBUTES_P_H
#define KCHARTTHREEDLINEATTRIBUTES_P_H

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
#include <KChartAbstractThreeDAttributes_p.h>
#include <KChartThreeDLineAttributes.h>

namespace KChart
{

/**
 * \internal
 */
class Q_DECL_HIDDEN ThreeDLineAttributes::Private : public AbstractThreeDAttributes::Private
{
    friend class ThreeDLineAttributes;

public:
    Private();

private:
    // ThreeDLines
    uint lineXRotation;
    uint lineYRotation;
};

KCHART_DERIVED_PRIVATE_FOOTER(ThreeDLineAttributes, AbstractThreeDAttributes)

}

#endif // KCHARTTHREEDLINEATTRIBUTES_P_H
