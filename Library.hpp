// Copyright 2022 undefinedev Timofeev Vladislav

#ifndef INC_22_DZ03_LIBRARY_HPP
#define INC_22_DZ03_LIBRARY_HPP

#include <algorithm>
#include <list>
#include <unordered_map>

#include "Book.hpp"
#include "LibraryErrors.hpp"
#include "LibraryVisitor.hpp"

class Library {
    std::list<Book> Books;
    std::unordered_map<size_t, bool> AccountBooks;
    std::list<LibraryVisitor> Visitors;
    size_t BooksCount;
    std::string Name;

public:
    Library();
    explicit Library(std::string &);
    void setName(std::string &);
    std::string getName() const;
    size_t getNum() const;
    void AddVisitor(std::string &);
    void PrintVisitors();
    void PrintVisitor(std::string &);
    void RemoveVisitor(std::string &);
    void AddBook(const Book &);
    void RemoveBook(size_t);
    void GetBook(std::string &, size_t);
    void ReturnBook(std::string &, size_t);

    void Sort(size_t);

    void Edit(size_t, size_t, size_t);

    void Search_Auth(std::string &);
    void Search_Name(std::string &);
    void Search_Year(int);
    void Search_Publisher(std::string &);
    void Search_ISBN(size_t);

    Library &operator+(const Book &);
    Library &operator-(const Book &);

    bool BookAv(size_t);
    bool VisitorAv(const std::string &);
    static bool Auth_(const Book &, const Book &);
    static bool Name_(const Book &, const Book &);
    static bool Year_(const Book &, const Book &);

    friend std::ostream &operator<<(std::ostream &, const Library &);
};


#endif//INC_22_DZ03_LIBRARY_HPP
