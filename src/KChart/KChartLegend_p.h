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

#ifndef KCHARTLEGEND_P_H
#define KCHARTLEGEND_P_H

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

#include "KChartLegend.h"

#include <KChartDiagramObserver.h>
#include "KChartAbstractAreaWidget_p.h"
#include <KChartTextAttributes.h>
#include <KChartMarkerAttributes.h>
#include "KChartMath_p.h"

#include <QList>
#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include <QVector>

QT_BEGIN_NAMESPACE
class QGridLayout;
class KTextDocument;
class QTextDocument;
QT_END_NAMESPACE

namespace KChart {
class AbstractDiagram;
struct DatasetItem;
class DiagramObserver;
class AbstractLayoutItem;

struct HDatasetItem
{
    HDatasetItem();
    int height() const;

    AbstractLayoutItem *markerLine;
    TextLayoutItem *label;
    VerticalLineLayoutItem *separatorLine;
    QSpacerItem *spacer;
};

class DiagramsObserversList : public QList<DiagramObserver*> {};

/**
 * \internal
 */
class Q_DECL_HIDDEN Legend::Private : public AbstractAreaWidget::Private
{
    friend class Legend;
public:
    Private();
    ~Private();

    DiagramObserver* findObserverForDiagram( AbstractDiagram* diagram )
    {
        for (int i = 0; i < observers.size(); ++i) {
            DiagramObserver * obs = observers.at(i);
            if ( obs->diagram() == diagram )
                return obs;
        }
        return nullptr;
    }

    void fetchPaintOptions( Legend *q );
    QSizeF markerSize( Legend *q, int dataset, qreal fontHeight ) const;
    QSizeF maxMarkerSize( Legend *q, qreal fontHeight ) const;
    void reflowHDatasetItems( Legend *q );
    void flowHDatasetItems( Legend *q );
    void destroyOldLayout();

private:
    // user-settable
    const QWidget* referenceArea;
    Position position;
    Qt::Alignment alignment;
    Qt::Alignment textAlignment;
    Qt::Alignment legendLineSymbolAlignment;
    RelativePosition relativePosition;
    Qt::Orientation orientation;
    Qt::SortOrder order;
    bool showLines;
    QMap<uint,QString> texts;
    QMap<uint,QBrush> brushes;
    QMap<uint,QPen> pens;
    QMap<uint, MarkerAttributes> markerAttributes;
    QList<uint> hiddenDatasets;
    TextAttributes textAttributes;
    QString titleText;
    TextAttributes titleTextAttributes;
    uint spacing;
    bool useAutomaticMarkerSize;
    LegendStyle legendStyle;

    // internal
    mutable QStringList modelLabels;
    mutable QList<QBrush> modelBrushes;
    mutable QList<QPen> modelPens;
    mutable QList< MarkerAttributes > modelMarkers;
    mutable QSize cachedSizeHint;
    QVector< AbstractLayoutItem* > paintItems;
    QGridLayout* layout;
    QList< HDatasetItem > hLayoutDatasets;
    DiagramsObserversList observers;
};

inline Legend::Legend( Private* p, QWidget* parent )
    : AbstractAreaWidget( p, parent ) { init(); }

inline Legend::Private * Legend::d_func()
{ return static_cast<Private*>( AbstractAreaWidget::d_func() ); }

inline const Legend::Private * Legend::d_func() const
{ return static_cast<const Private*>( AbstractAreaWidget::d_func() ); }

}

#endif /* KCHARTLEGEND_P_H */
