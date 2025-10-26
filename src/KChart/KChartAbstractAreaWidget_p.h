/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTABSTRACTAREAWIDGET_P_H
#define KCHARTABSTRACTAREAWIDGET_P_H

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

/** \file KChartAbstractAreaWidget_p.h
 *  \internal
 */

#include "KChartAbstractAreaBase_p.h"
#include "KChartAbstractAreaWidget.h"

#include "KChartMath_p.h"

namespace KChart
{

/**
 * \internal
 */
class Q_DECL_HIDDEN AbstractAreaWidget::Private : public AbstractAreaBase::Private
{
    friend class AbstractAreaWidget;

public:
    explicit Private();
    ~Private() override;

    Private(const Private &rhs)
        : AbstractAreaBase::Private(rhs)
        , currentLayoutSize()
    {
        // Just for consistency
    }

    QSize currentLayoutSize;

    // non-virtual method, calling widget->resizeLayout( size )
    void resizeLayout(AbstractAreaWidget *widget, const QSize &sz);
};

inline AbstractAreaWidget::AbstractAreaWidget(AbstractAreaWidget::Private *p, QWidget *parent)
    : QWidget(parent)
    , AbstractAreaBase(p)
{
    init();
}
inline AbstractAreaWidget::Private *AbstractAreaWidget::d_func()
{
    return static_cast<Private *>(AbstractAreaBase::d_func());
}
inline const AbstractAreaWidget::Private *AbstractAreaWidget::d_func() const
{
    return static_cast<const Private *>(AbstractAreaBase::d_func());
}

}

#endif /* KCHARTABSTRACTAREAWIDGET_P_H */
