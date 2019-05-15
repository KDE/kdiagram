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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef KCHARTABSTRACTAREABASE_P_H
#define KCHARTABSTRACTAREABASE_P_H

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

/** \file KChartAbstractAreaBase_p.h
 *  \internal
 */

#include "KChartAbstractAreaBase.h"
#include "KChartTextAttributes.h"
#include "KChartFrameAttributes.h"
#include "KChartBackgroundAttributes.h"
#include "KChartMath_p.h"


namespace KChart {

/**
 * \internal
 */
    class Q_DECL_HIDDEN AbstractAreaBase::Private
    {
        friend class AbstractAreaBase;
    public:
        explicit Private();
        virtual ~Private();

        Private( const Private& rhs ) :
            amountOfLeftOverlap( 0 ),
            amountOfRightOverlap( 0 ),
            amountOfTopOverlap( 0 ),
            amountOfBottomOverlap( 0 ),
            visible( rhs.visible ),
            frameAttributes( rhs.frameAttributes ),
            backgroundAttributes( rhs.backgroundAttributes )
            {
            }

    protected:
        void init();

        // These are set each time the area's sizeHint()
        // (or the maximumSize(), resp.) is calculated:
        // They store additional layout-information about
        // space needed around the area.
        // Other classes (e.g. KChart::AutoSpacer) can use
        // these data to determine how much space has to
        // be added additionally ...
        mutable int amountOfLeftOverlap;
        mutable int amountOfRightOverlap;
        mutable int amountOfTopOverlap;
        mutable int amountOfBottomOverlap;

    private:
        bool visible;
        KChart::FrameAttributes frameAttributes;
        KChart::BackgroundAttributes backgroundAttributes;
    };

    inline AbstractAreaBase::AbstractAreaBase( AbstractAreaBase::Private * p ) :
        _d( p ) { init(); }

}
#endif /* KCHARTABSTRACTAREABASE_P_H */
