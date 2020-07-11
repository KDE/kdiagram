/*
 * Copyright (C) 2019 Dag Andersen <danders@get2net.dk>
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

#include "kganttdatetimetimeline.h"

#include <QApplication>
#include <QDateTime>
#include <QString>
#include <QPalette>
#include <QPen>
#include <QTimer>
#include <QDebug>



namespace KGantt {
    class Q_DECL_HIDDEN DateTimeTimeLine::Private
    {
    public:
        Private() : options(Foreground) {}
        
        DateTimeTimeLine::Options options;
        QDateTime dateTime;
        QPen pen;
        QTimer timer;
    };
    
}

using namespace KGantt;




DateTimeTimeLine::DateTimeTimeLine()
    : _d( new Private())
{
    _d->options = {};
    _d->pen = QPen(QApplication::palette().color(QPalette::Highlight), 0);
    connect(&_d->timer, SIGNAL(timeout()), this, SIGNAL(updated()));
}

#define d d_func()

DateTimeTimeLine::Options DateTimeTimeLine::options() const
{
    return d->options;
}


void DateTimeTimeLine::setOptions(DateTimeTimeLine::Options options)
{
    d->options = options;
    if (options & Foreground) {
        d->options &= ~Background;
    }
    Q_EMIT updated();
}


QDateTime DateTimeTimeLine::dateTime() const
{
    return d->dateTime.isValid() ? d->dateTime : QDateTime::currentDateTime();
}


void DateTimeTimeLine::setDateTime(const QDateTime &dt)
{
    d->dateTime = dt;
    Q_EMIT updated();
}


int DateTimeTimeLine::interval() const
{
    return d->timer.interval();
}


void DateTimeTimeLine::setInterval(int msecs)
{
    d->timer.stop();
    d->timer.setInterval(msecs);
    Q_EMIT updated();
    if (msecs > 0) {
        d->timer.start();
    }
}


QPen DateTimeTimeLine::pen() const
{
    if (d->options & DateTimeTimeLine::UseCustomPen) {
        return d->pen;
    }
    return QPen(QApplication::palette().color(QPalette::Highlight), 0);
}


void DateTimeTimeLine::setPen(const QPen &pen)
{
    d->pen = pen;
    Q_EMIT updated();
}


QPen DateTimeTimeLine::customPen() const
{
    return d->pen;
}


#undef d
