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

#ifndef COLORSLIDER_H
#define COLORSLIDER_H

#include <QAbstractSlider>

class ColorSlider : public QAbstractSlider
{
    Q_OBJECT
    Q_PROPERTY( QColor startColor READ startColor WRITE setStartColor NOTIFY startColorChanged )
    Q_PROPERTY( QColor endColor READ endColor WRITE setStartColor NOTIFY endColorChanged )
public:
    explicit ColorSlider( QWidget *parent = nullptr );
    ~ColorSlider();
    QColor startColor() const;
    void setStartColor( const QColor &color );
    QColor endColor() const;
    void setEndColor( const QColor &color );
    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent( QPaintEvent *event ) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event ) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event ) Q_DECL_OVERRIDE;
    void mouseMoveEvent( QMouseEvent *event ) Q_DECL_OVERRIDE;

Q_SIGNALS:
    void startColorChanged();
    void endColorChanged();

public Q_SLOTS:
private:
    class Private;
    Private *d;

};

#endif // COLORSLIDER_H
