/**
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KD Chart library.
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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "Model.h"

#include "ui_Controls.h"

#include <QWidget>



namespace KChart {
class Plotter;
}

class Model;
class QPushButton;
class QRadioButton;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget();

private Q_SLOTS:
    void functionToggled( bool checked );
    void addPointsButtonClicked();

private:
    QWidget* m_controlsContainer;
    Ui::Controls m_controls;
    QVector< QRadioButton* > m_functionSelector;
    QVector< QPushButton* > m_addPointsButtons;

    KChart::Plotter* m_plotter;
    Model m_model;
};

#endif
