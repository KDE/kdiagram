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

#ifndef KCHARTLAYOUTITEMS_H
#define KCHARTLAYOUTITEMS_H

#include <QBrush>
#include <QFont>
#include <QFontMetricsF>
#include <QLayout>
#include <QLayoutItem>
#include <QPen>

#include "KChartTextAttributes.h"
#include "KChartMarkerAttributes.h"

QT_BEGIN_NAMESPACE
class QPainter;
class KTextDocument;
QT_END_NAMESPACE

// TODO remove
QRectF rotatedRect( const QRectF& pt, qreal rotation );

namespace KChart {
    class AbstractDiagram;
    class PaintContext;

    /**
     * Base class for all layout items of KChart
     * \internal
     */
    class KCHART_EXPORT AbstractLayoutItem : public QLayoutItem
    {
    public:
        AbstractLayoutItem( Qt::Alignment itemAlignment = Qt::Alignment() ) :
            QLayoutItem( itemAlignment ),
            mParent( 0 ),
            mParentLayout( 0 ) {}

        /**
         * Default impl: just call paint.
         *
         * Derived classes like KChart::AbstractArea are providing
         * additional action here.
         */
        virtual void paintAll( QPainter& painter );

        virtual void paint( QPainter* ) = 0;

        virtual void paintCtx( PaintContext* context );
        virtual void setParentWidget( QWidget* widget );
        virtual void sizeHintChanged() const;

        void setParentLayout( QLayout* lay )
        {
            mParentLayout = lay;
        }
        QLayout* parentLayout()
        {
            return mParentLayout;
        }
        void removeFromParentLayout()
        {
            if ( mParentLayout ) {
                if ( widget() )
                    mParentLayout->removeWidget( widget() );
                else
                    mParentLayout->removeItem( this );
            }
        }
    protected:
        QWidget* mParent;
        QLayout* mParentLayout;
    };

    /**
     * Layout item showing a text
     *\internal
     */
    class KCHART_EXPORT TextLayoutItem : public AbstractLayoutItem
    {
    public:
        TextLayoutItem();
        TextLayoutItem( const QString& text,
                        const TextAttributes& attributes,
                        const QObject* autoReferenceArea,
                        KChartEnums::MeasureOrientation autoReferenceOrientation,
                        Qt::Alignment alignment = Qt::Alignment() );

        void setAutoReferenceArea( const QObject* area );
        const QObject* autoReferenceArea() const;

        void setText(const QString & text);
        QString text() const;

        void setTextAlignment( Qt::Alignment );
        Qt::Alignment textAlignment() const;

        void setTextAttributes( const TextAttributes& a );
        TextAttributes textAttributes() const;

        /** pure virtual in QLayoutItem */
        bool isEmpty() const Q_DECL_OVERRIDE;
        /** pure virtual in QLayoutItem */
        Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
        /** pure virtual in QLayoutItem */
        QSize maximumSize() const Q_DECL_OVERRIDE;
        /** pure virtual in QLayoutItem */
        QSize minimumSize() const Q_DECL_OVERRIDE;
        /** pure virtual in QLayoutItem */
        QSize sizeHint() const Q_DECL_OVERRIDE;
        /** pure virtual in QLayoutItem */
        void setGeometry( const QRect& r ) Q_DECL_OVERRIDE;
        /** pure virtual in QLayoutItem */
        QRect geometry() const Q_DECL_OVERRIDE;

        virtual int marginWidth() const;

        virtual QSize sizeHintUnrotated() const;

        virtual bool intersects( const TextLayoutItem& other, const QPointF& myPos, const QPointF& otherPos ) const;
        virtual bool intersects( const TextLayoutItem& other, const QPoint& myPos, const QPoint& otherPos ) const;

        virtual qreal realFontSize() const;
        virtual QFont realFont() const;

        void paint( QPainter* ) Q_DECL_OVERRIDE;

        QPolygon boundingPolygon() const;
    private:
        bool maybeUpdateRealFont() const;
        QSize unrotatedSizeHint( const QFont& fnt = QFont() ) const;
        QSize unrotatedTextSize( QFont fnt = QFont() ) const;
        QSize calcSizeHint( const QFont& font ) const;
        int marginWidth( const QSize& textSize ) const;

