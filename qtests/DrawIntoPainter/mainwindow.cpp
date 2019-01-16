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

#include "mainwindow.h"
#include "framewidget.h"

#include <KChartChart>
#include <KChartAbstractCoordinatePlane>
#include <KChartLineDiagram>
#include <KChartLineAttributes>
#include <KChartTextAttributes>
#include <KChartDataValueAttributes>
#include <KChartThreeDLineAttributes>
#include <KChartMarkerAttributes>
#include <KChartFrameAttributes>
#include <KChartBackgroundAttributes>
#include <KChartLegend>

#include <QDebug>
#include <QPainter>
#include <QTime>

using namespace KChart;

static QPixmap drawIntoPixmap( const QSize& size, KChart::Chart* chart )
{
    QPixmap pix( size );
    pix.fill( Qt::white );
    QPainter painter( &pix );
    chart->paint( &painter, QRect( 0, 0, size.width(), size.height() ) );
    return pix;
}

// When set, this example uses FrameWidget which uses Chart::paint to paint itself.
// When not set, this example uses a Chart widget directly.
#define USE_FRAME_WIDGET 1


MainWindow::MainWindow( QWidget* parent ) :
    QWidget( parent )
{

    setupUi( this );

    connect( lineTypeCB, SIGNAL(currentIndexChanged(QString)), this, SLOT(setLineType(QString)) );
    connect( paintLegendCB, SIGNAL(toggled(bool)), this, SLOT(setLegendVisible(bool)) );
    connect( paintValuesCB, SIGNAL(toggled(bool)), this, SLOT(setValuesVisible(bool)) );
    connect( paintMarkersCB, SIGNAL(toggled(bool)), this, SLOT(setMarkersVisible(bool)) );
    connect( markersStyleCB, SIGNAL(currentIndexChanged(int)), this, SLOT(updateMarkers()) );
    connect( markersWidthSB, SIGNAL(valueChanged(int)), this, SLOT(updateMarkersHeight()) );
    connect( markersHeightSB, SIGNAL(valueChanged(int)), this, SLOT(updateMarkersWidth()) );
    connect( displayAreasCB, SIGNAL(toggled(bool)), this, SLOT(updateAreas(bool)) );
    connect( transparencySB, SIGNAL(valueChanged(int)), this, SLOT(updateAreasTransparency()) );
    connect( zoomFactorSB, SIGNAL(valueChanged(double)), this, SLOT(setZoomFactor(qreal)) );
    connect( hSBar, SIGNAL(valueChanged(int)), this, SLOT(setHPos(int)) );
    connect( vSBar, SIGNAL(valueChanged(int)), this, SLOT(setVPos(int)) );
    connect( savePB, SIGNAL(clicked()), this, SLOT(saveChart()) );

    QHBoxLayout* chartLayout = new QHBoxLayout( chartFrame );
#ifdef USE_FRAME_WIDGET
    FrameWidget* chartFrameWidget = new FrameWidget();
    chartLayout->addWidget( chartFrameWidget );
#endif
    hSBar->setVisible( false );
    vSBar->setVisible( false );

    m_model.loadFromCSV( ":/empty" );

    // Set up the diagram
    m_lines = new LineDiagram();

    m_lines->setModel( &m_model );

    CartesianAxis *xAxis = new CartesianAxis( m_lines );
    CartesianAxis *yAxis = new CartesianAxis ( m_lines );
    CartesianAxis *axisTop = new CartesianAxis ( m_lines );
    CartesianAxis *axisRight = new CartesianAxis ( m_lines );
    xAxis->setPosition ( KChart::CartesianAxis::Bottom );
    yAxis->setPosition ( KChart::CartesianAxis::Left );
    axisTop->setPosition( KChart::CartesianAxis::Top );
    axisRight->setPosition( KChart::CartesianAxis::Right );

    m_lines->addAxis( xAxis );
    m_lines->addAxis( yAxis );
    m_lines->addAxis( axisTop );
    m_lines->addAxis( axisRight );

    m_chart = new Chart();
    //m_chart->setGlobalLeading(10,10,10,10); // by default there is no leading

#ifdef USE_FRAME_WIDGET
    chartFrameWidget->setChart( m_chart );
    // make sure, we re-draw after changing one of the chart's properties
    connect( m_chart,          SIGNAL(propertiesChanged()),
             chartFrameWidget, SLOT(update()) ) ;
#else
    chartLayout->addWidget( m_chart );
#endif

    m_chart->coordinatePlane()->replaceDiagram( m_lines );

    for ( int iColumn = 0; iColumn<m_lines->model()->columnCount(); ++iColumn ) {
        QPen pen(m_lines->pen( iColumn ));
        pen.setWidth(4);
        m_lines->setPen( iColumn, pen );
    }

    FrameAttributes faChart( m_chart->frameAttributes() );
    faChart.setVisible( true );
    faChart.setPen( QPen(QColor(0x60,0x60,0xb0), 8) );
    m_chart->setFrameAttributes( faChart );

    BackgroundAttributes baChart( m_chart->backgroundAttributes() );
    baChart.setVisible( true );
    baChart.setBrush( QColor(0xd0,0xd0,0xff) );
    m_chart->setBackgroundAttributes( baChart );

    // Set up the legend
    m_legend = new Legend( m_lines, m_chart );

    m_legend->setPosition( Position::South );
    m_legend->setAlignment( Qt::AlignRight );
    m_legend->setShowLines( false );
    m_legend->setTitleText( tr( "Legend" ) );
    m_legend->setOrientation( Qt::Horizontal );

    // setting the legend frame and background to the same color:
    const QColor legendColor(0xff,0xe0,0x80);
    FrameAttributes faLegend( m_legend->frameAttributes() );
    faLegend.setVisible( true );
    faLegend.setPen( QPen(legendColor, 1) );
    m_legend->setFrameAttributes( faLegend );

    BackgroundAttributes baLegend( m_legend->backgroundAttributes() );
    baLegend.setVisible( true );
    baLegend.setBrush( legendColor );
    m_legend->setBackgroundAttributes( baLegend );

    m_chart->addLegend( m_legend );

    // for illustration we paint the same chart at different sizes:
    QSize size1 = QSize( 200, 200 );
    QSize size2 = QSize( 800, 800 );
    m_pix1 = drawIntoPixmap( size1, m_chart );
    m_pix2 = drawIntoPixmap( size2, m_chart );
    m_pix2 = m_pix2.scaled( size1 );

    m_smallChart1 = new QLabel( this );
    m_smallChart1->setWindowTitle( "200x200" );
    m_smallChart1->setPixmap( m_pix1 );
    m_smallChart1->setFixedSize( m_pix1.size() );
    m_smallChart1->move( width() - m_pix1.width()*2,
                         height()/2 - m_pix1.height()-5 );
    m_smallChart1->show();

    m_smallChart2 = new QLabel( this );
    m_smallChart2->setWindowTitle( "800x800 scaled down" );
    m_smallChart2->setPixmap( m_pix2 );
    m_smallChart2->setFixedSize( m_pix2.size() );
    m_smallChart2->move( width() - m_pix2.width()*2,
                         height()/2 + 5 );
    m_smallChart2->show();

    faChart.setPen( QPen(QColor(0xb0,0xb0,0xff), 8) );
    m_chart->setFrameAttributes( faChart );

    // initialize attributes; this is necessary because we need to enable data value attributes before
    // any of them (e.g. only markers) can be displayed. but if we enable data value attributs, a default
    // data value text is included, even if we only wanted to set markers. so we enable DVA and then
    // individually disable the parts we don't want.
    setValuesVisible( false );
    setMarkersVisible( false );
}

