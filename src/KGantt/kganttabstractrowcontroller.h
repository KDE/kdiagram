/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KGANTTABSTRACTROWCONTROLLER_H
#define KGANTTABSTRACTROWCONTROLLER_H

#include <QPair>
#include "kganttglobal.h"

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

namespace KGantt {


    /*!\class KGantt::AbstractRowController kganttabstractrowcontroller.h KGanttAbstractRowController
     * \ingroup KGantt
     * \brief Abstract baseclass for row controllers. A row controller is used
     * by the GraphicsView to nagivate the model and to determine the
     * row geometries
     */
    class KGANTT_EXPORT AbstractRowController {
    public:
        /*! Constructor. Does nothing */
        AbstractRowController();

        /*! Destructor. Does nothing */
        virtual ~AbstractRowController();

        /*!\fn virtual int AbstractRowController::headerHeight() const = 0
         * \returns The height of the header part of the view.
         *
         * Implement this to control how much space is reserved at
         * the top of the view for a header
         */
        virtual int headerHeight() const = 0;
        virtual int maximumItemHeight() const = 0;


        /*!\fn virtual int AbstractRowController::totalHeight() const = 0
        * \returns the total height of the rows. For uniformly sized rows that would be
        * number_of_rows*row_height.
        */
        virtual int totalHeight() const = 0;

        /*!\fn virtual bool AbstractRowController::isRowVisible( const QModelIndex& idx ) const
         * \returns true if the row containing index \a idx is visible
         * in the view.
         *
         * Implement this to allow KGantt to optimize how items on
         * screen are created. It is not harmful to always return true here,
         * but the View will not perform optimally.
         */
        virtual bool isRowVisible( const QModelIndex& idx ) const = 0;
        virtual bool isRowExpanded( const QModelIndex& idx ) const = 0;

        /*!\fn virtual Span AbstractRowController::rowGeometry( const QModelIndex& idx ) const
         * \returns A Span consisting of the row offset and height for the row
         * containing \a idx. A simple implementation might look like
         *
         * \code
         * Span MyRowCtrlr::rowGeometry(const QModelIndex& idx)
         * {
         *      return Span(idx.row()*10,10);
         * }
         * \endcode
         */
        virtual Span rowGeometry( const QModelIndex& idx ) const = 0;

        virtual QModelIndex indexAt( int height ) const = 0;

        /*!\fn virtual QModelIndex AbstractRowController::indexAbove( const QModelIndex& idx ) const
         *\returns The modelindex for the previous row before \a idx.
         *
         *\see QTreeView::indexAbove
         */
        virtual QModelIndex indexAbove( const QModelIndex& idx ) const = 0;


        /*!\fn virtual QModelIndex AbstractRowController::indexBelow( const QModelIndex& idx ) const
         *\returns The modelindex for the next row after \a idx.
         *
         *\see QTreeView::indexBelow
         */
        virtual QModelIndex indexBelow( const QModelIndex& idx ) const = 0;
    };
}

#endif /* KGANTTABSTRACTROWCONTROLLER_H */

