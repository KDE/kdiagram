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
