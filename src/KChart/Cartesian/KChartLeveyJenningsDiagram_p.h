/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTLEVEYJENNINGSDIAGRAM_P_H
#define KCHARTLEVEYJENNINGSDIAGRAM_P_H

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

#include <QDateTime>

#include "KChartLeveyJenningsDiagram.h"
#include "KChartThreeDLineAttributes.h"
#include "KChartLineDiagram_p.h"
#include "KChartMath_p.h"

QT_BEGIN_NAMESPACE
class QSvgRenderer;
QT_END_NAMESPACE

namespace KChart {

    class PaintContext;

/**
 * \internal
 */
    class Q_DECL_HIDDEN LeveyJenningsDiagram::Private : public LineDiagram::Private
    {
        friend class LeveyJenningsDiagram;
    public:
        Private();
        Private( const Private& rhs );
        ~Private();

        void setYAxisRange() const;

        Qt::Alignment lotChangedPosition;
        Qt::Alignment fluidicsPackChangedPosition;
        Qt::Alignment sensorChangedPosition;

        QVector< QDateTime > fluidicsPackChanges;
        QVector< QDateTime > sensorChanges;

        QPen scanLinePen;

        QMap< LeveyJenningsDiagram::Symbol, QString >  icons;
        QMap< LeveyJenningsDiagram::Symbol, QSvgRenderer* > iconRenderer;

        QPair< QDateTime, QDateTime > timeRange;

        float expectedMeanValue;
        float expectedStandardDeviation;

        mutable float calculatedMeanValue;
        mutable float calculatedStandardDeviation;
    };

    KCHART_IMPL_DERIVED_DIAGRAM( LeveyJenningsDiagram, LineDiagram, LeveyJenningsCoordinatePlane )
}

#endif /* KCHARTLINEDIAGRAM_P_H */
