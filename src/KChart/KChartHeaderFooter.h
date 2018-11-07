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

#ifndef KCHARTHEADERFOOTER_H
#define KCHARTHEADERFOOTER_H

#include "KChartTextArea.h"
#include "KChartPosition.h"

namespace KChart {

    class Chart;
    class TextAttributes;

/**
  * @brief A header or footer displaying text above or below charts
  */
class KCHART_EXPORT HeaderFooter : public TextArea
{
    Q_OBJECT

    KCHART_DECLARE_PRIVATE_DERIVED_PARENT( HeaderFooter, Chart* )

public:
    HeaderFooter( Chart* parent = nullptr );
    virtual ~HeaderFooter();

    virtual HeaderFooter * clone() const;

    bool compare( const HeaderFooter& other ) const;

    enum HeaderFooterType{ Header,
                           Footer };

    void setType( HeaderFooterType type );
    HeaderFooterType type() const;

    void setPosition( Position position );
    Position position() const;

    void setParent( QObject* parent );

Q_SIGNALS:
    void destroyedHeaderFooter( HeaderFooter* );
    void positionChanged( HeaderFooter* );

}; // End of class HeaderFooter

}


#endif // KCHARTHEADERFOOTER_H
