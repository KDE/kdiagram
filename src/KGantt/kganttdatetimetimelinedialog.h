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

#ifndef KGANTTDATETIMETIMELINEDIALOG_H
#define KGANTTDATETIMETIMELINEDIALOG_H

#include "kganttglobal.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

namespace KGantt {
    class DateTimeTimeLine;

    class DateTimeTimeLineDialog : public QDialog {
        Q_OBJECT
    public:
        explicit DateTimeTimeLineDialog(DateTimeTimeLine *timeLine, QWidget* parent = nullptr);
        ~DateTimeTimeLineDialog() override;

    private Q_SLOTS:
        void ok();
        void openColorDialog();
        void updateColorButton();

    private:
        class Private;
        Private *d;
    };
}

#endif
