#pragma once

#ifndef _NEWCORE_AOC_H
#define _NEWCORE_AOC_H

// standard library imports
#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <csignal>
#include <cstdint>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <regex>

#include <ios>
#include <type_traits>

// md5 import
#include "tools/md5.h"

namespace aoc {

namespace __detail {
/// @brief Implementation for split. Splits a string by a delimeter, optionally skipping empty strings.
/// @param __s The string to be split.
/// @param __d The delimeter to split the string by. Defaults to a single space.
/// @param __sk Determines if empty strings should be skipped. Defaults to true.
/// @return A vector containing substrings of the original string, split by the delimeter.
std::vector<std::string> __spl_imp(const std::string &__s, const std::string &__d = " ", bool __sk = true);

/// @brief Implementation for split in the unzip function. Splits a string into a pair of two strings given a delimeter, optionally skipping empty strings.
/// @param __s The string to be split.
/// @param __d The delimeter to split the string by. Defaults to a single space.
/// @param __sk Determines if empty strings should be skipped. Defaults to true.
/// @return A pair containing the two substrings produced through splitting.
std::pair<std::string, std::string> __unzipper(const std::string &__s, const std::string &__d = " ", bool __sk = true);
} // __detail

/// @class vector
/// @brief An extension of std::vector
///
/// This class is built to provide extra functionality directly in the vector class itself.
///
/// @tparam _T The vector type (e.g., int)
template <typename _T>
class vector : public std::vector<_T> {
public:
    using std::vector<_T>::vector;

    vector(const std::vector<_T> &__o) : std::vector<_T>(__o) {}

    /// @brief Pops the end of the vector.
    /// @return The value popped off the end.
    _T pop() {
        _T __v = this->back();
        this->pop_back();
        return __v;
    }

    // @brief Checks if the vector contains a value.
    // @param __t The value to check for.
    // @return Whether the vector contains the value or not.
    bool has(_T __t) const {
        return std::find(this->begin(), this->end(), __t) != this->end();
    }

    /// @brief Gets the index of an element in the vector.
    /// @param __t The value to look for.
    /// @param __s The offset index from the start of the vector.
    /// @return The index of the element in the vector. If it is not found, -1 is returned.
    int indexOf(_T __t, size_t __s = 0) const {
        auto __it = std::find(this->begin() + __s, this->end(), __t);
        if (__it != this->end()) {
            return std::distance(this->begin(), __it);
        } else {
            return -1;
        }
    }

    /// @brief Gets a slice of the vector given two indexes and a stride.
    /// @param __b The starting index in the vector. Defaults to the start of the vector.
    /// @param __e The ending index in the vector. Defaults to the end of the vector.
    /// @param __s The stride. Defaults to 1.
    /// @return A slice of the vector.
    vector<_T> sub(size_t __b = 0, size_t __e = static_cast<size_t>(-1), size_t __s = 1) const {
        vector<_T> __cl;
        if (__e <= __b) return __cl;
        if (__e > this->size()) __e = this->size();

        for (size_t __i = __b; __i < __e; __i += __s) {
            __cl.push_back(this->at(__i));
        }

        return __cl;
    }

    /// @brief Gets the intersection with another vector.
    /// @param __o The other vector to intersect with.
    /// @return The intersection of the two vectors.
    vector<_T> set_intersect(const vector<_T> &__o) const {
        std::unordered_set<_T> __s1(this->begin(), this->end()),
                               __s2(__o.begin(), __o.end());

        vector<_T> __i;
        for (const _T &__x : __s1) {
            if (__s2.find(__x) != __s2.end()) {
                __i.push_back(__x);
            }
        }

        return __i;
    }

    /// @brief Gets the union with another vector.
    /// @param __o The other vector to union with.
    /// @return The union of the two vectors.
    vector<_T> set_union(const vector<_T> &__o) const {
        std::unordered_set<_T> __s1(this->begin(), this->end()),
                               __s2(__o.begin(), __o.end());

        for (const _T &__x : __s2) {
            __s1.insert(__x);
        }

        return vector<_T>(__s1.begin(), __s1.end());
    }