void MainWindow::updateData(QString data)
{
    QTime t;
    t.start();

    m_model.loadFromCSV( data );

    qDebug("Time for loading data %s: %d ms", data.toLatin1().constData(), t.elapsed());
    t.restart();

    QSize size1 = QSize( 200, 200 );
    QSize size2 = QSize( 800, 800 );
    m_pix1 = drawIntoPixmap( size1, m_chart );
    m_pix2 = drawIntoPixmap( size2, m_chart );

    qDebug("Time for drawing pixmap %s: %d ms", data.toLatin1().constData(), t.elapsed());
    t.restart();

    m_lines->setModel( &m_model );

    qDebug("Time for setting model %s: %d ms", data.toLatin1().constData(), t.elapsed());
    t.restart();

    m_smallChart1->setPixmap( m_pix1 );
    m_smallChart2->setPixmap( m_pix2 );

    m_smallChart1->show();
    m_smallChart2->show();

    qDebug("Time for setting pixmap %s: %d ms", data.toLatin1().constData(), t.elapsed());
    t.restart();

}

void MainWindow::setLineType( const QString & text )
{
    if ( text == "Normal" )
        m_lines->setType( LineDiagram::Normal );
    else if ( text == "Stacked" )
        m_lines->setType( LineDiagram::Stacked );
    else if ( text == "Percent" )
        m_lines->setType( LineDiagram::Percent );
    else
        qWarning (" Does not match any type");
}

