/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
    ~HeaderFooter() override;

    /**
      * Creates an exact copy of this header/footer.
      */
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
    void destroyedHeaderFooter( KChart::HeaderFooter* );
    void positionChanged( KChart::HeaderFooter* );

}; // End of class HeaderFooter

}


#endif // KCHARTHEADERFOOTER_H