    /// @brief Overload of set_intersection for operator&. Gets the intersection with another vector.
    /// @param __o The other vector to intersect with.
    /// @return The intersection of the two vectors.
    vector<_T> operator&(const vector<_T> &__o) const {
        return set_intersect(__o);
    }

    /// @brief Overload of set_union for operator|. Gets the union with another vector.
    /// @param __o The other vector to union with.
    /// @return The union of the two vectors.
    vector<_T> operator|(const vector<_T> &__o) const {
        return set_union(__o);
    }

    vector<_T> operator+(const vector<_T> &__o) const {
        vector<_T> __r;
        __r.reserve(this->size() + __o.size());
        __r.insert(__r.end(), this->begin(), this->end());
        __r.insert(__r.end(), __o.begin(), __o.end());
        return __r;
    }

    template <typename _Ts>
    static vector<_T> from(const std::vector<_Ts> &__v) {
        vector<_T> __r{};
        __r.reserve(__v.capacity());
        for (const auto &__x : __v) {
            __r.emplace_back(__x);
        }

        return __r;
    }
};

/// @class basic_string
/// @brief An extension of std::basic_string
///
/// This class is built to provide extra functionality directly in the string class itself.
///
/// @tparam _C The character type (e.g., char or wchar_t).
template<typename _C>
class basic_string : public std::basic_string<_C> {
public:
    // inherit constructors
    using std::basic_string<_C>::basic_string;

    basic_string(const std::basic_string<_C> &__o) : std::basic_string<_C>(__o) {}

    /// @brief Splits a string by a delimeter, optionally skipping empty strings.
    /// @param __d The delimeter to split the string by. Defaults to a single space.
    /// @param __sk Determines if empty strings should be skipped. Defaults to true.
    /// @return A vector containing substrings of the original string, split by the delimeter.
    vector<basic_string<_C>> split(const basic_string<_C> &__d = " ", bool __sk = true) const {
        vector<basic_string<_C>> __r {};
        size_t __b = 0;
        size_t __e = this->find(__d);

        while (__e != basic_string<_C>::npos) {
            basic_string<_C> __tok = this->substr(__b, __e - __b);
            if (!__tok.empty() || !__sk) {
                __r.push_back(__tok);
            }

            __b = __e + __d.size();
            __e = this->find(__d, __b);
        }

        basic_string<_C> __tok = this->substr(__b);
        if (!__tok.empty() || !__sk) {
            __r.push_back(__tok);
        }

        return __r;
    }

    /// @brief Reverses the order of the string
    void reverse() {
        std::reverse(this->begin(), this->end());
    }

    /// @brief Trims the left side of the string
    /// @param __d The string of characters to check for when trimming. Defaults to standard whitespace characters.
    void ltrim(const std::basic_string<_C> &__d = " \t\n\r\f\v") {
        this->erase(0, this->find_first_not_of(__d));
    }

    /// @brief Trims the right side of the string
    /// @param __d The string of characters to check for when trimming. Defaults to standard whitespace characters.
    void rtrim(const std::basic_string<_C> &__d = " \t\n\r\f\v") {
        this->erase(this->find_last_not_of(__d) + 1);
    }

    /// @brief Trims both sides of the string
    /// @param __d The string of characters to check for when trimming. Defaults to standard whitespace characters.
    void trim(const std::basic_string<_C> &__d = " \t\n\r\f\v") {
        this->ltrim(__d);
        this->rtrim(__d);
    }

