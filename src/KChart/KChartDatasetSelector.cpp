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

#include "KChartDatasetSelector.h"

#include "ui_KChartDatasetSelector.h"

#include "KChartMath_p.h"

using namespace KChart;

DatasetSelectorWidget::DatasetSelectorWidget( QWidget* parent )
    : QFrame( parent )
    , mUi( new Ui::DatasetSelector() )
    , mSourceRowCount( 0 )
    , mSourceColumnCount( 0 )
{
    qWarning( "For DatasetSelectorWidget to become useful, it has to be connected to the proxy model it configures!" );

    mUi->setupUi( this );
    setMinimumSize( minimumSizeHint() );

    connect( mUi->sbStartColumn, SIGNAL(valueChanged(int)), this, SLOT(calculateMapping()) );
    connect( mUi->sbStartRow, SIGNAL(valueChanged(int)), this, SLOT(calculateMapping()) );
    connect( mUi->sbColumnCount, SIGNAL(valueChanged(int)), this, SLOT(calculateMapping()) );
    connect( mUi->sbRowCount, SIGNAL(valueChanged(int)), this, SLOT(calculateMapping()) );
    connect( mUi->cbReverseRows, SIGNAL(stateChanged(int)), this, SLOT(calculateMapping()) );
    connect( mUi->cbReverseColumns, SIGNAL(stateChanged(int)), this, SLOT(calculateMapping()) );
    connect( mUi->groupBox, SIGNAL(toggled(bool)), this, SLOT(updateState(bool)) );
}

DatasetSelectorWidget::~DatasetSelectorWidget()
{
    delete mUi;
}

void DatasetSelectorWidget::updateState( bool state )
{
    if ( state )
    {
        calculateMapping();
    } else {
        emit mappingDisabled();
    }
}


void DatasetSelectorWidget::setSourceRowCount( const int& rowCount )
{
    if ( rowCount != mSourceRowCount )
    {
        mSourceRowCount = rowCount;
        resetDisplayValues();
    }
}

void DatasetSelectorWidget::setSourceColumnCount( const int& columnCount )
{
    if ( columnCount != mSourceColumnCount )
    {
        mSourceColumnCount = columnCount;
        resetDisplayValues();
    }
}

void DatasetSelectorWidget::resetDisplayValues()
{
    mUi->sbStartRow->setValue( 0 );
    mUi->sbStartRow->setMinimum( 0 );
    mUi->sbStartRow->setMaximum( qMax( mSourceRowCount - 1, 0 ) );
    mUi->sbStartColumn->setValue( 0 );
    mUi->sbStartColumn->setMinimum( 0 );
    mUi->sbStartColumn->setMaximum( qMax( mSourceColumnCount - 1, 0 ) );
    mUi->sbRowCount->setMinimum( 1 );
    mUi->sbRowCount->setMaximum( mSourceRowCount );
    mUi->sbRowCount->setValue( mSourceRowCount );
    mUi->sbColumnCount->setMinimum( 1 );
    mUi->sbColumnCount->setMaximum( mSourceColumnCount );
    mUi->sbColumnCount->setValue( mSourceColumnCount );
    mUi->groupBox->setChecked( false );
    emit mappingDisabled();
}

void DatasetSelectorWidget::calculateMapping()
{
    if ( mSourceColumnCount < 2 && mSourceRowCount < 2 )
    {
        mUi->groupBox->setEnabled( false );
        emit mappingDisabled();
    } else {
        mUi->groupBox->setEnabled( true );

        if ( ! mUi->groupBox->isChecked() )
        {
            emit mappingDisabled();
            return;
        }

        // retrieve values:
        int startRow = mUi->sbStartRow->value();
        int startColumn = mUi->sbStartColumn->value();
        int rowCount = mUi->sbRowCount->value();
        int columnCount = mUi->sbColumnCount->value();
        bool reverseColumns = mUi->cbReverseColumns->checkState() == Qt::Checked;
        bool reverseRows = mUi->cbReverseRows->checkState() == Qt::Checked;

        // verify values:
        startRow = qMin( startRow,  mSourceRowCount - 2 );
        startRow = qMax( 0, startRow );
        startColumn = qMin( startColumn,  mSourceColumnCount - 2 );
        startColumn = qMax( 0,  startColumn );

        rowCount = qMin( rowCount, mSourceRowCount - startRow );
        rowCount = qMax( 1, rowCount );
        columnCount = qMin( columnCount, mSourceColumnCount - startColumn );
        columnCount = qMax( 1, columnCount );

        DatasetDescriptionVector rowConfig( rowCount );
        Q_ASSERT( rowConfig.size() > 0 );
        DatasetDescriptionVector columnConfig( columnCount );
        Q_ASSERT( columnConfig.size() > 0 );

        // fill the dataset description vectors:
        for ( int row = 0; row < rowCount; ++row )
        {
            if ( reverseRows )
            {
                rowConfig[row] = startRow + rowCount - row - 1;
            } else {
                rowConfig[row] = startRow + row;
            }
        }

        for ( int column = 0; column < columnCount; ++ column )
        {
            if ( reverseColumns )
            {
                columnConfig[column] = startColumn + columnCount - column -1;
            } else {
                columnConfig[column] = startColumn + column;
            }
        }

        // and tell the world:
        emit configureDatasetProxyModel( rowConfig, columnConfig );
    }
}

