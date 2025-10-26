/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTABSTRACTPROXYMODEL_H
#define KCHARTABSTRACTPROXYMODEL_H

#include <QAbstractProxyModel>

#include "KChartGlobal.h"

namespace KChart
{
/**
 * @brief Base class for all proxy models used inside KChart
 * \internal
 */
class KCHART_EXPORT AbstractProxyModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    /** This is basically KDAbstractProxyModel, but only the
          bits that we really need from it */
    explicit AbstractProxyModel(QObject *parent = nullptr);

    /*! \reimpl */
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;
    /*! \reimpl */
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;

    /*! \reimpl */
    QModelIndex index(int row, int col, const QModelIndex &index) const override;
    /*! \reimpl */
    QModelIndex parent(const QModelIndex &index) const override;
};
}

#endif /* KCHARTABSTRACTPROXYMODEL_H */
