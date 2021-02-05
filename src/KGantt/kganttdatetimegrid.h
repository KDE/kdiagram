/*
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KGantt library.
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

#ifndef KGANTTDATETIMEGRID_H
#define KGANTTDATETIMEGRID_H

#include "kganttabstractgrid.h"

#include <QDateTime>
#include <QSet>
#include <QPair>

namespace KGantt {

    class DateTimeScaleFormatter;
    class DateTimeTimeLine;


    /*!\class KGantt::DateTimeGrid
     * \ingroup KGantt
     *
     * This implementation of AbstractGrid works with QDateTime
     * and shows days and week numbers in the header
     */
    class KGANTT_EXPORT DateTimeGrid : public AbstractGrid
    {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_DERIVED( DateTimeGrid )
    public:
        enum Scale {
            ScaleAuto, 
            ScaleHour,
            ScaleDay,
            ScaleWeek,
            ScaleMonth,
            ScaleUserDefined
        };
        enum HeaderType {
            NoHeader,
            UpperHeader,
            LowerHeader
        };

        DateTimeGrid();
        virtual ~DateTimeGrid();

        /*! \returns The QDateTime used as start date for the grid.
         *
         * The default is three days before the current date.
         */
        QDateTime startDateTime() const;

        /*! \param dt The start date of the grid. It is used as the beginning of the
         * horizontal scrollbar in the view.
         *
         * Emits gridChanged() after the start date has changed.
         */
        void setStartDateTime( const QDateTime& dt );

        /*! \returns The width in pixels for each day in the grid.
         *
         * The default is 100 pixels.
         */
        qreal dayWidth() const;

        /*! \param w The width in pixels for each day in the grid.
         *
         * The signal gridChanged() is emitted after the day width is changed.
         */
        void setDayWidth( qreal );

        /*! Maps a given point in time \a dt to an X value in the scene.
         */
        qreal mapFromDateTime( const QDateTime& dt) const;

        /*! Maps a given X value \a x in scene coordinates to a point in time.
         */
        QDateTime mapToDateTime( qreal x ) const;

        /*! \param ws The start day of the week.
         *
         * A solid line is drawn on the grid to mark the beginning of a new week.
         * Emits gridChanged() after the start day has changed.
         */
        void setWeekStart( Qt::DayOfWeek );

        /*! \returns The start day of the week */
        Qt::DayOfWeek weekStart() const;

        /*! \param fd A set of days to mark as free in the grid.
         *
         * Free days are filled with the alternate base brush of the
         * palette used by the view.
         * The signal gridChanged() is emitted after the free days are changed.
         */
        void setFreeDays( const QSet<Qt::DayOfWeek>& fd );

        /*! \returns The days marked as free in the grid. */
        QSet<Qt::DayOfWeek> freeDays() const;

        /*! Sets the brush to use to paint free days.
        */
        void setFreeDaysBrush(const QBrush brush);

        /*!
          \returns The brush used to paint free days.
        */
        QBrush freeDaysBrush() const;

        /*! \param s The scale to be used to paint the grid.
         *
         * The signal gridChanged() is emitted after the scale has changed.
         * \sa Scale
         *
         * Following example demonstrates how to change the format of the header to use
         * a date-scaling with the header-label displayed with the ISO date-notation.
         * \code
         * DateTimeScaleFormatter* formatter = new DateTimeScaleFormatter(DateTimeScaleFormatter::Day, QString::fromLatin1("yyyy-MMMM-dddd"));
         * grid->setUserDefinedUpperScale( formatter );
         * grid->setUserDefinedLowerScale( formatter );
         * grid->setScale( DateTimeGrid::ScaleUserDefined );
         * \endcode
         */
        void setScale( Scale s );

        /*! \returns The scale used to paint the grid.
         *
         * The default is ScaleAuto, which means the day scale will be used
         * as long as the day width is less or equal to 500.
         * \sa Scale
         */
        Scale scale() const;

        /*! Sets the scale formatter for the lower part of the header to the
         *  user defined formatter to \a lower. The DateTimeGrid object takes
         *  ownership of the formatter, which has to be allocated with new.
         *
         * You have to set the scale to ScaleUserDefined for this setting to take effect.
         * \sa DateTimeScaleFormatter
         */
        void setUserDefinedLowerScale( DateTimeScaleFormatter* lower );

        /*! Sets the scale formatter for the upper part of the header to the
         *  user defined formatter to \a upper. The DateTimeGrid object takes
         *  ownership of the formatter, which has to be allocated with new.
         *
         * You have to set the scale to ScaleUserDefined for this setting to take effect.
         * \sa DateTimeScaleFormatter
         */
        void setUserDefinedUpperScale( DateTimeScaleFormatter* upper );

        /*! \return The DateTimeScaleFormatter being used to render the lower scale.
         */
        DateTimeScaleFormatter* userDefinedLowerScale() const;


        /*! \return The DateTimeScaleFormatter being used to render the upper scale.
         */
        DateTimeScaleFormatter* userDefinedUpperScale() const;

        /*! \returns true if row separators are used. */
        bool rowSeparators() const;

        /*! \param enable Whether to use row separators or not. */
        void setRowSeparators( bool enable );

        /*! Sets the brush used to display rows where no data is found.
         * Default is a red pattern. If set to QBrush() rows with no
         * information will not be marked.
         */
        void setNoInformationBrush( const QBrush& brush );

        /*! \returns the brush used to mark rows with no information.
         */
        QBrush noInformationBrush() const;

        /*! \param idx The index to get the Span for.
         * \returns The start and end pixels, in a Span, of the specified index.
         */
        /*reimp*/ Span mapToChart( const QModelIndex& idx ) const override;

        /*! Maps the supplied Span to QDateTimes, and puts them as start time and
         * end time for the supplied index.
         *
         * \param span The span used to map from.
         * \param idx The index used for setting the start time and end time in the model.
         * \param constraints A list of hard constraints to match against the start time and
         * end time mapped from the span.
         *
         * \returns true if the start time and time was successfully added to the model, or false
         * if unsucessful.
         * Also returns false if any of the constraints isn't satisfied. That is, if the start time of
         * the constrained index is before the end time of the dependency index, or the end time of the
         * constrained index is before the start time of the dependency index.
         */
        /*reimp*/ bool mapFromChart( const Span& span, const QModelIndex& idx,
                                     const QList<Constraint>& constraints=QList<Constraint>() ) const override;

        /*!
        * \param value The datetime to get the x value for.
        * \returns The x value corresponding to \a value or -1.0 if \a value is not a datetime variant.
        */
        /*reimp*/ qreal mapToChart( const QVariant& value ) const override;

        /*!
         * \param x The x value to get the datetime for.
         * \returns The datetime corresponding to \a x or an invalid datetime if x cannot be mapped.
         */
        /*reimp*/ QVariant mapFromChart( qreal x ) const override;
        /*reimp*/ void paintGrid( QPainter* painter, 
                                  const QRectF& sceneRect, const QRectF& exposedRect,
                                  AbstractRowController* rowController = nullptr,
                                  QWidget* widget = nullptr ) override;
        /*reimp*/ void paintHeader( QPainter* painter, 
                                    const QRectF& headerRect, const QRectF& exposedRect,
                                    qreal offset, QWidget* widget = nullptr ) override;

        /**
         * @return the timeline control object
         */
        DateTimeTimeLine *timeLine() const;

        HeaderType sectionHandleAtPos(int x, int y, const QRect &headerRect) const;

    protected:
        /*! Paints the hour scale header.
         * \sa paintHeader()
         */
        virtual void paintHourScaleHeader( QPainter* painter, 
                           const QRectF& headerRect, const QRectF& exposedRect,
                           qreal offset, QWidget* widget = nullptr );

        /*! Paints the day scale header.
         * \sa paintHeader()
         */
        virtual void paintDayScaleHeader( QPainter* painter, 
                          const QRectF& headerRect, const QRectF& exposedRect,
                          qreal offset, QWidget* widget = nullptr );

        /*! Paints the week scale header.
         * \sa paintHeader()
         */
        virtual void paintWeekScaleHeader( QPainter* painter,
                                           const QRectF& headerRect, const QRectF& exposedRect,
                                           qreal offset, QWidget* widget = nullptr );

        /*! Paints the week scale header.
         * \sa paintHeader()
         */
        virtual void paintMonthScaleHeader( QPainter* painter,
                                            const QRectF& headerRect, const QRectF& exposedRect,
                                            qreal offset, QWidget* widget = nullptr );

        virtual void paintUserDefinedHeader( QPainter* painter, 
                                     const QRectF& headerRect, const QRectF& exposedRect, 
                                     qreal offset, const DateTimeScaleFormatter* formatter, 
                                     QWidget* widget = nullptr );


        /*! Draw the background for a day.
        */
        virtual void drawDayBackground(QPainter* painter, const QRectF& rect, const QDate& date);

        /*! Draw the foreground for a day.
        */
        virtual void drawDayForeground(QPainter* painter, const QRectF& rect, const QDate& date);

        /** Return the rectangle that represents the date-range.
        */
        QRectF computeRect(const QDateTime& from, const QDateTime& to, const QRectF& rect) const;


        /** Return a date-range represented by the rectangle.
        */
        QPair<QDateTime, QDateTime> dateTimeRange(const QRectF& rect) const;

        /* reimp */ void drawBackground(QPainter* paint, const QRectF& rect) override;
        /* reimp */ void drawForeground(QPainter* paint, const QRectF& rect) override;
    };

    /*!\class KGantt::DateTimeScaleFormatter
     * \ingroup KGantt
     *
     * This class formats dates and times used in DateTimeGrid follawing a given format.
     *
     * The format follows the format of QDateTime::toString(), with one addition:
     * "w" is replaced with the week number of the date as number without a leading zero (1-53)
     * "ww" is replaced with the week number of the date as number with a leading zero (01-53)
     *
     * For example:
     *
     * \code
     *  // formatter to print the complete date over the current week
     *  // This leads to the first day of the week being printed
     *  DateTimeScaleFormatter formatter = DateTimeScaleFormatter( DateTimeScaleFormatter::Week, "yyyy-MM-dd" );
     * \endcode
     *
     * Optionally, you can set an user defined text alignment flag. The default value is Qt::AlignCenter.
     * \sa DateTimeScaleFormatter::DateTimeScaleFormatter
     *
     * This class even controls the range of the grid sections.
     * \sa KGanttDateTimeScaleFormatter::Range
     */
    class KGANTT_EXPORT DateTimeScaleFormatter
    {
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( DateTimeScaleFormatter )
    public:
        enum Range {
            Second,
            Minute,
            Hour,
            Day,
            Week,
            Month,
            Year
        };

        /*! Creates a DateTimeScaleFormatter using \a range and \a format.
         *  The text on the header is aligned following \a alignment.
         */
        DateTimeScaleFormatter( Range range, const QString& formatString,
                                Qt::Alignment alignment = Qt::AlignCenter );
        DateTimeScaleFormatter( Range range, const QString& formatString,
                                const QString& templ, Qt::Alignment alignment = Qt::AlignCenter );

        /*! \returns The format being used for formatting dates and times.
         */
        DateTimeScaleFormatter( const DateTimeScaleFormatter& other );
        virtual ~DateTimeScaleFormatter();

        DateTimeScaleFormatter& operator=( const DateTimeScaleFormatter& other );

        /*! \returns The format string
         */
        QString format() const;

        /*! \returns The range of each item on a DateTimeGrid header.
         * \sa DateTimeScaleFormatter::Range */
        Range range() const;
        Qt::Alignment alignment() const;

        /*! \returns the QDateTime being the begin of the range after the one containing \a datetime
         *  \sa currentRangeBegin
         */
        virtual QDateTime nextRangeBegin( const QDateTime& datetime ) const;

        /*! \returns the QDateTime being the begin of the range containing \a datetime
         *  \sa nextRangeBegin
         */
        virtual QDateTime currentRangeBegin( const QDateTime& datetime ) const;

        /*! \returns The \a datetime as string respecting the format.
         */
        QString format( const QDateTime& datetime ) const;
        virtual QString text( const QDateTime& datetime ) const;
    };
}



#ifndef QT_NO_DEBUG_STREAM
QDebug KGANTT_EXPORT operator<<( QDebug dbg, KGantt::DateTimeScaleFormatter::Range );
#endif

#endif /* KGANTTDATETIMEGRID_H */

