// Advent of Code C++ Utility Script
// Written by StarlitNova (@starlitnova, or simply Nova)
// provides simple usage functions based on python functions for AoC
// Usage:
//     std::string readfile(std::string fileName)
//         - returns an entire file's contents, retrieved from fileName
//     std::vector<std::string> split(std::string string, std::string delimiter)
//         - returns a vector of substrings, retrieved by splitting 'string' by 'delimiter'
//     std::vector<T> map([](T2) -> T {} transformFunction, std::vector<T2> oldVector)
//         - returns a vector of type T which contains the elements of oldVector transformed by transformFunction
//     T max(...)
//         - returns the max value provided, infinite argument function (or provide an std::vector<T>)
//     T min(...)
//         - returns the min value provided, infinite argument function (or provide an std::vector<T>)
//     T pop(std::vector<T> &vector)
//         - pops the last element of the provided vector and returns it
//     std::string removeAll(std::string string, std::string delimiter)
//         - removes all occurances of delimiter in string
//     std::string rep(std::string string, size_t count)
//         - returns a string that is what string is repeated count times
//     std::vector<T> sortip(std::vector<T> vector, sortFunction?)
//         - sorts the specified vector with the function and returns it
//     void sort(std::vector<T> vector, sortFunction?)
//         - sorts the specified vector with the function in place (sorry for naming these backwards)
//     std::string MD5(std::string str)
//         - returns the MD5 hash of str
//     bool all(std::vector<T> vec)
//         - returns true if everything in the vector is true (unknown behavior if T is not a bool)
// DEFINITIONS:
//     ASSERT_MSG(testCase, message)
//         - if testCase fails, message is printed to the output (along with "Assertion Failed: testCase")
//     ASSERT(testCase)
//         - same as ASSERT_MSG except message is "Program exit requested"
//

#pragma once

#ifndef _AOC_CORE_H

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
#include <string>
#include <vector>

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
#define AOC_UNDEFINED(s) __attribute__((warning(#s)))
#else
#define AOC_UNDEFINED(s)
#endif

#ifndef _AOC_NO_STRING_LITS
using namespace std::string_literals;
#endif

#define ASSERT_MSG(fn, msg)                                                                                            \
    if (!fn) {                                                                                                         \
        std::cout << "Assertion Failed: " #fn " | " << __FILE__ << " line " << __LINE__ << "\n";                       \
        std::cout << "    " << msg << "\n";                                                                            \
        std::raise(SIGABRT);                                                                                           \
    }
#define ASSERT(fn) ASSERT_MSG(fn, "Program exit requested")

#include "tools/md5.h"

namespace AOC {
std::string readfile(std::string fname) {
    std::ifstream f(fname);
    ASSERT_MSG(f.is_open(), "Failed to open file '" + fname);
    std::string v = std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    f.close();
    return v;
}

// coupable = if the string should be tested for being empty (coupable = false means a greedy vector and will have empty
// strings in it)
std::vector<std::string> split(std::string str, std::string delim = " ", bool coupable = true) {
    std::vector<std::string> fin{};
    size_t i = 0;
    while ((i = str.find(delim)) != std::string::npos) {
        if (coupable && str.substr(0, i).empty()) {
            str.erase(0, delim.size());
            continue;
        }
        fin.push_back(str.substr(0, i));
        str.erase(0, i + delim.size());
    }
    if (!str.empty())
        fin.push_back(str);
    return fin;
}

template <typename T, typename T2> std::vector<T> map(T (*f)(T2), std::vector<T2> vec) {
    std::vector<T> newVec{};
    for (const auto &val : vec)
        newVec.push_back(f(val));
    return newVec;
}

template <typename T> T max(T a, T b) { return b > a ? b : a; }
template <typename T, typename... Ts> T max(T first, const Ts &...rest) { return max(first, max(rest...)); }

template <typename T> T max(std::vector<T> vals) {
    int highest = INT_MIN;
    for (const auto &v : vals)
        if (v > highest)
            highest = v;
    return highest;
}

template <typename T> T min(T a, T b) { return b < a ? b : a; }
template <typename T, typename... Ts> T min(T first, const Ts &...rest) { return min(first, min(rest...)); }

template <typename T> T min(const std::vector<T> &vals) {
    int lowest = INT_MAX;
    for (const auto &v : vals)
        if (v < lowest)
            lowest = v;
    return lowest;
}

template <typename T> T pop(std::vector<T> &vec) {
    T v = vec.back();
    vec.pop_back();
    return v;
}

template <typename T> T popf(std::deque<T> &deq) {
    T v = deq.front();
    deq.pop_front();
    return v;
}

template <typename T> T popb(std::deque<T> &deq) {
    T v = deq.back();
    deq.pop_back();
    return v;
}

// std::string removeAll(std::string str, std::string delimiter) {
//     str.erase(std::remove(str.begin(), str.end(), delimiter), str.end());
//     return str;
// }

std::string rep(std::string str, size_t count = 2) {
    std::string fin = "";
    for (size_t i = 0; i < count; i++)
        fin += str;
    return fin;
}

template <typename T>
void sort(
    std::vector<T> &vec, bool (*sfn)(T, T) = [](T a, T b) -> bool { return a < b; }) {
    std::sort(vec.begin(), vec.end(), sfn);
}

template <typename T>
std::vector<T> sortip(
    std::vector<T> vec, bool (*sfn)(T, T) = [](T a, T b) -> bool { return a < b; }) {
    std::sort(vec.begin(), vec.end(), sfn);
    return vec;
}

std::string MD5(const std::string &str) { return _md5_imp(str); }

template <typename T> bool all(std::vector<T> vec) {
    for (const auto &v : vec)
        if (!v)
            return false;
    return true;
}

template <typename T> bool in(const std::vector<T> &vec, T v) {
    for (const auto &vv : vec)
        if (vv = v)
            return true;
    return false;
}

template <typename T> std::vector<T> intersect(std::vector<T> vec, std::vector<T> bAnd) {
    std::sort(vec.begin(), vec.end());
    std::sort(bAnd.begin(), bAnd.end());
    std::vector<T> res;
    std::set_intersection(vec.begin(), vec.end(), bAnd.begin(), bAnd.end(), std::back_inserter(res));
    return res;
}

template <typename T> std::vector<T> intersectOr(std::vector<T> vec, std::vector<T> bOr) {
    std::sort(vec.begin(), vec.end());
    std::sort(bOr.begin(), bOr.end());
    std::vector<T> res(vec.size() + bOr.size());
    auto it = std::set_union(vec.begin(), vec.end(), bOr.begin(), bOr.end(), res.begin());
    res.resize(it - res.begin());
    return res;
}

std::string trimleft(std::string str) { return str.erase(0, str.find_first_not_of(" \t\n\r\f\v")); }
std::string trimright(std::string str) { return str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1); }
std::string trim(std::string str) { return trimleft(trimright(str)); }
} // namespace AOC

#endif // _AOC_CORE_H

#ifndef _AOC_NO_DEFINES

#define _aoc_strtoi [](std::string v) -> int { return std::stoi(v); }
#define _aoc_strtoll [](std::string v) -> long long { return std::stoll(v); }
#define _aoc_strtoull [](std::string v) -> size_t { return (size_t)std::stoll(v); }

#endif // _AOC_NO_DEFINES