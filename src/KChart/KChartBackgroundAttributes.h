/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTBACKGROUNDATTRIBUTES_H
#define KCHARTBACKGROUNDATTRIBUTES_H

#include <QDebug>
#include <QMetaType>
#include <QBrush>
#include "KChartGlobal.h"

namespace KChart {

/**
  * Set of attributes usable for background pixmaps
  */
class KCHART_EXPORT BackgroundAttributes
{
public:
    BackgroundAttributes();
    BackgroundAttributes( const BackgroundAttributes& );
    BackgroundAttributes &operator= ( const BackgroundAttributes& );

    ~BackgroundAttributes();

    enum BackgroundPixmapMode { BackgroundPixmapModeNone,
                                BackgroundPixmapModeCentered,
                                BackgroundPixmapModeScaled,
                                BackgroundPixmapModeStretched };

    void setVisible( bool visible );
    bool isVisible() const;

    void setBrush( const QBrush &brush );
    QBrush brush() const;

    void setPixmapMode( BackgroundPixmapMode mode );
    BackgroundPixmapMode pixmapMode() const;

    void setPixmap( const QPixmap &backPixmap );
    QPixmap pixmap() const;

    bool operator==( const BackgroundAttributes& ) const;
    inline bool operator!=( const BackgroundAttributes& other ) const { return !operator==(other); }

    bool isEqualTo( const BackgroundAttributes& other, bool ignorePixmap=false ) const;

private:
    KCHART_DECLARE_PRIVATE_BASE_VALUE( BackgroundAttributes )
}; // End of class BackgroundAttributes

}

#if !defined(QT_NO_DEBUG_STREAM)
KCHART_EXPORT QDebug operator<<(QDebug, const KChart::BackgroundAttributes& );
#endif /* QT_NO_DEBUG_STREAM */

KCHART_DECLARE_SWAP_SPECIALISATION( KChart::BackgroundAttributes )

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO( KChart::BackgroundAttributes, Q_MOVABLE_TYPE );
QT_END_NAMESPACE

Q_DECLARE_METATYPE( KChart::BackgroundAttributes )

#endif // KCHARTBACKGROUNDATTRIBUTES_H
