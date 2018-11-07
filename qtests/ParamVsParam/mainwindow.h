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


#include	<QWidget>


class ModelParamVsParam;

class QGridLayout;
class QLineEdit;

namespace KChart
{
	class	LineDiagram;
}


class	MainWindow:	public QWidget
{
	 Q_OBJECT

public:
	 MainWindow(
		 QWidget					*p_parent =	nullptr);

	 virtual	~MainWindow();

private slots:
	void timeoutEditingFinished();
	void editingFinished();

private:
	void addPlots();
	void removePlots();
	void setMarkerAttributes(
		KChart::LineDiagram		*p_lineDiagram);

private:
	ModelParamVsParam		*m_sourceModel;
	QLineEdit				*m_timeoutLineEdit;
	QLineEdit				*m_nrOfParametersLineEdit;
	QLineEdit				*m_nrOfSamplesLineEdit;
	QGridLayout				*m_paramVsParamGridLayout;
};	//	class	MainWindow


#endif // MAINWINDOW_H
