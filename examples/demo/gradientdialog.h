/**
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef GRADIENTDIALOG_H
#define GRADIENTDIALOG_H

#include <QDialog>
#include <QGradient>

class GradientDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY( QGradient gradient READ gradient WRITE setGradient NOTIFY gradientChanged() )

public:
    explicit GradientDialog( QWidget *parent = nullptr );
    ~GradientDialog() override;
    QGradient gradient() const;
    void setGradient( const QGradient &gradient );
    static QGradient getGradient( const QGradient &gradient, QWidget *parent = nullptr, const QString &title = QString() );

Q_SIGNALS:
    void gradientChanged();

private:
    class Private;
    Private *d;
};

#endif // GRADIENTDIALOG_H
