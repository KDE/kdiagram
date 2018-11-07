/*
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

#ifndef KCHARTLEVEYJENNINGSAXIS_H
#define KCHARTLEVEYJENNINGSAXIS_H

#include <QList>

#include "KChartCartesianAxis.h"

#include "KChartLeveyJenningsGridAttributes.h"

namespace KChart {

    class LeveyJenningsDiagram;

    /**
      * The class for levey jennings axes.
      *
      * For being useful, axes need to be assigned to a diagram, see
      * LeveyJenningsDiagram::addAxis and LeveyJenningsDiagram::takeAxis.
      *
      * \sa PolarAxis, AbstractCartesianDiagram
      */
    class KCHART_EXPORT LeveyJenningsAxis : public CartesianAxis
    {
        Q_OBJECT

        Q_DISABLE_COPY( LeveyJenningsAxis )
        KCHART_DECLARE_PRIVATE_DERIVED_PARENT( LeveyJenningsAxis, AbstractDiagram* )

    public:
        /**
          * C'tor of the class for levey jennings axes.
          *
          * \note If using a zero parent for the constructor, you need to call
          * your diagram's addAxis function to add your axis to the diagram.
          * Otherwise, there is no need to call addAxis, since the constructor
          * does that automatically for you, if you pass a diagram as parameter.
          *
          * \sa AbstractCartesianDiagram::addAxis
          */
        explicit LeveyJenningsAxis ( LeveyJenningsDiagram* diagram = nullptr );
        ~LeveyJenningsAxis();

        LeveyJenningsGridAttributes::GridType type() const;
        void setType( LeveyJenningsGridAttributes::GridType type );

        Qt::DateFormat dateFormat() const;
        void setDateFormat( Qt::DateFormat format );

        /**
         * Returns true if both axes have the same settings.
         */
        bool compare( const LeveyJenningsAxis* other ) const;

        /** reimpl */
        void paintCtx( PaintContext* ) Q_DECL_OVERRIDE;

    protected:
        virtual void paintAsOrdinate( PaintContext* );

        virtual void paintAsAbscissa( PaintContext* );
    };

    typedef QList<LeveyJenningsAxis*> LeveyJenningsAxisList;
}

#endif
