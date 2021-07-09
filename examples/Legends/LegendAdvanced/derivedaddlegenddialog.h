/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef DERIVEDADDLEGENDDIALOG_H
#define DERIVEDADDLEGENDDIALOG_H

#include "ui_addlegenddialog.h"

class DerivedAddLegendDialog : public QDialog, public Ui::AddLegendDialog
{
    Q_OBJECT

public:
    DerivedAddLegendDialog( QWidget* parent = nullptr );
};

#endif // DERIVEDADDLEGENDDIALOG_H
