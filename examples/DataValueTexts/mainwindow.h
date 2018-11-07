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
#include <KChartDataValueAttributes>

namespace KChart {
    class Chart;
    class BarDiagram;
}

class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );

private slots:
    void on_scopeOneBarRB_toggled(  bool checked );
    void on_scopeBarDatasetSB_valueChanged( int i );
    void on_scopeBarItemSB_valueChanged(    int i );
    void on_scopeDatasetRB_toggled( bool checked );
    void on_scopeDatasetSB_valueChanged( int i );
    void on_scopeCommonRB_toggled( bool checked );

    void on_paintValuesCB_toggled( bool checked );

    void on_fontCombo_currentIndexChanged( const QString & text );
    void on_relativeSizeSB_valueChanged( int i );
    void on_minimumSizeSB_valueChanged(  int i );
    void on_rotationSB_valueChanged( int i );

    void on_posPosCombo_currentIndexChanged(   const QString & text );
    void on_posAlignCombo_currentIndexChanged( const QString & text );
    void on_posPadHoriSB_valueChanged( int i );
    void on_posPadVertSB_valueChanged( int i );
    void on_negPosCombo_currentIndexChanged(   const QString & text );
    void on_negAlignCombo_currentIndexChanged( const QString & text );
    void on_negPadHoriSB_valueChanged( int i );
    void on_negPadVertSB_valueChanged( int i );

    void on_labelLE_textEdited(  const QString & text );
    void on_prefixLE_textEdited( const QString & text );
    void on_suffixLE_textEdited( const QString & text );

private:
    const QModelIndex currentIndex() const;
    const KChart::DataValueAttributes attributes() const;
    const char* positionToScreenName( const KChart::Position& pos ) const;
    const Qt::Alignment alignmentFromScreeName( const QString& name ) const;
    const QString alignmentToScreenName( const Qt::Alignment& align ) const;
    void populateWidgets();
    void setAttributes( const KChart::DataValueAttributes& da );

    KChart::Chart* m_chart;
    KChart::BarDiagram* m_bars;
    TableModel m_model;
};


#endif /* MAINWINDOW_H */

