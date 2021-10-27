/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTABSTRACTCARTESIANDIAGRAM_P_H
#define KCHARTABSTRACTCARTESIANDIAGRAM_P_H

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

#include "KChartAbstractCartesianDiagram.h"

#include <KChartAbstractDiagram_p.h>
#include <KChartAbstractThreeDAttributes.h>
#include <KChartGridAttributes.h>
#include "KChartMath_p.h"


namespace KChart {

  class CartesianCoordinatePlane;
  class AbstractCartesianDiagram;

/**
 * \internal
 */
class Q_DECL_HIDDEN AbstractCartesianDiagram::Private : public AbstractDiagram::Private
{
    friend class AbstractCartesianDiagram;
public:
    Private();
    ~Private() override;

    Private( const Private& rhs ) :
        AbstractDiagram::Private( rhs ),
        // Do not copy axes and reference diagrams.
        axesList(),
        referenceDiagram( nullptr ),
        referenceDiagramOffset()
        {
        }

    /** \reimpl */
    CartesianDiagramDataCompressor::AggregatedDataValueAttributes aggregatedAttrs(
            const QModelIndex & index,
            const CartesianDiagramDataCompressor::CachePosition * position ) const override
    {
        if ( position )
            return compressor.aggregatedAttrs( diagram, index, *position );
        CartesianDiagramDataCompressor::AggregatedDataValueAttributes allAttrs;
        allAttrs[index] = diagram->dataValueAttributes( index );
        return allAttrs;
    }

   CartesianAxisList axesList;

   AbstractCartesianDiagram* referenceDiagram;
   QPointF referenceDiagramOffset;

   mutable CartesianDiagramDataCompressor compressor;
};

KCHART_IMPL_DERIVED_DIAGRAM( AbstractCartesianDiagram, AbstractDiagram, CartesianCoordinatePlane )

}
#endif /* KCHARTABSTRACTCARTESIANDIAGRAM_P_H */
