// Copyright 2022 undefinedev Timofeev Vladislav

#ifndef INC_22_DZ03_BOOK_HPP
#define INC_22_DZ03_BOOK_HPP

#include <string>
#include <iostream>

class Book {
    std::string Author;
    std::string Name;
    int Year;
    std::string Publisher;
    size_t Copies;
    size_t PageCount;
    size_t ISBN;

public:
    Book();
    Book(std::string &, std::string &, int, std::string &, size_t, size_t, size_t);
    Book(const Book &);
    ~Book();
    void set(std::string &, std::string &, int, std::string &, size_t, size_t, size_t);
    void setYear(int);
    void setCopies(size_t);
    void get(std::string &, std::string &, int &, std::string &, size_t &, size_t &, size_t &) const;
    [[nodiscard]] std::pair<std::string, std::string> getInfo() const;
    [[nodiscard]] size_t getISBN() const;
    friend std::ostream &operator<<(std::ostream &, const Book &);
};


#endif//INC_22_DZ03_BOOK_HPP
