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
/** \file KChartGlobal.h
\brief Contains KChart macros.

Contains KChart macros.  */

#ifndef __KCHARTGLOBAL_H__
#define __KCHARTGLOBAL_H__

#include <qglobal.h>

#include "kchart_export.h"

#ifndef KDAB_SET_OBJECT_NAME
template <typename T>
inline T & __kdab__dereference_for_methodcall( T & o ) {
    return o;
}

template <typename T>
inline T & __kdab__dereference_for_methodcall( T * o ) {
    return *o;
}

#define KDAB_SET_OBJECT_NAME( x ) __kdab__dereference_for_methodcall( x ).setObjectName( QLatin1String( #x ) )
#endif

#define KCHART_DECLARE_PRIVATE_DERIVED( X )      \
public:                                           \
    class Private;                                \
protected:                                        \
    inline Private * d_func();                    \
    inline const Private * d_func() const;        \
    explicit inline X( Private * );               \
private:                                          \
    void init();

#define KCHART_DECLARE_PRIVATE_DERIVED_PARENT( X, ParentType )      \
public:                                           \
    class Private;                                \
protected:                                        \
    inline Private * d_func();                    \
    inline const Private * d_func() const;        \
    explicit inline X( Private *, ParentType );   \
private:                                          \
    void init();

#define KCHART_DECLARE_PRIVATE_DERIVED_QWIDGET( X )         \
    KCHART_DECLARE_PRIVATE_DERIVED_PARENT( X, QWidget* )

#define KCHART_DECLARE_PRIVATE_BASE_VALUE( X )              \
public:                                                      \
    inline void swap( X & other ) { qSwap( _d, other._d ); } \
protected:                                                   \
    class Private;                                           \
    Private * d_func() { return _d; }                        \
    const Private * d_func() const { return _d; }            \
private:                                                     \
    void init();                                             \
    Private * _d;

#define KCHART_DECLARE_PRIVATE_BASE_POLYMORPHIC( X ) \
public:                                           \
    class Private;                                    \
protected:                                        \
    Private * d_func() { return _d; }                 \
    const Private * d_func() const { return _d; }     \
    explicit inline X( Private * );                   \
private:                                              \
    void init();                                      \
    Private * _d;

#define KCHART_DECLARE_PRIVATE_BASE_POLYMORPHIC_QWIDGET( X ) \
public:                                           \
    class Private;                                    \
protected:                                        \
    Private * d_func() { return _d; }                 \
    const Private * d_func() const { return _d; }     \
    explicit inline X( Private *, QWidget* );                  \
private:                                              \
    void init();                                      \
    Private * _d;

#define KCHART_DERIVED_PRIVATE_FOOTER( CLASS, PARENT )     \
inline CLASS::CLASS( Private * p )                          \
  : PARENT( p ) { init(); }                                 \
inline CLASS::Private * CLASS::d_func()                     \
{ return static_cast<Private*>( PARENT::d_func() ); }       \
inline const CLASS::Private * CLASS::d_func() const         \
{ return static_cast<const Private*>( PARENT::d_func() ); }


#define KCHART_DECLARE_DERIVED_DIAGRAM( X, PLANE )     \
public:                                                 \
    class Private;                                      \
protected:                                              \
    inline Private * d_func();                          \
    inline const Private * d_func() const;              \
    explicit inline X( Private * );                     \
    explicit inline X( Private *, QWidget *, PLANE * ); \
private:                                                \
    void init();

#define KCHART_IMPL_DERIVED_DIAGRAM( CLASS, PARENT, PLANE ) \
inline CLASS::CLASS( Private * p )                           \
    : PARENT( p ) { init(); }                                \
inline CLASS::CLASS(                            \
    Private * p, QWidget* parent, PLANE * plane )            \
    : PARENT( p, parent, plane ) { init(); }                 \
inline CLASS::Private * CLASS::d_func()                      \
    { return static_cast<Private *>( PARENT::d_func() ); }   \
inline const CLASS::Private * CLASS::d_func() const          \
    { return static_cast<const Private *>( PARENT::d_func() ); }


#define KCHART_IMPL_DERIVED_PLANE( CLASS, BASEPLANE )        \
inline CLASS::CLASS( Private * p, Chart* parent )           \
    : BASEPLANE( p, parent ) { init(); }                      \
inline CLASS::Private * CLASS::d_func()                       \
    { return static_cast<Private *>( BASEPLANE::d_func() ); } \
inline const CLASS::Private * CLASS::d_func() const           \
    { return static_cast<const Private *>( BASEPLANE::d_func() ); }


#include <QtAlgorithms> // qSwap
#ifndef QT_NO_STL
#include <algorithm>
#define KCHART_DECLARE_SWAP_SPECIALISATION( X )            \
QT_BEGIN_NAMESPACE                                          \
    template <> inline void qSwap<X>( X & lhs, X & rhs )    \
    { lhs.swap( rhs ); }                                    \
QT_END_NAMESPACE                                            \
    namespace std {                                         \
        template <> inline void swap<X>( X & lhs, X & rhs ) \
        { lhs.swap( rhs ); }                                \
    }
#else
#define KCHART_DECLARE_SWAP_SPECIALISATION( X )            \
QT_BEGIN_NAMESPACE                                          \
    template <> inline void qSwap<X>( X & lhs, X & rhs )    \
    { lhs.swap( rhs ); }                                    \
QT_END_NAMESPACE
#endif

#define KCHART_DECLARE_SWAP_SPECIALISATION_DERIVED( X )    \
    KCHART_DECLARE_SWAP_SPECIALISATION( X )

#define KCHART_DECLARE_SWAP_BASE( X ) \
protected: \
    void doSwap( X& other ) \
    { qSwap( _d, other._d); }

#define KCHART_DECLARE_SWAP_DERIVED( X ) \
    void swap( X& other ) { doSwap( other ); }

#if defined(Q_OS_WIN) && defined(QT_DLL)
#if defined(_MSC_VER) && _MSC_VER >= 1300
// workaround http://support.microsoft.com/default.aspx?scid=kb;en-us;309801
#include <QPointF>
#include <QVector>
template class Q_DECL_IMPORT QVector<QPointF>;
#endif
#endif

#include <Qt>

/**
  \namespace KChart
  \brief Global namespace
  */
namespace KChart {

enum DisplayRoles {
  DatasetPenRole = 0x0A79EF95,
  DatasetBrushRole,
  DataValueLabelAttributesRole,
  ThreeDAttributesRole,
  LineAttributesRole,
  ThreeDLineAttributesRole,
  BarAttributesRole,
  StockBarAttributesRole,
  ThreeDBarAttributesRole,
  PieAttributesRole,
  ThreeDPieAttributesRole,
  DataHiddenRole,
  ValueTrackerAttributesRole,
  CommentRole
};
}

#endif // __KCHARTGLOBAL_H__
