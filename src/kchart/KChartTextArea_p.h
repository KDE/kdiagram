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

#ifndef KCHART_TEXT_AREA_P_H
#define KCHART_TEXT_AREA_P_H

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

/** \file KChartTextArea_p.h
 *  \internal
 */

#include "KChartTextArea.h"
#include "KChartAbstractAreaBase_p.h"
#include "KChartMath_p.h"


namespace KChart {

/**
 * \internal
 */
    class Q_DECL_HIDDEN TextArea::Private : public AbstractAreaBase::Private
    {
        friend class TextArea;
    public:
        explicit Private();
        virtual ~Private();

        Private( const Private& rhs ) :
            AbstractAreaBase::Private( rhs )
            {
                // Just for consistency
            }
    };


    inline TextArea::TextArea( Private * p )
        :  QObject(), AbstractAreaBase( p ), TextLayoutItem()
    {
        init();
    }
    inline TextArea::Private * TextArea::d_func()
    {
        return static_cast<Private*>( AbstractAreaBase::d_func() );
    }
    inline const TextArea::Private * TextArea::d_func() const
    {
        return static_cast<const Private*>( AbstractAreaBase::d_func() );
    }

}

#endif /* KCHART_TEXT_AREA_P_H */

