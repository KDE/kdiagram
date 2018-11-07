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

private slots:
	void timeout();

private:
	QTimer					m_timer;
}; // class ModelParamVsParam


#endif // SUMGUI_MODELPARAMVSPARAM_H
