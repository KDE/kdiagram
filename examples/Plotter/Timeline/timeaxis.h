/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef TIMEAXIS_H
#define TIMEAXIS_H

#include <KChartCartesianAxis>

class TimeAxis : public KChart::CartesianAxis
{
    Q_OBJECT
public:
    explicit TimeAxis( KChart::AbstractCartesianDiagram* parent );
    const QString customizedLabel( const QString& label ) const override;
};


#endif
