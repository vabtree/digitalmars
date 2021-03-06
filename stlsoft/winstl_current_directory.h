/* /////////////////////////////////////////////////////////////////////////////
 * File:        winstl_current_directory.h
 *
 * Purpose:     Simple class that gets, and makes accessible, the current
 *              directory.
 *
 * Created:     10th December 2002
 * Updated:     11th September 2004
 *
 * Home:        http://stlsoft.org/
 *
 * Copyright (c) 2002-2004, Matthew Wilson and Synesis Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name(s) of Matthew Wilson and Synesis Software nor the names of
 *   any contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////////// */


/// \file winstl_current_directory.h
///
/// Simple class that gets, and makes accessible, the current directory.

#ifndef WINSTL_INCL_H_WINSTL_CURRENT_DIRECTORY
#define WINSTL_INCL_H_WINSTL_CURRENT_DIRECTORY

#ifndef __STLSOFT_DOCUMENTATION_SKIP_SECTION
# define WINSTL_VER_H_WINSTL_CURRENT_DIRECTORY_MAJOR    2
# define WINSTL_VER_H_WINSTL_CURRENT_DIRECTORY_MINOR    0
# define WINSTL_VER_H_WINSTL_CURRENT_DIRECTORY_REVISION 1
# define WINSTL_VER_H_WINSTL_CURRENT_DIRECTORY_EDIT     37
#endif /* !__STLSOFT_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////////
 * Compatibility
 */

/*
[Incompatibilies-start]
__STLSOFT_COMPILER_IS_MSVC: _MSC_VER<1200
[Incompatibilies-end]
 */

/* /////////////////////////////////////////////////////////////////////////////
 * Includes
 */

#ifndef WINSTL_INCL_H_WINSTL
# include "winstl.h"                    // Include the WinSTL root header
#endif /* !WINSTL_INCL_H_WINSTL */

#if defined(__STLSOFT_COMPILER_IS_MSVC) && \
    _MSC_VER < 1200
# error winstl_file_path_buffer.h is not compatible with Visual C++ 5.0 or earlier
#endif /* _MSC_VER < 1200 */

#ifndef WINSTL_INCL_H_WINSTL_FILESYSTEM_TRAITS
# include "winstl_filesystem_traits.h"  // filesystem_traits
#endif /* !WINSTL_INCL_H_WINSTL_FILESYSTEM_TRAITS */
#ifndef WINSTL_INCL_H_WINSTL_FILE_PATH_BUFFER
# include "winstl_file_path_buffer.h"   // basic_file_path_buffer
#endif /* !WINSTL_INCL_H_WINSTL_FILE_PATH_BUFFER */
#ifndef WINSTL_INCL_H_WINSTL_STRING_ACCESS
# include "winstl_string_access.h"                  // winstl::string_access
#endif /* WINSTL_INCL_H_WINSTL_STRING_ACCESS */

/* /////////////////////////////////////////////////////////////////////////////
 * Namespace
 */

#ifndef _WINSTL_NO_NAMESPACE
# if defined(_STLSOFT_NO_NAMESPACE) || \
     defined(__STLSOFT_DOCUMENTATION_SKIP_SECTION)
