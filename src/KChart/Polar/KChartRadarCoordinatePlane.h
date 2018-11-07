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

#ifndef KCHART_RADAR_COORDINATEPLANE_H
#define KCHART_RADAR_COORDINATEPLANE_H

#include "KChartPolarCoordinatePlane.h"

namespace KChart {

    class Chart;
    
    /**
      * @brief Radar coordinate plane
      */
    class KCHART_EXPORT RadarCoordinatePlane : public PolarCoordinatePlane
    {
        Q_OBJECT

        Q_DISABLE_COPY( RadarCoordinatePlane )
        KCHART_DECLARE_PRIVATE_DERIVED_PARENT( RadarCoordinatePlane, Chart* )

    public:

        explicit RadarCoordinatePlane ( Chart* parent = nullptr );
        ~RadarCoordinatePlane();
        
                
        /**
         * Set the attributes to be used for axis captions.
         *
         * To disable axis captions, for example, your code should like this:
         * \code
         * TextAttributes ta = plane->textAttributes();
         * ta.setVisible( false );
         * plane-setTextAttributes( ta );
         * \endcode
         */
        void setTextAttributes( const TextAttributes & attr );
 
        /**
         * \return The attributes used for axis.
         *
         * \note This function always returns a valid set of text attributes:
         * If no special text attributes was set a default one is 
         * returned.
         *
         * \sa setTextAttributes
         */
        const TextAttributes textAttributes() const;

    };
    
}

#endif
