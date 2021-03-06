/* /////////////////////////////////////////////////////////////////////////////
 * File:        stlsoft_true_typedef.h
 *
 * Purpose:     Contains the auto_destructor and auto_array_destructor template
 *              classes.
 *
 * Created:     16th January 2002
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


/// \file stlsoft_true_typedef.h
///
/// Contains the auto_destructor and auto_array_destructor template classes.

#ifndef STLSOFT_INCL_H_STLSOFT_TRUE_TYPEDEF
#define STLSOFT_INCL_H_STLSOFT_TRUE_TYPEDEF

#ifndef __STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_H_STLSOFT_TRUE_TYPEDEF_MAJOR       2
# define STLSOFT_VER_H_STLSOFT_TRUE_TYPEDEF_MINOR       0
# define STLSOFT_VER_H_STLSOFT_TRUE_TYPEDEF_REVISION    1
# define STLSOFT_VER_H_STLSOFT_TRUE_TYPEDEF_EDIT        51
#endif /* !__STLSOFT_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////////
 * Includes
 */

#ifndef STLSOFT_INCL_H_STLSOFT
# include "stlsoft.h"   // Include the STLSoft root header
#endif /* !STLSOFT_INCL_H_STLSOFT */

/* /////////////////////////////////////////////////////////////////////////////
 * Namespace
 */

#ifndef _STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* _STLSOFT_NO_NAMESPACE */

/* /////////////////////////////////////////////////////////////////////////////
 * Classes
 */

/* U is the unique type, and is usually a type generated by the
 * stlsoft_gen_opaque() macro, as in
 *
 *  stlsoft_gen_opaque(h_uniquelong_tt)
 *  typedef true_typedef<long, h_uniquelong_tt>     uniquelong_tt;
 *
 * thus generating a unique type uniquelong over base-type long.
 */

/// This class is used to create strong types from base types, to facilitate
/// type disambiguation, overloading and mutual incompatibility.
///
/// For example, the following code creates two types based on the \c int type:
///
/// &nbsp;&nbsp;<code>stlsoft_gen_opaque(h_protocol_tt)</code><br>
/// &nbsp;&nbsp;<code>stlsoft_gen_opaque(h_port_tt)</code><br>
/// &nbsp;&nbsp;<code>typedef true_typedef<long, h_protocol_tt>  protocol_tt;</code><br>
/// &nbsp;&nbsp;<code>typedef true_typedef<long, h_port_tt>      port_tt;</code><br>
/// <br>
/// &nbsp;&nbsp;<code>protocol_tt pro1(3);    // Ok</code><br>
/// &nbsp;&nbsp;<code>port_tt     prt1(8088); // Ok</code><br>
/// &nbsp;&nbsp;<code>protocol_tt pro2(pro1); // Ok, can copy from another protocol_tt</code><br>
/// &nbsp;&nbsp;<code>port_tt     prt2(pro2); // Error, cannot copy from a protocol_tt</code><br>
///
///
/// \param T The base type, e.g. \c int, \c std::wstring
/// \param U The unique type, usually created by using stlsoft_gen_opaque()

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
class true_typedef
{
public:
    /// The value type
    typedef T                   value_type;
    /// The unique type
    typedef U                   unique_type;
    /// The type of the current parameterisation
    typedef true_typedef<T, U>  class_type;
    /// The reference type
    typedef T                   &reference;
    /// The non-mutating (const) reference type
    typedef T const             &const_reference;

// Construction
public:
    /// Default constructor
    true_typedef()
        : m_value(value_type())
    {}
    /// Construct from a value type instance
    ss_explicit_k true_typedef(value_type const &value)
        : m_value(value)
    {}
    /// Copy constructor
    true_typedef(class_type const &rhs)
        : m_value(rhs.m_value)
    {}

