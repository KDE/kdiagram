/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "AdjustedCartesianAxis.h"


AdjustedCartesianAxis::AdjustedCartesianAxis ( KChart::AbstractCartesianDiagram* diagram )
    : CartesianAxis ( diagram )
    , m_lowerBound(0.0)
    , m_upperBound(0.0)
{
    // this block left empty intentionally
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
