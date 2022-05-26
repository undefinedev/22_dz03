#include <fstream>

#include "Book.hpp"
#include "Library.hpp"
#include "windows.h"

void Read(std::map<size_t, Book> &books, std::string &filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        return;
    }
    while (!in.eof()) {
        std::string Author;
        std::string Name;
        int Year;
        std::string Publisher;
        size_t Copies;
        size_t PageCount;
        size_t ISBN;
        in >> Author >> Name >> Year >> Publisher >> Copies >> PageCount >> ISBN;
        books.insert({ISBN, Book(Author, Name, Year, Publisher, Copies, PageCount, ISBN)});
    }
}

void Write(const Library &lib, std::string &filename) {
    std::ofstream out(filename);
    out << lib;
}

void PrintAvBooks(std::map<size_t, Book> &books) {
    for (const auto &i: books) {
        std::cout << i.second;
    }
}

void PrintLib(std::vector<Library> &libs) {
    size_t count = 0;
    for (const auto &i: libs) {
        std::cout << ++count << " " << i.getName() << "  " << i.getNum() << " книг.\n";
    }
}

int main() {
    //SetConsoleOutputCP(CP_UTF8);
    //SetConsoleCP(1251);
    SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8);

    bool work = true;
    size_t choice;
    size_t lib_choice;
    size_t book_choice;
    std::string temp;
    std::string Author;
    std::string Name;
    int Year;
    std::string Publisher;
    size_t Copies;
    size_t PageCount;
    size_t ISBN;
    std::map<size_t, Book> books;
    std::vector<Library> libs;
    while (work) {
        std::cout << "1 - выбор библиотеки по умолчанию; 2 - печать всех библиотек; 3 - печать доступных книг;"
                     "4 - добавление книги;\n5 - удаление книги; 6 - печать книг в библиотеке;"
                     "7 - поиск книги; 8 - редактирование книги;\n9 - чтение из файла;"
                     "10 - запись книг библиотеки в файл;"
                     "\n0 - выход\n";
        std::cin >> choice;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Вводите цифры!!!" << std::endl;
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                if (libs.empty()) {
                    std::cout << "Нет библиотек\n";
                }
                PrintLib(libs);
                std::cout << "Для добавления библиотеки введите 0. Для выбора нужной введите её номер.\n";
                std::cin >> lib_choice;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(100, '\n');
                    std::cout << "Вводите цифры!!!" << std::endl;
                    lib_choice = 0;
                    break;
                }
                if (lib_choice == 0) {
                    std::cout << "Введите название библиотеки\n";
                    std::cin.clear();
                    std::cin.ignore(100, '\n');
                    std::getline(std::cin, temp);
                    libs.emplace_back(temp);
                    lib_choice = 1;
                }
                break;
            case 2:
                PrintLib(libs);
                break;
            case 3:
                PrintAvBooks(books);
                break;
            case 4:
                std::cout << "Введите ISBN книги или создайте новую, введя"
                             "\nISBN >> Автор >> Название >> Год >> Издательство >> Тираж >> Число страниц";
                std::cin >> ISBN;
                std::getline(std::cin, Author);
                if (Author.empty()) {
                    libs[lib_choice - 1].AddBook(books[ISBN]);
                    break;
                }
                std::cin.sync();
                std::getline(std::cin, Name);
                std::cin >> Year;
                std::getline(std::cin, Publisher);
                std::cin >> Copies;
                std::cin >> PageCount;
                if (!std::cin) {
                    std::cin.clear();
                    std::cout << "Вводите цифры!!!" << std::endl;
                    Author.clear();
                    break;
                }
                try {
                    libs[lib_choice - 1].AddBook(Book(Author, Name, Year, Publisher, Copies, PageCount, ISBN));
                } catch (LibraryErrors &e) {
                    std::cout << e.what();
                }
                break;
            case 0:
                work = false;
                break;
            default:
                std::cout << "Just Read the Instructions!!!" << std::endl;
                std::cin.ignore(100, '\n');
        }
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
