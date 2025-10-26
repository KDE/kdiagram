/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef CHARTGRAPHICSITEM_H
#define CHARTGRAPHICSITEM_H

#include <QGraphicsPolygonItem>

namespace KChart
{

/**
 * @brief Graphics item used inside of the ReverseMapper
 * \internal
 */
class ChartGraphicsItem : public QGraphicsPolygonItem
{
public:
    enum {
        Type = UserType + 1
    };

    ChartGraphicsItem();

    ChartGraphicsItem(int row, int column);

    int row() const
    {
        return m_row;
    }
    int column() const
    {
        return m_column;
    }
    int type() const override
    {
        return Type;
    }

private:
    int m_row;
    int m_column;
};

}

#endif
