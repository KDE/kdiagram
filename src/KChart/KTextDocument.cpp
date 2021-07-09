/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KTextDocument.h"

#include "KChartMath_p.h"

#include <QRect>
#include <QAbstractTextDocumentLayout>
#include <QtDebug>
#include <QTextBlock>

// This is an internal class that mimicks some of the behavior of a
// QLabel with rich text assigned, this is mostly a workaround around
// QTextDocumentLayout not being a public class.

KTextDocument::KTextDocument( QObject * p )
    : QTextDocument( p ),
      mHintValid( false ),
      mSizeHint(),
      mMinimumSizeHint()
{

}

KTextDocument::KTextDocument( const QString & text, QObject * p )
    : QTextDocument( text, p ),
      mHintValid( false ),
      mSizeHint(),
      mMinimumSizeHint()
{

}

KTextDocument::~KTextDocument() {}


QSize KTextDocument::sizeHint()
{
    if ( !mHintValid )
        (void)minimumSizeHint();
    return mSizeHint;
}

QSize KTextDocument::minimumSizeHint()
{
    /*
    QTextCursor cursor( this );
    if ( ! cursor.atEnd() )
        cursor.movePosition( QTextCursor::NextBlock );
    qDebug() << "KTextDocument::minimumSizeHint() found:" << cursor.block().text();
    QSizeF s( documentLayout()->blockBoundingRect( cursor.block() ).size() );
    qDebug() << "KTextDocument::minimumSizeHint() found rect" << documentLayout()->blockBoundingRect( cursor.block());
    return QSize( static_cast<int>(s.width()),
                  static_cast<int>(s.height()) );
    */

    if ( mHintValid )
        return mMinimumSizeHint;

    mHintValid = true;
    mSizeHint = sizeForWidth( -1 );
    QSize sz(-1, -1);

    // PENDING(kalle) Cache
    sz.rwidth() = sizeForWidth( 0 ).width();
    sz.rheight() = sizeForWidth( 32000 ).height();
    if ( mSizeHint.height() < sz.height())
        sz.rheight() = mSizeHint.height();

    mMinimumSizeHint = sz;
    return sz;
}


QSize KTextDocument::sizeForWidth(int w)
{
    Q_UNUSED( w );

    setPageSize(QSize(0, 100000));

    return documentLayout()->documentSize().toSize();
}
