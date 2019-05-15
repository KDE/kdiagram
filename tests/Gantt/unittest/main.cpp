/**
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KGantt library.
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "unittest/testregistry.h"

#include <QApplication>
#include <iostream>

int main( int argc , char ** argv ) {

  QApplication app( argc, argv );

  KDAB::UnitTest::Runner r;
  unsigned int failed = 0;
  if ( argc == 1 )
    failed = r.run();
  else {
    for ( int i = 1 ; i < argc ; ++i )
      if ( argv[i] && *argv[i] )
        failed += r.run( argv[i] );
      else {
        std::cerr << argv[0] << ": skipping empty group name" << std::endl;
      }
  }
  std::cout << failed << " tests failed." << std::endl;
  return failed;
}
