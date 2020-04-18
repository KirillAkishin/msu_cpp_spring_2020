// #pragma once
#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <iostream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    std::ostream& out_;

    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
            : out_(out)
        {
        }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }
    
private:
    template <class T>
    Error process(T&& val)
    {
        return Error::NoError;
    }

    template <class T, class... Args>
    Error process(T&& val, Args&&... args)
    {
        // if val == bool{
        //     std::cout << "it is bool" << '\n';
        // }
        out_ << val << Separator;
        std::cout << val << '\n';
        process(std::forward<Args>(args)...);
        return Error::NoError;
    }
};

#endif