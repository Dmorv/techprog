#include <iostream>
#include <string>

using namespace std;

class ItemNode {
public:
    int cost;
    double quantity;
    string name;
    ItemNode* next;

    ItemNode(int cost, double quantity, string name) 
        : cost(cost), quantity(quantity), name(name), next(nullptr) {}
};

class InventoryList {
private:
    ItemNode* head;

public:
    InventoryList() : head(nullptr) {}

    ~InventoryList() {
        clearInventory();
    }

    // Вывод всего инвентаря
    void display() const {
        if (head == nullptr) {
            cout << "Inventory is empty.\n";
            return;
        }

        ItemNode* current = head;
        cout << "========== INVENTORY ==========\n";
        while (current != nullptr) {
            cout << "| " << current->name << " | "
                 << "Cost: $" << current->cost << " | "
                 << "Qty: " << current->quantity << " |\n";
            current = current->next;
        }
        cout << "================================\n\n";
    }

    // Добавление в конец списка
    void appendItem(int cost, double quantity, string name) {
        ItemNode* newItem = new ItemNode(cost, quantity, name);
        
        if (head == nullptr) {
            head = newItem;
        } else {
            ItemNode* last = head;
            while (last->next != nullptr) {
                last = last->next;
            }
            last->next = newItem;
        }
    }

    // Добавление в начало списка
    void prependItem(int cost, double quantity, string name) {
        ItemNode* newItem = new ItemNode(cost, quantity, name);
        newItem->next = head;
        head = newItem;
    }

    // Добавление после указанного индекса
    void insertAfter(int index, int cost, double quantity, string name) {
        ItemNode* current = head;
        int count = 0;

        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }

        if (current == nullptr) {
            cout << "Error: Index out of bounds.\n";
            return;
        }

        ItemNode* newItem = new ItemNode(cost, quantity, name);
        newItem->next = current->next;
        current->next = newItem;
    }

    // Добавление перед указанным названием
    void insertBefore(string targetName, int cost, double quantity, string name) {
        if (head == nullptr) return;

        if (head->name == targetName) {
            prependItem(cost, quantity, name);
            return;
        }

        ItemNode* prev = head;
        while (prev->next != nullptr && prev->next->name != targetName) {
            prev = prev->next;
        }

        if (prev->next != nullptr) {
            ItemNode* newItem = new ItemNode(cost, quantity, name);
            newItem->next = prev->next;
            prev->next = newItem;
        } else {
            cout << "Item '" << targetName << "' not found.\n";
        }
    }

    // Удаление по стоимости
    void removeByCost(int targetCost) {
        if (head == nullptr) return;

        if (head->cost == targetCost) {
            ItemNode* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }

        ItemNode* prev = head;
        while (prev->next != nullptr && prev->next->cost != targetCost) {
            prev = prev->next;
        }

        if (prev->next == nullptr) {
            cout << "Item with cost $" << targetCost << " not found.\n";
        } else {
            ItemNode* toDelete = prev->next;
            prev->next = prev->next->next;
            delete toDelete;
        }
    }

private:
    // Очистка всей памяти
    void clearInventory() {
        ItemNode* current = head;
        while (current != nullptr) {
            ItemNode* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
};

int main() {
    InventoryList inventory;

    // Добавляем элементы разными способами
    inventory.appendItem(3, 90, "Tango");
    inventory.insertBefore("Tango", 5, 1900, "Mask of Madness");
    inventory.prependItem(69, 4950, "Butterfly");
    inventory.insertAfter(1, 33, 5650, "Abyssal Blade");

    // Выводим инвентарь
    cout << "Initial inventory:\n";
    inventory.display();

    // Удаляем элемент и снова выводим
    inventory.removeByCost(69);
    cout << "After removing Butterfly (cost $69):\n";
    inventory.display();

    return 0;
}