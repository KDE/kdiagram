/*
 * SPDX-FileCopyrightText: 2020 Dag Andersen <danders@get2net.dk>
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTPENSTYLECOMBOBOX_H
#define KGANTTPENSTYLECOMBOBOX_H

#include <QComboBox>

#include "kgantt_export.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
QT_END_NAMESPACE

namespace KGantt
{

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
