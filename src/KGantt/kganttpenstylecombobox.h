/*
 * Copyright (C) 2020 Dag Andersen <danders@get2net.dk>
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

#ifndef KGANTTPENSTYLECOMBOBOX_H
#define KGANTTPENSTYLECOMBOBOX_H

#include <QComboBox>

#include "kgantt_export.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
QT_END_NAMESPACE

namespace KGantt {

    class KGANTT_EXPORT PenStyleComboBox : public QComboBox
    {
        Q_OBJECT
    public:
        explicit PenStyleComboBox(QWidget *parent = nullptr);

        void setCurrentStyle(Qt::PenStyle style);
        Qt::PenStyle currentStyle() const;

    protected:
        void paintEvent(QPaintEvent *pe) override;
    };
}

#endif
