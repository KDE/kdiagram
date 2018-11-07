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

#include "diagramsettings.h"
#include "ui_diagramsettings.h"

#include "gradientdialog.h"

#include <QColorDialog>

#include <QStyleFactory>

#include <QFileDialog>

#include <KChartThreeDBarAttributes>
#include <KChartThreeDLineAttributes>
#include <KChartThreeDPieAttributes>

#include <KChartChart>
#include <KChartBarDiagram>
#include <KChartLineDiagram>
#include <KChartPieDiagram>
#include <KChartCartesianCoordinatePlane>

#include <KChartBackgroundAttributes>

using namespace KChart;

class DiagramSettings::Private : public QObject
{
    Q_OBJECT
public:
    Private( Chart *chart = nullptr, DiagramSettings *q = nullptr );
    ~Private();
    void init();
    void setThreeDData( const AbstractThreeDAttributes &attr );

    Chart *m_chart;
    Ui::DiagramSettings *ui;
    DiagramSettings *qq;
public Q_SLOTS:
    void changeThreeD();
    void changeBackgroundColor();
    void changeBackgroundVisibility();
    void changeAutoGradient();
};

DiagramSettings::Private::Private( Chart *chart, DiagramSettings *q )
    : QObject( q )
    , m_chart( chart )
    , ui(new Ui::DiagramSettings)
    , qq( q )
{

}

DiagramSettings::Private::~Private()
{

}

void DiagramSettings::Private::changeAutoGradient()
{
    changeThreeD();
}

void DiagramSettings::Private::changeThreeD()
{
    if ( m_chart && m_chart->coordinatePlane() && m_chart->coordinatePlane()->diagram() )
    {
        BarDiagram *bars = qobject_cast< BarDiagram* >( m_chart->coordinatePlane()->diagram() );
        LineDiagram *lines = qobject_cast< LineDiagram* >( m_chart->coordinatePlane()->diagram() );
        PieDiagram *pie = qobject_cast< PieDiagram* >( m_chart->coordinatePlane()->diagram() );
        if ( bars )
        {
            ThreeDBarAttributes td( bars->threeDBarAttributes() );
            td.setEnabled( ui->threeDSelector->checkState() == Qt::Checked );
            td.setUseShadowColors( true );
            td.setDepth( ui->barHeightInput->value() );
            td.setThreeDBrushEnabled( ui->autoGradient->checkState() == Qt::Checked );
            bars->setThreeDBarAttributes( td );
            m_chart->update();
        }
        else if ( lines )
        {
            ThreeDLineAttributes td( lines->threeDLineAttributes() );
            td.setEnabled( ui->threeDSelector->checkState() == Qt::Checked );
            td.setDepth( ui->barHeightInput->value() );
            td.setThreeDBrushEnabled( ui->autoGradient->checkState() == Qt::Checked );
            lines->setThreeDLineAttributes( td );
            m_chart->update();
        }
        else if ( pie )
        {
            ThreeDPieAttributes td( pie->threeDPieAttributes() );
            td.setEnabled( ui->threeDSelector->checkState() == Qt::Checked );
            td.setDepth( ui->barHeightInput->value() );
            td.setThreeDBrushEnabled( ui->autoGradient->checkState() == Qt::Checked );
            pie->setThreeDPieAttributes( td );
            m_chart->update();
        }
    }
}
void DiagramSettings::Private::changeBackgroundColor()
{
    if ( m_chart && m_chart->coordinatePlane() && m_chart->coordinatePlane()->diagram() )
    {
        BackgroundAttributes bat = m_chart->coordinatePlane()->backgroundAttributes();
        bat.setVisible( true );
        ui->visibleBtn->setChecked( true );

        if ( ui->color->isChecked() )
        {

            QBrush setBrush = bat.brush();
            const QColor color = QColorDialog::getColor( setBrush.color(), qq, tr( "Choose new color" ) );
            if ( !color.isValid() )
                return;
            bat.setBrush( color );
            QPalette palette = ui->diagramBackground->palette();
            palette.setBrush( QPalette::Button, color );
            ui->diagramBackground->setPalette( palette );
        }
        else if ( ui->textureBtn->isChecked() )
        {
            //QBrush setBrush = m_chart->coordinatePlane()->diagram()->brush( index );
            QImage texture;

            const QString filename = QFileDialog::getOpenFileName( qq, tr( "Choose Texture" ), QString(), tr( "Images (*.png *.xpm *.jpg)" ) );
            if ( filename.isEmpty() )
                return;
            texture = QImage( filename );
            bat.setBrush( texture );
            QPalette palette = ui->diagramBackground->palette();
            palette.setBrush( QPalette::Button, QBrush( texture ) );
            ui->diagramBackground->setPalette( palette );
        }
        else
        {
            QBrush setBrush = bat.brush();
            QGradient grad;
            QLinearGradient lGrad;
            lGrad.setColorAt( 0, Qt::black );
            lGrad.setColorAt( 1, setBrush.color() );
            grad = lGrad;

            if ( setBrush.gradient() )
                grad = *setBrush.gradient();
            const QGradient &color = GradientDialog::getGradient( grad, qq, tr( "Choose new color" ) );
            bat.setBrush( color );
            QPalette palette = ui->diagramBackground->palette();
            palette.setBrush( QPalette::Button, QBrush( color ) );
            ui->diagramBackground->setPalette( palette );
        }
        bat.setVisible( true );
        m_chart->coordinatePlane()->setBackgroundAttributes( bat );
        qq->update();
    }
}

