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
        /*! Create a default context */
        PrintingContext();
        /*! Copy the \a other context into this */
        PrintingContext(const PrintingContext &other);
        /*! Copy the \a other context into this */
        PrintingContext &operator=(const PrintingContext &other);
        /*! Destroy this context */
        ~PrintingContext();

        /*! \enum KGantt::PrintingContext::Fitting
         * Specifies how the diagram shall be fitted
         * to the printed pages.
         */
        enum Fitting {
            NoFitting = 1,     ///< No scaling, print as many pages as needed
            FitSinglePage = 2, ///< Scale diagram to fit on a single page
            FitPageHeight = 4  ///< Scale diagram height to fit one page
        };

        /*! \return scene rect
         */
        QRectF sceneRect() const;

        /*! Set sceneRect to \a rect
         * Setting a  null() rect means the whole diagram (default).
         */
        void setSceneRect(const QRectF &rect);

        /*! \return print scaling
         */
        Fitting fitting() const;
        /*! Set print scaling to \a value
         */
        void setFitting(const Fitting &value);

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
        qreal left() const;

        /*! Set left position to start printing to @p left
         * 
         * The default is 0.0, meaning the left of the chart.
         * 
         * To print a certain range of a chart with a DateTimeGrid, use
         * qreal DateTimeGrid::mapFromDateTime( const QDateTime& dt) const
         * to figure out the values for @p left.
         */
        void setLeft(qreal left);

        /*! \return top position in the diagram to start printing
         */
        qreal top() const;

        /*! Set the top position to start printing to @p top
         */
        void setTop(qreal top);

        /*! \return position in the diagram to end printing
         */
        qreal right() const;

        /*! Set right position to right printing to @p right
         * 
         * The default is 0.0, meaning the right of the chart.
         * 
         * To print a certain range of a chart with a DateTimeGrid, use
         * qreal DateTimeGrid::mapFromDateTime( const QDateTime& dt) const
         * to figure out the values for @p right.
         */
        void setRight(qreal right);

        /*! \return bottom position in the diagram to end printing
         */
        qreal bottom() const;

        /*! Set bottom position to end printing to @p right
         */
        void setBottom(qreal bottom);

    private:
        class Private;
        Private *d;
    };

} // namespace KGantt

#ifndef QT_NO_DEBUG_STREAM
QDebug KGANTT_EXPORT operator<<( QDebug dbg, const KGantt::PrintingContext::Fitting &f);
QDebug KGANTT_EXPORT operator<<( QDebug dbg, const KGantt::PrintingContext &ctx);
#endif

#endif
