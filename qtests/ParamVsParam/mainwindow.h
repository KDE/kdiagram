/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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

private Q_SLOTS:
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
