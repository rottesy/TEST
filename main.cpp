#include <cstring>
#include <iostream>

using namespace std;

int myStrlen(const char *str) {
  if (str == nullptr) {
    return 0;
  }
  int len = 0;

  for (int ind = 0; str[ind] != '\0'; ind++) {
    len++;
  }

  return len;
}

class Ancestor {
private:
  char *humanName = nullptr;

public:
  explicit Ancestor(const char *name) {
    humanName = new char[myStrlen(name) + 1];
    strcpy_s(humanName, myStrlen(name) + 1, name);
  }
  virtual ~Ancestor() { delete[] humanName; }
  virtual void print() const = 0;
  [[nodiscard]] char *getName() const { return humanName; }
};

class Kid : public Ancestor {
public:
  explicit Kid(const char *name) : Ancestor(name) {}
  void print() const override { cout << "Kid : " << getName() << "\n"; }
};

class GrandSon : public Kid {
private:
  char *patronymic = nullptr;

public:
  GrandSon(const char *name, const char *pat) : Kid(name) {
    patronymic = new char[myStrlen(pat) + 1];
    strcpy_s(patronymic, myStrlen(pat) + 1, pat);
  }
  ~GrandSon() override { delete[] patronymic; }
  void print() const override {
    cout << "GrandSon : " << getName() << " " << patronymic << "\n";
  }
};

// Функция для получения числа от пользователя
int getNumber(const char *prompt) {
  if (prompt && strlen(prompt) > 0) {
    cout << prompt;
  }
  int number;
  cin >> number;
  cin.ignore(); // Очищаем буфер после ввода числа
  return number;
}

// Функция для получения строки от пользователя
void getString(char *&dest, const char *prompt) {
  if (prompt) {
    cout << prompt;
  }
  char buffer[100];
  cin.getline(buffer, 100);
  dest = new char[strlen(buffer) + 1];
  strcpy_s(dest, strlen(buffer) + 1, buffer);
}

// Меню работы с Предком
void showAncestorMenu() {
  cout << "\n=== ANCESTOR OPERATIONS ===" << "\n";
  cout << "1. Create Kid" << "\n";
  cout << "2. Create GrandSon" << "\n";
  cout << "3. Show all objects" << "\n";
  cout << "0. Back to main menu" << "\n";
  cout << "Choose option: ";
}

// Меню создания объектов
void showCreateMenu() {
  cout << "\n=== CREATE OBJECT ===" << "\n";
  cout << "1. Create Kid" << "\n";
  cout << "2. Create GrandSon" << "\n";
  cout << "0. Back" << "\n";
  cout << "Choose option: ";
}

// Главное меню
void showMainMenu() {
  cout << "\n=== FAMILY TREE MENU ===" << "\n";
  cout << "1. Work with Ancestors" << "\n";
  cout << "2. Show all objects" << "\n";
  cout << "0. Exit" << "\n";
  cout << "Choose option: ";
}

// Обработка операций с предками
void handleAncestorOperations(Ancestor **&objects, int &count) {
  int choice;
  do {
    showAncestorMenu();
    choice = getNumber("");

    switch (choice) {
    case 1: // Create Kid
    {
      char *name = nullptr;
      getString(name, "Enter Kid's name: ");

      // Увеличиваем массив объектов
      auto **newObjects = new Ancestor *[count + 1];
      for (int i = 0; i < count; i++) {
        newObjects[i] = objects[i];
      }
      newObjects[count] = new Kid(name);
      delete[] objects;
      objects = newObjects;
      count++;

      delete[] name;
      cout << "Kid created successfully!\n";
      break;
    }

    case 2: // Create GrandSon
    {
      char *name = nullptr;
      char *patronymic = nullptr;

      getString(name, "Enter GrandSon's name: ");
      getString(patronymic, "Enter GrandSon's patronymic: ");

      // Увеличиваем массив объектов
      auto **newObjects = new Ancestor *[count + 1];
      for (int i = 0; i < count; i++) {
        newObjects[i] = objects[i];
      }
      newObjects[count] = new GrandSon(name, patronymic);
      delete[] objects;
      objects = newObjects;
      count++;

      delete[] name;
      delete[] patronymic;
      cout << "GrandSon created successfully!\n";
      break;
    }

    case 3: // Show all objects
    {
      if (count == 0) {
        cout << "No objects created yet!\n";
      }

      cout << "\n=== ALL OBJECTS ===\n";
      for (int i = 0; i < count; i++) {
        objects[i]->print();
      }
      break;
    }

    case 0:
      break;

    default:
      cout << "Invalid choice!\n";
    }
  } while (choice != 0);
}

// Главная функция обработки меню
void handleMainMenu() {
  Ancestor **objects = nullptr;
  int objectCount = 0;
  int choice;

  do {
    showMainMenu();
    choice = getNumber("");

    switch (choice) {
    case 1:
      handleAncestorOperations(objects, objectCount);
      break;

    case 2:
      if (objectCount == 0) {
        cout << "No objects created yet!\n";
      }
      cout << "\n=== ALL OBJECTS ===\n";
      for (int i = 0; i < objectCount; i++) {
        objects[i]->print();
      }
      break;

    case 0:
      cout << "Exiting program...\n";
      break;

    default:
      cout << "Invalid choice! Please try again.\n";
    }
  } while (choice != 0);

  // Очистка памяти
  for (int i = 0; i < objectCount; i++) {
    delete objects[i];
  }
  delete[] objects;
}

int main() {
  handleMainMenu();
  return 0;
}