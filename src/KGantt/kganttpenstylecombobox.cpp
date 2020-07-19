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


#include "kganttpenstylecombobox.h"
#include "kganttpenstylecombobox_p.h"

#include <QStandardItemModel>
#include <QStyleOptionComboBox>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QMetaEnum>
#include <QPixmap>
#include <QDebug>

using namespace KGantt;

PenStyleComboBoxListView::PenStyleComboBoxListView(QComboBox *cmb)
    : combo(cmb)
{}

void PenStyleComboBoxListView::resizeEvent(QResizeEvent *event)
{
    resizeContents(viewport()->width(), contentsSize().height());
    QListView::resizeEvent(event);
}

void PenStyleComboBoxListView::paintEvent(QPaintEvent *e)
{
    if (combo) {
        QStyleOptionComboBox opt;
        opt.initFrom(combo);
        opt.editable = combo->isEditable();
        if (combo->style()->styleHint(QStyle::SH_ComboBox_Popup, &opt, combo)) {
            //we paint the empty menu area to avoid having blank space that can happen when scrolling
            QStyleOptionMenuItem menuOpt;
            menuOpt.initFrom(this);
            menuOpt.palette = palette();
            menuOpt.state = QStyle::State_None;
            menuOpt.checkType = QStyleOptionMenuItem::NotCheckable;
            menuOpt.menuRect = e->rect();
            menuOpt.maxIconWidth = 0;
            menuOpt.tabWidth = 0;
            QPainter p(viewport());
            combo->style()->drawControl(QStyle::CE_MenuEmptyArea, &menuOpt, &p, this);
        }
    }
    QListView::paintEvent(e);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    QRect rect = e->rect();
    QModelIndex idx = indexAt(rect.topLeft());
    while (idx.isValid()) {
        QRect itemRect = rectForIndex(idx);
        pen.setStyle(static_cast<Qt::PenStyle>(idx.data(Qt::UserRole).toInt()));
        QPainter painter(viewport());
        painter.setPen(pen);
        painter.drawLine(itemRect.left()+1, itemRect.center().y(), itemRect.right()-1, itemRect.center().y());
        rect.adjust(0, itemRect.height(), 0, 0);
        idx = indexAt(rect.topLeft());
    }    
}

PenStyleComboBox::PenStyleComboBox(QWidget *parent)
    : QComboBox(parent)
{
    PenStyleComboBoxListView *v = new PenStyleComboBoxListView(this);
    v->setViewMode(QListView::ListMode);
    v->setModel(new QStandardItemModel(this));
    setView(v);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    QMetaEnum styles = QMetaEnum::fromType<Qt::PenStyle>();
    for (int i = 0; i < styles.keyCount(); ++i) {
        int value = styles.value(i);
        if (value == Qt::NoPen) {
            continue;
        }
        addItem(QString(), value);
    }
}

void PenStyleComboBox::setCurrentStyle(Qt::PenStyle style)
{
    setCurrentIndex(findData(static_cast<int>(style)));
}

Qt::PenStyle PenStyleComboBox::currentStyle() const
{
    return static_cast<Qt::PenStyle>(currentData().toInt());
}

void PenStyleComboBox::paintEvent(QPaintEvent *pe)
{
    QComboBox::paintEvent(pe);

    QStyleOptionComboBox option;
    option.initFrom(this);
    option.frame = hasFrame();
    QRect r = style()->subControlRect(QStyle::CC_ComboBox, &option, QStyle::SC_ComboBoxEditField, this);
    if (!option.frame) { // frameless combo boxes have smaller margins but styles do not take this into account
        r.adjust(-14, 0, 14, 1);
    }
    QPen pen;
    pen.setStyle(currentStyle());
    pen.setColor(Qt::black);
    pen.setWidth(2);
    
    QPainter painter(this);
    painter.setPen(pen);
    painter.drawLine(r.left(), r.center().y(), r.right(), r.center().y());
}
