/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef KTEXTDOCUMENT_H
#define KTEXTDOCUMENT_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the KD Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QTextDocument>
#include <QSize>

/**
  * KTextDocument is an internally used enhanced QTextDocument
  * \internal
  */
class KTextDocument : public QTextDocument
{
    Q_OBJECT

public:
    explicit KTextDocument( QObject* parent = nullptr );
    explicit KTextDocument( const QString& text, QObject* parent = nullptr );
    ~KTextDocument() override;

    QSize sizeHint();
    QSize minimumSizeHint();

private:
    QSize sizeForWidth( int width );

private:
    bool mHintValid;
    QSize mSizeHint;
    QSize mMinimumSizeHint;
};


#endif /* KTEXTDOCUMENT_H */

