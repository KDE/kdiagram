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


#include "kganttdatetimetimelinedialog.h"
#include "ui_kganttdatetimetimelinedialog.h"
#include "kganttdatetimetimeline.h"
#include "kganttpenstylecombobox.h"

#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QColorDialog>
#include <QTime>
#include <QTimer>
#include <QMetaEnum>
#include <QAbstractItemModel>

namespace KGantt {
    class DateTimeTimeLineDialog::Private
    {
    public:
        Private() : timeLine(nullptr) {}

        Ui::DateTimeTimeLineDialog ui;
        DateTimeTimeLine *timeLine;
        QColor penColor;
    };
}

using namespace KGantt;

DateTimeTimeLineDialog::DateTimeTimeLineDialog(DateTimeTimeLine *timeLine, QWidget* parent)
    : QDialog(parent)
    , d( new Private())
{
    d->timeLine = timeLine;
    d->ui.setupUi(this);

    DateTimeTimeLine::Options opt = d->timeLine->options();
    if (opt & DateTimeTimeLine::Foreground) {
        d->ui.foreground->setChecked(true);
    } else if (opt & DateTimeTimeLine::Background) {
        d->ui.background->setChecked(true);
    }
    d->ui.useCustomPen->setCheckState((opt & DateTimeTimeLine::UseCustomPen) ? Qt::Checked : Qt::Unchecked);

    QPen pen = d->timeLine->pen(); // get standard if not set
    d->ui.penWidth->setValue(pen.width());
    d->ui.penStyle->setCurrentStyle(pen.style());
    d->penColor = pen.color();

    d->ui.updateInterval->setTime(QTime::fromMSecsSinceStartOfDay(d->timeLine->interval()));
    d->ui.dateTime->setDateTime(timeLine->dateTime());

    connect(d->ui.buttonBox, &QDialogButtonBox::accepted, this, &DateTimeTimeLineDialog::ok);
    connect(d->ui.openColorDialog, &QAbstractButton::clicked, this, &DateTimeTimeLineDialog::openColorDialog);

    QTimer::singleShot(0, this, SLOT(updateColorButton())); // wait for correct button size
}

DateTimeTimeLineDialog::~DateTimeTimeLineDialog()
{
}

void DateTimeTimeLineDialog::ok()
{
    DateTimeTimeLine::Options opt;
    if (d->ui.foreground->isChecked()) {
        opt |= DateTimeTimeLine::Foreground;
    } else if (d->ui.background->isChecked()) {
        opt |= DateTimeTimeLine::Background;
    }
    if (d->ui.useCustomPen->checkState()) {
        opt |= DateTimeTimeLine::UseCustomPen;
    }
    d->timeLine->setOptions(opt);
    QPen pen;
    pen.setWidth(d->ui.penWidth->value());
    pen.setStyle(static_cast<Qt::PenStyle>(d->ui.penStyle->currentData().toInt()));
    pen.setColor(d->penColor);
    d->timeLine->setPen(pen);

    d->timeLine->setInterval(d->ui.updateInterval->time().msecsSinceStartOfDay());
    d->timeLine->setDateTime(d->ui.dateTime->dateTime());
}

void DateTimeTimeLineDialog::updateColorButton()
{
    QSize size = d->ui.openColorDialog->size();
    qInfo()<<Q_FUNC_INFO<<size<<d->penColor;
    QPixmap px(size);
    px.fill();
    QPainter painter(&px);
    painter.fillRect(0, 0, size.width(), size.height(), d->penColor);
    d->ui.openColorDialog->setIcon(QIcon(px));    
}

void DateTimeTimeLineDialog::openColorDialog()
{
    QColorDialog dlg;
    if (dlg.exec() == QDialog::Accepted) {
        d->penColor = dlg.selectedColor();
        updateColorButton();
    }
}
