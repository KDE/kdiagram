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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __ASCSHARED_UTIL_LIBUTIL_H__
#define __ASCSHARED_UTIL_LIBUTIL_H__

// These two macros can be used to force the loading of static objects in static libraries.
// Under normal circumstances, the linker automatically discards unused library symbols from the final executable,
// which is a problem for static objects with a constructor performing a specific action such as registration.
// Note that the export macro only needs to be included once per .cpp file (even if there are many static objects in the file).
// Parameters :
// - ID : an file-wide identifier, e.g. the filename without the extension.
//        It shouldn't be quoted, no spaces, and contain only alphanumerical characters.
#define KDAB_EXPORT_STATIC_SYMBOLS( ID ) int __init_##ID##_static_symbols() { return 0; }
#define KDAB_IMPORT_STATIC_SYMBOLS( ID ) extern int __init_##ID##_static_symbols(); \
    static int fake_init##ID = __init_##ID##_static_symbols();

#endif // __ASCSHARED_UTIL_LIBUTIL_H__
