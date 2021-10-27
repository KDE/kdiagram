/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTABSTRACTAREA_P_H
#define KCHARTABSTRACTAREA_P_H

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

/** \file KChartAbstractArea_p.h
 *  \internal
 */

#include "KChartAbstractArea.h"
#include "KChartAbstractAreaBase_p.h"

#include "KChartMath_p.h"


namespace KChart {

/**
 * \internal
 */
class Q_DECL_HIDDEN AbstractArea::Private : public AbstractAreaBase::Private
{
    friend class AbstractArea;
public:
    explicit Private();
    ~Private() override;
};


inline AbstractArea::AbstractArea( Private * p )
  :  QObject(), AbstractAreaBase( p ), AbstractLayoutItem()
{
    init();
}
inline AbstractArea::Private * AbstractArea::d_func()
{
    return static_cast<Private*>( AbstractAreaBase::d_func() );
}
inline const AbstractArea::Private * AbstractArea::d_func() const
{
    return static_cast<const Private*>( AbstractAreaBase::d_func() );
}

}

#endif /* KCHARTABSTRACTAREA_P_H */

