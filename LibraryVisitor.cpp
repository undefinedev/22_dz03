// Copyright 2022 undefinedev Timofeev Vladislav

#include "LibraryVisitor.hpp"

LibraryVisitor::LibraryVisitor() = default;

LibraryVisitor::LibraryVisitor(std::string &name) : Name(std::move(name)) {}

LibraryVisitor::~LibraryVisitor() = default;

const char* LibraryVisitor::getName() const {
    return Name.c_str();
}

bool LibraryVisitor::empty() {
    return Books.empty();
}

void LibraryVisitor::AddBook(const Book &book) {
    Books.push_back(book);
}

void LibraryVisitor::RemoveBook(size_t isbn) {
    auto temp = std::find_if(Books.begin(), Books.end(),
                             [&isbn](const Book &t) { return t.getISBN() == isbn; });
    if (temp == Books.end() && temp->getISBN() != isbn) {
        throw LibraryErrors("У этого посетителя нет данной книги\n");
    }
    Books.erase(temp);
}

std::ostream &operator<<(std::ostream &out, const LibraryVisitor &vis) {
    std::cout << vis.getName() << "\n";
    std::cout << "Книги на руках:\n";
    for (const auto &k: vis.Books) {
        std::cout << k.getInfo().first << "  " << k.getInfo().second << "  ISBN: " << k.getISBN() << "\n";
    }
    std::cout << "\n";
    return out;
}
