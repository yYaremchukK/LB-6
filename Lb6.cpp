#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Структура для зберігання інформації про товар
struct Product {
    string name;
    int quantity;
    double price;
};

// Функція для додавання товару
void addProduct(vector<Product>& inventory, const string& name, int quantity, double price) {
    inventory.push_back({name, quantity, price});
    cout << "Товар \"" << name << "\" додано до складу." << endl;
}

// Функція для видалення товару за назвою
void deleteProduct(vector<Product>& inventory, const string& name) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->name == name) {
            inventory.erase(it);
            cout << "Товар \"" << name << "\" видалено зі складу." << endl;
            return;
        }
    }
    cout << "Товар \"" << name << "\" не знайдено." << endl;
}

// Функція для оновлення кількості товару
void updateQuantity(vector<Product>& inventory, const string& name, int quantity) {
    for (auto& product : inventory) {
        if (product.name == name) {
            product.quantity += quantity;
            if (product.quantity < 0) product.quantity = 0; // Запобігання від'ємній кількості
            cout << "Кількість товару \"" << name << "\" оновлено. Нова кількість: " << product.quantity << endl;
            return;
        }
    }
    cout << "Товар \"" << name << "\" не знайдено." << endl;
}

// Функція для показу всіх товарів
void displayProducts(const vector<Product>& inventory) {
    if (inventory.empty()) {
        cout << "Склад порожній." << endl;
        return;
    }

    cout << left << setw(20) << "Назва"
         << setw(10) << "Кількість"
         << setw(10) << "Ціна"
         << endl;
    cout << string(40, '-') << endl;

    for (const auto& product : inventory) {
        cout << left << setw(20) << product.name
             << setw(10) << product.quantity
             << setw(10) << fixed << setprecision(2) << product.price
             << endl;
    }
}

// Функція для розрахунку загальної вартості товарів
double calculateTotalValue(const vector<Product>& inventory) {
    double totalValue = 0.0;
    for (const auto& product : inventory) {
        totalValue += product.quantity * product.price;
    }
    return totalValue;
}

int main() {
    vector<Product> inventory;
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Додати товар\n";
        cout << "2. Видалити товар\n";
        cout << "3. Оновити кількість товару\n";
        cout << "4. Показати всі товари\n";
        cout << "5. Розрахувати загальну вартість\n";
        cout << "6. Вийти\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int quantity;
                double price;
                cout << "Введіть назву товару: ";
                cin.ignore();
                getline(cin, name);
                cout << "Введіть кількість: ";
                cin >> quantity;
                cout << "Введіть ціну: ";
                cin >> price;
                addProduct(inventory, name, quantity, price);
                break;
            }
            case 2: {
                string name;
                cout << "Введіть назву товару для видалення: ";
                cin.ignore();
                getline(cin, name);
                deleteProduct(inventory, name);
                break;
            }
            case 3: {
                string name;
                int quantity;
                cout << "Введіть назву товару для оновлення кількості: ";
                cin.ignore();
                getline(cin, name);
                cout << "Введіть зміну кількості (може бути від’ємною): ";
                cin >> quantity;
                updateQuantity(inventory, name, quantity);
                break;
            }
            case 4:
                displayProducts(inventory);
                break;
            case 5: {
                double totalValue = calculateTotalValue(inventory);
                cout << "Загальна вартість товарів на складі: " << fixed << setprecision(2) << totalValue << " грн." << endl;
                break;
            }
            case 6:
                cout << "Програма завершена. До побачення!" << endl;
                break;
            default:
                cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    } while (choice != 6);

    return 0;
}
