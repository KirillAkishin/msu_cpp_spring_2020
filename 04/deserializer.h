#pragma once

#include <iostream>
#include "errors.h"


template <typename T>
using is_bool = std::is_same<T, bool>;

class Deserializer
{
    std::istream& in_;

    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in)
            : in_(in) {}

    Error load(bool& value)
    {
        std::string text;
        in_ >> text;

        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else{
            return Error::CorruptedArchive;
        }


        return Error::NoError;
    }

    Error load(uint64_t& value)
    {
        std::string text;
        in_ >> text;
        if (text[0] == '-')
        {
            return Error::CorruptedArchive;
        }
        try {
            value = stoull(text);
        }
        catch(std::invalid_argument& e){
            return Error::CorruptedArchive;
        }
        catch(std::out_of_range& e){
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template <class T>
    Error load(T& object)
    {
        // std::cout << "load" << std::endl;
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args)
    {
        // std::cout << "operator()" << std::endl;
        return process(args...);
    }

private:
    template <class T>
    Error process(T& val)
    {
        // std::cout << "process_finish" << std::endl;
        return load(val);
    }

    template <class T, class... Args>
    Error process(T& val, Args&... args)
    {
        // std::cout << "process; val=" << val << std::endl;
        Error err = load(val);
        if (err != Error::NoError){
            return err;
        }
        return process(std::forward<Args&>(args)...);
    }
};

