/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTTERNARYPOINTDIAGRAM_P_H
#define KCHARTTERNARYPOINTDIAGRAM_P_H

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

#include "KChartTernaryPointDiagram.h"
#include "KChartAbstractTernaryDiagram_p.h"
#include "KChartMath_p.h"

namespace KChart {

/**
 * \internal
 */
    class Q_DECL_HIDDEN TernaryPointDiagram::Private : public AbstractTernaryDiagram::Private
    {
        friend class TernaryPointDiagram;
    public:
        Private();
        ~Private() override {}

        Private( const Private& rhs )
            : AbstractTernaryDiagram::Private( rhs )
        {
        }

    };

KCHART_IMPL_DERIVED_DIAGRAM( TernaryPointDiagram, AbstractTernaryDiagram, TernaryCoordinatePlane )
/*
inline TernaryPointDiagram::TernaryPointDiagram( Private * p, TernaryCoordinatePlane* plane )
  : AbstractTernaryDiagram( p, plane ) { init(); }
inline TernaryPointDiagram::Private * TernaryPointDiagram::d_func()
{ return static_cast<Private*>( AbstractTernaryDiagram::d_func() ); }
inline const TernaryPointDiagram::Private * TernaryPointDiagram::d_func() const
{ return static_cast<const Private*>( AbstractTernaryDiagram::d_func() ); }
*/

}

#endif /* KCHARTTERNARYPOINTDIAGRAM_P_H */

