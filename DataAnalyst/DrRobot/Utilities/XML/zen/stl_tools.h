// **************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under *
// * GNU General Public License: http://www.gnu.org/licenses/gpl.html       *
// * Copyright (C) Zenju (zenju AT gmx DOT de) - All Rights Reserved        *
// **************************************************************************

#ifndef STL_TOOLS_HEADER_84567184321434
#define STL_TOOLS_HEADER_84567184321434

#include <memory>
#include <algorithm>
#if defined _MSC_VER && _MSC_VER <= 1600
#include <set>
#include <map>
#else
#include <unordered_set>
#include <unordered_map>
#endif


//enhancements for <algorithm>
namespace zen
{
//idomatic remove selected elements from container
template <class V, class Predicate>
void vector_remove_if(V& vec, Predicate p);

template <class V, class W>
void vector_append(V& vec, W& vec2);

template <class S, class Predicate>
void set_remove_if(S& set, Predicate p);

template <class M, class Predicate>
void map_remove_if(M& map, Predicate p);

template <class M, class K, class V>
V& map_add_or_update(M& map, const K& key, const V& value); //efficient add or update without "default-constructible" requirement (Effective STL, item 24)

//binary search returning an iterator
template <class ForwardIterator, class T, typename Compare>
ForwardIterator binary_search(ForwardIterator first, ForwardIterator last, const T& value, Compare comp);

template <class BidirectionalIterator, class T>
BidirectionalIterator find_last(BidirectionalIterator first, BidirectionalIterator last, const T& value);

//replacement for std::find_end taking advantage of bidirectional iterators (and giving the algorithm a reasonable name)
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator1 search_last(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
                                   BidirectionalIterator2 first2, BidirectionalIterator2 last2);

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1,
           InputIterator2 first2, InputIterator2 last2);

//hash container: proper name + mitigate MSVC performance bug
template <class T> class hash_set;
template <class K, class V> class hash_map;

template<typename T, typename Arg1>
std::unique_ptr<T> make_unique(Arg1&& arg1); //should eventually make it into the std at some time























//######################## implementation ########################

template <class V, class Predicate> inline
void vector_remove_if(V& vec, Predicate p)
{
    vec.erase(std::remove_if(vec.begin(), vec.end(), p), vec.end());
}


template <class V, class W> inline
void vector_append(V& vec, W& vec2)
{
    vec.insert(vec.end(), vec2.begin(), vec2.end());
}


template <class S, class Predicate> inline
void set_remove_if(S& set, Predicate p)
{
    for (auto iter = set.begin(); iter != set.end();)
        if (p(*iter))
            set.erase(iter++);
        else
            ++iter;
}


template <class M, class Predicate> inline
void map_remove_if(M& map, Predicate p) { set_remove_if(map, p); }


template <class M, class K, class V> inline
V& map_add_or_update(M& map, const K& key, const V& value) //efficient add or update without "default-constructible" requirement (Effective STL, item 24)
{
    auto iter = map.lower_bound(key);
    if (iter != map.end() && !(map.key_comp()(key, iter->first)))
    {
        iter->second = value;
        return iter->second;
    }
    else
        return map.insert(iter, typename M::value_type(key, value))->second;
}


template <class ForwardIterator, class T, typename Compare> inline
ForwardIterator binary_search(ForwardIterator first, ForwardIterator last, const T& value, Compare comp)
{
    first = std::lower_bound(first, last, value, comp);
    if (first != last && !comp(value, *first))
        return first;
    else
        return last;
}


template <class BidirectionalIterator, class T> inline
BidirectionalIterator find_last(const BidirectionalIterator first, const BidirectionalIterator last, const T& value)
{
    for (BidirectionalIterator iter = last; iter != first;) //reverse iteration: 1. check 2. decrement 3. evaluate
    {
        --iter; //

        if (*iter == value)
            return iter;
    }
    return last;
}


