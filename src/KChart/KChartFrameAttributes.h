/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTFRAMEATTRIBUTES_H
#define KCHARTFRAMEATTRIBUTES_H

#include <QDebug>
#include <QMetaType>
#include <QPen>
#include "KChartGlobal.h"

namespace KChart {

/**
  * @brief A set of attributes for frames around items
  */
class KCHART_EXPORT FrameAttributes
{
public:
    FrameAttributes();
    FrameAttributes( const FrameAttributes& );
    FrameAttributes &operator= ( const FrameAttributes& );

    ~FrameAttributes();

    void setVisible( bool visible );
    bool isVisible() const;

    void setPen( const QPen & pen );
    QPen pen() const;

    void setCornerRadius( qreal radius );
    qreal cornerRadius() const;

    void setPadding( int padding );
    int padding() const;

    bool operator==( const FrameAttributes& ) const;
    inline bool operator!=( const FrameAttributes& other ) const { return !operator==(other); }

private:

    KCHART_DECLARE_PRIVATE_BASE_VALUE( FrameAttributes )
}; // End of class FrameAttributes

}

#if !defined(QT_NO_DEBUG_STREAM)
KCHART_EXPORT QDebug operator<<(QDebug, const KChart::FrameAttributes& );
#endif /* QT_NO_DEBUG_STREAM */

KCHART_DECLARE_SWAP_SPECIALISATION( KChart::FrameAttributes )

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO( KChart::FrameAttributes, Q_MOVABLE_TYPE );
QT_END_NAMESPACE

Q_DECLARE_METATYPE( KChart::FrameAttributes )

#endif // KCHARTFRAMEATTRIBUTES_H
