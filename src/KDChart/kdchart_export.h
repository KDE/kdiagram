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

#ifndef KDCHART_EXPORT_H
#define KDCHART_EXPORT_H

#include <qglobal.h>

# ifdef KDCHART_STATICLIB
#  undef KDCHART_SHAREDLIB
#  define KDCHART_EXPORT
#  define KDGANTT_EXPORT
#  define KDCHART_COMPAT_EXPORT
# else
#  ifdef KDCHART_BUILD_KDCHART_LIB
#   define KDCHART_EXPORT Q_DECL_EXPORT
#   define KDGANTT_EXPORT Q_DECL_EXPORT
#  else
#   define KDCHART_EXPORT Q_DECL_IMPORT
#   define KDGANTT_EXPORT Q_DECL_IMPORT
#  endif
#  ifdef KDCHART_BUILD_KDCHART_COMPAT_LIB
#   define KDCHART_COMPAT_EXPORT Q_DECL_EXPORT
#  else
#   define KDCHART_COMPAT_EXPORT Q_DECL_IMPORT
#  endif
#  ifdef KDCHART_BUILD_PLUGIN_LIB
#   define KDCHART_PLUGIN_EXPORT Q_DECL_EXPORT
#  else
#   define KDCHART_PLUGIN_EXPORT Q_DECL_IMPORT
#  endif
# endif

#endif // KDCHART_EXPORT_H