/* There is no stlsoft namespace, so must define ::winstl */
namespace winstl
{
# else
/* Define stlsoft::winstl_project */

namespace stlsoft
{

namespace winstl_project
{

# endif /* _STLSOFT_NO_NAMESPACE */
#endif /* !_WINSTL_NO_NAMESPACE */

/* ////////////////////////////////////////////////////////////////////////// */

/// \weakgroup libraries STLSoft Libraries
/// \brief The individual libraries

/// \weakgroup libraries_filesystem File-System Library
/// \ingroup libraries
/// \brief This library provides facilities for defining and manipulating file-system objects

/// \weakgroup winstl_filesystem_library File-System Library (WinSTL)
/// \ingroup WinSTL libraries_filesystem
/// \brief This library provides facilities for defining and manipulating file-system objects for the Win32 API
/// @{

/* /////////////////////////////////////////////////////////////////////////////
 * basic_current_directory
 *
 * This class wraps the GetCurrentDirectory() API function, and effectively acts
 * as a C-string of its value.
 */

/// Represents the current directory
///
/// \param C The character type
/// \param T The traits type. On translators that support default template arguments, this defaults to filesystem_traits<C>
template<   ss_typename_param_k C
#ifdef __STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_CLASS_ARGUMENT_SUPPORT
        ,   ss_typename_param_k T = filesystem_traits<C>
#else
        ,   ss_typename_param_k T /* = filesystem_traits<C> */
#endif /* __STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_CLASS_ARGUMENT_SUPPORT */
        >
class basic_current_directory
{
public:
    /// The char type
    typedef C                               char_type;
    /// The traits type
    typedef T                               traits_type;
    /// The current parameterisation of the type
    typedef basic_current_directory<C, T>   class_type;
    /// The size type
    typedef ws_size_t                       size_type;

// Construction
public:
    /// Default constructor
    basic_current_directory();

// Operations
public:
    /// Gets the current directory into the given buffer
    static size_type   get_path(ws_char_a_t *buffer, size_type cchBuffer);
    /// Gets the current directory into the given buffer
    static size_type   get_path(ws_char_w_t *buffer, size_type cchBuffer);

// Attributes
public:
    /// Returns a non-mutable (const) pointer to the path
    char_type const *get_path() const;
    /// Returns a pointer to a nul-terminated string
    char_type const *c_str() const;
    /// Returns the length of the converted path
    size_type       length() const;

// Conversions
public:
    /// Implicit conversion to a non-mutable (const) pointer to the path
    operator char_type const *() const
    {
        return get_path();
    }

// Members
private:
    basic_file_path_buffer<char_type>   m_dir;
    size_type const                     m_len;

// Not to be implemented
private:
    basic_current_directory(const class_type &);
    basic_current_directory &operator =(const class_type &);
};

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs for commonly encountered types
 */

/// Instantiation of the basic_current_directory template for the ANSI character type \c char
typedef basic_current_directory<ws_char_a_t, filesystem_traits<ws_char_a_t> >     current_directory_a;
/// Instantiation of the basic_current_directory template for the Unicode character type \c wchar_t
typedef basic_current_directory<ws_char_w_t, filesystem_traits<ws_char_w_t> >     current_directory_w;
/// Instantiation of the basic_current_directory template for the Win32 character type \c TCHAR
typedef basic_current_directory<TCHAR, filesystem_traits<TCHAR> >                 current_directory;

/* /////////////////////////////////////////////////////////////////////////////
 * Shims
 */

template<   ss_typename_param_k C
        ,   ss_typename_param_k T
        >
inline C const *c_str_ptr_null(basic_current_directory<C, T> const &b)
{
    return stlsoft_ns_qual(c_str_ptr_null)(b.c_str());
}

template<   ss_typename_param_k C
        ,   ss_typename_param_k T
        >
inline C const *c_str_ptr(basic_current_directory<C, T> const &b)
{
    return stlsoft_ns_qual(c_str_ptr)(b.c_str());
}

template<   ss_typename_param_k C
        ,   ss_typename_param_k T
        >
inline ws_size_t c_str_len(basic_current_directory<C, T> const &b)
{
    return stlsoft_ns_qual(c_str_len)(b.c_str());
}

template<   ss_typename_param_k C
        ,   ss_typename_param_k T
        >
inline ws_size_t c_str_size(basic_current_directory<C, T> const &b)
{
    return stlsoft_ns_qual(c_str_size)(b.c_str());
}

template<   ss_typename_param_k S
        ,   ss_typename_param_k C
        ,   ss_typename_param_k T
        >
inline S &operator <<(S & s, basic_current_directory<C, T> const &b)
{
    s << b.c_str();

    return s;
}

/* /////////////////////////////////////////////////////////////////////////////
 * Unit-testing
 */

#ifdef STLSOFT_UNITTEST

namespace unittest
{
    ss_bool_t test_winstl_current_directory(unittest_reporter *r)
    {
        using stlsoft::unittest::unittest_initialiser;

        ss_bool_t               bSuccess    =   true;

        unittest_initialiser    init(r, "WinSTL", "current_directory", __FILE__);

        typedef basic_current_directory<char>   curr_dir_t;

        char        sz[1 + _MAX_PATH];
        curr_dir_t  cd;

        ::GetCurrentDirectoryA(stlsoft_num_elements(sz), sz);

        if(0 != strcmp(sz, cd))
        {
            r->report("basic_current_directory<char> failed ", __LINE__);
            bSuccess = false;
        }

        return bSuccess;
    }

