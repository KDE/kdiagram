/*
 * SPDX-FileCopyrightText: 2020 Dag Andersen <dag.andersen@kdemail.net>
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "kganttprintingcontext.h"

namespace KGantt
{

class Q_DECL_HIDDEN PrintingContext::Private
{
public:
    PrintingContext::Fitting fitting;
    QRectF sceneRect;
    bool drawRowLabels;
    bool drawColumnLabels;
};

PrintingContext::PrintingContext()
    : d(new Private())
{
    d->fitting = NoFitting;
    d->drawRowLabels = true;
    d->drawColumnLabels = true;
}

PrintingContext::PrintingContext(const PrintingContext &other)
    : d(new Private(*other.d))
{
}

PrintingContext &PrintingContext::operator=(const PrintingContext &other)
{
    *d = *other.d;
    return *this;
}

PrintingContext::~PrintingContext()
{
    delete d;
    d = nullptr;
}

QRectF PrintingContext::sceneRect() const
{
    return d->sceneRect;
}

void PrintingContext::setSceneRect(const QRectF &rect)
{
    d->sceneRect = rect;
}

PrintingContext::Fitting PrintingContext::fitting() const
{
    return d->fitting;
}

void PrintingContext::setFitting(const PrintingContext::Fitting &value)
{
    d->fitting = value;
}

bool PrintingContext::drawRowLabels() const
{
    return d->drawRowLabels;
}

void PrintingContext::setDrawRowLabels(bool state)
{
    d->drawRowLabels = state;
}

bool PrintingContext::drawColumnLabels() const
{
    return d->drawColumnLabels;
}

void PrintingContext::setDrawColumnLabels(bool state)
{
    d->drawColumnLabels = state;
}

qreal PrintingContext::left() const
{
    return d->sceneRect.left();
}

void PrintingContext::setLeft(qreal left)
{
    d->sceneRect.setLeft(left);
}

qreal PrintingContext::top() const
{
    return d->sceneRect.top();
}

void PrintingContext::setTop(qreal top)
{
    d->sceneRect.setTop(top);
}

qreal PrintingContext::right() const
{
    return d->sceneRect.right();
}

void PrintingContext::setRight(qreal right)
{
    d->sceneRect.setRight(right);
}

qreal PrintingContext::bottom() const
{
    return d->sceneRect.bottom();
}

void PrintingContext::setBottom(qreal bottom)
{
    d->sceneRect.setBottom(bottom);
}

}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const KGantt::PrintingContext::Fitting &f)
{
    switch (f) {
    case KGantt::PrintingContext::NoFitting:
        dbg << "Fitting::NoFitting";
        break;
    case KGantt::PrintingContext::FitSinglePage:
        dbg << "Fitting::FitSinglePage";
        break;
    case KGantt::PrintingContext::FitPageHeight:
        dbg << "Fitting::FitPageHeight";
        break;
    default:
        break;
    }
    return dbg;
}
QDebug operator<<(QDebug dbg, const KGantt::PrintingContext &ctx)
{
    dbg << "KGantt::PrintingContext[";
    dbg << ctx.fitting();
    dbg << "Rows:" << ctx.drawRowLabels();
    dbg << "Cols:" << ctx.drawColumnLabels();
    dbg << ctx.sceneRect();
    dbg << ']';
    return dbg;
}
#endif
