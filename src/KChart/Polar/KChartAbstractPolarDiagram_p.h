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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef KCHARTABSTRACTPOLARDIAGRAM_P_H
#define KCHARTABSTRACTPOLARDIAGRAM_P_H

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

#include "KChartAbstractPolarDiagram.h"
#include "KChartAbstractDiagram_p.h"
#include <KChartGridAttributes.h>
#include "KChartMath_p.h"


namespace KChart {

  class PolarCoordinatePlane;

/**
 * \internal
 */
class Q_DECL_HIDDEN AbstractPolarDiagram::Private : public AbstractDiagram::Private
{
    friend class AbstractPolarDiagram;
public:
    Private();
    ~Private();

    Private( const Private& rhs ) :
        AbstractDiagram::Private( rhs ),
        granularity( 0 )
        {
            // just for consistency
        }

    /** \reimpl */
    // FIXME: Optimize when needed
    qreal calcPercentValue( const QModelIndex & index ) const override
    {
        Q_ASSERT( index.isValid() );
        qreal sum = 0.0;
        for ( int row = 0; row < attributesModel->rowCount( QModelIndex() ); row++ )
            sum += attributesModel->data( attributesModel->index( row, index.column(), QModelIndex() ) ).toReal(); // checked
        if ( sum == 0.0 )
            return 0.0;
        return attributesModel->data( attributesModel->mapFromSource( index ) ).toReal() / sum * 100.0;
    }

private:
    qreal granularity;
};

KCHART_IMPL_DERIVED_DIAGRAM( AbstractPolarDiagram, AbstractDiagram, PolarCoordinatePlane )
/*
inline AbstractPolarDiagram::AbstractPolarDiagram( Private * p )
    : AbstractDiagram( p ) { init(); }
inline AbstractPolarDiagram::AbstractPolarDiagram(
    Private *p, QWidget* parent, PolarCoordinatePlane* plane )
    : AbstractDiagram( p, parent, plane ) { init(); }
inline AbstractPolarDiagram::Private * AbstractPolarDiagram::d_func()
{ return static_cast<Private*>( AbstractDiagram::d_func() ); }
inline const AbstractPolarDiagram::Private * AbstractPolarDiagram::d_func() const
{ return static_cast<const Private*>( AbstractDiagram::d_func() ); }
*/

}
#endif /* KCHARTABSTRACTCARTESIANDIAGRAM_P_H */