        qreal fitFontSizeToGeometry() const;

        QRect mRect;
        QString mText;
        Qt::Alignment mTextAlignment;
        TextAttributes mAttributes;
        const QObject* mAutoReferenceArea;
        KChartEnums::MeasureOrientation mAutoReferenceOrientation;
        mutable QSize cachedSizeHint;
        mutable QPolygon mCachedBoundingPolygon;
        mutable qreal cachedFontSize;
        mutable QFont cachedFont;
    };

    class KCHART_EXPORT TextBubbleLayoutItem : public AbstractLayoutItem
    {
    public:
        TextBubbleLayoutItem();
        TextBubbleLayoutItem( const QString& text,
                              const TextAttributes& attributes,
                              const QObject* autoReferenceArea,
                              KChartEnums::MeasureOrientation autoReferenceOrientation,
                              Qt::Alignment alignment = Qt::Alignment() );

        ~TextBubbleLayoutItem();

        void setAutoReferenceArea( const QObject* area );
        const QObject* autoReferenceArea() const;

        void setText(const QString & text);
        QString text() const;

        void setTextAttributes( const TextAttributes& a );
        TextAttributes textAttributes() const;

        /** pure virtual in QLayoutItem */
        bool isEmpty() const Q_DECL_OVERRIDE;
        /** pure virtual in QLayoutItem */
        Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
        /** pure virtual in QLayoutItem */
        QSize maximumSize() const Q_DECL_OVERRIDE;
        /** pure virtual in QLayoutItem */
        QSize minimumSize() const Q_DECL_OVERRIDE;
        /** pure virtual in QLayoutItem */
        QSize sizeHint() const Q_DECL_OVERRIDE;
        /** pure virtual in QLayoutItem */
        void setGeometry( const QRect& r ) Q_DECL_OVERRIDE;
        /** pure virtual in QLayoutItem */
        QRect geometry() const Q_DECL_OVERRIDE;

        void paint( QPainter* painter ) Q_DECL_OVERRIDE;

    protected:
        int borderWidth() const;

    private:
        TextLayoutItem* const m_text;
    };

    /**
     * Layout item showing a data point marker
     * \internal
     */
    class KCHART_EXPORT MarkerLayoutItem : public AbstractLayoutItem
    {
        public:
            MarkerLayoutItem( AbstractDiagram* diagram,
                              const MarkerAttributes& marker,
                              const QBrush& brush,
                              const QPen& pen,
                              Qt::Alignment alignment = Qt::Alignment() );

            Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
            QRect geometry() const Q_DECL_OVERRIDE;
            bool isEmpty() const Q_DECL_OVERRIDE;
            QSize maximumSize() const Q_DECL_OVERRIDE;
            QSize minimumSize() const Q_DECL_OVERRIDE;
            void setGeometry( const QRect& r ) Q_DECL_OVERRIDE;
            QSize sizeHint() const Q_DECL_OVERRIDE;

            void paint( QPainter* ) Q_DECL_OVERRIDE;

            static void paintIntoRect(
                    QPainter* painter,
                    const QRect& rect,
                    AbstractDiagram* diagram,
                    const MarkerAttributes& marker,
                    const QBrush& brush,
                    const QPen& pen );

        private:
            AbstractDiagram* mDiagram;
            QRect mRect;
            MarkerAttributes mMarker;
            QBrush mBrush;
            QPen mPen;
    };

    /**
     * Layout item showing a coloured line
     * \internal
     */
    class KCHART_EXPORT LineLayoutItem : public AbstractLayoutItem
    {
        public:
            LineLayoutItem( AbstractDiagram* diagram,
                            int length,
                            const QPen& pen,
                            Qt::Alignment mLegendLineSymbolAlignment,
                            Qt::Alignment alignment = Qt::Alignment() );

            Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
            QRect geometry() const Q_DECL_OVERRIDE;
            bool isEmpty() const Q_DECL_OVERRIDE;
            QSize maximumSize() const Q_DECL_OVERRIDE;
            QSize minimumSize() const Q_DECL_OVERRIDE;
            void setGeometry( const QRect& r ) Q_DECL_OVERRIDE;
            QSize sizeHint() const Q_DECL_OVERRIDE;