template <class BidirectionalIterator1, class BidirectionalIterator2> inline
BidirectionalIterator1 search_last(const BidirectionalIterator1 first1,       BidirectionalIterator1 last1,
                                   const BidirectionalIterator2 first2, const BidirectionalIterator2 last2)
{
    const BidirectionalIterator1 iterNotFound = last1;

    //reverse iteration: 1. check 2. decrement 3. evaluate
    for (;;)
    {
        BidirectionalIterator1 it1 = last1;
        BidirectionalIterator2 it2 = last2;

        for (;;)
        {
            if (it2 == first2) return it1;
            if (it1 == first1) return iterNotFound;

            --it1;
            --it2;

            if (*it1 != *it2) break;
        }
        --last1;
    }
}


template <class InputIterator1, class InputIterator2> inline
bool equal(InputIterator1 first1, InputIterator1 last1,
           InputIterator2 first2, InputIterator2 last2)
{
    return last1 - first1 == last2 - first2 && std::equal(first1, last1, first2);
}


#if defined _MSC_VER && _MSC_VER <= 1600 //VS2010 performance bug in std::unordered_set<>: http://drdobbs.com/blogs/cpp/232200410 -> should be fixed in VS11
template <class T>          class hash_set : public std::set<T> {};
template <class K, class V> class hash_map : public std::map<K, V> {};
#else
template <class T>          class hash_set : public std::unordered_set<T> {};
template <class K, class V> class hash_map : public std::unordered_map<K, V> {};
//C++11:
//template <class T>          using hash_set = std::unordered_set<T>;
//template <class K, class V> using hash_map = std::unordered_map<K, V>;
#endif

//as long as variadic templates are not available in MSVC
template<class T>																	      inline std::unique_ptr<T> make_unique()																		      { return std::unique_ptr<T>(new T); }
template<class T, class Arg1>														      inline std::unique_ptr<T> make_unique(Arg1&& arg1)															      { return std::unique_ptr<T>(new T(std::forward<Arg1>(arg1))); }
template<class T, class Arg1, class Arg2>											      inline std::unique_ptr<T> make_unique(Arg1&& arg1, Arg2&& arg2)												      { return std::unique_ptr<T>(new T(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2))); }
template<class T, class Arg1, class Arg2, class Arg3>								      inline std::unique_ptr<T> make_unique(Arg1&& arg1, Arg2&& arg2, Arg3&& arg3)										  { return std::unique_ptr<T>(new T(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2), std::forward<Arg3>(arg3))); }
template<class T, class Arg1, class Arg2, class Arg3, class Arg4>						  inline std::unique_ptr<T> make_unique(Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4)							  { return std::unique_ptr<T>(new T(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2), std::forward<Arg3>(arg3), std::forward<Arg4>(arg4))); }
template<class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>			  inline std::unique_ptr<T> make_unique(Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4, Arg5&& arg5)              { return std::unique_ptr<T>(new T(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2), std::forward<Arg3>(arg3), std::forward<Arg4>(arg4), std::forward<Arg5>(arg5))); }
template<class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6> inline std::unique_ptr<T> make_unique(Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4, Arg5&& arg5, Arg6&& arg6) { return std::unique_ptr<T>(new T(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2), std::forward<Arg3>(arg3), std::forward<Arg4>(arg4), std::forward<Arg5>(arg5), std::forward<Arg6>(arg6))); }
template<class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7> inline std::unique_ptr<T> make_unique(Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4, Arg5&& arg5, Arg6&& arg6, Arg7&& arg7) { return std::unique_ptr<T>(new T(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2), std::forward<Arg3>(arg3), std::forward<Arg4>(arg4), std::forward<Arg5>(arg5), std::forward<Arg6>(arg6), std::forward<Arg7>(arg7))); }

//template<typename T, typename ...Args> inline
//std::unique_ptr<T> make_unique(Args&& ...args)
//{
//    return std::unique_ptr<T>(new T( std::forward<Args>(args)... ));
//}
}

#endif //STL_TOOLS_HEADER_84567184321434
