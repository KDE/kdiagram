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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __KCHART_PALETTE_H__
#define __KCHART_PALETTE_H__

#include <QObject>
#include <QBrush>
#include "KChartGlobal.h"

namespace KChart {

  /**
   * \brief A Palette is a set of brushes (or colors) to be used
   * for painting data sets.
   *
   * The palette class encapsulates a colletion of brushes, which in
   * the simplest case are colors, to be used for painting a series of
   * data sets. When asked for the m-th color, a palette of size n will
   * wrap around and thus cycle through the available colors.
   *
   * Three builtin palettes are provided for convenience, one with a default
   * set of colors, one with a subdued color selection, one with rainbow
   * colors.
   *
   * When a palette changes, it emits a changed() signal. Hook up to it, if
   * you want to repaint when the color selection changes.
   */

class KCHART_EXPORT Palette: public QObject
{
    Q_OBJECT
public:
    explicit Palette( QObject *parent  = nullptr );
    Palette( const Palette& );
    Palette &operator= ( const Palette & );

    ~Palette();

    /** Provide access to the three builtin palettes, one with standard bright
     * colors, one with more subdued colors, and one with rainbow colors.  */
    static const Palette& defaultPalette();
    static const Palette& subduedPalette();
    static const Palette& rainbowPalette();

    /** @return whether this represents a valid palette. For a palette to be
     * valid it needs to have at least one brush associated. */
    bool isValid() const;

    /** @return the number of brushed in the palette.  */
    int size() const;

    /** Adds \a brush to the palette. If no \a position is specified, the
     * brush is appended.
     */
    void addBrush( const QBrush & brush, int position = -1 );

    /**
     * Query the palette for a brush at the specified position. If the
     * position exceeds the size of the palette, it wraps around.
     */
    QBrush getBrush( int position ) const;

    /** Remove the brush at position \a position, if there is one.  */
    void removeBrush( int position );

Q_SIGNALS:
    /**  Emitted whenever the palette changes. Views listen to this and
     * repaing.  */
    void changed();

private:
    KCHART_DECLARE_PRIVATE_BASE_VALUE( Palette )
};

}

KCHART_DECLARE_SWAP_SPECIALISATION( KChart::Palette )

#endif