void MainWindow::setLegendVisible(bool visible )
{
    KChart::Legend* legend = m_chart->legend();
    if ( visible != ( legend != nullptr ) ) {
        if ( visible )
            m_chart->addLegend( m_legend );
        else
            m_chart->takeLegend( legend );
    }
}

void MainWindow::setValuesVisible(bool visible )
{
    const int colCount = m_lines->model()->columnCount();
    for ( int iColumn = 0; iColumn<colCount; ++iColumn ) {
        DataValueAttributes a = m_lines->dataValueAttributes( iColumn );
        a.setVisible( true );

        TextAttributes ta = a.textAttributes();
        ta.setRotation( 0 );
        ta.setFont( QFont( "Comic", 10 ) );
        ta.setPen( m_lines->brush( iColumn ).color() );
        ta.setVisible( visible );

        a.setTextAttributes( ta );
        m_lines->setDataValueAttributes( iColumn, a);
    }
}


void MainWindow::setMarkersVisible( bool visible )
{
    paintMarkers( visible, QSize() );
}

void MainWindow::updateMarkers()
{
    setMarkersVisible( paintMarkersCB->isChecked() );
}

void MainWindow::updateMarkersHeight()
{
    markersHeightSB->setValue( markersWidthSB->value() );
    updateMarkers();
}

void MainWindow::updateMarkersWidth()
{
    markersWidthSB->setValue( markersHeightSB->value() );
    updateMarkers();
}

void MainWindow::updateAreas( bool visible )
{
    const int colCount = m_lines->model()->columnCount();
    for ( int iColumn = 0; iColumn<colCount; ++iColumn ) {
        LineAttributes la( m_lines->lineAttributes( iColumn ) );
        la.setDisplayArea( visible );
        if ( visible  )
            la.setTransparency( transparencySB->value() );
        m_lines->setLineAttributes( iColumn,  la );
    }
}

void MainWindow::updateAreasTransparency()
{
    if ( !displayAreasCB->isChecked() )
        displayAreasCB->setChecked( true );
    else
        updateAreas( true );
}

void MainWindow::setZoomFactor( qreal factor )
{
    const bool isZoomedIn = factor > 1.0f;
    hSBar->setVisible( isZoomedIn );
    vSBar->setVisible( isZoomedIn );
    if ( !isZoomedIn ) {
        hSBar->setValue( 500 );
        vSBar->setValue( 500 );
    }
    m_chart->coordinatePlane()->setZoomFactorX( factor );
    m_chart->coordinatePlane()->setZoomFactorY( factor );
}

void MainWindow::setHPos( int hPos )
{
    m_chart->coordinatePlane()->setZoomCenter( QPointF(hPos/1000.0, vSBar->value()/1000.0) );
    m_chart->update();
}

void MainWindow::setVPos( int vPos )
{
    m_chart->coordinatePlane()->setZoomCenter( QPointF( hSBar->value()/1000.0, vPos/1000.0) );
}

