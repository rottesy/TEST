#include <cstring>
#include <iostream>


using namespace std;

const char *kGreenColor = "\033[32m";
const char *kRedColor = "\033[31m";
const char *kWhiteColor = "\033[0m";

class Ancestor {
private:
  char *humanName = nullptr;

  // Запрет копирования и присваивания
  Ancestor(const Ancestor &) = delete;
  Ancestor &operator=(const Ancestor &) = delete;

protected:
  // Защищенный метод для безопасного доступа к имени
  const char *getName() const { return humanName; }

public:
  explicit Ancestor(const char *name) {
    if (name) {
      size_t len = strlen(name) + 1;
      humanName = new char[len];
      strcpy(humanName, name);
    }
  }

  virtual ~Ancestor() { delete[] humanName; }

  virtual void print() const = 0;

  // Виртуальный метод для клонирования (вместо конструктора копирования)
  virtual Ancestor *clone() const = 0;
};

class Kid : public Ancestor {
public:
  explicit Kid(const char *name) : Ancestor(name) {}

  void print() const override { cout << "Kid: " << getName() << endl; }

  Kid *clone() const override { return new Kid(getName()); }
};

class GrandSon : public Kid {
private:
  char *patronymic = nullptr;

public:
  GrandSon(const char *name, const char *pat) : Kid(name) {
    if (pat) {
      size_t len = strlen(pat) + 1;
      patronymic = new char[len];
      strcpy(patronymic, pat);
    }
  }

  ~GrandSon() override { delete[] patronymic; }

  void print() const override {
    cout << "GrandSon: " << getName() << " " << patronymic << endl;
  }

  GrandSon *clone() const override {
    return new GrandSon(getName(), patronymic);
  }
};

// Утилиты для ввода
int getNumber(const string &prompt, int min, int max) {
  int number;
  while (true) {
    cout << prompt << " (" << min << "-" << max << "): ";
    cin >> number;

    if (cin.fail() || number < min || number > max) {
      cin.clear();
      cin.ignore(10000, '\n');
      cout << kRedColor << "Error! Please enter a valid number." << kWhiteColor
           << endl;
    } else {
      cin.ignore();
      return number;
    }
  }
}

class FamilyProgram {
private:
  Ancestor **familyMembers;
  int size;
  int capacity;

  void expandMembers() {
    if (size < 0)
      size = 0;

    if (size + 1 >= capacity) {
      capacity = (capacity == 0) ? 2 : capacity * 2;
      Ancestor **newMembers = new Ancestor *[capacity];

      for (int i = 0; i < size; i++) {
        newMembers[i] = familyMembers[i];
      }

      delete[] familyMembers;
      familyMembers = newMembers;
    }
    size++;
  }

  void addMember() {
    expandMembers();

    cout << "\n=== ADD FAMILY MEMBER ===" << endl;
    cout << "1. Add Kid" << endl;
    cout << "2. Add GrandSon" << endl;

    int opt = getNumber("Choose type", 1, 2);

    char name[100];
    cout << "Enter name: ";
    cin.getline(name, 100);

    if (opt == 1) {
      familyMembers[size - 1] = new Kid(name);
    } else {
      char patronymic[100];
      cout << "Enter patronymic: ";
      cin.getline(patronymic, 100);
      familyMembers[size - 1] = new GrandSon(name, patronymic);
    }
  }

public:
  FamilyProgram() : familyMembers(nullptr), size(0), capacity(0) {}

  ~FamilyProgram() { clear(); }

  // Запрет копирования
  
  void addFamilyMember() {
    addMember();
    cout << kGreenColor << "Member added successfully!" << kWhiteColor << endl;
  }

  void showAllMembers() const {
    if (size == 0) {
      cout << kRedColor << "No family members!" << kWhiteColor << endl;
      return;
    }

    cout << "\n=== FAMILY MEMBERS ===" << endl;
    for (int i = 0; i < size; i++) {
      cout << i + 1 << ". ";
      familyMembers[i]->print(); // Полиморфный вызов!
    }
  }

  void clear() {
    for (int i = 0; i < size; i++) {
      delete familyMembers[i]; // Виртуальные деструкторы работают!
    }
    delete[] familyMembers;
    familyMembers = nullptr;
    size = capacity = 0;
  }

  void run() {
    system("clear");

    while (true) {
      cout << "\n=== FAMILY TREE ===" << endl;
      cout << "1. Add member" << endl;
      cout << "2. Show members" << endl;
      cout << "3. Exit" << endl;

      int opt = getNumber("Choose option", 1, 3);

      switch (opt) {
      case 1:
        addFamilyMember();
        break;
      case 2:
        showAllMembers();
        break;
      case 3:
        cout << kGreenColor << "Goodbye!" << kWhiteColor << endl;
        return;
      }
    }
  }
};

int main() {
  FamilyProgram program;
  program.run();
  return 0;
}