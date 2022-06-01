#include <fstream>
#include <future>
#include <map>
#include <vector>

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
    Library *main;
    while (work) {
        std::cout << "1 - добавление и выбор библиотеки; 2 - печать всех библиотек; 3 - печать всех книг;"
                     " 4 - добавление книги;\n5 - удаление книги; 6 - печать книг в библиотеке с сортировкой;"
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
                    std::cout << "Вводите цифры!!!" << std::endl;
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
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет такой библиотеки\n";
                    lib_choice = 1;
                }
                main = &libs[lib_choice - 1];
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
                        *main + books[ISBN];
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
                    *main + tempB;
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
                    main->RemoveBook(ISBN);
                } catch (LibraryErrors &e) {
                    std::cout << e.what();
                }
                break;
            case 6:
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотек\n";
                    break;
                }
                std::cout << "0 - обычная печать\n1 - Сортировка по автору\n2 - Сортировка по названию\n3 - Сортировка по году\n";
                std::cin >> choice;
                if (!std::cin) {
                    std::cin.clear();
                    std::cout << "Вводите цифры!!!" << std::endl;
                    break;
                }
                main->Sort(choice);
                std::cout << *main;
                break;
            case 7:
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотек\n";
                    break;
                }
                std::cout << "1 - поиск по автору\n2 - поиск по названию\n3 - поиск по году\n4 - поиск по издательству\n5 - поиск по ISBN\n";
                std::cin >> choice;
                if (!std::cin) {
                    std::cin.clear();
                    std::cout << "Вводите цифры!!!" << std::endl;
                    break;
                }
                switch (choice) {
                    case 1:
                        std::cout << "Введите имя автора: ";
                        std::cin >> temp;
                        main->Search_Auth(temp);
                        break;
                    case 2:
                        std::cout << "Введите название: ";
                        std::cin >> temp;
                        main->Search_Name(temp);
                        break;
                    case 3:
                        std::cout << "Введите год: ";
                        std::cin >> Year;
                        if (!std::cin) {
                            std::cin.clear();
                            std::cout << "Вводите цифры!!!" << std::endl;
                            break;
                        }
                        main->Search_Year(Year);
                        break;
                    case 4:
                        std::cout << "Введите название: ";
                        std::cin >> temp;
                        main->Search_Publisher(temp);
                        break;
                    case 5:
                        std::cout << "Введите ISBN: ";
                        std::cin >> ISBN;
                        if (!std::cin) {
                            std::cin.clear();
                            std::cout << "Вводите цифры!!!" << std::endl;
                            break;
                        }
                        main->Search_ISBN(ISBN);
                        break;
                    default:
                        break;
                }
                break;
            case 8:
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотек\n";
                    break;
                }
                std::cout << "1 - редактирование года\n2 - редактирование тиража\n";
                std::cin >> choice;
                if (!std::cin) {
                    std::cin.clear();
                    std::cout << "Вводите цифры!!!" << std::endl;
                    break;
                }
                std::cout << "ISBN: ";
                std::cin >> ISBN;
                if (!std::cin) {
                    std::cin.clear();
                    std::cout << "Вводите цифры!!!" << std::endl;
                    break;
                }
                std::cout << "Введите нужное значение\n";
                std::cin >> Year;
                if (!std::cin) {
                    std::cin.clear();
                    std::cout << "Вводите цифры!!!" << std::endl;
                    break;
                }
                try {
                    main->Edit(ISBN, choice, Year);
                } catch (LibraryErrors &e) {
                    std::cout << e.what();
                }
                break;
            case 9:
                std::future(std::async(std::launch::async, Read, std::ref(books), std::ref(in)));
                break;
            case 10:
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотек\n";
                    break;
                }
                std::future(std::async(std::launch::async, Write, *main, std::ref(out)));
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
                    main->GetBook(temp, ISBN);
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
                    main->ReturnBook(temp, ISBN);
                } catch (LibraryErrors &e) {
                    std::cout << e.what();
                }
                break;
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
                        main->AddVisitor(temp);
                    } else if (choice == 2) {
                        main->RemoveVisitor(temp);
                    } else if (choice == 3) {
                        main->PrintVisitor(temp);
                    }
                    break;
                } catch (LibraryErrors &e) {
                    std::cout << e.what();
                    break;
                }
            case 14:
                if (AnyLibs(libs, lib_choice)) {
                    std::cout << "Нет библиотек\n";
                    break;
                }
                main->PrintVisitors();
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
