/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTRADARDIAGRAM_P_H
#define KCHARTRADARDIAGRAM_P_H

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

#include "KChartAbstractPolarDiagram_p.h"
#include "KChartRadarDiagram.h"
#include "KChartMath_p.h"


namespace KChart {

/**
 * \internal
 */
class Q_DECL_HIDDEN RadarDiagram::Private : public AbstractPolarDiagram::Private
{
    friend class RadarDiagram;
public:
    Private();
    ~Private() override;

    Private( const Private& rhs ) :
        AbstractPolarDiagram::Private( rhs ),
        closeDatasets( rhs.closeDatasets ),
        reverseData( rhs.reverseData ),
        fillAlpha( rhs.fillAlpha )
        {
        }

private:
    bool closeDatasets;
    bool reverseData;
    qreal fillAlpha;
    LabelPaintCache labelPaintCache;
};

KCHART_IMPL_DERIVED_DIAGRAM( RadarDiagram, AbstractPolarDiagram, RadarCoordinatePlane )

}

#endif /* KCHARTRADARDIAGRAM_P_H */
