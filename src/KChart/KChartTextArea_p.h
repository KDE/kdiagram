/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHART_TEXT_AREA_P_H
#define KCHART_TEXT_AREA_P_H

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

/** \file KChartTextArea_p.h
 *  \internal
 */

#include "KChartAbstractAreaBase_p.h"
#include "KChartMath_p.h"
#include "KChartTextArea.h"

namespace KChart
{

/**
 * \internal
 */
class Q_DECL_HIDDEN TextArea::Private : public AbstractAreaBase::Private
{
    friend class TextArea;

public:
    explicit Private();
    ~Private() override;

    Private(const Private &rhs)
        : AbstractAreaBase::Private(rhs)
    {
        // Just for consistency
    }
};

inline TextArea::TextArea(Private *p)
    : QObject()
    , AbstractAreaBase(p)
    , TextLayoutItem()
{
    init();
}
inline TextArea::Private *TextArea::d_func()
{
    return static_cast<Private *>(AbstractAreaBase::d_func());
}
inline const TextArea::Private *TextArea::d_func() const
{
    return static_cast<const Private *>(AbstractAreaBase::d_func());
}

}

#endif /* KCHART_TEXT_AREA_P_H */
