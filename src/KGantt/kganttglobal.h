/*
 * SPDX-FileCopyrightText: 2001-2015 Klaralvdalens Datakonsult AB. All rights reserved.
 *
 * This file is part of the KGantt library.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
/** \file kganttglobal.h
\brief Contains KGantt macros.

Contains KGantt macros.  */

#ifndef KGANTTGLOBAL_H
#define KGANTTGLOBAL_H

#include <Qt>
#include <QDateTime>
#include <QDebug>
#include <QMetaType>

#include "kgantt_export.h"

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 4) && (__GNUC_PATCHLEVEL__ == 0)
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
int vswprintf(wchar_t *, const wchar_t *, va_list);
#endif

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

#if defined(_MSC_VER) && _MSC_VER <= 1300
#define KGANTT_DECLARE_PRIVATE_DERIVED( X )      \
public:                                           \
    class Private;                                \
	friend class Private;                     \
protected:                                        \
    inline Private * d_func();                    \
    inline const Private * d_func() const;        \
    explicit inline X( Private * );               \
private:                                          \
    void init();
#else
#define KGANTT_DECLARE_PRIVATE_DERIVED( X )      \
protected:                                        \
    class Private;                                \
	friend class Private;                     \
    inline Private * d_func();                    \
    inline const Private * d_func() const;        \
    explicit inline X( Private * );               \
private:                                          \
    void init();
#endif

#if defined(_MSC_VER) && _MSC_VER <= 1300
#define KGANTT_DECLARE_PRIVATE_DERIVED_PARENT( X, ParentType )      \
public:                                           \
    class Private;                                \
	friend class Private;                     \
protected:                                        \
    inline Private * d_func();                    \
    inline const Private * d_func() const;        \
    explicit inline X( Private *, ParentType );   \
private:                                          \
    void init();
#else
#define KGANTT_DECLARE_PRIVATE_DERIVED_PARENT( X, ParentType )      \
protected:                                        \
    class Private;                                \
	friend class Private;                     \
    inline Private * d_func();                    \
    inline const Private * d_func() const;        \
    explicit inline X( Private *, ParentType );   \
private:                                          \
    void init();
#endif

#define KGANTT_DECLARE_PRIVATE_DERIVED_QWIDGET( X )         \
    KGANTT_DECLARE_PRIVATE_DERIVED_PARENT( X, QWidget* )

#define KGANTT_DECLARE_PRIVATE_BASE_VALUE( X )              \
public:                                                      \
    inline void swap( X & other ) { qSwap( _d, other._d ); } \
protected:                                                   \
    class Private;                                           \
	friend class Private;                                \
    Private * d_func() { return _d; }                        \
    const Private * d_func() const { return _d; }            \
private:                                                     \
    void init();                                             \
    Private * _d;

#if defined(_MSC_VER) && _MSC_VER <= 1300
#define KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( X ) \
public:                                               \
    class Private;                                    \
	friend class Private;                         \
protected:                                            \
    Private * d_func() { return _d; }                 \
    const Private * d_func() const { return _d; }     \
    explicit inline X( Private * );                   \
private:                                              \
    void init();                                      \
    Private * _d;
#else
#define KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( X ) \
protected:                                            \
    class Private;                                    \
	friend class Private;                         \
    Private * d_func() { return _d; }                 \
    const Private * d_func() const { return _d; }     \
    explicit inline X( Private * );                   \
private:                                              \
    void init();                                      \
    Private * _d;
#endif

#if defined(_MSC_VER) && _MSC_VER <= 1300
#define KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC_QWIDGET( X ) \
public:                                               \
    class Private;                                    \
	friend class Private;                         \
protected:                                            \
    Private * d_func() { return _d; }                 \
    const Private * d_func() const { return _d; }     \
    explicit inline X( Private *, QWidget* );         \
private:                                              \
    void init();                                      \
    Private * _d;
#else
#define KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC_QWIDGET( X ) \
protected:                                            \
    class Private;                                    \
	friend class Private;                         \
    Private * d_func() { return _d; }                 \
    const Private * d_func() const { return _d; }     \
    explicit inline X( Private *, QWidget* );         \
private:                                              \
    void init();                                      \
    Private * _d;
#endif



// enable this for testing if KD Gantt works without STL support in Qt:
//
// #define QT_NO_STL


#include <QtAlgorithms> // qSwap
#ifndef QT_NO_STL
#include <algorithm>
#define KGANTT_DECLARE_SWAP_SPECIALISATION( X )            \
QT_BEGIN_NAMESPACE                                          \
    template <> inline void qSwap<X>( X & lhs, X & rhs )    \
    { lhs.swap( rhs ); }                                    \
QT_END_NAMESPACE                                            \
    namespace std {                                         \
        template <> inline void swap<X>( X & lhs, X & rhs ) \
        { lhs.swap( rhs ); }                                \
    }
#else
#define KGANTT_DECLARE_SWAP_SPECIALISATION( X )            \
QT_BEGIN_NAMESPACE                                          \
    template <> inline void qSwap<X>( X & lhs, X & rhs )    \
    { lhs.swap( rhs ); }                                    \
QT_END_NAMESPACE
#endif

#define KGANTT_DECLARE_SWAP_SPECIALISATION_DERIVED( X )    \
    KGANTT_DECLARE_SWAP_SPECIALISATION( X )

