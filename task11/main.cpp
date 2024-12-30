#include "inventory.h"

void menu() {
    Product* inventory = nullptr;
    int size = 0;
    int choice;
    const char* targetName = "Exit";

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1.  Создать инвентарь\n";
        std::cout << "2.  Просмотреть инвентарь\n";
        std::cout << "3.  Добавить товар\n";
        std::cout << "4.  Поиск товара по цене\n";
        std::cout << "5.  Удалить товар\n";
        std::cout << "6.  Изменить товар\n";
        std::cout << "7.  Сортировать инвентарь\n";
        std::cout << "8.  Сохранить в файл\n";
        std::cout << "9.  Загрузить из файла\n";
        std::cout << "10. Изменить товар в файле\n";
        std::cout << "11. Скидки на товар\n";
        std::cout << "12. Поиск товара\n";
        std::cout << "0.  Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                inventory = createInventory(&size, targetName);
                break;
            case 2:
                viewInventory(inventory, size);
                break;
            case 3:
                inventory = addProducts(inventory, &size);
                break;
            case 4: {
                double minPrice;
                std::cout << "Введите минимальную цену: ";
                std::cin >> minPrice;
                searchProduct(inventory, size, minPrice);
                break;
            }
            case 5: {
                char name[50];
                std::cout << "Введите название товара для удаления: ";
                std::cin >> name;
                deleteProduct(inventory, &size, name);
                break;
            }
            case 6: {
                char name[50];
                std::cout << "Введите название товара для изменения: ";
                std::cin >> name;
                modifyProduct(inventory, size, name);
                break;
            }
            case 7:
                sortInventory(inventory, size);
                std::cout << "Инвентарь отсортирован по цене.\n";
                break;
            case 8:
                saveToFile(inventory, size);
                break;
            case 9:
                loadFromFile(&inventory, &size);
                break;
            case 10: {
                char name[50];
                std::cout << "Введите название товара для изменения в файле: ";
                std::cin >> name;
                modifyProductInFile(name);
                break;
            }
            case 11:
                inventory = modaddProduct(inventory, &size);
                break;
            case 12: {
                char name[50];
                std::cout << "Введите название товара для поиска: ";
                std::cin >> name;
                findAndDisplayProduct(inventory, size, name);
                break;
            }
            case 0:
                delete[] inventory;
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор, попробуйте снова.\n";
        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
