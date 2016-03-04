// **************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under *
// * GNU General Public License: http://www.gnu.org/licenses/gpl.html       *
// * Copyright (C) Zenju (zenju AT gmx DOT de) - All Rights Reserved        *
// **************************************************************************

#include <set>
#include <map>
#include <deque>
#include <vector>
#include <list>
#include <utility>
#include "xml.h"

using namespace zen;

namespace
{
void unit_test()
{
    class Dummy {};

    //compile time checks only

    assert_static(!IsStlContainer<wchar_t>                     ::value);
    assert_static(!IsStlContainer<char>                        ::value);
    assert_static(!IsStlContainer<Dummy>                       ::value);
    assert_static(!IsStlContainer<NullType>                    ::value);
    assert_static(IsStlContainer<std::set      <int>>          ::value);
    assert_static(IsStlContainer<std::deque    <float>>        ::value);
    assert_static(IsStlContainer<std::list     <size_t>>       ::value);
    assert_static((IsStlContainer<std::map     <double, char>> ::value));
    assert_static((IsStlContainer<std::multimap<short, double>>::value));
    assert_static(IsStlContainer <std::vector  <wchar_t>>      ::value);
    assert_static((IsStlPair     <std::pair<int, double>>      ::value));
    assert_static(!IsStlPair<Dummy>                            ::value);

    assert_static(!IsStringLike<Dummy>::value);
    assert_static(!IsStringLike<int>::value);
    assert_static(!IsStringLike<double>::value);
    assert_static(!IsStringLike<short>::value);
    assert_static(IsStringLike<char>::value);
    assert_static(IsStringLike<const wchar_t>::value);
    assert_static(IsStringLike<const char>::value);
    assert_static(IsStringLike<wchar_t>::value);
    assert_static(IsStringLike<char*>::value);
    assert_static(IsStringLike<wchar_t*>::value);
    assert_static(IsStringLike<char* const>::value);
    assert_static(IsStringLike<wchar_t* const>::value);
    assert_static(IsStringLike<const char*>::value);
    assert_static(IsStringLike<const char* const>::value);
    assert_static(IsStringLike<const wchar_t*>::value);
    assert_static(IsStringLike<const wchar_t* const>::value);
    assert_static(IsStringLike<const char[4]>::value);
    assert_static(IsStringLike<const wchar_t[4]>::value);
    assert_static(IsStringLike<char[4]>::value);
    assert_static(IsStringLike<wchar_t[4]>::value);
    assert_static(IsStringLike<std::string>::value);
    assert_static(IsStringLike<std::wstring>::value);
    assert_static(IsStringLike<const std::string>::value);
    assert_static(IsStringLike<const std::wstring>::value);
    assert_static(IsStringLike<const std::string&>::value);
    assert_static(IsStringLike<const std::wstring&>::value);
    assert_static(IsStringLike<std::string&>::value);
    assert_static(IsStringLike<std::wstring&>::value);

    assert_static(!(IsSameType<GetCharType<int>::Type, char>::value));
    assert_static(!(IsSameType<GetCharType<double>::Type, char>::value));
    assert_static(!(IsSameType<GetCharType<short>::Type, char>::value));
    assert_static((IsSameType<GetCharType<char>::Type, char>::value));
    assert_static((IsSameType<GetCharType<wchar_t>::Type, wchar_t>::value));
    assert_static((IsSameType<GetCharType<const char>::Type, char>::value));
    assert_static((IsSameType<GetCharType<const wchar_t>::Type, wchar_t>::value));
    assert_static((IsSameType<GetCharType<char*>::Type, char>::value));
    assert_static((IsSameType<GetCharType<wchar_t*>::Type, wchar_t>::value));
    assert_static((IsSameType<GetCharType<char* const>::Type, char>::value));
    assert_static((IsSameType<GetCharType<wchar_t* const>::Type, wchar_t>::value));
    assert_static((IsSameType<GetCharType<const char*>::Type, char>::value));
    assert_static((IsSameType<GetCharType<const char* const>::Type, char>::value));
    assert_static((IsSameType<GetCharType<const wchar_t*>::Type, wchar_t>::value));
    assert_static((IsSameType<GetCharType<const wchar_t* const>::Type, wchar_t>::value));
    assert_static((IsSameType<GetCharType<const char[4]>::Type, char>::value));
    assert_static((IsSameType<GetCharType<const wchar_t[4]>::Type, wchar_t>::value));
    assert_static((IsSameType<GetCharType<char[4]>::Type, char>::value));
    assert_static((IsSameType<GetCharType<wchar_t[4]>::Type, wchar_t>::value));
    assert_static((IsSameType<GetCharType<std::string>::Type, char>::value));
    assert_static((IsSameType<GetCharType<std::wstring>::Type, wchar_t>::value));
    assert_static((IsSameType<GetCharType<const std::string>::Type, char>::value));
    assert_static((IsSameType<GetCharType<const std::wstring>::Type, wchar_t>::value));
    assert_static((IsSameType<GetCharType<const std::string&>::Type, char>::value));
    assert_static((IsSameType<GetCharType<const std::wstring&>::Type, wchar_t>::value));
    assert_static((IsSameType<GetCharType<std::string&>::Type, char>::value));
    assert_static((IsSameType<GetCharType<std::wstring&>::Type, wchar_t>::value));
}
}
