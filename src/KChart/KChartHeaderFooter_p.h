/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTHEADERFOOTER_P_H
#define KCHARTHEADERFOOTER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the KD Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "KChartHeaderFooter.h"
#include "KChartTextArea_p.h"
#include "KChartChart.h"
#include "KChartMath_p.h"

#include <QMap>


class KTextDocument;

namespace KChart {
    class Chart;
    class TextAttributes;
}

/**
 * \internal
 */
class Q_DECL_HIDDEN KChart::HeaderFooter::Private : public KChart::TextArea::Private
{
    friend class KChart::HeaderFooter;
public:
    explicit Private();
    ~Private();

    Private( const Private& rhs ) :
        TextArea::Private( rhs ),
        type( rhs.type ),
        position( rhs.position )
        {
        }

    void updateTextDoc();

private:
    // user-settable
    HeaderFooterType type;
    Position position;
};

inline KChart::HeaderFooter::HeaderFooter( Private* d, KChart::Chart* parent )
    : TextArea( d )
{
    setParent( parent );
    init();
}
inline KChart::HeaderFooter::Private * KChart::HeaderFooter::d_func()
{
    return static_cast<Private*>( TextArea::d_func() );
}
inline const KChart::HeaderFooter::Private * KChart::HeaderFooter::d_func() const
{
    return static_cast<const Private*>( TextArea::d_func() );
}


#endif /* KCHARTHEADERFOOTER_P_H */