void DiagramSettings::Private::changeBackgroundVisibility()
{
    if ( m_chart && m_chart->coordinatePlane() && m_chart->coordinatePlane()->diagram() )
    {
        BackgroundAttributes bat = m_chart->coordinatePlane()->backgroundAttributes();
        bat.setVisible( ui->visibleBtn->checkState() == Qt::Checked );
        m_chart->coordinatePlane()->setBackgroundAttributes( bat );
        m_chart->update();
    }
}

void DiagramSettings::Private::init()
{
    ui->setupUi( qq );
#ifdef Q_OS_LINUX
    ui->diagramBackground->setStyle( QStyleFactory::create( QStringLiteral( "cleanlooks" ) ) );
#endif

    connect( ui->threeDSelector, SIGNAL(toggled(bool)), this, SLOT(changeThreeD()) );
    connect( ui->diagramBackground, SIGNAL(clicked()), this, SLOT(changeBackgroundColor()) );
    connect( ui->visibleBtn, SIGNAL(toggled(bool)), this, SLOT(changeBackgroundVisibility()) );
    connect( ui->barHeightInput, SIGNAL(valueChanged(int)), this, SLOT(changeThreeD()) );
    connect( ui->autoGradient, SIGNAL(toggled(bool)), this, SLOT(changeAutoGradient()) );

    qq->refreshSettings();
}

void DiagramSettings::Private::setThreeDData( const AbstractThreeDAttributes &attr )
{
    ui->threeDSelector->setCheckState( attr.isEnabled() ? Qt::Checked : Qt::Unchecked );
    ui->autoGradient->setCheckState( attr.isThreeDBrushEnabled() ? Qt::Checked : Qt::Unchecked );
    ui->barHeightInput->setValue( attr.depth() );
}

DiagramSettings::DiagramSettings( Chart *chart, QWidget *parent )
    : QWidget( parent )
    , d( new Private( chart, this ) )
{
    d->init();
}

DiagramSettings::~DiagramSettings()
{
    delete d;
}

void DiagramSettings::refreshSettings()
{
    if ( d->m_chart && d->m_chart->coordinatePlane() && d->m_chart->coordinatePlane()->diagram() )
    {
        BarDiagram *bars = qobject_cast< BarDiagram* >( d->m_chart->coordinatePlane()->diagram() );
        LineDiagram *lines = qobject_cast< LineDiagram* >( d->m_chart->coordinatePlane()->diagram() );
        PieDiagram *pie = qobject_cast< PieDiagram* >( d->m_chart->coordinatePlane()->diagram() );

        if ( bars )
        {
            const AbstractThreeDAttributes &td = bars->threeDBarAttributes();
            d->setThreeDData( td );
        }
        else if ( lines )
        {
            const AbstractThreeDAttributes &td = lines->threeDLineAttributes();
            d->setThreeDData( td );
        }
        else if ( pie )
        {
            const AbstractThreeDAttributes &td = pie->threeDPieAttributes();
            d->setThreeDData( td );
        }
        BackgroundAttributes bat = d->m_chart->coordinatePlane()->backgroundAttributes();
        QBrush setBrush = bat.brush();
        QPalette palette = d->ui->diagramBackground->palette();
        if ( bat.isVisible() )
            palette.setBrush( QPalette::Button, setBrush );
        else
            palette.setBrush( QPalette::Button, this->palette().brush( QPalette::Button ) );
        d->ui->diagramBackground->setPalette( palette );
    }
}

#include "diagramsettings.moc"
