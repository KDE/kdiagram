/*
 * SPDX-FileCopyrightText: 2019 Dag Andersen <danders@get2net.dk>
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTDATETIMETIMELINE_H
#define KGANTTDATETIMETIMELINE_H

#include "kganttglobal.h"

#include <QObject>

class QDateTime;

namespace KGantt {

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
     *  timeLine->setOptions(Foreground | UseCustomPen);
     *  timeLine->setPen(QPen(Qt:red));
     *  // Update the timeline every 5 seconds
     *  timeLine->setInterval(5000);
     * \endcode
     */
    class KGANTT_EXPORT DateTimeTimeLine : public QObject
    {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( DateTimeTimeLine )
    public:
        enum Option {
            Foreground = 1,     ///< Display the timeline in the foreground.
            Background = 2,     ///< Display the timeline in the background.
            UseCustomPen = 4,   ///< Paint the timeline using the pen set with setPen().
            MaxOptions = 0xFFFF
        };
        Q_DECLARE_FLAGS(Options, Option)

        /**
         * Create a timeline object.
         * 
         * By default, no timeline is displayed.
         */
        DateTimeTimeLine();

        /**
         * @return options
         */
        DateTimeTimeLine::Options options() const;

        /**
         * Set options to @p options.
         * If both Background and Foreground are set, Foreground is used.
         */
        void setOptions(DateTimeTimeLine::Options options);

        /**
         * @return the datetime
         * If the datetime is not valid, the current datetime is returned.
         */
        QDateTime dateTime() const;

        /**
         * Set datetime to @p dt.
         */
        void setDateTime(const QDateTime &dt);

        /**
         * @return the update interval in milliseconds
         */
        int interval() const;

        /**
         * Set timer interval to @p msecs milliseconds.
         * Setting a zero time disables the timer.
         */
        void setInterval(int msec);

        /**
         * @return the pen that will be used for rendering the timeline
         * If no pen has been set with setPen(), a default pen is returned.
         */
        QPen pen() const;

        /**
         * Set the custom pen to @p pen.
         */
        void setPen(const QPen &pen);

        /**
         * @return the pen that has been set with setPen()
         */
        QPen customPen() const;

    Q_SIGNALS:
        void updated();
    };
}

Q_DECLARE_OPERATORS_FOR_FLAGS(KGantt::DateTimeTimeLine::Options)

#endif /* KGANTTDATETIMETIMELINE_H */

