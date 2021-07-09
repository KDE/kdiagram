/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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

    const QString customizedLabel( const QString& label ) const override;

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