            void setLegendLineSymbolAlignment(Qt::Alignment legendLineSymbolAlignment);
            virtual Qt::Alignment legendLineSymbolAlignment() const;

            void paint( QPainter* ) Q_DECL_OVERRIDE;

            static void paintIntoRect(
                    QPainter* painter,
                    const QRect& rect,
                    const QPen& pen,
                    Qt::Alignment lineAlignment);

        private:
            AbstractDiagram* mDiagram;  //TODO: not used. remove it
            int mLength;
            QPen mPen;
            QRect mRect;
            Qt::Alignment mLegendLineSymbolAlignment;
    };

    /**
     * Layout item showing a coloured line and a data point marker
     * \internal
     */
    class KCHART_EXPORT LineWithMarkerLayoutItem : public AbstractLayoutItem
    {
        public:
            LineWithMarkerLayoutItem( AbstractDiagram* diagram,
                                      int lineLength,
                                      const QPen& linePen,
                                      int markerOffs,
                                      const MarkerAttributes& marker,
                                      const QBrush& markerBrush,
                                      const QPen& markerPen,
                                      Qt::Alignment alignment = Qt::Alignment() );

            Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
            QRect geometry() const Q_DECL_OVERRIDE;
            bool isEmpty() const Q_DECL_OVERRIDE;
            QSize maximumSize() const Q_DECL_OVERRIDE;
            QSize minimumSize() const Q_DECL_OVERRIDE;
            void setGeometry( const QRect& r ) Q_DECL_OVERRIDE;
            QSize sizeHint() const Q_DECL_OVERRIDE;

            void paint( QPainter* ) Q_DECL_OVERRIDE;

        private:
            AbstractDiagram* mDiagram;
            QRect mRect;
            int mLineLength;
            QPen mLinePen;
            int mMarkerOffs;
            MarkerAttributes mMarker;
            QBrush mMarkerBrush;
            QPen mMarkerPen;
    };


    /**
     * Layout item showing a horizontal line
     * \internal
     */
    class KCHART_EXPORT HorizontalLineLayoutItem : public AbstractLayoutItem
    {
    public:
        HorizontalLineLayoutItem();

        Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
        QRect geometry() const Q_DECL_OVERRIDE;
        bool isEmpty() const Q_DECL_OVERRIDE;
        QSize maximumSize() const Q_DECL_OVERRIDE;
        QSize minimumSize() const Q_DECL_OVERRIDE;
        void setGeometry( const QRect& r ) Q_DECL_OVERRIDE;
        QSize sizeHint() const Q_DECL_OVERRIDE;

        void paint( QPainter* ) Q_DECL_OVERRIDE;

    private:
        QRect mRect;
    };

    /**
     * Layout item showing a vertial line
     * \internal
     */
    class KCHART_EXPORT VerticalLineLayoutItem : public AbstractLayoutItem
    {
        public:
            VerticalLineLayoutItem();

            Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
            QRect geometry() const Q_DECL_OVERRIDE;
            bool isEmpty() const Q_DECL_OVERRIDE;
            QSize maximumSize() const Q_DECL_OVERRIDE;
            QSize minimumSize() const Q_DECL_OVERRIDE;
            void setGeometry( const QRect& r ) Q_DECL_OVERRIDE;
            QSize sizeHint() const Q_DECL_OVERRIDE;

            void paint( QPainter* ) Q_DECL_OVERRIDE;

        private:
            QRect mRect;
    };

