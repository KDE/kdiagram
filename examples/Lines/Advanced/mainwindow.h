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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <TableModel.h>

namespace KChart {
    class Chart;
    class LineDiagram;
}

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );

private:
    bool eventFilter(QObject* target, QEvent* event) Q_DECL_OVERRIDE;

private slots:

    void on_lineTypeCB_currentIndexChanged( const QString & text );
    void on_paintValuesCB_toggled( bool checked );
    void on_centerDataPointsCB_toggled( bool checked );
    void on_threeDModeCB_toggled( bool checked );
    void on_depthSB_valueChanged( int i );
    void on_animateAreasCB_toggled( bool checked );
    void on_highlightAreaCB_toggled( bool checked );
    void on_highlightAreaSB_valueChanged( int i );
    void setHighlightArea( int row, int column, int opacity,
                           bool checked, bool doUpdate );
    void on_trackAreasCB_toggled( bool checked );
    void on_trackAreasSB_valueChanged( int i );
    void setTrackedArea( int column, bool checked, bool doUpdate );
    void slot_timerFired();
    void on_reverseHorizontalCB_toggled( bool checked );
    void on_reverseVerticalCB_toggled( bool checked );

private:
    KChart::Chart* m_chart;
    KChart::LineDiagram* m_lines;
    TableModel m_model;
    int m_curRow;
    int m_curColumn;
    int m_curOpacity;
};


#endif /* MAINWINDOW_H */

