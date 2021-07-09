/*
 * SPDX-FileCopyrightText: 2020 Dag Andersen <danders@get2net.dk>
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTPENSTYLECOMBOBOX_P_H
#define KGANTTPENSTYLECOMBOBOX_P_H

#include <QComboBox>
#include <QListView>
#include <QStyleOptionMenuItem>

namespace KGantt {

    class PenStyleComboBoxListView : public QListView
    {
        Q_OBJECT
    public:
        PenStyleComboBoxListView(QComboBox *cmb = nullptr);
        
    protected:
        void resizeEvent(QResizeEvent *event) override;
        void paintEvent(QPaintEvent *e) override;

    private:
        QComboBox *combo;
    };
}

#endif