    /// Copy assignment operator
    class_type const &operator =(class_type const &rhs)
    {
        m_value = rhs.m_value;

        return *this;
    }

// Accessors
public:
    /// Provides non-mutating (const) access to the base type value
    const_reference base_type_value() const
    {
        return m_value;
    }
    /// Provides mutating access to the base type value
    reference base_type_value()
    {
        return m_value;
    }

// Members
private:
    value_type  m_value;

// Not to be implemented
private:
    // Not provided, as the syntax is less ambiguous when
    // assignment from an explicit temporary is made
    class_type const &operator =(value_type const &value);
};

/* /////////////////////////////////////////////////////////////////////////////
 * Unit-testing
 */

#ifdef STLSOFT_UNITTEST

namespace unittest
{
    ss_bool_t test_stlsoft_true_typedef(unittest_reporter *r)
    {
        ss_bool_t               bSuccess    =   true;

        unittest_initialiser    init(r, "STLSoft", "true_typedef", __FILE__);

#if 0
        if(<<TODO>>)
        {
            r->report("<<TODO>> failed ", __LINE__);
            bSuccess = false;
        }
#endif /* 0 */

        return bSuccess;
    }

    unittest_registrar    unittest_stlsoft_true_typedef(test_stlsoft_true_typedef);

} // namespace unittest

#endif /* STLSOFT_UNITTEST */

/* /////////////////////////////////////////////////////////////////////////////
 * Implementation
 */

#ifndef __STLSOFT_DOCUMENTATION_SKIP_SECTION

// Pre-increment

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> &operator ++(true_typedef<T, U> &v)
{
    ++v.base_type_value();

    return v;
}

// Post-increment

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> const operator ++(true_typedef<T, U> &v, int)
{
    true_typedef<T, U>  r(v);

    v.base_type_value()++;

    return r;
}

// Pre-decrement

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> &operator --(true_typedef<T, U> &v)
{
    --v.base_type_value();

    return v;
}

// Post-decrement

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> const operator --(true_typedef<T, U> &v, int)
{
    true_typedef<T, U>  r(v);

    v.base_type_value()--;

    return r;
}

