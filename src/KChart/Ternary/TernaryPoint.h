/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef TERNARYPOINT_H
#define TERNARYPOINT_H

#include <QPointF>
#include <QtDebug>

/**
 * @brief TernaryPoint defines a point within a ternary coordinate plane
 * \internal
 */
class TernaryPoint
{
public:
    TernaryPoint();
    TernaryPoint(qreal a, qreal b);

    qreal a() const
    {
        return m_a;
    }
    qreal b() const
    {
        return m_b;
    }
    qreal c() const
    {
        return 1.0 - m_a - m_b;
    }

    void set(qreal a, qreal b);

    bool isValid() const;

private:
    qreal m_a;
    qreal m_b;
};

QDebug operator<<(QDebug stream, const TernaryPoint &point);

QPointF translate(const TernaryPoint &);

#endif
