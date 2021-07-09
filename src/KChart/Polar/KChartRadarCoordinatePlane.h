/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
