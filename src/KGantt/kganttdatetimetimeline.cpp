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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

/*!\class KGantt::DateTimeTimeLine
 * \ingroup KGantt
 *
 * This class implements a timeline.
 *
 * The timeline can optionally be shown in the Background or in the Foreground.
 * Default is Foreground.
 * 
 * The pen can be set with setPen(), and must be activated by setting the option UseCustomPen.
 * 
 * The datetime can be set using setDateTime().
 * 
 * The timeline can priodically moved to the current datetime
 * by setting the interval > 0 with setInterval().
 * Setting a zero interval turns the periodically update off.
 * 
 * The timeline is off by default.
 *
 * For example:
 * \code
 *  // Show a red timeline in the foreground
 *  timeLine->setOptions(UseCustomPen);
 *  timeLine->setPen(QPen(Qt:red));
 *  // Update the timeline every 5 seconds
 *  timeLine->setInterval(5000);
 * \endcode
 */

/**
 * Create a timeline object.
 * 
 * By default, no timeline is displayed.
 */
DateTimeTimeLine::DateTimeTimeLine()
    : _d( new Private())
{
    _d->pen = QPen(QApplication::palette().color(QPalette::Highlight), 0);
    connect(&_d->timer, SIGNAL(timeout()), this, SIGNAL(updated()));
}

#define d d_func()
/**
 * @return options
 */
DateTimeTimeLine::Options DateTimeTimeLine::options() const
{
    return d->options;
}

/**
 * Set options to @p options.
 * If both Background and Foreground are set, Foreground is used.
 */
void DateTimeTimeLine::setOptions(DateTimeTimeLine::Options options)
{
    d->options = options;
    if (options & Foreground) {
        d->options &= ~Background;
    }
    Q_EMIT updated();
}

/**
 * @return the datetime
 * If the datetime is not valid, the current datetime is returned.
 */
QDateTime DateTimeTimeLine::dateTime() const
{
    return d->dateTime.isValid() ? d->dateTime : QDateTime::currentDateTime();
}

/**
 * Set datetime to @p dt.
 */
void DateTimeTimeLine::setDateTime(const QDateTime &dt)
{
    d->dateTime = dt;
    Q_EMIT updated();
}

/**
 * Set timer interval to @p msecs milliseconds.
 * Setting a zero time disables the timer.
 */
void DateTimeTimeLine::setInterval(int msecs)
{
    d->timer.stop();
    d->timer.setInterval(msecs);
    Q_EMIT updated();
    if (msecs > 0) {
        d->timer.start();
    }
}

/**
 * @return the pen to be used to draw the timeline.
 * If option UseCustomPen is not set a default pen is returned.
 */
QPen DateTimeTimeLine::pen() const
{
    if (d->options & DateTimeTimeLine::UseCustomPen) {
        return d->pen;
    }
    return QPen(QApplication::palette().color(QPalette::Highlight), 0);
}

/**
 * Set the custom pen to @p pen.
 */
void DateTimeTimeLine::setPen(const QPen &pen)
{
    d->pen = pen;
    Q_EMIT updated();
}

#undef d