    operator std::string() const {
        return std::string(this->c_str());
    }
};

// alias for convenience
using string = basic_string<char>;

namespace string_literals {
inline string operator""_s(const char *str, size_t) {
    return string(str);
}
} // namespace string_literals

/// @class deque
/// @brief An extension of std::deque
///
/// This class is built to provide extra functionality directly in the deque class itself.
///
/// @tparam _T The vector type (e.g., int)
template <typename _T>
class deque : public std::deque<_T> {
public:
    /// @brief Pops the end of the deque.
    /// @return The value popped off the end.
    _T pop() {
        _T __v = this->back();
        this->pop_back();
        return __v;
    }

    /// @brief Shifts the front of the deque.
    /// @return The value shifted off the front.
    _T shift() {
        _T __v = this->front();
        this->pop_front();
        return __v;
    }
};

namespace __detail {
/// @brief Implementation for split. Splits a string by a delimeter, optionally skipping empty strings.
/// @param __s The string to be split.
/// @param __d The delimeter to split the string by. Defaults to a single space.
/// @param __sk Determines if empty strings should be skipped. Defaults to true.
/// @return A vector containing substrings of the original string, split by the delimeter.
std::vector<std::string> __spl_imp(const std::string &__s, const std::string &__d, bool __sk) {
    std::vector<std::string> __r {};
    size_t __b = 0;
    size_t __e = __s.find(__d);

    while (__e != std::string::npos) {
        std::string __tok = __s.substr(__b, __e - __b);
        if (!__tok.empty() || !__sk) {
            __r.push_back(__tok);
        }

        __b = __e + __d.size();
        __e = __s.find(__d, __b);
    }

    std::string __tok = __s.substr(__b);
    if (!__tok.empty() || !__sk) {
        __r.push_back(__tok);
    }

    return __r;
}

/// @brief Implementation for split. Splits a string by a delimeter, optionally skipping empty strings.
/// @param __s The string to be split.
/// @param __d The delimeter to split the string by. Defaults to a single space.
/// @param __sk Determines if empty strings should be skipped. Defaults to true.
/// @return A vector containing substrings of the original string, split by the delimeter.
vector<string> __spl_imp(const string &__s, const string &__d = " ", bool __sk = true) {
    vector<string> __r {};
    size_t __b = 0;
    size_t __e = __s.find(__d);

    while (__e != aoc::string::npos) {
        string __tok = __s.substr(__b, __e - __b);
        if (!__tok.empty() || !__sk) {
            __r.push_back(__tok);
        }

        __b = __e + __d.size();
        __e = __s.find(__d, __b);
    }

    string __tok = __s.substr(__b);
    if (!__tok.empty() || !__sk) {
        __r.push_back(__tok);
    }

    return __r;
}


/// @brief Implementation for split in the unzip function. Splits a string into a pair of two strings given a delimeter, optionally skipping empty strings.
/// @param __s The string to be split.
/// @param __d The delimeter to split the string by. Defaults to a single space.
/// @param __sk Determines if empty strings should be skipped. Defaults to true.
/// @return A pair containing the two substrings produced through splitting.
std::pair<std::string, std::string> __unzipper(const std::string &__s, const std::string &__d, bool __sk) {
    std::vector<std::string> __vpa = __spl_imp(__s, __d, __sk);
    if (__vpa.size() < 2) {
        throw std::invalid_argument("unzipper input string could not be split into two parts");
    }

    return std::make_pair(__vpa.at(0), __vpa.at(1));
}
} // __detail


/// @brief Reads the entire contents of a file into an std::string.
/// @param __file The path to the file to read.
/// @return A string containing the file's contents.
/// @throws std::ios_base::failure if the file cannot be opened.
std::string read_file(const std::string &__file) {
    std::ifstream __f(__file);
    if (!__f.is_open()) {
        throw std::ios_base::failure("Could not open file '" + __file + "'");
    }

    std::stringstream __ss;
    __ss << __f.rdbuf();
    __f.close();
    return __ss.str();
}

/// @brief Splits a string by a delimeter, optionally skipping empty strings.
/// @param __s The string to be split.
/// @param __d The delimeter to split the string by. Defaults to a single space.
/// @param __sk Determines if empty strings should be skipped. Defaults to true.
/// @return A vector containing substrings of the original string, split by the delimeter.
std::vector<std::string> split(const std::string &__s, const std::string &__d = " ", bool __sk = true) {
    return __detail::__spl_imp(__s, __d, __sk);
}

/// @brief Splits a string by a delimeter, optionally skipping empty strings.
/// @param __s The string to be split.
/// @param __d The delimeter to split the string by. Defaults to a single space.
/// @param __sk Determines if empty strings should be skipped. Defaults to true.
/// @return A vector containing substrings of the original string, split by the delimeter.
aoc::vector<aoc::string> split(const aoc::string &__s, const aoc::string &__d = " ", bool __sk = true) {
    return __detail::__spl_imp(__s, __d, __sk);
}

/// @brief Applies a function repeatedly to each value of a vector.
/// @param __f The function to apply, takes an argument of the new type and the old type.
/// @param __v The vector to use.
/// @param __i The initial value to use when applying the vector in case of type transformations.
/// @return The return value of the final call to the function __f.
///
/// @tparam _T Return and initial input types, first argument for __f.
/// @tparam _T2 Type stored in the vector, second argument for __f.
template <typename _T, typename _T2>
_T apply(_T (*__f)(_T, _T2), const std::vector<_T2> &__v, _T __i) {
    _T __x = __i;
    for (const auto &__xx : __v) {
        __x = f(__x, __xx);
    }

    return __x;
}

/// @brief Applies a transformation function to each value of a vector.
/// @param __f The transformation function.
/// @param __v The vector to transform.
/// @return A vector transformed by function __f.
///
/// @tparam _T The output type of the transformation.
/// @tparam _VX The type stored in the vector.
template <typename _F, typename _C>
auto map(_F __f, const _C &__v) {
    using __R = decltype(__f(*std::begin(__v)));
    std::vector<__R> __nv {};
    for (const auto &__t : __v) {
        __nv.push_back(__f(__t));
    }

    return __nv;
}

/// @brief Applies a transformation function to each value of two vectors at once.
/// @param __f The transformation function. Takes two parameters provided by the types of each vector.
/// @param __vx The first vector.
/// @param __vy The second vector.
/// @return A vector transformed by __f through sources __vx and __vy.
///
/// @tparam _T The output type of the transformation.
/// @tparam _VX The type stored in the first vector.
/// @tparam _VY The type stored in the second vector.
template <typename _T, typename _VX, typename _VY>
std::vector<_T> zip(_T (*__f)(_VX, _VY), const std::vector<_VX> &__vx, const std::vector<_VY> &__vy) {
    std::vector<_T> __nv {};
    for (size_t __i = 0; __i < std::min(__vx.size(), __vy.size()); __i++) {
        __nv.push_back(__f(__vx[__i], __vy[__i]));
    }

    return __nv;
}

/// @brief Applies a transformation and delimeter function to each value of a vector.
/// @param __f The transformation function. Applied after delimetation.
/// @param __v The vector to transform.
/// @param __h The delimeter function to split values of __v.
/// @param __va Variadic args passed to __h.
/// @return A pair containing two vectors generated by the delimeter function and the transformation function.
///
/// @tparam _T The return type of each vector and result of transformation.
/// @tparam _VX The type stored in the vector.
/// @tparam _Args... Variadic template for types passed to __h.
template <typename _T, typename _VX, typename... _Args>
std::pair<std::vector<_T>, std::vector<_T>> unzip(_T (*__f)(_VX), const std::vector<_VX> &__v, std::pair<_T, _T> (*__h)(_VX, _Args...), _Args &&...__va) {
    static_assert(std::is_invocable_v<decltype(__h), _VX, _Args...>, "__h must be invocable with _VX and _Args...");

    std::vector<_T> __a, __b;
    for (const auto &__x : __v) {
        std::pair<_T, _T> __ts = __h(__x, std::forward<_Args>(__va)...);
        __a.push_back(__f(std::get<0>(__ts)));
        __b.push_back(__f(std::get<1>(__ts)));
    }

    return std::make_pair<std::vector<_T>, std::vector<_T>>(__a, __b);
}

/// @brief Applies a transformation and delimeter function to each value of a vector.
/// @param __f The transformation function. Applied after delimetation.
/// @param __v The vector to transform.
/// @param __h The delimeter function to split values of __v.
/// @return A pair containing two vectors generated by the delimeter function and the transformation function.
///
/// @tparam _T The return type of each vector and result of transformation.
/// @tparam _VX The type stored in the vector.
template <typename _T, typename _VX>
std::pair<std::vector<_T>, std::vector<_T>> unzip(_T (*__f)(_VX), const std::vector<_VX> &__v, std::pair<_T, _T> (*__h)(_VX)) {
    std::vector<_T> __a, __b;
    for (const auto &__x : __v) {
        std::pair<_T, _T> __ts = __h(__x);
        __a.push_back(__f(std::get<0>(__ts)));
        __b.push_back(__f(std::get<1>(__ts)));
    }

    return std::make_pair<std::vector<_T>, std::vector<_T>>(__a, __b);
}

/// @brief Applies a transformation and delimeter function to each string in a vector.
/// @param __f The transformation function. Applied after delimetation.
/// @param __v The vector of strings to transform.
/// @param __d The delimeter substring to split strings by. Defaults to a single space.
/// @param __sk Whether to skip empty strings or not. Defaults to false.
/// @return A pair containing two vectors generated by the delimeter and the transformation function.
///
/// @tparam _T The return type of each vector and result of transformation.
template <typename _T>
std::pair<std::vector<_T>, std::vector<_T>> unzip(_T (*__f)(const std::string &), const std::vector<std::string> &__v, const std::string &__d = " ", bool __sk = false) {
    return unzip(__f, __v, __detail::__unzipper, __d, __sk);
}

/// @brief Applies a transformation and delimeter function to each string in a vector.
/// @param __f The transformation function. Applied after delimetation.
/// @param __v The vector of strings to transform.
/// @param __d The delimeter substring to split strings by. Defaults to a single space.
/// @param __sk Whether to skip empty strings or not. Defaults to false.
/// @return A pair containing two vectors generated by the delimeter and the transformation function.
///
/// @tparam _T The return type of each vector and result of transformation.
///
/// @warning inefficient definition as __f takes an std::string instead of a const std::string &. Only helpful for when writing code fast.
template <typename _T>
std::pair<std::vector<_T>, std::vector<_T>> unzip(_T (*__f)(std::string), const std::vector<std::string> &__v, const std::string &__d = " ", bool __sk = false) {
    return unzip(__f, __v, __detail::__unzipper, __d, __sk);
}

/// @brief Repeats a string a certain amount of times optionally joined by a separator.
/// @param __s The string to repeat.
/// @param __c The amount of times to repeat the string.
/// @param __sep The separator to join the occurrences by. Defaults to an empty string.
/// @return A string repeated __c amount of times joined by __sep.
std::string rep(const std::string &__s, size_t __c, const std::string &__sep = "") {
    if (__c == 0) return "";

    size_t __re = __s.size() * __c + __sep.size() * (__c - 1);
    std::string __r;
    __r.reserve(__re);

    __r += __s;
    for (size_t __i = 1; __i < __c; ++__i) {
        __r += __sep;
        __r += __s;
    }

    return __r;
}

/// @brief Sorts a vector in place.
/// @param __v The vector to sort.
///
/// @tparam _T The type stored in the vector.
template <typename _T>
void sort(std::vector<_T> &__v) {
    std::sort(__v.begin(), __v.end());
}

/// @brief Sorts a vector in place given a sort function.
/// @param __f The sort function.
/// @param __v The vector to sort.
///
/// @tparam _T The type stored in the vector.
template <typename _T>
void sort(bool (*__f)(_T, _T), std::vector<_T> &__v) {
    std::sort(__v.begin(), __v.end(), __f);
}

/// @brief Sorts multiple vectors in place.
/// @param __vx The first vector to sort.
/// @param __va The rest of the vectors to sort.
///
/// @tparam _T The type stored in the vector.
/// @tparam _Args The variadic args of vectors to sort.
template <typename _T, typename... _Args>
void sort(std::vector<_T> &__vx, _Args &...__va) {
    sort(__vx);
    sort(std::forward<_Args>(__va)...);
}

/// @brief Sorts multiple vectors in place given a sort function.
/// @param __f The sort function.
/// @param __v The vector to sort.
/// @param __va The rest of the vectors to sort.
///
/// @tparam _T The type stored in the vector.
/// @tparam _Args The variadic args of vectors to sort.
template <typename _T, typename... _Args>
void sort(bool (*__f)(_T, _T), std::vector<_T> &__vx, _Args &...__va) {
    sort(__f, __vx);
    sort(__f, std::forward<_Args>(__va)...);
}

/// @brief Hashes a string using md5.
/// @param __s The string to hash.
/// @returns A string hashed using md5.
std::string hash_md5(const std::string &__s) {
    return _md5_imp(__s);
}

/// @brief Checks if all values in a vector evaluate to true.
/// @param __v The vector to check the values of.
/// @returns Whether all the values within the vector evaluate to true or not.
///
/// @tparam _T The type stored within the vector.
template <typename _T>
bool all(const std::vector<_T> &__v) {
    for (const auto &__x : __v) {
        if (!__x) {
            return false;
        }
    }

    return true;
}

template <typename _T>
bool any(const std::vector<_T> &__v) {
    for (const auto &__x : __v) {
        if (__x) {
            return true;
        }
    }

    return false;
}

/// @brief Rotates a vector of iterables 90 degrees.
/// @param __v The vector to rotate.
/// @returns A vector containing the same data, just rotated 90 degrees.
///
/// @tparam _T The type stored within the vector.
template <typename _T>
std::vector<_T> rotate(const std::vector<_T> &__v) {
    std::vector<_T> __r;

    size_t __ms = 0;
    for (const auto &__i : __v) {
        __ms  = std::max(__ms, __i.size());
    }

    for (size_t __i = 0; __i < __ms; ++__i) {
        _T __ni;
        for (const auto &__ii : __v) {
            auto __it = __ii.begin();
            std::advance(__it, __i);
            if (__it != __ii.end()) {
                __ni.insert(__ni.end(), *__it);
            } else {
                __ni.resize(__ni.size() + 1);
            }
        }

        __r.push_back(__ni);
    }

    return __r;
}

/// @brief Checks if a value is within a range.
/// @param __l The lower bound.
/// @param __v The value to check.
/// @param __h The upper bound.
/// @param __i Whether the upper bound should be inclusive or exclusive (true is inclusive). Defaults to true.
/// @return Wether the value is within the range or not.
///
/// @tparam _T The type of value to check.
template <typename _T>
bool within(_T __l, _T __v, _T __h, bool __i = true) {
    return __l <= __v && (__i ? __v <= __h : __v < __h);
}

template <typename _T>
std::vector<size_t> range(const std::vector<_T> &__v) {
    std::vector<size_t> __r;
    for (size_t __i = 0; __i < __v.size(); ++__i) {
        __r.push_back(__i);
    }

    return __r;
}

} // namespace aoc

#ifndef _AOC_NO_STRING_LITS
using namespace aoc::string_literals;
#endif

#ifndef _AOC_NO_IN_PLACE_FUNCS
int _aoc_strtoi(aoc::string v) { return std::stoi((std::string)v); }
long long _aoc_strtoll(aoc::string v) { return std::stoll((std::string)v); }
size_t _aoc_strtoull(aoc::string v) { return (size_t)std::stoll((std::string)v); }
#endif

#endif // _NEWCORE_AOC_H
