/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTABSTRACTTERNARYDIAGRAM_P_H
#define KCHARTABSTRACTTERNARYDIAGRAM_P_H

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

#include "KChartAbstractTernaryDiagram.h"

#include "KChartTernaryCoordinatePlane.h"
#include <KChartAbstractDiagram_p.h>
#include <KChartAbstractThreeDAttributes.h>
#include <KChartGridAttributes.h>
#include "KChartPainterSaver_p.h"
#include "KChartMath_p.h"

#include "ReverseMapper.h"
#include "ChartGraphicsItem.h"

namespace KChart {

/**
 * \internal
 */
    class Q_DECL_HIDDEN AbstractTernaryDiagram::Private : public AbstractDiagram::Private
    {
        friend class AbstractTernaryDiagram;
    public:
        Private();
        ~Private() {}

        Private( const Private& rhs ) :
            AbstractDiagram::Private( rhs ),
            // Do not copy axes and reference diagrams.
            axesList(),
            referenceDiagram( nullptr ),
            referenceDiagramOffset()
        {
        }

        TernaryAxisList axesList;

        AbstractTernaryDiagram* referenceDiagram;
        QPointF referenceDiagramOffset;

        void drawPoint( QPainter* p, int row, int column,
                        const QPointF& widgetLocation )
        {
            // Q_ASSERT( false ); // unused, to be removed
            static const qreal Diameter = 5.0;
            static const qreal Radius = Diameter / 2.0;
            QRectF ellipseRect( widgetLocation - QPointF( Radius, Radius ),
                                QSizeF( Diameter, Diameter ) );
            p->drawEllipse( ellipseRect );

            reverseMapper.addRect( row, column, ellipseRect );
        }

        virtual void paint( PaintContext* paintContext )
        {
            paintContext->painter()->setRenderHint( QPainter::Antialiasing,
                                                    antiAliasing );
            if ( !axesList.isEmpty() ) {

                for ( TernaryAxis* axis : qAsConst(axesList) ) {
                    PainterSaver s( paintContext->painter() );
                    axis->paintCtx( paintContext );
                }
            }
        }
    };

    KCHART_IMPL_DERIVED_DIAGRAM( AbstractTernaryDiagram, AbstractDiagram, TernaryCoordinatePlane )
}

#endif /* KCHARTABSTRACTTERNARYDIAGRAM_P_H */
