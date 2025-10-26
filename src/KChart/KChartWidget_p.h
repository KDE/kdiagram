/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef __KCHARTWIDGET_P_H__
#define __KCHARTWIDGET_P_H__

//
//  W A R N I N G
//  -------------
//
// This file is not part of the KD Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "KChartMath_p.h"
#include <KChartCartesianCoordinatePlane.h>
#include <KChartChart.h>
#include <KChartPolarCoordinatePlane.h>
#include <KChartWidget.h>

#include <QGridLayout>
#include <QStandardItemModel>

/**
 * \internal
 */
class Q_DECL_HIDDEN KChart::Widget::Private
{
    friend class ::KChart::Widget;
    Widget *const q;

public:
    explicit Private(Widget *qq);
    ~Private(); // non-virtual, since nothing inherits this

protected:
    QGridLayout layout;
    QStandardItemModel m_model;
    Chart m_chart;
    CartesianCoordinatePlane m_cartPlane;
    PolarCoordinatePlane m_polPlane;

    int usedDatasetWidth;
};

#endif // KChartWidget_p_H
