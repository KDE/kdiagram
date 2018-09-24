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

#include "mainwindow.h"

#include <KChartWidget>
#include <KChartAbstractDiagram>
#include <QDebug>
#include <QMessageBox>

using namespace KChart;

MainWindow::MainWindow( QWidget* parent )
 : QWidget( parent ), datasetCount( 3 )
{
    setupUi( this );

    QHBoxLayout* chartLayout = new QHBoxLayout( chartFrame );
    widget = new Widget( chartFrame );
    chartLayout->addWidget( widget );

    typeSelector->setCurrentIndex(1); // we start by LineDiagram

    connect( typeSelector, SIGNAL(activated(int)), SLOT(changeType()) );

    connect( btnAddDataset, SIGNAL(clicked()), SLOT(addDataset()) );

    connect( leadingSelector, SIGNAL(valueChanged(int)),
             this, SLOT(changeLeading(int)) );
}

void MainWindow::changeType()
{
    QString text = typeSelector->currentText();
    if ( text == "Widget::Bar" )
        widget->setType( Widget::Bar );
    else if ( text == "Widget::Line" )
        widget->setType( Widget::Line );
    else if ( text == "Widget::Pie" )
        widget->setType( Widget::Pie );
    else if ( text == "Widget::Polar" )
        widget->setType( Widget::Polar );
    else
        widget->setType( Widget::NoType );
}

void MainWindow::changeLeading( int leading )
{
    widget->setGlobalLeading( leading, leading, leading, leading );
}

void MainWindow::addDataset()
{
    QStringList parts = lineAddDataset->text().split( ';' );
    bool ok;
    QVector< qreal > vec;
    foreach ( const QString &str, parts ) {
        const qreal val = str.toDouble( &ok );
        if ( ok )
            vec.append( val );
    }
    const int rows = widget->diagram()->model()->rowCount();
    if ( vec.count() != rows ) {
        QMessageBox::warning( this, "Wrong number of values entered!",
                              QString( "You have entered %1 values,<br>but the data model needs %2 ones."
                                       "<br><br>Note: Use <b>;</b> to separate the values!" )
                                      .arg(vec.count()).arg(rows));
    } else {
        widget->setDataset( datasetCount++, vec, "user data" );
    }
}
