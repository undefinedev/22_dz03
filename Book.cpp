// Copyright 2022 undefinedev Timofeev Vladislav

#include "Book.hpp"

Book::Book() : Author(),
               Name(),
               Year(),
               Publisher(),
               Copies(),
               PageCount(),
               ISBN() {}

Book::Book(std::string &auth, std::string &name, int year, std::string &pub, size_t cop, size_t pag, size_t isbn)
    : Author(std::move(auth)),
      Name(std::move(name)),
      Year(year),
      Publisher(std::move(pub)),
      Copies(cop),
      PageCount(pag),
      ISBN(isbn) {}

Book::Book(const Book &) = default;

Book::~Book() = default;

void Book::set(std::string &auth, std::string &name, int year, std::string &pub, size_t cop, size_t pag, size_t isbn) {
    Author = std::move(auth);
    Name = std::move(name);
    Year = year;
    Publisher = std::move(pub);
    Copies = cop;
    PageCount = pag;
    ISBN = isbn;
}

void Book::setYear(int year) {
    Year = year;
}

void Book::setCopies(size_t cop) {
    Copies = cop;
}
void Book::get(std::string &auth, std::string &name, int &year, std::string &pub, size_t &cop, size_t &pag, size_t &isbn) const {
    auth = Author;
    name = Name;
    year = Year;
    pub = Publisher;
    cop = Copies;
    pag = PageCount;
    isbn = ISBN;
}

std::pair<std::string, std::string> Book::getInfo() const {
    return std::make_pair(Author, Name);
}

size_t Book::getISBN() const {
    return ISBN;
}

size_t Book::getYear() const {
    return Year;
}

std::string Book::getPub() const {
    return Publisher;
}

std::ostream &operator<<(std::ostream &out, const Book &book) {
    out << book.Author << " " << book.Name
        << "\nИздательство " << book.Publisher << " Год издания " << book.Year
        << "\nЧисло страниц: " << book.PageCount << "\nТираж " << book.Copies << " экз."
        << "\nISBN " << book.ISBN << "\n"
        << std::endl;
    return out;
}
