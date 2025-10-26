/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KCHARTTERNARYAXIS_H
#define KCHARTTERNARYAXIS_H

#include <KChartAbstractAxis.h>
#include <KChartPosition.h>
#include <KChartTextAttributes.h>

class PrerenderedLabel;

namespace KChart
{

class AbstractTernaryDiagram;

/**
 * The class for ternary axes
 */
class KCHART_EXPORT TernaryAxis : public AbstractAxis
{
    Q_OBJECT

    Q_DISABLE_COPY(TernaryAxis)
    KCHART_DECLARE_PRIVATE_DERIVED_PARENT(TernaryAxis, AbstractDiagram *)

public:
    explicit TernaryAxis(AbstractTernaryDiagram *diagram = nullptr);
    ~TernaryAxis() override;

    void paintAll(QPainter &) override;
    void paint(QPainter *) override;
    void paintCtx(PaintContext *) override;

    QRect geometry() const override;
    void setGeometry(const QRect &rect) override;

    bool isEmpty() const override;
    QSize minimumSize() const override;
    QSize maximumSize() const override;
    QSize sizeHint() const override;
    Qt::Orientations expandingDirections() const override;

    virtual const Position position() const;
    virtual void setPosition(Position p);

    void setTitleText(const QString &text);
    QString titleText() const;
    void setTitleTextAttributes(const TextAttributes &a);
    TextAttributes titleTextAttributes() const;
    void resetTitleTextAttributes();
    bool hasDefaultTitleTextAttributes() const;

    QPair<QSizeF, QSizeF> requiredMargins() const;

private:
    void updatePrerenderedLabels();
    // TODO, move class variables to private class
    QRect m_geometry;
    Position m_position;

    QString m_title;
    TextAttributes m_titleAttributes;

    // FIXME (Mirko): Move axis labels from grid to here, do not
    // expose them, just paint them. Use title text for text. Make
    // a function to allow the coordinate plane to calculate the
    // necessary margins, like this:
    PrerenderedLabel *m_label;
    PrerenderedLabel *m_fifty;
};

typedef QList<TernaryAxis *> TernaryAxisList;
}

#endif
