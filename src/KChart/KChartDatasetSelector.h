/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTDATASETSELECTOR_H
#define KCHARTDATASETSELECTOR_H

#include <QFrame>

#include "KChartDatasetProxyModel.h"


/**
 * \cond PRIVATE_API_DOCU
 *
 * ( This class is used internally by DatasetSelectorWidget. )
 */
QT_BEGIN_NAMESPACE
namespace Ui {
    class DatasetSelector;
}
QT_END_NAMESPACE
/**
 * \endcond
 */

namespace KChart {

    class KCHART_EXPORT DatasetSelectorWidget : public QFrame
    {
        Q_OBJECT

    public:
        explicit DatasetSelectorWidget ( QWidget* parent = nullptr );
        ~DatasetSelectorWidget() override;

    public Q_SLOTS:
        void setSourceRowCount ( const int& rowCount );
        void setSourceColumnCount ( const int& columnCount );

    Q_SIGNALS:
        void configureDatasetProxyModel (
            const KChart::DatasetDescriptionVector& rowConfig,
            const KChart::DatasetDescriptionVector& columnConfig );

        void mappingDisabled ();

    private Q_SLOTS:
        void updateState ( bool );
        void calculateMapping();

    private:
        void resetDisplayValues ();

        Ui::DatasetSelector* mUi;
        int mSourceRowCount;
        int mSourceColumnCount;
    };

}

#endif
