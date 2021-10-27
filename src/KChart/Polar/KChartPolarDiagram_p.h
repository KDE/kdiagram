/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTPOLARDIAGRAM_P_H
#define KCHARTPOLARDIAGRAM_P_H

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

#include "KChartPolarDiagram.h"
#include "KChartAbstractPolarDiagram_p.h"

#include "KChartMath_p.h"


namespace KChart {

/**
 * \internal
 */
class Q_DECL_HIDDEN PolarDiagram::Private : public AbstractPolarDiagram::Private
{
    friend class PolarDiagram;
public:
    Private();
    ~Private() override;

    Private( const Private& rhs ) :
        AbstractPolarDiagram::Private( rhs ),
        showDelimitersAtPosition( rhs.showDelimitersAtPosition ),
        showLabelsAtPosition( rhs.showLabelsAtPosition ),
        rotateCircularLabels( rhs.rotateCircularLabels ),
        closeDatasets( rhs.closeDatasets )
        {
        }

private:
    QMap<int,bool> showDelimitersAtPosition;
    QMap<int,bool> showLabelsAtPosition;
    bool rotateCircularLabels;
    bool closeDatasets;
    LabelPaintCache labelPaintCache;
};

KCHART_IMPL_DERIVED_DIAGRAM( PolarDiagram, AbstractPolarDiagram, PolarCoordinatePlane )

}

#endif /* KCHARTPOLARDIAGRAM_P_H */
