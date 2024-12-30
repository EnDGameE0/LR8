#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

struct Kvitancia {
    union {
        int intGroupName;
        char charGroupName;
    };
    bool isInt; // Флаг для определения типа groupName
    std::string brand;
    std::string date;
    bool isReady;
};

// Функция для добавления новой квитанции
void addKvitancia(std::vector<Kvitancia>& kvitancii) {
    Kvitancia newKvitancia;
    int choice;
    std::cout << "Введите тип группы изделий (1 - int, 2 - char): ";
    std::cin >> choice;

    if (choice == 1) {
        int groupInt;
        std::cout << "Введите артикул техники: ";
        std::cin >> groupInt;
        newKvitancia.intGroupName = groupInt;
        newKvitancia.isInt = true;
    } else if (choice == 2) {
        char groupChar;
        std::cout << "Введите группу изделий : ";
        std::cin >> groupChar;
        newKvitancia.charGroupName = groupChar;
        newKvitancia.isInt = false;
    } else {
        std::cout << "Неверный выбор. Группа изделий не будет добавлена." << std::endl;
        return;
    }

    std::cout << "Введите марку изделия: ";
    std::cin >> newKvitancia.brand;
    std::cout << "Введите дату приемки в ремонт (ГГГГ-ММ-ДД): ";
    std::cin >> newKvitancia.date;
    std::cout << "Введите состояние готовности заказа (1 - выполнен, 0 - не выполнен): ";
    int ready;
    std::cin >> ready;
    newKvitancia.isReady = (ready == 1);
    kvitancii.push_back(newKvitancia);
}

// Функция для удаления квитанции
void deleteKvitancia(std::vector<Kvitancia>& kvitancii) {
    std::string brand;
    std::cout << "Введите марку изделия для удаления: ";
    std::cin >> brand;
    for (auto it = kvitancii.begin(); it != kvitancii.end(); ++it) {
        if (it->brand == brand) {
            kvitancii.erase(it);
            std::cout << "Квитанция удалена." << std::endl;
            return;
        }
    }
    std::cout << "Квитанция не найдена." << std::endl;
}

// Функция для корректировки квитанции
void correctKvitancia(std::vector<Kvitancia>& kvitancii) {
    std::string brand;
    std::cout << "Введите марку изделия для корректировки: ";
    std::cin >> brand;
    for (auto& kvitancia : kvitancii) {
        if (kvitancia.brand == brand) {
            int choice;
            std::cout << "Введите тип группы изделий (1 - int, 2 - char): ";
            std::cin >> choice;

            if (choice == 1) {
                int groupInt;
                std::cout << "Введите новую группу изделий (int): ";
                std::cin >> groupInt;
                kvitancia.intGroupName = groupInt;
                kvitancia.isInt = true;
            } else if (choice == 2) {
                char groupChar;
                std::cout << "Введите новую группу изделий (char): ";
                std::cin >> groupChar;
                kvitancia.charGroupName = groupChar;
                kvitancia.isInt = false;
            } else {
                std::cout << "Неверный выбор. Группа изделий не будет изменена." << std::endl;
                return;
            }

            std::cout << "Введите новую марку изделия: ";
            std::cin >> kvitancia.brand;
            std::cout << "Введите новую дату приемки в ремонт (ГГГГ-ММ-ДД): ";
            std::cin >> kvitancia.date;
            std::cout << "Введите новое состояние готовности заказа (1 - выполнен, 0 - не выполнен): ";
            int ready;
            std::cin >> ready;
            kvitancia.isReady = (ready == 1);
            std::cout << "Квитанция откорректирована." << std::endl;
            return;
        }
    }
    std::cout << "Квитанция не найдена." << std::endl;
}

// Функция для просмотра всех квитанций
void viewKvitancii(const std::vector<Kvitancia>& kvitancii) {
    for (const auto& kvitancia : kvitancii) {
        std::cout << "\033[1m\033[33mГруппа:       \033[0m" << (kvitancia.isInt ? std::to_string(kvitancia.intGroupName) : std::string(1, kvitancia.charGroupName)) << std::endl;
        std::cout << "\033[1m\033[33mБренд:        \033[0m" << kvitancia.brand << std::endl;
        std::cout << "\033[1m\033[33mДата:         \033[0m" << kvitancia.date << std::endl;
        std::cout << "\033[1m\033[33mГотовность:   \033[0m" << (kvitancia.isReady ? "\033[32mВыполнен\033[0m" : "\033[31mНе выполнен\033[0m") << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
    }
}

