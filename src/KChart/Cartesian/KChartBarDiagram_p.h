/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTBARDIAGRAM_P_H
#define KCHARTBARDIAGRAM_P_H

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

#include "KChartBarDiagram.h"

#include <QPainterPath>

#include "KChartAbstractCartesianDiagram_p.h"
#include "KChartThreeDBarAttributes.h"
#include "KChartMath_p.h"


namespace KChart {

class PaintContext;

/**
 * \internal
 */
class Q_DECL_HIDDEN BarDiagram::Private : public AbstractCartesianDiagram::Private
{
    friend class BarDiagram;
    friend class BarDiagramType;

public:
    Private();
    Private( const Private& rhs );
    ~Private() override;

    void setOrientationAndType( Qt::Orientation, BarDiagram::BarType );

    Qt::Orientation orientation;

    BarDiagramType* implementor; // the current type
    BarDiagramType* normalDiagram;
    BarDiagramType* stackedDiagram;
    BarDiagramType* percentDiagram;
    BarDiagramType* normalLyingDiagram;
    BarDiagramType* stackedLyingDiagram;
    BarDiagramType* percentLyingDiagram;
};

KCHART_IMPL_DERIVED_DIAGRAM( BarDiagram, AbstractCartesianDiagram, CartesianCoordinatePlane )

    class BarDiagram::BarDiagramType
    {
    public:
        explicit BarDiagramType( BarDiagram* d )
            : m_private( d->d_func() )
        {
        }
        virtual ~BarDiagramType() {}
        virtual BarDiagram::BarType type() const = 0;
        virtual const QPair<QPointF,  QPointF> calculateDataBoundaries() const = 0;
        virtual void paint( PaintContext* ctx ) = 0;
        BarDiagram* diagram() const;

    protected:
        // make some elements of m_private available to derived classes:
        AttributesModel* attributesModel() const;
        QModelIndex attributesModelRootIndex() const;
        ReverseMapper& reverseMapper();
        CartesianDiagramDataCompressor& compressor() const;

        void paintBars( PaintContext* ctx, const QModelIndex& index, const QRectF& bar, qreal maxDepth );
        void calculateValueAndGapWidths( int rowCount, int colCount,
            qreal groupWidth,
            qreal& barWidth,
            qreal& spaceBetweenBars,
            qreal& spaceBetweenGroups );

        BarDiagram::Private* m_private;
    };
}

#endif /* KCHARTBARDIAGRAM_P_H */
