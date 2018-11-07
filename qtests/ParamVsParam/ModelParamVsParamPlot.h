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

#ifndef SUMGUI_MODELPARAMVSPARAMPLOT_H
#define SUMGUI_MODELPARAMVSPARAMPLOT_H


#include <QSortFilterProxyModel>


class ModelParamVsParamPlot: public QSortFilterProxyModel
{
public:
	ModelParamVsParamPlot(
		QAbstractItemModel	*p_sourceModel,
		int						p_column1,
		int						p_column2,
		QObject					*p_parent = nullptr);

	int columnCount(
		const QModelIndex	&p_parent = QModelIndex()) const Q_DECL_OVERRIDE;

protected:
	QVariant data(
		const QModelIndex		&p_index,
		int						p_role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

	bool filterAcceptsColumn(
		int						p_source_column,
		const QModelIndex		&p_source_parent) const Q_DECL_OVERRIDE;

private:
	int					m_column1;
	int					m_column2;
}; // class ModelParamVsParamPlot


#endif // SUMGUI_MODELPARAMVSPARAMPLOT_H
