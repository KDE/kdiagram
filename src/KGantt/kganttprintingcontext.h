/*
 * Copyright (C) 2020 Dag Andersen <dag.andersen@kdemail.net>
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

#ifndef KGANTTPRINTINGCONTEXT_H
#define KGANTTPRINTINGCONTEXT_H

#include "kganttglobal.h"

#include <QRectF>

class QPainter;
class QPrinter;

namespace KGantt
{
    /*!\class KGantt::PrintingContext kganttprintingcontext.h KGanttPrintingContext
     * \ingroup KGantt
     * \brief The PrintingContext class provides options for printing the gantt chart.
     * 
     * \since 2.8.0
     */
    class KGANTT_EXPORT PrintingContext
    {
    public:
        PrintingContext();
        PrintingContext(const PrintingContext &other);
        ~PrintingContext();

        /*! \enum KGantt::PrintingContext::Scaling
         * Specifies how the diagram shall be printed
         */
        enum Scaling {
            NoScaling = 1,   ///< No scaling, print as many pages as needed
            FitSingle = 2,   ///< Scale diagram to fit on a single page
            FitVertical = 4  ///< Scale diagram height to fit one page
        };

        /*! \return print scaling
         */
        Scaling scaling() const;
        /*! Set print scaling to \a value
         */
        void setScaling(const Scaling &value);

        /*! \return if the the row labels shall be printed 
         */
        bool drawRowLabels() const;

        /*! Set if the row labels shall be printed to @p state
         * The row labels are printed to the left of the chart.
         */
        void setDrawRowLabels(bool state);

        /*! \return if the the column labels shall be printed 
         */
        bool drawColumnLabels() const;

        /*! Set if the column labels shall be printed to @p state.
         */
        void setDrawColumnLabels(bool state);

        /*! \return position in the diagram to start printing
         */
        qreal start() const;

        /*! Set where to start printing to @p start
         * 
         * The default is 0.0, meaning the start of the chart.
         * 
         * To print a certain range of a chart with a DateTimeGrid, use
         * qreal DateTimeGrid::mapFromDateTime( const QDateTime& dt) const
         * to figure out the values for @p start.
         */
        void setStart(qreal start);

        /*! \return position in the diagram to end printing
         */
        qreal end() const;

        /*! Set where to end printing to @p end
         * 
         * The default is 0.0, meaning the end of the chart.
         * 
         * To print a certain range of a chart with a DateTimeGrid, use
         * qreal DateTimeGrid::mapFromDateTime( const QDateTime& dt) const
         * to figure out the values for @p end.
         */
        void setEnd(qreal end);

    private:
        class Private;
        Private *d;
    };

} // namespace KGantt

#ifndef QT_NO_DEBUG_STREAM
QDebug KGANTT_EXPORT operator<<( QDebug dbg, const KGantt::PrintingContext::Scaling &s);
QDebug KGANTT_EXPORT operator<<( QDebug dbg, const KGantt::PrintingContext &ctx);
#endif

#endif
