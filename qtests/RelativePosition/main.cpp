/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <QtTest/QtTest>

#include <QLabel>

#include <KChartGlobal>
#include <KChartPosition>
#include <KChartMeasure>
#include <KChartRelativePosition>

using namespace KChart;

class TestRelativePosition: public QObject {
    Q_OBJECT
private Q_SLOTS:

    void initTestCase()
    {
        m_window = new QLabel(nullptr);
        m_window->setGeometry(100,100, 300,200);
        m_window->show();
    }

    void testRelativePositionHRelativeVAbsolute()
    {
        const qreal horizPerMille = 100.0;
        KChart::Measure mHoriz(
                horizPerMille,
                KChartEnums::MeasureCalculationModeRelative,
                KChartEnums::MeasureOrientationHorizontal );
        mHoriz.setReferenceArea( m_window );

        const qreal vertAbsolute = -50.0;
        KChart::Measure mVert(
                vertAbsolute,
                KChartEnums::MeasureCalculationModeAbsolute );

        KChart::RelativePosition relPos;
        relPos.setReferenceArea( m_window );
        relPos.setReferencePosition( KChart::Position::NorthWest );
        relPos.setHorizontalPadding( mHoriz );
        relPos.setVerticalPadding(   mVert );

        // no auto mode is active, so we pass an empty QSizeF:
        const QPointF pt( relPos.calculatedPoint( QSizeF() ) );
        const QRectF geo( m_window->geometry() );
        QCOMPARE( pt.x(), geo.topLeft().x() + geo.size().width() / 1000.0 * horizPerMille );
        QCOMPARE( pt.y(), geo.topLeft().y() + vertAbsolute );
    }

    void testRelativePositionHAbsoluteVRelative()
    {
        const qreal horizAbsolute = 100.0;
        KChart::Measure mHoriz(
                horizAbsolute,
                KChartEnums::MeasureCalculationModeAbsolute );

        const qreal vertRelative = -50.0;
        KChart::Measure mVert(
                vertRelative,
                KChartEnums::MeasureCalculationModeRelative,
                KChartEnums::MeasureOrientationVertical );
        mVert.setReferenceArea( m_window );

        KChart::RelativePosition relPos;
        relPos.setReferenceArea( m_window );
        relPos.setReferencePosition( KChart::Position::Center );
        relPos.setHorizontalPadding( mHoriz );
        relPos.setVerticalPadding(   mVert );

        // no auto mode is active, so we pass an empty QSizeF:
        const QPointF pt( relPos.calculatedPoint( QSizeF() ) );
        const QRectF geo( m_window->geometry() );
        QCOMPARE( pt.x(), geo.center().x() + horizAbsolute );
        QCOMPARE( pt.y(), geo.center().y() + geo.size().height() / 1000.0 * vertRelative );
    }


    void cleanupTestCase()
    {
    }

private:
    QLabel *m_window;

};

QTEST_MAIN(TestRelativePosition)

#include "main.moc"
