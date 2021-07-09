/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTLINEATTRIBUTES_H
#define KCHARTLINEATTRIBUTES_H

#include <QMetaType>
#include "KChartGlobal.h"

namespace KChart {

/**
  * @brief Set of attributes for changing the appearance of line charts
  */
class KCHART_EXPORT LineAttributes
{
public:
    /**
      \brief MissingValuesPolicy specifies how a missing value will be shown in a line diagram.

      Missing value is assumed if the data cell contains a QVariant that can not be
      interpreted as a qreal, or if the data cell is hidden while its dataset is not hidden.

      \li \c MissingValuesAreBridged the default: No markers will be shown for missing values
      but the line will be bridged if there is at least one valid cell before and after
      the missing value(s), otherwise the segment will be hidden.
      \li \c MissingValuesHideSegments Line segments starting with a missing value will
      not be shown, and no markers will be shown for missing values, so this will look like
      a piece of the line is missing.
      \li \c MissingValuesShownAsZero Missing value(s) will be treated like normal zero values,
      and markers will shown for them too, so there will be no visible difference between a
      zero value and a missing value.
      \li \c MissingValuesPolicyIgnored (internal value, do not use)

      */
    enum MissingValuesPolicy {
        MissingValuesAreBridged,
        MissingValuesHideSegments,
        MissingValuesShownAsZero,
        MissingValuesPolicyIgnored };

    LineAttributes();
    LineAttributes( const LineAttributes& );
    LineAttributes &operator= ( const LineAttributes& );

    ~LineAttributes();

    /* line chart and area chart - all types */
    void setMissingValuesPolicy( MissingValuesPolicy policy );
    MissingValuesPolicy missingValuesPolicy() const;

    /* area chart - all types */
    /**
     * Sets the lower or upper (depending on the displayed value being positive or
     * negative, resp.) bounding line (i.e., the dataset with the line data). The area
     * is then drawn between this line and the line of the specified dataset.
     * Pass -1 to draw the area between this line and the zero line.
     */
    void setAreaBoundingDataset( int dataset );
    int areaBoundingDataset() const;

    /**
     * Determines if lines are to be drawn or not. This property does not
     * effect visibility of markers and text labels.
     *
     * This is useful for e.g. bubble charts where you need circular markers
     * but want no connecting lines to be drawn.
     *
     * By default lines are drawn, i.e. this property is true.
     */
    void setVisible( bool visible );
    bool isVisible() const;

    void setDisplayArea( bool display );
    bool displayArea() const;
    /*allows viewing the covered areas*/
    void setTransparency( uint alpha );
    uint transparency() const;

    bool operator==( const LineAttributes& ) const;
    inline bool operator!=( const LineAttributes& other ) const { return !operator==(other); }

private:
    KCHART_DECLARE_PRIVATE_BASE_VALUE( LineAttributes )
}; // End of class LineAttributes

}

#if !defined(QT_NO_DEBUG_STREAM)
KCHART_EXPORT QDebug operator<<(QDebug, const KChart::LineAttributes& );
#endif /* QT_NO_DEBUG_STREAM */

KCHART_DECLARE_SWAP_SPECIALISATION( KChart::LineAttributes )

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO( KChart::LineAttributes, Q_MOVABLE_TYPE );
QT_END_NAMESPACE

Q_DECLARE_METATYPE( KChart::LineAttributes )

#endif // KCHARTLINEATTRIBUTES_H
