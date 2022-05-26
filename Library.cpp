// Copyright 2022 undefinedev Timofeev Vladislav

#include "Library.hpp"

Library::Library() : BooksCount(0) {}

Library::Library(std::string &name) : BooksCount(0),
                                      Name(std::move(name)) {}

void Library::setName(std::string &name) {
    Name = std::move(name);
}

bool Library::BookAv(size_t isbn) {
    return std::find_if(Books.begin(), Books.end(),
                        [isbn](const Book &t) { return t.getISBN() == isbn; })
                   ->getISBN() == isbn;
}

bool Library::VisitorAv(std::string &name) {
    return std::find_if(Visitors.begin(), Visitors.end(),
                        [&name](const LibraryVisitor &t) { return t.getName() == name; })
                   ->getName() == name;
}

std::pair<std::string, size_t> Library::get() const {
    return std::make_pair(Name, BooksCount);
}

void Library::AddVisitor(std::string &name) {
    if (VisitorAv(name)) {
        throw LibraryErrors("Такой пользователь уже зарегистрирован");
    }
    Visitors.emplace_back(name);
}

void Library::PrintVisitors() {
    if (Visitors.empty()) {
        std::cout << "Нет посетителей" << std::endl;
    }
    for (const auto &i: Visitors) {
        std::cout << i;
    }
}

void Library::PrintVisitor(std::string &name) {
    auto temp = std::find_if(Visitors.begin(), Visitors.end(),
                             [&name](const LibraryVisitor &t) { return t.getName() == name; });
    if (temp == Visitors.end() && temp->getName() != name) {
        throw LibraryErrors("В системе нет такого пользователя");
    }
    std::cout << *temp;
}

void Library::RemoveVisitor(std::string &name) {
    auto temp = std::find_if(Visitors.begin(), Visitors.end(),
                             [&name](const LibraryVisitor &t) { return t.getName() == name; });
    if (temp == Visitors.end() && temp->getName() != name) {
        throw LibraryErrors("В системе нет такого пользователя");
    }
    Visitors.erase(temp);
}

void Library::AddBook(const Book &book) {
    if (BookAv(book.getISBN())) {
        throw LibraryErrors("Книга не добавлена в библиотеку, так как уже имеется");
    }
    Books.push_back(book);
    AccountBooks.insert({book.getISBN(), false});
    ++BooksCount;
}

void Library::RemoveBook(size_t isbn) {
    auto temp = std::find_if(Books.begin(), Books.end(), [isbn](const Book &t) { return t.getISBN() == isbn; });
    if (temp == Books.end() && temp->getISBN() != isbn) {
        throw LibraryErrors("Нет такой книги");
    }
    Books.erase(temp);
    AccountBooks.erase(isbn);
    --BooksCount;
}

void Library::GetBook(std::string &name, size_t isbn) {
    if (!VisitorAv(name)) {
        AddVisitor(name);
    }
    auto temp = std::find_if(Books.begin(), Books.end(), [isbn](const Book &t) { return t.getISBN() == isbn; });
    auto tempB = std::find_if(Visitors.begin(), Visitors.end(),
                             [&name](const LibraryVisitor &t) { return t.getName() == name; });
    if (temp == Books.end() && temp->getISBN() != isbn) {
        throw LibraryErrors("Нет такой книги");
    }
    if (AccountBooks[isbn]) {
        throw LibraryErrors("Книга уже не имеется в наличии");
    }
    tempB->AddBook(*temp);
    AccountBooks[isbn] = true;
}

void Library::ReturnBook(std::string &name, size_t isbn) {
    if (!VisitorAv(name)) {
        throw LibraryErrors("В системе нет такого пользователя");
    }
    auto temp = std::find_if(Books.begin(), Books.end(), [isbn](const Book &t) { return t.getISBN() == isbn; });
    if (!BookAv(isbn)) {
        throw LibraryErrors("Нет такой книги");
    }
    auto tempB = std::find_if(Visitors.begin(), Visitors.end(),
                              [&name](const LibraryVisitor &t) { return t.getName() == name; });
    tempB->RemoveBook(isbn);
    AccountBooks[isbn] = false;
}

std::string Library::getName() const {
    return Name;
}

size_t Library::getNum() const {
    return BooksCount;
}

std::ostream &operator<<(std::ostream &out, const Library &lib) {
    out << "Название библиотеки: " << lib.Name << std::endl;
    out << "Число книг: " << lib.BooksCount << std::endl;
    for (const auto &i: lib.Books) {
        out << i;
    }
    return out;
}
