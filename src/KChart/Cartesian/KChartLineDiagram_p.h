/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTLINEDIAGRAM_P_H
#define KCHARTLINEDIAGRAM_P_H

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

#include "KChartLineDiagram.h"

#include <QPainterPath>

#include "KChartThreeDLineAttributes.h"
#include "KChartAbstractCartesianDiagram_p.h"
#include "KChartCartesianDiagramDataCompressor_p.h"
#include "KChartMath_p.h"


namespace KChart {

    class PaintContext;

/**
 * \internal
 */
    class Q_DECL_HIDDEN LineDiagram::Private : public AbstractCartesianDiagram::Private
    {
        friend class LineDiagram;
        friend class LineDiagramType;

    public:
        Private();
        Private( const Private& rhs );
        ~Private() override;

        LineDiagramType* implementor; // the current type
        LineDiagramType* normalDiagram;
        LineDiagramType* stackedDiagram;
        LineDiagramType* percentDiagram;
        bool centerDataPoints;
        bool reverseDatasetOrder;
    };

    KCHART_IMPL_DERIVED_DIAGRAM( LineDiagram, AbstractCartesianDiagram, CartesianCoordinatePlane )

    class LineDiagram::LineDiagramType
    {
    public:
        explicit LineDiagramType( LineDiagram* d )
            : m_private( d->d_func() )
        {
        }
        virtual ~LineDiagramType() {}
        virtual LineDiagram::LineType type() const = 0;
        virtual const QPair<QPointF,  QPointF> calculateDataBoundaries() const = 0;
        virtual void paint( PaintContext* ctx ) = 0;
        LineDiagram* diagram() const;

    protected:
        // make some elements of m_private available to derived classes:
        AttributesModel* attributesModel() const;
        QModelIndex attributesModelRootIndex() const;
        ReverseMapper& reverseMapper();
        CartesianDiagramDataCompressor& compressor() const;

        qreal interpolateMissingValue( const CartesianDiagramDataCompressor::CachePosition& pos ) const;

        int datasetDimension() const;

        qreal valueForCell( int row, int column ) const;

        LineDiagram::Private* m_private;
    };
}

#endif /* KCHARTLINEDIAGRAM_P_H */
