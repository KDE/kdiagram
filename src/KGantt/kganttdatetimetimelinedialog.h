/*
 * SPDX-FileCopyrightText: 2020 Dag Andersen <danders@get2net.dk>
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
