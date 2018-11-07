/*
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
    virtual ~Private();

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
            const CartesianDiagramDataCompressor::CachePosition * position ) const Q_DECL_OVERRIDE
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