// Функция для сохранения данных в файл
void saveToFile(const std::vector<Kvitancia>& kvitancii, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& kvitancia : kvitancii) {
            file << (kvitancia.isInt ? std::to_string(kvitancia.intGroupName) : std::string(1, kvitancia.charGroupName)) << " "
                 << kvitancia.brand << " "
                 << kvitancia.date << " "
                 << (kvitancia.isReady ? "Выполнен" : "Не выполнен") << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
    }
}

// Функция для загрузки данных из файла
void loadFromFile(std::vector<Kvitancia>& kvitancii, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        kvitancii.clear();
        Kvitancia kvitancia;
        std::string groupName;
        std::string readyStatus;
        while (file >> groupName >> kvitancia.brand >> kvitancia.date >> readyStatus) {
            if (groupName.size() == 1 && std::isalpha(groupName[0])) {
                kvitancia.charGroupName = groupName[0];
                kvitancia.isInt = false;
            } else {
                kvitancia.intGroupName = std::stoi(groupName);
                kvitancia.isInt = true;
            }
            kvitancia.isReady = (readyStatus == "Выполнен");
            kvitancii.push_back(kvitancia);
        }
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

// Функция для корректировки или удаления квитанции прямо из файла
void editKvitanciaInFile(const std::string& filename) {
    std::vector<Kvitancia> kvitancii;
    loadFromFile(kvitancii, filename);

    std::string brand;
    std::cout << "Введите марку изделия для редактирования: ";
    std::cin >> brand;

    for (auto& kvitancia : kvitancii) {
        if (kvitancia.brand == brand) {
            int choice;
            std::cout << "Выберите действие (1 - корректировать, 2 - удалить): ";
            std::cin >> choice;

            if (choice == 1) {
                int typeChoice;
                std::cout << "Введите тип группы изделий (1 - int, 2 - char): ";
                std::cin >> typeChoice;

                if (typeChoice == 1) {
                    int groupInt;
                    std::cout << "Введите новую группу изделий (int): ";
                    std::cin >> groupInt;
                    kvitancia.intGroupName = groupInt;
                    kvitancia.isInt = true;
                } else if (typeChoice == 2) {
                    char groupChar;
                    std::cout << "Введите новую группу изделий (char): ";
                    std::cin >> groupChar;
                    kvitancia.charGroupName = groupChar;
                    kvitancia.isInt = false;
                } else {
                    std::cout << "Неверный выбор. Группа изделий не будет изменена." << std::endl;
                    return;
                }

                std::cout << "Введите новую марку изделия: ";
                std::cin >> kvitancia.brand;
                std::cout << "Введите новую дату приемки в ремонт (ГГГГ-ММ-ДД): ";
                std::cin >> kvitancia.date;
                std::cout << "Введите новое состояние готовности заказа (1 - выполнен, 0 - не выполнен): ";
                int ready;
                std::cin >> ready;
                kvitancia.isReady = (ready == 1);
                std::cout << "Квитанция откорректирована." << std::endl;
            } else if (choice == 2) {
                kvitancii.erase(std::remove_if(kvitancii.begin(), kvitancii.end(),
                                              [&](const Kvitancia& k) { return k.brand == brand; }),
                                kvitancii.end());
                std::cout << "Квитанция удалена." << std::endl;
            } else {
                std::cout << "Неверный выбор. Никаких изменений не внесено." << std::endl;
            }

            saveToFile(kvitancii, filename);
            return;
        }
    }
    std::cout << "Квитанция не найдена." << std::endl;
}

int main() {
    std::vector<Kvitancia> kvitancii;

    int choice;
    do {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить квитанцию" << std::endl;
        std::cout << "2. Удалить квитанцию" << std::endl;
        std::cout << "3. Откорректировать квитанцию" << std::endl;
        std::cout << "4. Просмотреть все квитанции" << std::endl;
        std::cout << "5. Сохранить в файл" << std::endl;
        std::cout << "6. Загрузить из файла" << std::endl;
        std::cout << "7. Редактировать квитанцию в файле" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addKvitancia(kvitancii);
                break;
            case 2:
                deleteKvitancia(kvitancii);
                break;
            case 3:
                correctKvitancia(kvitancii);
                break;
            case 4:
                viewKvitancii(kvitancii);
                break;
            case 5:
                saveToFile(kvitancii, "kvitancii.txt");
                break;
            case 6:
                loadFromFile(kvitancii, "kvitancii.txt");
                break;
            case 7:
                editKvitanciaInFile("kvitancii.txt");
                break;
            case 0:
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