    /**
     * @brief An empty layout item
     * \internal
     *
     * The AutoSpacerLayoutItem is automatically put into each corner cell of
     * the planeLayout grid: one of its reference-layouts is a QVBoxLayout (for
     * the top, or bottom axes resp.), the other one is a QHBoxLayout (for the
     * left/right sided axes).
     *
     * The spacer reserves enough space so all of the AbstractAreas contained
     * in the two reference-layouts can display not only their in-bounds
     * content but also their overlapping content reaching out of their area.
     *
     * KChart's layouting is applying this schema:
\verbatim
    +------------------+-------------------------+-----------------+
    | +--------------+ | +---------------------+ | +-------------+ |
    | |              | | |  QVBoxLayout for    | | |             | |
    | |     AUTO     | | |  the top axis/axes  | | |    AUTO     | |
    | |    SPACER    | | +---------------------+ | |   SPACER    | |
    | |     ITEM     | | |                     | | |    ITEM     | |
    | |              | | |                     | | |             | |
    | +--------------+ | +---------------------+ | +-------------+ |
    +------------------+-------------------------+-----------------+
    | +--------+-----+ | +---------------------+ | +-------+-----+ |
    | |        |     | | |                     | | |       |     | |
    | |        |     | | |                     | | |       |     | |
    | | QHBox- |     | | |                     | | | Right |     | |
    | | Layout |     | | |                     | | |       |     | |
    | |        |     | | |                     | | | axes  |     | |
    | | for    |     | | |                     | | |       |     | |
    | |        |     | | |                     | | | layout|     | |
    | | the    |     | | |      DIAGRAM(s)     | | |       |     | |
    | |        |     | | |                     | | |       |     | |
    | | left   |     | | |                     | | |       |     | |
    | |        |     | | |                     | | |       |     | |
    | | axis   |     | | |                     | | |       |     | |
    | | or     |     | | |                     | | |       |     | |
    | | axes   |     | | |                     | | |       |     | |
    | |        |     | | |                     | | |       |     | |
    | +--------+-----+ | +---------------------+ | +-------+-----+ |
    +------------------+-------------------------+-----------------+
    | +--------------+ | +---------------------+ | +-------------+ |
    | |              | | |   QVBoxLayout for   | | |             | |
    | |    AUTO      | | |   the bottom axes   | | |    AUTO     | |
    | |   SPACER     | | +---------------------+ | |   SPACER    | |
    | |    ITEM      | | |                     | | |    ITEM     | |
    | |              | | |                     | | |             | |
    | +--------------+ | +---------------------+ | +-------------+ |
    +------------------+-------------------------+-----------------+
\endverbatim
     *
     * A typical use case is an Abscissa axis with long labels:
\verbatim
    2 -|
       |
    1 -|
       |
    0 -+------------------------------------
       |        |        |        |        |
    Monday  Tuesday  Wednesday Thursday Friday
\endverbatim
     * The last letters of the word "Friday" would have been
     * cut off in previous versions of KChart - that is
     * if you did not call KChart::Chart::setGlobalLeading().
     *
     * Now the word will be shown completely because there
     * is an auto-spacer-item taking care for the additional
     * space needed in the lower/right corner.
     */
    class KCHART_EXPORT AutoSpacerLayoutItem : public AbstractLayoutItem
    {
        public:
            AutoSpacerLayoutItem(
                    bool layoutIsAtTopPosition, QHBoxLayout *rightLeftLayout,
                    bool layoutIsAtLeftPosition,  QVBoxLayout *topBottomLayout );

            Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
            QRect geometry() const Q_DECL_OVERRIDE;
            bool isEmpty() const Q_DECL_OVERRIDE;
            QSize maximumSize() const Q_DECL_OVERRIDE;
            QSize minimumSize() const Q_DECL_OVERRIDE;
            void setGeometry( const QRect& r ) Q_DECL_OVERRIDE;
            QSize sizeHint() const Q_DECL_OVERRIDE;

            void paint( QPainter* ) Q_DECL_OVERRIDE;

        private:
            QRect mRect;
            bool mLayoutIsAtTopPosition;
            QHBoxLayout *mRightLeftLayout;
            bool mLayoutIsAtLeftPosition;
            QVBoxLayout *mTopBottomLayout;

            mutable QBrush mCommonBrush;
            mutable QSize mCachedSize;
    };

}

#endif /* KCHARTLAYOUTITEMS_H */
