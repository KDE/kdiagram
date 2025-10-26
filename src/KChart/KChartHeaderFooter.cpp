/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KChartHeaderFooter.h"
#include "KChartHeaderFooter_p.h"

#include "KChartChart.h"
#include "KChartMath_p.h"
#include "KTextDocument.h"
#include <KChartTextAttributes.h>

#include <QAbstractTextDocumentLayout>
#include <QFont>
#include <QLabel>
#include <QPainter>
#include <QTextBlock>
#include <QTextDocumentFragment>
#include <QtDebug>

using namespace KChart;

HeaderFooter::Private::Private()
    : type(Header)
    , position(Position::North)
{
}

HeaderFooter::Private::~Private()
{
}

#define d d_func()

HeaderFooter::HeaderFooter(Chart *parent)
    : TextArea(new Private())
{
    setParent(parent);
    init();
}

HeaderFooter::~HeaderFooter()
{
    Q_EMIT destroyedHeaderFooter(this);
}

void HeaderFooter::setParent(QObject *parent)
{
    QObject::setParent(parent);
    setParentWidget(qobject_cast<QWidget *>(parent));
    if (parent && !autoReferenceArea())
        setAutoReferenceArea(parent);
}

void HeaderFooter::init()
{
    TextAttributes ta;
    ta.setPen(QPen(Qt::black));
    ta.setFont(QFont(QLatin1String("helvetica"), 10, QFont::Bold, false));

    Measure m(35.0);
    m.setRelativeMode(autoReferenceArea(), KChartEnums::MeasureOrientationMinimum);
    ta.setFontSize(m);

    m.setValue(8.0);
    m.setCalculationMode(KChartEnums::MeasureCalculationModeAbsolute);
    ta.setMinimalFontSize(m);

    setTextAttributes(ta);
}

HeaderFooter *HeaderFooter::clone() const
{
    HeaderFooter *headerFooter = new HeaderFooter(new Private(*d), nullptr);
    headerFooter->setType(type());
    headerFooter->setPosition(position());
    headerFooter->setText(text());
    headerFooter->setTextAttributes(textAttributes());
    return headerFooter;
}

bool HeaderFooter::compare(const HeaderFooter &other) const
{
    return (type() == other.type()) && (position() == other.position()) &&
        // also compare members inherited from the base class:
        (autoReferenceArea() == other.autoReferenceArea()) && (text() == other.text()) && (textAttributes() == other.textAttributes());
}

void HeaderFooter::setType(HeaderFooterType type)
{
    if (d->type != type) {
        d->type = type;
        Q_EMIT positionChanged(this);
    }
}

HeaderFooter::HeaderFooterType HeaderFooter::type() const
{
    return d->type;
}

void HeaderFooter::setPosition(Position position)
{
    if (d->position != position) {
        d->position = position;
        Q_EMIT positionChanged(this);
    }
}

Position HeaderFooter::position() const
{
    return d->position;
}
