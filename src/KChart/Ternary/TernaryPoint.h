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

#ifndef TERNARYPOINT_H
#define TERNARYPOINT_H

#include <QtDebug>
#include <QPointF>

/**
  * @brief TernaryPoint defines a point within a ternary coordinate plane
  * \internal
  */
class TernaryPoint
{
public:
    TernaryPoint();
    TernaryPoint( qreal a, qreal b );

    qreal a() const { return m_a; }
    qreal b() const { return m_b; }
    qreal c() const { return 1.0 - m_a - m_b; }

    void set( qreal a, qreal b );

    bool isValid() const;

private:
    qreal m_a;
    qreal m_b;
};

QDebug operator<<( QDebug stream, const TernaryPoint& point );

QPointF translate( const TernaryPoint& );

#endif
