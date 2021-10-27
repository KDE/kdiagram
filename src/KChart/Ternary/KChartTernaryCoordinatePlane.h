/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTTERNARYCOORDINATEPLANE_H
#define KCHARTTERNARYCOORDINATEPLANE_H

#include "KChartAbstractCoordinatePlane.h"

namespace KChart {

    class TernaryGrid;

    /**
      * @brief Ternary coordinate plane
      */
    class KCHART_EXPORT TernaryCoordinatePlane
        : public AbstractCoordinatePlane
    {
        Q_OBJECT
        Q_DISABLE_COPY( TernaryCoordinatePlane )
        KCHART_DECLARE_PRIVATE_DERIVED_PARENT( TernaryCoordinatePlane, Chart* )

    public:
        explicit TernaryCoordinatePlane( Chart* parent = nullptr );
        ~TernaryCoordinatePlane() override;

        void addDiagram( AbstractDiagram* diagram ) override;

        void layoutDiagrams() override;

        const QPointF translate ( const QPointF& diagramPoint ) const override;

        void paint( QPainter* ) override;
        DataDimensionsList getDataDimensionsList() const override;

        /** \reimpl */
        QSize minimumSizeHint() const;
        /** \reimpl */
        QSizePolicy sizePolicy() const;

    private:
        TernaryGrid* grid() const;
    };

}

#endif
