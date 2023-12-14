// Advent of Code C++ Utility Script
// Written by StarlitNova (@starlitnova, or simply Nova)
// provides simple usage functions based on python functions for AoC

// Documentation was removed due to it being out of date. Once I finished
// AOC 2023 I will rewrite the documentation.

// For now, the arguments and names of the functions should explain themselves

// Some things you can define are also here:
// #define _AOC_NO_STRING_LITS
//    --> disables std::string_literals, it is enabled by default for the operator""s
// #define _AOC_NO_DEFINES
//    --> disables helpful defines that this script generates. Note that none of the defines
//        have short names and are all prefixed with _aoc_ (ex _aoc_strtoi)

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
#include <sstream>
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
    std::stringstream ss;
    ss << f.rdbuf();
    f.close();
    return ss.str();
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

std::string rep(std::string str, size_t count = 2, std::string separator = "") {
    std::string fin = "";
    for (size_t i = 0; i < count; i++) {
        if (i != 0)
            fin += separator;
        fin += str;
    }
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

std::vector<std::string> rezip(std::vector<std::string> vec) {
    std::vector<std::string> result{};
    for (size_t i = 0; i < vec[0].size(); i++)
        result.push_back("");
    for (const auto &val : vec) {
        for (size_t i = 0; i < val.size(); i++) {
            result[i] += val[i];
        }
    }
    return result;
}

std::string reverse(std::string str) {
    std::string res{};
    for (size_t i = str.size() - 1; i >= 0; i--)
        res += str[i];
    return res;
}

template <typename T>
std::vector<T> subvec(const std::vector<T> &vec, size_t start, size_t end = static_cast<size_t>(-1), int step = 1) {
    std::vector<T> gen{};

    if (start >= vec.size())
        start = vec.size();

    if (end == static_cast<size_t>(-1) || end > vec.size())
        end = vec.size();

    size_t reserving = max((end - start) / abs(step) + (size_t)1, (size_t)1);
    if (reserving < 1000)
        gen.reserve(reserving);

    if (end < start) {
        for (size_t i = start; i >= end; i += step) {
            if (i >= vec.size())
                continue;
            gen.push_back(vec[i]);
            if (i == 0)
                break;
        }
    } else
        for (size_t i = start; i < end; i += step)
            gen.push_back(vec[i]);

    return gen;
}

template <typename T> bool vecEquals(const std::vector<T> &a, const std::vector<T> &b) {
    if (a.size() != b.size())
        return false;
    for (size_t i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return false;
    return true;
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