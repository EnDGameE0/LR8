#include "inventory.h"

Product* createInventory(int* size, const char* targetName) {
    std::cout << "Введите количество товаров: ";
    std::cin >> *size;
    Product* inventory = new Product[*size];

    for (int i = 0; i < *size; i++) {
        std::cout << "\n\033[1m\033[33mТовар " << i + 1 << "\033[0m" << std::endl;
        std::cout << "Введите название товара: ";
        std::cin >> inventory[i].name;

        if (strcmp(inventory[i].name, targetName) == 0) {
            std::cout << "Структура с заданным признаком найдена. Ввод завершен.\n";
            *size = i + 1;
            return inventory;
        }

        std::cout << "Введите количество: ";
        std::cin >> inventory[i].quantity;
        std::cout << "Введите цену: ";
        std::cin >> inventory[i].price;
        std::cout << "Введите дату поступления (YYYY-MM-DD): ";
        std::cin >> inventory[i].date;
    }

    return inventory;
}

void findAndDisplayProduct(Product* inventory, int size, const char* name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            std::cout << "\n\033[1m\033[33mТовар найден:\033[0m\n";
            std::cout << "\n\033[1mНазвание:     \033[0m" << inventory[i].name
                      << "\n\033[1mКоличество:   \033[0m" << inventory[i].quantity
                      << "\n\033[1mЦена:         \033[0m" << inventory[i].price
                      << "\n\033[1mДата:         \033[0m" << inventory[i].date
                      << "\n";
            return;
        }
    }
    std::cout << "Товар не найден.\n";
}

void viewInventory(Product* inventory, int size) {
    std::cout << "\nСписок товаров:\n";
    for (int i = 0; i < size; i++) {
        std::cout << "\n\033[1m\033[33mТовар " << i + 1 << "\033[0m";
        std::cout << "\n\033[1mНазвание:     \033[0m" << inventory[i].name
                  << "\n\033[1mКоличество:   \033[0m" << inventory[i].quantity
                  << "\n\033[1mЦена:         \033[0m" << inventory[i].price
                  << "\n\033[1mДата:         \033[0m" << inventory[i].date
                  << "\n";
    }
}

Product* addProducts(Product* inventory, int* size) {
    int newSize = *size + 1;
    Product* newInventory = new Product[newSize];
    for (int i = 0; i < *size; i++) {
        newInventory[i] = inventory[i];
    }
    delete[] inventory;

    std::cout << "Введите название нового товара: ";
    std::cin >> newInventory[*size].name;
    std::cout << "Введите количество: ";
    std::cin >> newInventory[*size].quantity;
    std::cout << "Введите цену: ";
    std::cin >> newInventory[*size].price;
    std::cout << "Введите дату поступления (YYYY-MM-DD): ";
    std::cin >> newInventory[*size].date;

    *size = newSize;
    return newInventory;
}

double calculatePrice(const char* date) {
    int year = std::stoi(std::string(date).substr(0, 4)); // Извлекаем первые 4 символа для года
    int currentYear = 2024;

    return currentYear - year; // Возвращаем разницу между текущим годом и годом выпуска
}

Product* modaddProduct(Product* inventory, int* size) {
    int newSize = *size + 1;
    Product* newInventory = new Product[newSize];
    for (int i = 0; i < *size; i++) {
        newInventory[i] = inventory[i];
    }
    delete[] inventory;

    std::cout << "Введите название нового товара: ";
    std::cin >> newInventory[*size].name;
    std::cout << "Введите количество: ";
    std::cin >> newInventory[*size].quantity;
    std::cout << "Введите дату поступления (YYYY-MM-DD): ";
    std::cin >> newInventory[*size].date;
    newInventory[*size].price = calculatePrice(newInventory[*size].date);
    std::cout << "Акция! Всем товарам, которым больше года (или год) стоят столько же, сколько они и существуют! Ваша цена: " << newInventory[*size].price << std::endl;

    *size = newSize;
    return newInventory;
}

void searchProduct(Product* inventory, int size, double minPrice) {
    std::cout << "\nТовары с ценой выше " << minPrice << ":\n";
    for (int i = 0; i < size; i++) {
        if (inventory[i].price > minPrice) {
            std::cout << "\n\033[1m\033[33mТовар " << i + 1 << "\033[0m";
            std::cout << "\n\033[1mНазвание:     \033[0m" << inventory[i].name
                      << "\n\033[1mКоличество:   \033[0m" << inventory[i].quantity
                      << "\n\033[1mЦена:         \033[0m" << inventory[i].price
                      << "\n\033[1mДата:         \033[0m" << inventory[i].date
                      << "\n";
        }
    }
}

void deleteProduct(Product* inventory, int* size, const char* name) {
    for (int i = 0; i < *size; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            for (int j = i; j < *size - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            (*size)--;
            Product* newInventory = new Product[*size];
            for (int k = 0; k < *size; k++) {
                newInventory[k] = inventory[k];
            }
            delete[] inventory;
            inventory = newInventory;
            std::cout << "Товар " << name << " удален.\n";
            return;
        }
    }
    std::cout << "Товар не найден.\n";
}

void modifyProduct(Product* inventory, int size, const char* name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            std::cout << "Введите новое количество: ";
            std::cin >> inventory[i].quantity;
            std::cout << "Введите новую цену: ";
            std::cin >> inventory[i].price;
            std::cout << "Введите новую дату поступления (YYYY-MM-DD): ";
            std::cin >> inventory[i].date;
            std::cout << "Товар " << name << " изменен.\n";
            return;
        }
    }
    std::cout << "Товар не найден.\n";
}

void sortInventory(Product* inventory, int size) {
    for (int i = 1; i < size; i++) {
        Product key = inventory[i];
        int j = i - 1;

        while (j >= 0 && inventory[j].price < key.price) {
            inventory[j + 1] = inventory[j];
            j = j - 1;
        }
        inventory[j + 1] = key;
    }
}

void saveToFile(Product* inventory, int size) {
    std::ofstream file("inventory.dat", std::ios::binary);
    if (file) {
        file.write(reinterpret_cast<const char*>(inventory), size * sizeof(Product));
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл для записи.\n";
    }
}

void loadFromFile(Product** inventory, int* size) {
    std::ifstream file("inventory.dat", std::ios::binary);
    if (file) {
        file.seekg(0, std::ios::end);
        *size = file.tellg() / sizeof(Product);
        file.seekg(0, std::ios::beg);
        *inventory = new Product[*size];
        file.read(reinterpret_cast<char*>(*inventory), *size * sizeof(Product));
        file.close();
    } else {
        *size = 0;
        *inventory = nullptr;
    }
}

void modifyProductInFile(const char* name) {
    std::fstream file("inventory.dat", std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        std::cerr << "Не удалось открыть файл для чтения/записи.\n";
        return;
    }

    Product product;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (strcmp(product.name, name) == 0) {
            found = true;
            std::cout << "Введите новое количество: ";
            std::cin >> product.quantity;
            std::cout << "Введите новую цену: ";
            std::cin >> product.price;
            std::cout << "Введите новую дату поступления (YYYY-MM-DD): ";
            std::cin >> product.date;

            file.seekp(-static_cast<std::streamoff>(sizeof(Product)), std::ios::cur);
            file.write(reinterpret_cast<const char*>(&product), sizeof(Product));
            std::cout << "Товар " << name << " изменен в файле.\n";
            break;
        }
    }

    if (!found) {
        std::cout << "Товар не найден.\n";
    }

    file.close();
}
