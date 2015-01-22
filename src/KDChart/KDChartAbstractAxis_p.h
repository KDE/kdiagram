/**
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

#ifndef KDCHARTAXIS_P_H
#define KDCHARTAXIS_P_H

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

#include <QQueue>
#include <QTimer>

#include "KDChartAbstractArea_p.h"
#include "KDChartAbstractDiagram.h"
#include <KDChartTextAttributes.h>
#include <KDChartRulerAttributes.h>
#include <KDChartDiagramObserver.h>

#include <KDABLibFakes>


namespace KDChart {

/**
 * \internal
 */
class AbstractAxis::Private : public AbstractArea::Private
{
    friend class AbstractAxis;

public:
    Private( AbstractDiagram* diagram, AbstractAxis* axis );
    ~Private();

    bool setDiagram( AbstractDiagram* diagram, bool delayedInit = false );
    void unsetDiagram( AbstractDiagram* diagram );
    AbstractDiagram* diagram() const
    {
        return mDiagram;
    }
    bool hasDiagram( AbstractDiagram* diagram ) const;

    DiagramObserver* observer;

    TextAttributes textAttributes;
    RulerAttributes rulerAttributes;
    QStringList hardLabels;
    QStringList hardShortLabels;
    QQueue<AbstractDiagram*> secondaryDiagrams;

protected:
    AbstractDiagram* mDiagram;
    AbstractAxis*    mAxis;
};


inline AbstractAxis::AbstractAxis( Private * p, AbstractDiagram* diagram )
    :  AbstractArea( p )
{
    Q_UNUSED( diagram );
    init();
    QTimer::singleShot(0, this, SLOT(delayedInit()));
}

inline AbstractAxis::Private * AbstractAxis::d_func()
{ return static_cast<Private*>( AbstractArea::d_func() ); }
inline const AbstractAxis::Private * AbstractAxis::d_func() const
{ return static_cast<const Private*>( AbstractArea::d_func() ); }

}
#endif /* KDCHARTAREA_P_H */

