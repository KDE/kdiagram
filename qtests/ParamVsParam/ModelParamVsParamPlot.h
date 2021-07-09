/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
		const QModelIndex	&p_parent = QModelIndex()) const override;

protected:
	QVariant data(
		const QModelIndex		&p_index,
		int						p_role = Qt::DisplayRole) const override;

	bool filterAcceptsColumn(
		int						p_source_column,
		const QModelIndex		&p_source_parent) const override;

private:
	int					m_column1;
	int					m_column2;
}; // class ModelParamVsParamPlot


#endif // SUMGUI_MODELPARAMVSPARAMPLOT_H