// since DataValue markers have no relative sizing mode we need to scale them for printing
void MainWindow::paintMarkers( bool checked, const QSize& printSize )
{
    MarkerAttributes::MarkerStylesMap map;
    map.insert( 0, MarkerAttributes::MarkerSquare );
    map.insert( 1, MarkerAttributes::MarkerCircle );
    map.insert( 2, MarkerAttributes::MarkerRing );
    map.insert( 3, MarkerAttributes::MarkerCross );
    map.insert( 4, MarkerAttributes::MarkerDiamond );

    // next: Specify column- / cell-specific attributes!
    const int colCount = m_lines->model()->columnCount();
    for ( int iColumn = 0; iColumn<colCount; ++iColumn ) {
        DataValueAttributes dva = m_lines->dataValueAttributes( iColumn );
        dva.setVisible( true );
        MarkerAttributes ma( dva.markerAttributes() );

    switch ( markersStyleCB->currentIndex() ) {
        case 0:
                   ma.setMarkerStyle( MarkerAttributes::MarkerSquare );
                   break;
        case 1:
                   // Column-specific attributes
                   ma.setMarkerStyle( map.value( iColumn ) );
                   break;
        case 2:
                   ma.setMarkerStyle( MarkerAttributes::MarkerCircle );
                   break;
        case 3:
                   ma.setMarkerStyle( MarkerAttributes::MarkerDiamond );
                   break;
        case 4:
                   ma.setMarkerStyle( MarkerAttributes::Marker1Pixel );
                   break;
        case 5:
                   ma.setMarkerStyle( MarkerAttributes::Marker4Pixels );
                   break;
        case 6:
                   ma.setMarkerStyle( MarkerAttributes::MarkerRing );
                   break;
        case 7:
                   ma.setMarkerStyle( MarkerAttributes::MarkerCross );
                   break;
        case 8:
                   ma.setMarkerStyle( MarkerAttributes::MarkerFastCross );
                   break;
        default:
            Q_ASSERT( false );
    }
    ma.setVisible( checked );

        qreal factorWidth = printSize.isValid() ? ( printSize.width() / m_chart->rect().width() ) : 1.0f;
        qreal factorHeight = printSize.isValid() ? ( printSize.height() / m_chart->rect().height() ) : 1.0f;
        ma.setMarkerSize( QSize( markersWidthSB->value() * factorWidth, markersHeightSB->value() * factorHeight ) );

        dva.setMarkerAttributes( ma );
        m_lines->setDataValueAttributes( iColumn, dva );

    // make a special one for certain values
    DataValueAttributes yellowAttributes( dva );
    MarkerAttributes yellowMarker( yellowAttributes.markerAttributes() );
    yellowMarker.setMarkerColor( Qt::yellow );
    yellowAttributes.setMarkerAttributes( yellowMarker );

    const int rowCount = m_lines->model()->rowCount();
        for ( int j=0; j< rowCount; ++j ) {
            QModelIndex index = m_lines->model()->index( j, iColumn, QModelIndex() );
            QBrush brush = m_lines->model()->headerData( iColumn, Qt::Vertical, DatasetBrushRole ).value<QBrush>();
            qreal value = m_lines->model()->data( index ).toReal();
            /* Set a specific color - marker for a specific value */
            if ( value == 13 ) {
                m_lines->setDataValueAttributes( index, yellowAttributes );
            }
        }
    }
}

void MainWindow::saveChart()
{
    qDebug() << "Painting into PNG";
    QPixmap qpix(600,600);
    QPainter painter(&qpix);
    painter.setBrush(Qt::white);
    painter.fillRect( 0, 0, 600, 600, Qt::white);
    m_chart->paint( &painter,
                    QRect(100, 100, 400, 400) );
    painter.end();
    qpix.save("kchart-demo.png", "PNG");
    qDebug() << "Painting into PNG - done";
}

void MainWindow::resizeEvent ( QResizeEvent * )
{
    m_smallChart1->move( width() - m_pix1.width()*2,
                         height()/2 - m_pix1.height()-5 );
    m_smallChart2->move( width() - m_pix2.width()*2,
                         height()/2 + 5 );
}


