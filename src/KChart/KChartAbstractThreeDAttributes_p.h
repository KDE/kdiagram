/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTABSTRACTTHREEDATTRIBUTES_P_H
#define KCHARTABSTRACTTHREEDATTRIBUTES_P_H

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

#include <KChartAbstractThreeDAttributes.h>

#include "KChartMath_p.h"


namespace KChart {

/**
 * \internal
 */
class Q_DECL_HIDDEN AbstractThreeDAttributes::Private
{
    friend class AbstractThreeDAttributes;
public:
    Private();

private:
    bool enabled;
// FIXME: What is this needed for? height is not referenced anywhere.
//    int height;
    qreal depth;
    bool threeDBrushEnabled;
};

inline AbstractThreeDAttributes::AbstractThreeDAttributes( Private * p ) : _d( p ) { init(); }

}

#endif // KCHARTABSTRACTTHREEDATTRIBUTES_P_H