#define KGANTT_DECLARE_SWAP_BASE( X ) \
protected: \
    void doSwap( X& other ) \
    { qSwap( _d, other._d); }

#define KGANTT_DECLARE_SWAP_DERIVED( X ) \
    void swap( X& other ) { doSwap( other ); }

#if defined(Q_OS_WIN) && defined(QT_DLL)
#if defined(_MSC_VER) && _MSC_VER >= 1300
// workaround http://support.microsoft.com/default.aspx?scid=kb;en-us;309801
#include <QPointF>
#include <QVector>
template class Q_DECL_IMPORT QVector<QPointF>;
#endif
#endif

/*!\namespace KGantt
 *\ingroup KGantt
 *\brief Global namespace
 */
namespace KGantt {

    /*!\enum KGantt::ItemDataRole
     *\ingroup KGantt
     * The values of this enum are used for the special data roles
     * for gantt items
     */
    enum ItemDataRole {
        KGanttRoleBase     = Qt::UserRole + 1174, ///< The base value used for the KGantt role enum values. The actual roles have values base+1, base+2, ...
        StartTimeRole       = KGanttRoleBase + 1, ///< Start time (or other start value) for a gantt item.
        EndTimeRole         = KGanttRoleBase + 2, ///< End time (or other end value) for a gantt item.
        TaskCompletionRole  = KGanttRoleBase + 3, ///< Task completion percentage used by Task items. Should be an integer og a qreal between 0 and 100.
        ItemTypeRole        = KGanttRoleBase + 4, ///< The item type. \see KGantt::ItemType.
        LegendRole          = KGanttRoleBase + 5, ///< The Legend text
        TextPositionRole    = KGanttRoleBase + 6 ///< The position of the text label on the item. The type of this value is KGantt::StyleOptionGanttItem::Position and the default values is Right.
    };

    /*!\enum KGantt::ItemType
     *\ingroup KGantt
     * The values of this enum are used to represent the different
     * types of gantt items that KGantt understands. The itemtype
     * is served through the KGantt::ItemTypeRole role
     */
    enum ItemType {
        TypeNone    = 0,
        TypeEvent   = 1,
        TypeTask    = 2,
        TypeSummary = 3,
        TypeMulti   = 4,
        TypeUser    = 1000
    };

    /*!\class KGantt::Span kganttglobal.h KGanttGlobal
     *\ingroup KGantt
     * \brief A class representing a start point and a length */
    class Span {
        qreal m_start;
        qreal m_length;
    public:
        inline Span() : m_start( -1 ), m_length( 0 ) {}
        inline Span( qreal start, qreal length ) : m_start( start ), m_length( length ) {}
        inline Span( const Span& other ) : m_start(other.m_start), m_length(other.m_length) {}

        inline Span& operator=( const Span& other ) { m_start=other.m_start; m_length=other.m_length; return *this; }

        inline void setStart( qreal start ) { m_start=start; }
        inline qreal start() const { return m_start; }
        inline void setEnd( qreal end ) { m_length = m_start-end; }
        inline qreal end() const { return m_start+m_length; }

        inline void setLength( qreal length ) { m_length=length; }
        inline qreal length() const { return m_length; }

        inline bool isValid() const { return m_start >= 0.;}

        inline bool equals( const Span& other ) const {
            return m_start == other.m_start && m_length == other.m_length;
        }
        inline Span expandedTo( const Span& other) const {
            const qreal new_start = qMin(start(),other.start());
            return Span( new_start, (end()<other.end())?other.end()-new_start:end()-new_start);
        }
    };

    inline bool operator==( const Span& s1, const Span& s2) { return s1.equals( s2 ); }
    inline bool operator!=( const Span& s1, const Span& s2) { return !s1.equals( s2 ); }


    class DateTimeSpan {
        QDateTime m_start;
        QDateTime m_end;
    public:
        DateTimeSpan();
        DateTimeSpan( const QDateTime& start, const QDateTime& end );
        DateTimeSpan( const DateTimeSpan& other );
        ~DateTimeSpan();

        DateTimeSpan& operator=( const DateTimeSpan& other );

        inline void setStart( const QDateTime& start ) { m_start=start; }
        inline QDateTime start() const { return m_start; }

        inline void setEnd( const QDateTime& end ) { m_end=end; }
        inline QDateTime end() const { return m_end; }

        bool isValid() const;

        bool equals( const DateTimeSpan& other ) const;
    };

    inline bool operator==( const DateTimeSpan& s1, const DateTimeSpan& s2) { return s1.equals( s2 ); }
    inline bool operator!=( const DateTimeSpan& s1, const DateTimeSpan& s2) { return !s1.equals( s2 ); }
}

Q_DECLARE_METATYPE(KGantt::ItemType)

#ifndef QT_NO_DEBUG_STREAM
QDebug KGANTT_EXPORT operator<<( QDebug dbg, KGantt::ItemDataRole r);
QDebug KGANTT_EXPORT operator<<( QDebug dbg, KGantt::ItemType t);
QDebug KGANTT_EXPORT operator<<( QDebug dbg, const KGantt::Span& s );
QDebug KGANTT_EXPORT operator<<( QDebug dbg, const KGantt::DateTimeSpan& s );
#endif /* QT_NO_DEBUG_STREAM */

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(KGantt::Span, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(KGantt::DateTimeSpan, Q_MOVABLE_TYPE);
QT_END_NAMESPACE

#endif /* KGANTTGLOBAL_H */
