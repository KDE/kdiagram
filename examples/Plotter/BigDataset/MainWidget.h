/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
