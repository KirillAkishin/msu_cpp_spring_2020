#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <sstream>

std::string format(const std::string&);
std::string format(const std::string&, const std::vector<std::string>&);

template <typename T>
std::string collect_args(const T& arg)
{
    std::stringstream stream;
    stream << arg;
    return stream.str();
}

template <typename T, typename... ArgsT>
std::string format(const std::string& str, std::vector<std::string>& strings, T&& arg, ArgsT&&... args)
{
    strings.push_back(collect_args(std::forward<T>(arg)));
    return format(str, strings, std::forward<ArgsT>(args)...);
}

template <typename T, typename... ArgsT>
std::string format(const std::string& str, T&& arg, ArgsT&&... args)
{
    std::vector<std::string> strings;
    return format(str, strings, std::forward<T>(arg), std::forward<ArgsT>(args)...);
}