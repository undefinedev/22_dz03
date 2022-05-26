#include <fstream>
#include <future>

#include "Book.hpp"
#include "Library.hpp"

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

bool AnyLibs(std::vector<Library> &libs, size_t choice) {
    return libs.empty() || choice > libs.size();
}

void PrintLib(std::vector<Library> &libs) {
    size_t count = 0;
    for (const auto &i: libs) {
        std::cout << ++count << " " << i.getName() << "  " << i.getNum();
        if (i.getNum() % 10 == 1) {
            std::cout << " книгa.\n";
        } else if (i.getNum() % 10 == 2 || i.getNum() % 10 == 3 || i.getNum() % 10 == 4) {
            std::cout << " книги.\n";
        } else {
            std::cout << " книг.\n";
        }
    }
}

int main() {
    bool work = true;
    std::string in = "input.txt";
    std::string out = "output.txt";
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
        std::cout << "1 - добавление и выбор библиотеки; 2 - печать всех библиотек; 3 - печать доступных книг;"
                     " 4 - добавление книги;\n5 - удаление книги; 6 - печать книг в библиотеке;"
                     " 7 - поиск книги; 8 - редактирование книги;\n9 - чтение из файла;"
                     " 10 - запись книг библиотеки в файл; 11 - взять книгу; 12 - сдать книгу;"
                     "\n13 - действия с посетителями; 14 - список посетителей;"
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
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотеки\n";
                    break;
                }
                std::cout << "Введите ISBN книги и 0 через Enter или создайте новую, введя"
                             "\nISBN >> Автор >> Название >> Год >> Издательство >> Тираж >> Число страниц\n";
                std::cin >> ISBN >> Author;
                if (!std::cin) {
                    std::cin.clear();
                    std::cout << "Вводите цифры!!!" << std::endl;
                    Author.clear();
                    break;
                }
                if (Author == "0" && books.contains(ISBN)) {
                    try {
                        libs[lib_choice - 1].AddBook(books[ISBN]);
                    } catch (LibraryErrors &e) {
                        std::cout << e.what();
                        Author.clear();
                    }
                    break;
                } else if (Author == "0") {
                    std::cout << "Нет такой книги\n";
                    break;
                }
                std::cin >> Name >> Year >> Publisher >> Copies >> PageCount;
                if (!std::cin) {
                    std::cin.clear();
                    std::cout << "Вводите цифры!!!" << std::endl;
                    break;
                }
                try {
                    auto tempB = Book(Author, Name, Year, Publisher, Copies, PageCount, ISBN);
                    books.insert({ISBN, tempB});
                    libs[lib_choice - 1].AddBook(tempB);
                } catch (LibraryErrors &e) {
                    std::cout << e.what();
                    Author.clear();
                }
                break;
            case 5:
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотек\n";
                    break;
                }
                std::cout << "Введите ISBN книги, которую хотите удалить\n";
                std::cin >> ISBN;
                if (!std::cin) {
                    std::cin.clear();
                    std::cout << "Вводите цифры!!!" << std::endl;
                    break;
                }
                try {
                    libs[lib_choice - 1].RemoveBook(ISBN);
                } catch (LibraryErrors &e) {
                    std::cout << e.what();
                }
                break;
            case 6:
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотек\n";
                    break;
                }
                std::cout << libs[lib_choice - 1];
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                Read(books, in);
                break;
            case 10:
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотек\n";
                    break;
                }
                Write(libs[lib_choice - 1], out);
                break;
            case 11:
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотек\n";
                    break;
                }
                std::cout << "Введите имя пользователя: ";
                std::cin >> temp;
                std::cout << "\nВведите ISBN: ";
                std::cin >> ISBN;
                if (!std::cin) {
                    std::cin.clear();
                    std::cout << "Вводите цифры!!!" << std::endl;
                    break;
                }
                try {
                    libs[lib_choice - 1].GetBook(temp, ISBN);
                } catch (LibraryErrors &e) {
                    std::cout << e.what();
                }
                break;
            case 12:
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотек\n";
                    break;
                }
                std::cout << "Введите имя пользователя: ";
                std::cin >> temp;
                std::cout << "\nВведите ISBN: ";
                std::cin >> ISBN;
                if (!std::cin) {
                    std::cin.clear();
                    std::cout << "Вводите цифры!!!" << std::endl;
                    break;
                }
                try {
                    libs[lib_choice - 1].ReturnBook(temp, ISBN);
                } catch (LibraryErrors &e) {
                    std::cout << e.what();
                }
            case 13:
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотек\n";
                    break;
                }
                std::cout << "1 - добавить посетителя\n2 - удалить посетителя\n3 - напечатать книги посетителя\n";
                std::cin >> choice;
                if (!std::cin) {
                    std::cin.clear();
                    std::cout << "Вводите цифры!!!" << std::endl;
                    break;
                }

                std::cout << "Введите имя посетителя\n";
                std::cin >> temp;
                try {
                    if (choice == 1) {
                        libs[lib_choice - 1].AddVisitor(temp);
                        break;
                    } else if (choice == 2){
                        libs[lib_choice - 1].RemoveVisitor(temp);
                        break;
                    } else if (choice == 3) {
                        libs[lib_choice - 1].PrintVisitor(temp);
                        break;
                    }
                } catch (LibraryErrors &e) {
                    std::cout << e.what();
                    break;
                }
            case 14:
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотек\n";
                    break;
                }
                libs[lib_choice - 1].PrintVisitors();
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
