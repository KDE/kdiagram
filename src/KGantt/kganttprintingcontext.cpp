/*
 * Copyright (C) 2020 Dag Andersen <dag.andersen@kdemail.net>
 *
 * This file is part of the KGantt library.
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "kganttprintingcontext.h"

namespace KGantt
{

class Q_DECL_HIDDEN PrintingContext::Private {
public:
    PrintingContext::Scaling scaling;
    bool drawRowLabels;
    bool drawColumnLabels;
    qreal start;
    qreal end;
};

PrintingContext::PrintingContext()
    : d(new Private())
{
    d->scaling = NoScaling;
    d->drawRowLabels= true;
    d->drawColumnLabels =true;
    d->start = 0.0;
    d->end = 0.0;
}

PrintingContext::PrintingContext(const PrintingContext &other)
    : d(new Private())
{
    *d = *other.d;
}

PrintingContext::~PrintingContext()
{
    delete d;
}

PrintingContext::Scaling PrintingContext::scaling() const
{
    return d->scaling;
}

void PrintingContext::setScaling(const PrintingContext::Scaling &value)
{
    d->scaling = value;
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

qreal PrintingContext::start() const
{
    return d->start;
}

void PrintingContext::setStart(qreal start)
{
    d->start = start;
}

qreal PrintingContext::end() const
{
    return d->end;
}

void PrintingContext::setEnd(qreal end)
{
    d->end = end;
}

}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<( QDebug dbg, const KGantt::PrintingContext::Scaling &s)
{
    switch (s) {
        case KGantt::PrintingContext::NoScaling: dbg << "Scaling::NoScaling"; break;
        case KGantt::PrintingContext::FitSingle: dbg << "Scaling::FitSingle"; break;
        case KGantt::PrintingContext::FitVertical: dbg << "Scaling::FitVertical"; break;
        default: break;
    }
    return dbg;
}
QDebug operator<<( QDebug dbg, const KGantt::PrintingContext &ctx)
{
    dbg << "KGantt::PrintingContext[";
    dbg << ctx.scaling();
    dbg << "Rows:" << ctx.drawRowLabels();
    dbg << "Cols:" << ctx.drawColumnLabels();
    dbg << "range:" << ctx.start() << ',' << ctx.end();
    dbg << ']';
    return dbg;
}
#endif
