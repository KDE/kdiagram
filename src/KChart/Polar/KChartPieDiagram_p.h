/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTPIEDIAGRAM_P_H
#define KCHARTPIEDIAGRAM_P_H

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

#include "KChartPieDiagram.h"
#include "KChartAbstractPieDiagram_p.h"
#include "KChartMath_p.h"


namespace KChart {

/**
 * \internal
 */
class Q_DECL_HIDDEN PieDiagram::Private : public AbstractPieDiagram::Private
{
    friend class PieDiagram;
public:
    Private();
    ~Private() override;

    Private( const Private& rhs ) :
        AbstractPieDiagram::Private( rhs ),
        startAngles(),
        angleLens(),
        size( 0 ),
        labelDecorations( NoDecoration ),
        isCollisionAvoidanceEnabled( false )
        {
            // just for consistency
        }

protected:
    // this information needed temporarily at drawing time
    QVector< qreal > startAngles;
    QVector< qreal > angleLens;
    qreal size;
    LabelPaintCache labelPaintCache;
    PieDiagram::LabelDecorations labelDecorations;
    bool isCollisionAvoidanceEnabled;
};

KCHART_IMPL_DERIVED_DIAGRAM( PieDiagram, AbstractPieDiagram, PolarCoordinatePlane )

}

#endif /* KCHARTPIEDIAGRAM_P_H */
