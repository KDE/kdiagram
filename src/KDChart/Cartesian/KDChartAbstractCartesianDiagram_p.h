/**
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

#ifndef KDCHARTABSTRACTCARTESIANDIAGRAM_P_H
#define KDCHARTABSTRACTCARTESIANDIAGRAM_P_H

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

#include "KDChartAbstractCartesianDiagram.h"

#include <KDChartAbstractDiagram_p.h>
#include <KDChartAbstractThreeDAttributes.h>
#include <KDChartGridAttributes.h>

#include <KDABLibFakes>


namespace KDChart {

  class CartesianCoordinatePlane;
  class AbstractCartesianDiagram;

/**
 * \internal
 */
class AbstractCartesianDiagram::Private : public AbstractDiagram::Private
{
    friend class AbstractCartesianDiagram;
public:
    Private();
    virtual ~Private();

    Private( const Private& rhs ) :
        AbstractDiagram::Private( rhs ),
        // Do not copy axes and reference diagrams.
        axesList(),
        referenceDiagram( 0 )
        {
        }

    /** \reimpl */
    virtual CartesianDiagramDataCompressor::AggregatedDataValueAttributes aggregatedAttrs(
            const QModelIndex & index,
            const CartesianDiagramDataCompressor::CachePosition * position ) const
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

KDCHART_IMPL_DERIVED_DIAGRAM( AbstractCartesianDiagram, AbstractDiagram, CartesianCoordinatePlane )

}
#endif /* KDCHARTABSTRACTCARTESIANDIAGRAM_P_H */

