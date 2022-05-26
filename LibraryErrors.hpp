// Copyright 2022 undefinedev Timofeev Vladislav

#ifndef INC_22_DZ03_LIBRARYERRORS_HPP
#define INC_22_DZ03_LIBRARYERRORS_HPP

#include <exception>
#include <string>
#include <utility>

class LibraryErrors : public std::exception {
    std::string msg;
public:
    LibraryErrors() = default;
    explicit LibraryErrors(std::string msg_) : msg(std::move(msg_)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return msg.c_str();
    };
};


#endif//INC_22_DZ03_LIBRARYERRORS_HPP
