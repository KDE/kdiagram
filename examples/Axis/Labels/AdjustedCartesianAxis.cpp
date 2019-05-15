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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "AdjustedCartesianAxis.h"


AdjustedCartesianAxis::AdjustedCartesianAxis ( KChart::AbstractCartesianDiagram* diagram )
    : CartesianAxis ( diagram )
    , m_lowerBound(0.0)
    , m_upperBound(0.0)
{
    // this bloc left empty intentionally
}

const QString AdjustedCartesianAxis::customizedLabel( const QString& label ) const
{
    bool bOK;
    qreal val = label.toDouble( & bOK );
    if ( bOK ) {
        if ( val < m_lowerBound )
            return tr("LOW");
        else if ( val > m_upperBound )
            return tr("HIGH");
    }
    return label;
}
