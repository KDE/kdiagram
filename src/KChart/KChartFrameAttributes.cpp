/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartFrameAttributes.h"

#include "KChartMath_p.h"

#define d d_func()

using namespace KChart;

class Q_DECL_HIDDEN FrameAttributes::Private
{
    friend class FrameAttributes;

public:
    Private();

private:
    bool visible;
    QPen pen;
    qreal cornerRadius;
    int padding;
};

FrameAttributes::Private::Private()
    : visible(false)
    , cornerRadius(0)
    , padding(0)
{
}

FrameAttributes::FrameAttributes()
    : _d(new Private())
{
}

FrameAttributes::FrameAttributes(const FrameAttributes &r)
    : _d(new Private(*r.d))
{
}

FrameAttributes &FrameAttributes::operator=(const FrameAttributes &r)
{
    if (this == &r)
        return *this;

    *d = *r.d;

    return *this;
}

FrameAttributes::~FrameAttributes()
{
    delete _d;
    _d = nullptr;
}

bool FrameAttributes::operator==(const FrameAttributes &r) const
{
    return (isVisible() == r.isVisible() && pen() == r.pen() && cornerRadius() == r.cornerRadius() && padding() == r.padding());
}

void FrameAttributes::setVisible(bool visible)
{
    d->visible = visible;
}

bool FrameAttributes::isVisible() const
{
    return d->visible;
}

void FrameAttributes::setPen(const QPen &pen)
{
    d->pen = pen;
}

QPen FrameAttributes::pen() const
{
    return d->pen;
}

void FrameAttributes::setCornerRadius(qreal radius)
{
    d->cornerRadius = radius;
}

qreal FrameAttributes::cornerRadius() const
{
    return d->cornerRadius;
}

void FrameAttributes::setPadding(int padding)
{
    d->padding = padding;
}

int FrameAttributes::padding() const
{
    return d->padding;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KChart::FrameAttributes &fa)
{
    dbg << "KChart::FrameAttributes("
        << "visible=" << fa.isVisible() << "pen=" << fa.pen() << "cornerRadius=" << fa.cornerRadius() << "padding=" << fa.padding() << ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
