/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTABSTRACTPIEDIAGRAM_P_H
#define KCHARTABSTRACTPIEDIAGRAM_P_H

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

#include "KChartAbstractPieDiagram.h"
#include "KChartAbstractPolarDiagram_p.h"
#include <KChartAbstractThreeDAttributes.h>
#include "KChartMath_p.h"


namespace KChart {

class PolarCoordinatePlane;

/**
 * \internal
 */
class Q_DECL_HIDDEN AbstractPieDiagram::Private : public AbstractPolarDiagram::Private
{
    friend class AbstractPieDiagram;
public:
    Private();
    ~Private() override;

    Private( const Private& rhs ) :
        AbstractPolarDiagram::Private( rhs ),
        granularity( rhs.granularity ),
        autoRotateLabels( false )
        {
        }

private:
    qreal granularity;
    bool autoRotateLabels;
};

KCHART_IMPL_DERIVED_DIAGRAM( AbstractPieDiagram, AbstractPolarDiagram, PolarCoordinatePlane )

}
#endif /* KCHARTABSTRACTPIEDIAGRAM_P_H */
