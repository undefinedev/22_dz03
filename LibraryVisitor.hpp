// Copyright 2022 undefinedev Timofeev Vladislav

#ifndef INC_22_DZ03_LIBRARYVISITOR_HPP
#define INC_22_DZ03_LIBRARYVISITOR_HPP

#include "Book.hpp"
#include "LibraryErrors.hpp"
#include <list>

class LibraryVisitor {
    std::string Name;
    std::list<Book> Books;
public:
    LibraryVisitor();
    explicit LibraryVisitor(std::string &);
    ~LibraryVisitor();
    [[nodiscard]] std::string getName() const;
    void AddBook(const Book &);
    void RemoveBook(size_t);

    friend std::ostream &operator<<(std::ostream &, const LibraryVisitor &);
};


#endif//INC_22_DZ03_LIBRARYVISITOR_HPP
