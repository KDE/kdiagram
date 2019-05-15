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

#include <QStandardItemModel>

#include <KChartChart>
#include <KChartGridAttributes>
#include <KChartFrameAttributes>
#include <KChartTextAttributes>
#include <KChartDataValueAttributes>
#include <KChartMarkerAttributes>
#include <KChartPlotter>
#include <KChartLegend>
#include <KChartBackgroundAttributes>

#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	KChart::Chart chart;

	QStandardItemModel model;

        const double offset = 600;
	model.setRowCount( 100 );
	model.setColumnCount( 2 ); // 1 data set
	for ( int i = 0; i < 100; ++i ) {
		double t = i + offset;
		double v = i + offset;
		QModelIndex index = model.index( i, 0 );
		model.setData( index, t );
		index = model.index( i, 1 );
		model.setData( index, v );
	}

	model.setHeaderData( 0, Qt::Horizontal, "Dataset 1" );

	// general chart layout
	KChart::FrameAttributes fm = chart.frameAttributes();
	fm.setVisible( true );
	fm.setPen( QPen( Qt::black ) );
	chart.setFrameAttributes( fm );
	chart.setGlobalLeading( 10, 0, 10, 10 );

	KChart::BackgroundAttributes chart_bg;
	chart_bg.setBrush( Qt::white );
	chart_bg.setVisible( true );
	chart.setBackgroundAttributes( chart_bg );

	// coordinate plane setup
	KChart::AbstractCoordinatePlane * plane1 = chart.coordinatePlane();
	plane1->setRubberBandZoomingEnabled( true );

	// create cartesian diagrams
	KChart::Plotter * plotter = new KChart::Plotter;
	plotter->setAntiAliasing( false );
	plotter->setModel( &model );
	plane1->replaceDiagram( plotter );

	// customize grids
	KChart::CartesianCoordinatePlane * cp1 = static_cast< KChart::CartesianCoordinatePlane * >( plane1 );
	KChart::GridAttributes gv = cp1->gridAttributes( Qt::Vertical );
	QPen gridPen( QColor( 200, 100, 100 ) );
	gridPen.setStyle( Qt::DashLine );
	gv.setGridPen( gridPen );
	gridPen.setStyle( Qt::DotLine );
	gridPen.setColor( QColor( 255,155,155 ) );
	gv.setSubGridPen( gridPen );
	cp1->setGridAttributes( Qt::Vertical,  gv );

        // Enable isometric scaling
        cp1->setIsometricScaling( true );

	// axis
	KChart::CartesianAxis * xAxis = new KChart::CartesianAxis( plotter );
	xAxis->setPosition( KChart::CartesianAxis::Bottom );
	xAxis->setTitleText("X-Title");

	KChart::TextAttributes att = xAxis->titleTextAttributes();
	QFont f = att.font();
	f.setBold( true );
	att.setFont( f );
	att.setAutoShrink( true );
	att.setFontSize( KChart::Measure( 16 ) );
	xAxis->setTitleTextAttributes( att );

	KChart::CartesianAxis * y1Axis = new KChart::CartesianAxis( plotter );
	y1Axis->setPosition( KChart::CartesianAxis::Left );
	y1Axis->setTitleText( "Y-Title" );

	att = y1Axis->titleTextAttributes();
	f = att.font();
	f.setBold( true );
	att.setFont( f );
	att.setAutoShrink( true );
	att.setFontSize( KChart::Measure( 16 ) );
	y1Axis->setTitleTextAttributes( att );

	// add the axis to the plotter
	plotter->addAxis( xAxis );
	plotter->addAxis( y1Axis );

	// create legend
	KChart::Legend * legend = new KChart::Legend( plotter, &chart );
	chart.addLegend( legend );
	att = legend->textAttributes();
	f = att.font();
	f.setBold( false );
	att.setFont( f );
	att.setAutoShrink( true );
	legend->setTextAttributes( att );

	legend->setPosition( KChart::Position::East );
	legend->setAlignment( Qt::AlignCenter );
	legend->setTitleText( "Curves" );
	att = legend->titleTextAttributes();
	f = att.font();
	f.setBold( true );
	att.setFont( f );
	att.setAutoShrink( true );
	att.setFontSize( KChart::Measure( 16 ) );
	legend->setTitleTextAttributes( att );

	KChart::BackgroundAttributes legend_bg;
	legend_bg.setBrush( Qt::white );
	legend_bg.setVisible( true );
	legend->setBackgroundAttributes( legend_bg );

	KChart::DataValueAttributes attr = plotter->dataValueAttributes();
	KChart::TextAttributes tattr = attr.textAttributes();
        tattr.setFontSize( KChart::Measure( 12, KChartEnums::MeasureCalculationModeAbsolute ) );
	tattr.setRotation( 0 );
	attr.setTextAttributes( tattr );
	plotter->setDataValueAttributes( attr );

	// customize marker properties

	// Dataset 1 : green, MarkerRing, no line
	QColor SERIES_1_OUTLINE = QColor( 0, 128, 0 );
	attr = plotter->dataValueAttributes( 0 );
	KChart::MarkerAttributes mattr = attr.markerAttributes();
	mattr.setMarkerColor( SERIES_1_OUTLINE );
//        mattr.setMarkerStyle( KChart::MarkerAttributes::MarkerRing );
	mattr.setMarkerSize( QSizeF( 6.0, 6.0 ) );
	mattr.setVisible( true );
	attr.setMarkerAttributes( mattr );
	attr.setVisible( true );
	plotter->setDataValueAttributes( 0, attr );
	plotter->setPen( 0, Qt::NoPen );

	chart.show();
	return a.exec();
}
