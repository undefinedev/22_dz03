// Copyright 2022 undefinedev Timofeev Vladislav

#include "Library.hpp"

Library::Library() : BooksCount(0) {}

Library::Library(std::string &name) : BooksCount(0),
                                      Name(std::move(name)) {}

void Library::setName(std::string &name) {
    Name = std::move(name);
}

bool Library::BookAv(size_t isbn) {
    return std::ranges::any_of(Books.cbegin(), Books.cend(), [isbn](const Book &b) { return b.getISBN() == isbn; });
}

bool Library::VisitorAv(const std::string &name) {
    return std::ranges::any_of(Visitors.cbegin(), Visitors.cend(), [&name](const LibraryVisitor &v) { return v.getName() == name; });
}

void Library::AddVisitor(std::string &name) {
    if (VisitorAv(name)) {
        throw LibraryErrors("Такой пользователь уже зарегистрирован\n\n");
    }
    Visitors.emplace_back(name);
}

void Library::PrintVisitors() {
    if (Visitors.empty()) {
        std::cout << "Нет посетителей\n\n"
                  << std::endl;
    }
    for (const auto &i: Visitors) {
        std::cout << i;
    }
}

void Library::PrintVisitor(std::string &name) {
    auto temp = std::find_if(Visitors.begin(), Visitors.end(),
                             [&name](const LibraryVisitor &t) { return t.getName() == name; });
    if (temp == Visitors.end() && temp->getName() != name) {
        throw LibraryErrors("В системе нет такого пользователя\n\n");
    }
    std::cout << *temp;
}

void Library::RemoveVisitor(std::string &name) {
    auto temp = std::find_if(Visitors.begin(), Visitors.end(),
                             [&name](const LibraryVisitor &t) { return t.getName() == name; });
    if (temp == Visitors.end() && temp->getName() != name) {
        throw LibraryErrors("В системе нет такого пользователя\n\n");
    }
    if (!temp->empty()) {
        throw LibraryErrors("Верните сначала книги\n\n");
    }
    Visitors.erase(temp);
}

void Library::AddBook(const Book &book) {
    if (BookAv(book.getISBN())) {
        throw LibraryErrors("Книга не добавлена в библиотеку, так как уже имеется\n\n");
    }
    Books.push_back(book);
    AccountBooks.insert({book.getISBN(), false});
    ++BooksCount;
}

void Library::RemoveBook(size_t isbn) {
    auto temp = std::find_if(Books.begin(), Books.end(), [isbn](const Book &t) { return t.getISBN() == isbn; });
    if (temp == Books.end() && temp->getISBN() != isbn) {
        throw LibraryErrors("Нет такой книги\n\n");
    }
    Books.erase(temp);
    AccountBooks.erase(isbn);
    --BooksCount;
}

void Library::GetBook(std::string &name, size_t isbn) {
    if (!VisitorAv(name)) {
        throw LibraryErrors("В системе нет такого пользователя\n\n");
    }
    auto temp = std::find_if(Books.begin(), Books.end(), [isbn](const Book &t) { return t.getISBN() == isbn; });
    auto tempB = std::find_if(Visitors.begin(), Visitors.end(),
                              [&name](const LibraryVisitor &t) { return t.getName() == name; });
    if (temp == Books.end() && temp->getISBN() != isbn) {
        throw LibraryErrors("Нет такой книги\n\n");
    }
    if (AccountBooks[isbn]) {
        throw LibraryErrors("Книга уже не имеется в наличии\n\n");
    }
    tempB->AddBook(*temp);
    AccountBooks[isbn] = true;
}

void Library::ReturnBook(std::string &name, size_t isbn) {
    if (!VisitorAv(name)) {
        throw LibraryErrors("В системе нет такого пользователя\n\n");
    }
    auto temp = std::find_if(Books.begin(), Books.end(), [isbn](const Book &t) { return t.getISBN() == isbn; });
    if (!BookAv(isbn)) {
        throw LibraryErrors("Нет такой книги\n\n");
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

bool Library::Auth_(const Book &a, const Book &b) {
    return a.getInfo().first < b.getInfo().first;
}

bool Library::Name_(const Book &a, const Book &b) {
    return a.getInfo().second < b.getInfo().second;
}

bool Library::Year_(const Book &a, const Book &b) {
    return a.getYear() < b.getYear();
}

void Library::Sort(size_t choice) {
    if (choice == 1) {
        Books.sort(Auth_);
    }
    if (choice == 2) {
        Books.sort(Name_);
    }
    if (choice == 3) {
        Books.sort(Year_);
    }
}

void Library::Search_Auth(std::string &auth) {
    std::cout << "Книги под авторством " << auth << std::endl;
    for (const auto &i: Books) {
        if (i.getInfo().first == auth) {
            std::cout << i;
        }
    }
}

void Library::Search_Name(std::string &name) {
    for (const auto &i: Books) {
        if (i.getInfo().second == name) {
            std::cout << i;
        }
    }
}

void Library::Search_Year(int year) {
    for (const auto &i: Books) {
        if (i.getYear() == year) {
            std::cout << i;
        }
    }
}

void Library::Search_Publisher(std::string &pub) {
    for (const auto &i: Books) {
        if (i.getPub() == pub) {
            std::cout << i;
        }
    }
}

void Library::Search_ISBN(size_t isbn) {
    for (const auto &i: Books) {
        if (i.getISBN() == isbn) {
            std::cout << i;
        }
    }
}

void Library::Edit(size_t isbn, size_t choice, size_t val) {
    if (!BookAv(isbn)) {
        throw LibraryErrors("Нет такой книги.\n\n");
    }
    auto temp = std::find_if(Books.begin(), Books.end(), [isbn](const Book &t) { return t.getISBN() == isbn; });
    if (choice == 1) {
        temp->setYear(int(val));
    } else if (choice == 2) {
        temp->setCopies(val);
    }
}

Library &Library::operator+(const Book &book) {
    AddBook(book);
    return *this;
}

Library &Library::operator-(const Book &book) {
    RemoveBook(book.getISBN());
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Library &lib) {
    out << "Название библиотеки: " << lib.Name << std::endl;
    out << "Число книг: " << lib.BooksCount << std::endl;
    for (const auto &i: lib.Books) {
        out << i;
    }
    return out;
}
