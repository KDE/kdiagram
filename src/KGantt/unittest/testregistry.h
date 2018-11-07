/*
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __KDAB__UNITTEST__TESTREGISTRY_H__
#define __KDAB__UNITTEST__TESTREGISTRY_H__

#ifndef KDAB_NO_UNIT_TESTS

#include "../kganttglobal.h"

#include <string>
#include <map>
#include <vector>
#include <cassert>

namespace KDAB {
namespace UnitTest {

    class Test;
    class TestFactory;

    class KGANTT_EXPORT TestRegistry {
        friend class ::KDAB::UnitTest::TestFactory;
        static TestRegistry * mSelf;
        TestRegistry();
        ~TestRegistry();
    public:
        static TestRegistry * instance();
        static void deleteInstance();

        void registerTestFactory( const TestFactory * tf, const char * group );

        /*! runs all tests in all groups.
           @return the number of failed tests (if any) */
        unsigned int run() const;
        /*! runs only tests in group \a group
            @return the number of failed tests (if any) */
        unsigned int run( const char * group ) const;

    private:
        std::map< std::string, std::vector<const TestFactory*> > mTests;
    };

    class KGANTT_EXPORT Runner {
    public:
        ~Runner();
        unsigned int run( const char * group = nullptr ) const;
    };

}
}

#endif // KDAB_NO_UNIT_TESTS

#endif // __KDAB__UNITTEST__TESTREGISTRY_H__
