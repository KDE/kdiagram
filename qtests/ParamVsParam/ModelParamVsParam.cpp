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

#include "ModelParamVsParam.h"


ModelParamVsParam::ModelParamVsParam(
	QObject					*p_parent)
:
	QStandardItemModel(p_parent)
{
	connect(&m_timer, SIGNAL(timeout()), SLOT(timeout()));
	//m_timer.setSingleShot(true);
	m_timer.setInterval(2000);
} // ModelParamVsParam::ModelParamVsParam()


void ModelParamVsParam::setTimeout(
	int					p_timeout)
{
	m_timer.setInterval(p_timeout * 1000);
} // ModelParamVsParam::setTimeout()


void ModelParamVsParam::startSampling()
{
	m_timer.start();
} // ModelParamVsParam::startSampling()


void ModelParamVsParam::stopSampling()
{
	m_timer.stop();
} // ModelParamVsParam::stopSampling()


void ModelParamVsParam::populate(
	int					p_nrOfParameters,
	int					p_nrOfSamples)
{
	m_timer.stop();

	setColumnCount(p_nrOfParameters);
	setRowCount(p_nrOfSamples);
	timeout();

	m_timer.start();
} // ModelParamVsParam::populate()


void ModelParamVsParam::timeout()
{
	blockSignals(true);

	for (int r = 0; r < rowCount(); r++)
		for (int c = 0; c < columnCount(); c++)
		{
			// First column values in range 0..10, second column in range 10..20 etc.
			qreal	offset(c * 10);
			qreal	value(offset + (10.0 * rand()) / RAND_MAX);
			setData(index(r, c), value);
		}

	blockSignals(false);

	QModelIndex	topLeft(index(0, 0));
	QModelIndex	bottomRight(index(rowCount() - 1, columnCount() - 1));
	Q_EMIT dataChanged(topLeft, bottomRight);
} // ModelParamVsParam::timeout()
