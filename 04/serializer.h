// #pragma once
#pragma once

#include <iostream>
#include "errors.h"


template <typename T>
using is_bool = std::is_same<T, bool>;

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
    Error operator()(ArgsT&& ... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
    
private:
    template <class T>
    Error process(T& val)
    {
        if constexpr (is_bool<T>::value) {
            if (val) 
            {
                out_ << "true" << Separator;
            } else 
            {
                out_ << "false" << Separator;
            }
        }
        else {
            out_ << val;
        }
        return Error::NoError;
    }

    template <class T, class... Args>
    Error process(T& val, Args&& ... args)
    {
        if constexpr (is_bool<T>::value) {
            if (val) 
            {
                out_ << "true" << Separator;
            } else 
            {
                out_ << "false" << Separator;
            }
        }
        else {
            out_ << val << Separator;
        }
        process(std::forward<Args>(args)...);
        return Error::NoError;
    }
};
