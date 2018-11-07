/**
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
    ~GradientDialog();
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
