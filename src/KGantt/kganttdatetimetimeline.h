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

#ifndef KGANTTDATETIMETIMELINE_H
#define KGANTTDATETIMETIMELINE_H

#include "kganttglobal.h"

#include <QObject>

class QDateTime;

namespace KGantt {

    class KGANTT_EXPORT DateTimeTimeLine : public QObject
    {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( DateTimeTimeLine )
    public:
        enum Option {
            Foreground = 1,     /// Display the timeline in the foreground.
            Background = 2,     /// Display the timeline in the background.
            UseCustomPen = 4,   /// Paint the timeline using the pen set with setTimelinePen().
            MaxOptions = 0xFFFF
        };
        Q_DECLARE_FLAGS(Options, Option)

        DateTimeTimeLine();

        DateTimeTimeLine::Options options() const;
        void setOptions(DateTimeTimeLine::Options options);
        QDateTime dateTime() const;
        void setDateTime(const QDateTime &dt);
        void setInterval(int msec);
        QPen pen() const;
        void setPen(const QPen &pen);

    Q_SIGNALS:
        void updated();
    };
    Q_DECLARE_OPERATORS_FOR_FLAGS(DateTimeTimeLine::Options)
}

#endif /* KGANTTDATETIMETIMELINE_H */

