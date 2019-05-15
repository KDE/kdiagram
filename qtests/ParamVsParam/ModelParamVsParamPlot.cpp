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

#include "ModelParamVsParamPlot.h"

#include <QAbstractItemModel>

#include <KChartGlobal>


using namespace KChart;


static int	nrOfValid(0);
static int	nrOfInvalid(0);
static int	nrOfQt(0);
static int	nrOfKChart(0);


ModelParamVsParamPlot::ModelParamVsParamPlot(
	QAbstractItemModel	*p_sourceModel,
	int						p_column1,
	int						p_column2,
	QObject					*p_parent)
: QSortFilterProxyModel(p_parent),
	m_column1(p_column1),
	m_column2(p_column2)
{
	setSourceModel(p_sourceModel);
} // ModelParamVsParamPlot::ModelParamVsParamPlot()


int ModelParamVsParamPlot::columnCount(
	const QModelIndex	&/*p_parent*/) const
{
	return 2;
} // ModelParamVsParamPlot::columnCount()


QVariant ModelParamVsParamPlot::data(
	const QModelIndex		&p_index,
	int						p_role) const
{
	QVariant			ret;

	if (p_index.isValid())
	{
		nrOfValid++;

		switch (p_role)
		{
			case Qt::DisplayRole:
			case Qt::EditRole:
				nrOfQt++;

				switch (p_index.column())
				{
					case 0: // Parameter1
						ret = sourceModel()->data(sourceModel()->index(p_index.row(), m_column1));
					break;

					case 1: // Parameter2
						ret = sourceModel()->data(sourceModel()->index(p_index.row(), m_column2));
					break;

					default:
						ret = "Invalid column index";
						// Invalid column index cannot occur.
					break;
				} // switch column
			break;

			default:
				nrOfKChart++;
		} // switch role
	} // if index valid
	else
	{
		nrOfInvalid++;
	}

	return ret;
} // ModelParamVsParamPlot::data()


bool ModelParamVsParamPlot::filterAcceptsColumn(
	int						p_source_column,
	const QModelIndex		&/*p_source_parent*/) const
{
	return p_source_column == m_column1 || p_source_column == m_column2;
} // ModelParamVsParamPlot::filterAcceptsColumn()
