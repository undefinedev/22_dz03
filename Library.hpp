// Copyright 2022 undefinedev Timofeev Vladislav

#ifndef INC_22_DZ03_LIBRARY_HPP
#define INC_22_DZ03_LIBRARY_HPP

#include <list>
#include <map>
#include <unordered_map>
#include <vector>

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
    std::pair<std::string, size_t> get() const;
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

    bool BookAv(size_t);
    bool VisitorAv(std::string &);

    friend std::ostream &operator<<(std::ostream &, const Library &);
};


#endif//INC_22_DZ03_LIBRARY_HPP