// operator ==

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline ss_bool_t operator ==(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return lhs.base_type_value() == rhs.base_type_value();
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline ss_bool_t operator ==(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline ss_bool_t operator ==(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs.base_type_value() == rhs;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline ss_bool_t operator ==(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline ss_bool_t operator ==(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs == rhs.base_type_value();
}


// operator !=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline ss_bool_t operator !=(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return ! operator ==(lhs, rhs);
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline ss_bool_t operator !=(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline ss_bool_t operator !=(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return ! operator ==(lhs, rhs);
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline ss_bool_t operator !=(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline ss_bool_t operator !=(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return ! operator ==(lhs, rhs);
}

// operator <

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline ss_bool_t operator <(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return lhs.base_type_value() < rhs.base_type_value();
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline ss_bool_t operator <(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline ss_bool_t operator <(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs.base_type_value() < rhs;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline ss_bool_t operator <(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline ss_bool_t operator <(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs < rhs.base_type_value();
}

// operator <=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline ss_bool_t operator <=(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return lhs.base_type_value() <= rhs.base_type_value();
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline ss_bool_t operator <=(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline ss_bool_t operator <=(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs.base_type_value() <= rhs;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline ss_bool_t operator <=(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline ss_bool_t operator <=(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs <= rhs.base_type_value();
}

// operator >

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline ss_bool_t operator >(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return lhs.base_type_value() > rhs.base_type_value();
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline ss_bool_t operator >(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline ss_bool_t operator >(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs.base_type_value() > rhs;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline ss_bool_t operator >(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline ss_bool_t operator >(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs > rhs.base_type_value();
}

// operator >=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline ss_bool_t operator >=(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return lhs.base_type_value() >= rhs.base_type_value();
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline ss_bool_t operator >=(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline ss_bool_t operator >=(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs.base_type_value() >= rhs;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline ss_bool_t operator >=(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline ss_bool_t operator >=(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs >= rhs.base_type_value();
}

// operator +

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> operator +(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return true_typedef<T, U>(lhs.base_type_value() + rhs.base_type_value());
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator +(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> operator +(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs.base_type_value() + rhs);
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator +(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline true_typedef<T, U> operator +(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs + rhs.base_type_value());
}

// operator -

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> operator -(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return true_typedef<T, U>(lhs.base_type_value() - rhs.base_type_value());
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator -(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> operator -(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs.base_type_value() - rhs);
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator -(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline true_typedef<T, U> operator -(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs - rhs.base_type_value());
}

// operator *

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> operator *(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return true_typedef<T, U>(lhs.base_type_value() * rhs.base_type_value());
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator *(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> operator *(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs.base_type_value() * rhs);
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator *(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline true_typedef<T, U> operator *(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs * rhs.base_type_value());
}

// operator /

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> operator /(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return true_typedef<T, U>(lhs.base_type_value() / rhs.base_type_value());
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator /(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> operator /(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs.base_type_value() / rhs);
}


template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator /(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline true_typedef<T, U> operator /(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs / rhs.base_type_value());
}

// operator %

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> operator %(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return true_typedef<T, U>(lhs.base_type_value() % rhs.base_type_value());
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator %(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> operator %(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs.base_type_value() % rhs);
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator %(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline true_typedef<T, U> operator %(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs % rhs.base_type_value());
}

// operator ^

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> operator ^(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return true_typedef<T, U>(lhs.base_type_value() ^ rhs.base_type_value());
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator ^(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> operator ^(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs.base_type_value() ^ rhs);
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator ^(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline true_typedef<T, U> operator ^(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs ^ rhs.base_type_value());
}

// operator ~

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> operator ~(true_typedef<T, U> const &v)
{
    return true_typedef<T, U>(~v.base_type_value());
}

// operator <<

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> operator <<(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return true_typedef<T, U>(lhs.base_type_value() << rhs.base_type_value());
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator <<(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> operator <<(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs.base_type_value() << rhs);
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator <<(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline true_typedef<T, U> operator <<(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs << rhs.base_type_value());
}

// operator >>

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> operator >>(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return true_typedef<T, U>(lhs.base_type_value() >> rhs.base_type_value());
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator >>(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> operator >>(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs.base_type_value() >> rhs);
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator >>(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline true_typedef<T, U> operator >>(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs >> rhs.base_type_value());
}

// operator &

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> operator &(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return true_typedef<T, U>(lhs.base_type_value() & rhs.base_type_value());
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator &(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> operator &(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs.base_type_value() & rhs);
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator &(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline true_typedef<T, U> operator &(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs & rhs.base_type_value());
}

// operator |

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> operator |(true_typedef<T, U> const &lhs, true_typedef<T, U> const &rhs)
{
    return true_typedef<T, U>(lhs.base_type_value() | rhs.base_type_value());
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator |(true_typedef<T, U> const &lhs, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> operator |(true_typedef<T, U> const &lhs, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs.base_type_value() | rhs);
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> operator |(ss_typename_type_k true_typedef<T, U>::value_type const &lhs, true_typedef<T, U> const &rhs)
#else
inline true_typedef<T, U> operator |(T const &lhs, true_typedef<T, U> const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return true_typedef<T, U>(lhs | rhs.base_type_value());
}

// operator +=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> const &operator +=(true_typedef<T, U> &v, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> const &operator +=(true_typedef<T, U> &v, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    v.base_type_value() += rhs;

    return v;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> const &operator +=(true_typedef<T, U> &v, true_typedef<T, U> const &rhs)
{
    v.base_type_value() += rhs.base_type_value();

    return v;
}

// operator -=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> const &operator -=(true_typedef<T, U> &v, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> const &operator -=(true_typedef<T, U> &v, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    v.base_type_value() -= rhs;

    return v;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> const &operator -=(true_typedef<T, U> &v, true_typedef<T, U> const &rhs)
{
    v.base_type_value() -= rhs.base_type_value();

    return v;
}

// operator *=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> const &operator *=(true_typedef<T, U> &v, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> const &operator *=(true_typedef<T, U> &v, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    v.base_type_value() *= rhs;

    return v;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> const &operator *=(true_typedef<T, U> &v, true_typedef<T, U> const &rhs)
{
    v.base_type_value() *= rhs.base_type_value();

    return v;
}

// operator /=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> const &operator /=(true_typedef<T, U> &v, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> const &operator /=(true_typedef<T, U> &v, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    v.base_type_value() /= rhs;

    return v;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> const &operator /=(true_typedef<T, U> &v, true_typedef<T, U> const &rhs)
{
    v.base_type_value() /= rhs.base_type_value();

    return v;
}

// operator %=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> const &operator %=(true_typedef<T, U> &v, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> const &operator %=(true_typedef<T, U> &v, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    v.base_type_value() %= rhs;

    return v;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> const &operator %=(true_typedef<T, U> &v, true_typedef<T, U> const &rhs)
{
    v.base_type_value() %= rhs.base_type_value();

    return v;
}

// operator ^=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> const &operator ^=(true_typedef<T, U> &v, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> const &operator ^=(true_typedef<T, U> &v, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    v.base_type_value() ^= rhs;

    return v;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> const &operator ^=(true_typedef<T, U> &v, true_typedef<T, U> const &rhs)
{
    v.base_type_value() ^= rhs.base_type_value();

    return v;
}

// operator <<=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> const &operator <<=(true_typedef<T, U> &v, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> const &operator <<=(true_typedef<T, U> &v, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    v.base_type_value() <<= rhs;

    return v;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> const &operator <<=(true_typedef<T, U> &v, true_typedef<T, U> const &rhs)
{
    v.base_type_value() <<= rhs.base_type_value();

    return v;
}

// operator >>=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> const &operator >>=(true_typedef<T, U> &v, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> const &operator >>=(true_typedef<T, U> &v, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    v.base_type_value() >>= rhs;

    return v;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> const &operator >>=(true_typedef<T, U> &v, true_typedef<T, U> const &rhs)
{
    v.base_type_value() >>= rhs.base_type_value();

    return v;
}

// operator &=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> const &operator &=(true_typedef<T, U> &v, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> const &operator &=(true_typedef<T, U> &v, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    v.base_type_value() &= rhs;

    return v;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> const &operator &=(true_typedef<T, U> &v, true_typedef<T, U> const &rhs)
{
    v.base_type_value() &= rhs.base_type_value();

    return v;
}

// operator |=

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
#ifdef __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
inline true_typedef<T, U> const &operator |=(true_typedef<T, U> &v, ss_typename_type_k true_typedef<T, U>::value_type const &rhs)
#else
inline true_typedef<T, U> const &operator |=(true_typedef<T, U> &v, T const &rhs)
#endif /* __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    v.base_type_value() |= rhs;

    return v;
}

template<   ss_typename_param_k T
        ,   ss_typename_param_k U>
inline true_typedef<T, U> const &operator |=(true_typedef<T, U> &v, true_typedef<T, U> const &rhs)
{
    v.base_type_value() |= rhs.base_type_value();

    return v;
}

#endif /* !__STLSOFT_DOCUMENTATION_SKIP_SECTION */

/* ////////////////////////////////////////////////////////////////////////// */

#ifndef _STLSOFT_NO_NAMESPACE
} // namespace stlsoft
#endif /* _STLSOFT_NO_NAMESPACE */

/* ////////////////////////////////////////////////////////////////////////// */

#endif /* !STLSOFT_INCL_H_STLSOFT_TRUE_TYPEDEF */

/* ////////////////////////////////////////////////////////////////////////// */
