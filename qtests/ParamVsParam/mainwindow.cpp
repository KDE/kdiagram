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

#include "ModelParamVsParam.h"
#include "ModelParamVsParamPlot.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>


#include <KChartChart>
#include <KChartDataValueAttributes>
#include <KChartGridAttributes>
#include <KChartLineDiagram>


using namespace KChart;


MainWindow::MainWindow(
    QWidget					*p_parent)
:
    QWidget(p_parent),
	m_sourceModel(new ModelParamVsParam),
	m_timeoutLineEdit(new QLineEdit("1")),
	m_nrOfParametersLineEdit(new QLineEdit("4")),
	m_nrOfSamplesLineEdit(new QLineEdit("4")),
	m_paramVsParamGridLayout(new QGridLayout)
{
	connect(m_timeoutLineEdit, SIGNAL(editingFinished()), SLOT(timeoutEditingFinished()));
	connect(m_nrOfParametersLineEdit, SIGNAL(editingFinished()), SLOT(editingFinished()));
	connect(m_nrOfSamplesLineEdit, SIGNAL(editingFinished()), SLOT(editingFinished()));

	QVBoxLayout	*vBoxLayout = new QVBoxLayout;
	setLayout(vBoxLayout);

	QGridLayout	*gridLayout = new QGridLayout;
	vBoxLayout->addLayout(gridLayout);
	gridLayout->setColumnStretch(2, 1);

	int	row(0);

	gridLayout->addWidget(new QLabel("Timeout [sec]:"), row, 0);
	gridLayout->addWidget(m_timeoutLineEdit, row++, 1);

	gridLayout->addWidget(new QLabel("Number of Parameters:"), row, 0);
	gridLayout->addWidget(m_nrOfParametersLineEdit, row++, 1);

	gridLayout->addWidget(new QLabel("Number of Samples:"), row, 0);
	gridLayout->addWidget(m_nrOfSamplesLineEdit, row++, 1);

	vBoxLayout->addLayout(m_paramVsParamGridLayout);

	m_sourceModel->setTimeout(m_timeoutLineEdit->text().toInt());
	m_sourceModel->populate(m_nrOfParametersLineEdit->text().toInt(), m_nrOfSamplesLineEdit->text().toInt());
	addPlots();
} // MainWindow::MainWindow()


MainWindow::~MainWindow()
{
	delete m_sourceModel;
	m_sourceModel = nullptr;
} // MainWindow::~MainWindow()


void MainWindow::timeoutEditingFinished()
{
	if (m_timeoutLineEdit->isModified())
	{
		m_timeoutLineEdit->setModified(false);
		m_sourceModel->setTimeout(m_timeoutLineEdit->text().toInt());
	}
} // MainWindow::timeoutEditingFinished()


void MainWindow::editingFinished()
{
	if (m_nrOfParametersLineEdit->isModified() || m_nrOfSamplesLineEdit->isModified())
	{
		m_nrOfParametersLineEdit->setModified(false);
		m_nrOfSamplesLineEdit->setModified(false);

		m_sourceModel->populate(m_nrOfParametersLineEdit->text().toInt(), m_nrOfSamplesLineEdit->text().toInt());
		m_sourceModel->stopSampling();
		removePlots();
		addPlots();
		m_sourceModel->startSampling();
	}
} // MainWindow::editingFinished()


void MainWindow::addPlots()
{
	for (int r = 0; r < m_sourceModel->columnCount(); r++)
	{
		for (int c = 0; c < m_sourceModel->columnCount(); c++)
		{

			Chart * chart = new Chart;
			m_paramVsParamGridLayout->addWidget(chart, r, c);

			CartesianCoordinatePlane * plane = static_cast<CartesianCoordinatePlane *>(chart->coordinatePlane());

			// Hide grid.
			GridAttributes ga = plane->globalGridAttributes();
			ga.setGridVisible(false);
			plane->setGlobalGridAttributes(ga);

			// Set axes fixed scale.
			qreal						xoffset(c * 10);
			qreal						yoffset(r * 10);
			QPair<qreal, qreal>	horizontalRange(xoffset, xoffset + 10);
			QPair<qreal, qreal>	verticalRange(yoffset, yoffset + 10);
			plane->setHorizontalRange(horizontalRange);
			plane->setVerticalRange(verticalRange);

			if (r == c)
			{
			}
			else
			{
				ModelParamVsParamPlot	*modelParamVsParamPlot =
					new ModelParamVsParamPlot(m_sourceModel, c, r);

				LineDiagram	*lineDiagram = new LineDiagram;
				lineDiagram->setDatasetDimension(2);
				lineDiagram->setModel(modelParamVsParamPlot);
				lineDiagram->setPen(Qt::NoPen);
				setMarkerAttributes(lineDiagram);

				CartesianAxis	*xAxis = new CartesianAxis(lineDiagram);
				CartesianAxis	*yAxis = new CartesianAxis(lineDiagram);
				xAxis->setPosition(CartesianAxis::Bottom);
				yAxis->setPosition(CartesianAxis::Left);
				xAxis->setTitleText('P' + QString::number(c));
				yAxis->setTitleText('P' + QString::number(r));
				lineDiagram->addAxis(xAxis);
				lineDiagram->addAxis(yAxis);

				chart->coordinatePlane()->replaceDiagram(lineDiagram);
			}
		} // for all rows
	} // for all columns
} // MainWindow::addPlots()


void MainWindow::removePlots()
{
	while (m_paramVsParamGridLayout->count())
	{
		Chart *chart = static_cast<Chart *>(m_paramVsParamGridLayout->itemAt(0)->widget());
		m_paramVsParamGridLayout->removeWidget(chart);
		delete chart;
	}
} // MainWindow::removePlots()


void MainWindow::setMarkerAttributes(
	KChart::LineDiagram		*p_lineDiagram)
{
	QColor								markerColor			= Qt::green;
	MarkerAttributes::MarkerStyle	markerStyle			= MarkerAttributes::Marker4Pixels;
	QColor								firstMarkerColor	= Qt::red;
	MarkerAttributes::MarkerStyle	firstMarkerStyle	= MarkerAttributes::MarkerDiamond;
	DataValueAttributes				dva					= p_lineDiagram->dataValueAttributes();
	MarkerAttributes					ma						= dva.markerAttributes();
	TextAttributes						ta						= dva.textAttributes();

	ma.setVisible(true);
	ma.setMarkerColor(markerColor);
	ma.setMarkerStyle(markerStyle);
	dva.setMarkerAttributes(ma);

	ta.setVisible(false);
	dva.setTextAttributes(ta);

	dva.setVisible(true);
	p_lineDiagram->setDataValueAttributes(0, dva);
	p_lineDiagram->setDataValueAttributes(1, dva);

	// Override for first row.
	ma.setMarkerColor(firstMarkerColor);
	ma.setMarkerStyle(firstMarkerStyle);
	dva.setMarkerAttributes(ma);
	QAbstractItemModel	*model = p_lineDiagram->model();
	p_lineDiagram->setDataValueAttributes(model->index(0, 0), dva);
	p_lineDiagram->setDataValueAttributes(model->index(0, 1), dva);
} // MainWindow::setMarkerAttributes()