    unittest_registrar    unittest_winstl_current_directory(test_winstl_current_directory);

} // namespace unittest

#endif /* STLSOFT_UNITTEST */

/* /////////////////////////////////////////////////////////////////////////////
 * Implementation
 */

#ifndef __STLSOFT_DOCUMENTATION_SKIP_SECTION

template<   ss_typename_param_k C
        ,   ss_typename_param_k T
        >
inline basic_current_directory<C, T>::basic_current_directory()
    : m_len(get_path(&m_dir[0], m_dir.size()))
{}

template<   ss_typename_param_k C
        ,   ss_typename_param_k T
        >
inline /* static */ ss_typename_type_k basic_current_directory<C, T>::size_type basic_current_directory<C, T>::get_path(ws_char_a_t *buffer, ss_typename_type_k basic_current_directory<C, T>::size_type cchBuffer)
{
    return static_cast<size_type>(::GetCurrentDirectoryA(cchBuffer, buffer));
}

template<   ss_typename_param_k C
        ,   ss_typename_param_k T
        >
inline /* static */ ss_typename_type_k basic_current_directory<C, T>::size_type basic_current_directory<C, T>::get_path(ws_char_w_t *buffer, ss_typename_type_k basic_current_directory<C, T>::size_type cchBuffer)
{
    return static_cast<size_type>(::GetCurrentDirectoryW(cchBuffer, buffer));
}

template<   ss_typename_param_k C
        ,   ss_typename_param_k T
        >
inline ss_typename_type_k basic_current_directory<C, T>::char_type const *basic_current_directory<C, T>::get_path() const
{
    return stlsoft_ns_qual(c_str_ptr)(m_dir);
}

template<   ss_typename_param_k C
        ,   ss_typename_param_k T
        >
inline ss_typename_type_k basic_current_directory<C, T>::char_type const *basic_current_directory<C, T>::c_str() const
{
    return get_path();
}

template<   ss_typename_param_k C
        ,   ss_typename_param_k T
        >
inline ss_typename_type_k basic_current_directory<C, T>::size_type basic_current_directory<C, T>::length() const
{
    return m_len;
}

#endif /* !__STLSOFT_DOCUMENTATION_SKIP_SECTION */

/* ////////////////////////////////////////////////////////////////////////// */

/// @} // end of group winstl_filesystem_library

/* ////////////////////////////////////////////////////////////////////////// */

#ifndef _WINSTL_NO_NAMESPACE
# if defined(_STLSOFT_NO_NAMESPACE) || \
     defined(__STLSOFT_DOCUMENTATION_SKIP_SECTION)
} // namespace winstl
# else
} // namespace winstl_project
} // namespace stlsoft
# endif /* _STLSOFT_NO_NAMESPACE */
#endif /* !_WINSTL_NO_NAMESPACE */

/* /////////////////////////////////////////////////////////////////////////////
 * Namespace
 *
 * The string access shims exist either in the stlsoft namespace, or in the
 * global namespace. This is required by the lookup rules.
 *
 */

#ifndef _WINSTL_NO_NAMESPACE
# if !defined(_STLSOFT_NO_NAMESPACE) && \
     !defined(__STLSOFT_DOCUMENTATION_SKIP_SECTION)
namespace stlsoft
{
# else /* ? _STLSOFT_NO_NAMESPACE */
/* There is no stlsoft namespace, so must define in the global namespace */
# endif /* !_STLSOFT_NO_NAMESPACE */

using ::winstl::c_str_ptr_null;

using ::winstl::c_str_ptr;

using ::winstl::c_str_len;

using ::winstl::c_str_size;

# if !defined(_STLSOFT_NO_NAMESPACE) && \
     !defined(__STLSOFT_DOCUMENTATION_SKIP_SECTION)
} // namespace stlsoft
# else /* ? _STLSOFT_NO_NAMESPACE */
/* There is no stlsoft namespace, so must define in the global namespace */
# endif /* !_STLSOFT_NO_NAMESPACE */
#endif /* !_WINSTL_NO_NAMESPACE */

/* ////////////////////////////////////////////////////////////////////////// */

#endif /* WINSTL_INCL_H_WINSTL_CURRENT_DIRECTORY */

/* ////////////////////////////////////////////////////////////////////////// */
