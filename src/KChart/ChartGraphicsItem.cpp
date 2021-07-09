/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "ChartGraphicsItem.h"

using namespace KChart;

ChartGraphicsItem::ChartGraphicsItem()
    : QGraphicsPolygonItem()
    , m_row( -1 )
    , m_column( -1 )
{
}

ChartGraphicsItem::ChartGraphicsItem( int row, int column )
    : QGraphicsPolygonItem()
    , m_row( row )
    , m_column( column )
{
}
