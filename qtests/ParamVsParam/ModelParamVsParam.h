/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef SUMGUI_MODELPARAMVSPARAM_H
#define SUMGUI_MODELPARAMVSPARAM_H


#include <QStandardItemModel>
#include <QTimer>


class ModelParamVsParam: public QStandardItemModel
{
	Q_OBJECT

public:
	ModelParamVsParam(
		QObject					*p_parent = nullptr);

	void setTimeout(
		int					p_timeout);

	void startSampling();

	void stopSampling();

	void populate(
		int					p_nrOfParameters = 8,
		int					p_nrOfSamples = 100);

private Q_SLOTS:
	void timeout();

private:
	QTimer					m_timer;
}; // class ModelParamVsParam


#endif // SUMGUI_MODELPARAMVSPARAM_H
