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

#ifndef ADJUSTED_CARTESIAN_AXIS_H
#define ADJUSTED_CARTESIAN_AXIS_H

#include <KChartCartesianAxis>
#include <KChartGlobal>


class AdjustedCartesianAxis: public KChart::CartesianAxis
{
    Q_OBJECT

    Q_DISABLE_COPY( AdjustedCartesianAxis )

public:
    explicit AdjustedCartesianAxis( KChart::AbstractCartesianDiagram* diagram = nullptr );

    const QString customizedLabel( const QString& label ) const Q_DECL_OVERRIDE;

    void setBounds( qreal lower, qreal upper ) {
        m_lowerBound = lower;
        m_upperBound = upper;
    }
    qreal lowerBound() const { return m_lowerBound; }
    qreal upperBound() const { return m_upperBound; }

private:
    qreal m_lowerBound;
    qreal m_upperBound;
};

#endif // ADJUSTED_CARTESIAN_AXIS_H
