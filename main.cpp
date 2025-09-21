// #include <cstring>
// #include <iostream>

// inline constexpr const int kMaxInt = 2147483647;
// inline constexpr const int kMinInt = -2147483648;

// using namespace std;

// int myStrlen(const char *str) {
//   if (str == nullptr) {
//     return 0;
//   }
//   int len = 0;

//   for (int ind = 0; str[ind] != '\0'; ind++) {
//     len++;
//   }

//   return len;
// }

// class Ancestor {
// private:
//   char *humanName = nullptr;

// public:
//   explicit Ancestor(const char *name) {
//     humanName = new char[myStrlen(name) + 1];
//     strcpy_s(humanName, myStrlen(name) + 1, name);
//   }
//   virtual ~Ancestor() { delete[] humanName; }
//   virtual void print() const = 0;
//   [[nodiscard]] char *getName() const { return humanName; }
// };

// class Kid : public Ancestor {
// public:
//   explicit Kid(const char *name) : Ancestor(name) {}
//   void print() const override { cout << "Kid : " << getName() << "\n"; }
// };

// class GrandSon : public Kid {
// private:
//   char *patronymic = nullptr;

// public:
//   GrandSon(const char *name, const char *pat) : Kid(name) {
//     patronymic = new char[myStrlen(pat) + 1];
//     strcpy_s(patronymic, myStrlen(pat) + 1, pat);
//   }
//   ~GrandSon() override { delete[] patronymic; }
//   void print() const override {
//     cout << "GrandSon : " << getName() << " " << patronymic << "\n";
//   }
// };

// // Функция для получения числа от пользователя
// int getNumber(const char *msg)
// {
//     int num = 0;

//     std::cout << msg;

//     while (true)
//     {
//         if (std::cin.peek() == '\n' || std::cin.peek() == ' ' || std::cin.fail())
//         {
//             std::cin.clear();
//             while (std::cin.get() != '\n' && !std::cin.eof())
//                 ;
//             std::cout << "\nError, invalid input. Please try again: ";
//             continue;
//         }
//         if ((std::cin >> num).good() && std::cin.get() == '\n' && (kMinInt <= num) && (num <= kMaxInt))
//         {
//             return num;
//         }
//     }
// }

// // Функция для получения строки от пользователя
// void getString(char *&dest, const char *prompt) {
//   if (prompt) {
//     cout << prompt;
//   }
//   char buffer[100];
//   cin.getline(buffer, 100);
//   dest = new char[myStrlen(buffer) + 1];
//   strcpy_s(dest, myStrlen(buffer) + 1, buffer);
// }

// // Меню работы с Предком
// void showAncestorMenu() {
//   cout << "\n=== ANCESTOR OPERATIONS ===" << "\n";
//   cout << "1. Create Kid" << "\n";
//   cout << "2. Create GrandSon" << "\n";
//   cout << "3. Show all objects" << "\n";
//   cout << "0. Back to main menu" << "\n";
//   cout << "Choose option: ";
// }

// // Меню создания объектов
// void showCreateMenu() {
//   cout << "\n=== CREATE OBJECT ===" << "\n";
//   cout << "1. Create Kid" << "\n";
//   cout << "2. Create GrandSon" << "\n";
//   cout << "0. Back" << "\n";
//   cout << "Choose option: ";
// }

// // Главное меню
// void showMainMenu() {
//   cout << "\n=== FAMILY TREE MENU ===" << "\n";
//   cout << "1. Work with Ancestors" << "\n";
//   cout << "2. Show all objects" << "\n";
//   cout << "0. Exit" << "\n";
//   cout << "Choose option: ";
// }

// // Обработка операций с предками
// void handleAncestorOperations(Ancestor **&objects, int &count) {
//   int choice;
//   do {
//     showAncestorMenu();
//     choice = getNumber("");

//     switch (choice) {
//     case 1: // Create Kid
//     {
//       char *name = nullptr;
//       getString(name, "Enter Kid's name: ");

//       // Увеличиваем массив объектов
//       auto **newObjects = new Ancestor *[count + 1];
//       for (int i = 0; i < count; i++) {
//         newObjects[i] = objects[i];
//       }
//       newObjects[count] = new Kid(name);
//       delete[] objects;
//       objects = newObjects;
//       count++;

//       delete[] name;
//       cout << "Kid created successfully!\n";
//       break;
//     }

//     case 2: // Create GrandSon
//     {
//       char *name = nullptr;
//       char *patronymic = nullptr;

//       getString(name, "Enter GrandSon's name: ");
//       getString(patronymic, "Enter GrandSon's patronymic: ");

//       // Увеличиваем массив объектов
//       auto **newObjects = new Ancestor *[count + 1];
//       for (int i = 0; i < count; i++) {
//         newObjects[i] = objects[i];
//       }
//       newObjects[count] = new GrandSon(name, patronymic);
//       delete[] objects;
//       objects = newObjects;
//       count++;

//       delete[] name;
//       delete[] patronymic;
//       cout << "GrandSon created successfully!\n";
//       break;
//     }

//     case 3: // Show all objects
//     {
//       if (count == 0) {
//         cout << "No objects created yet!\n";
//       }

//       cout << "\n=== ALL OBJECTS ===\n";
//       for (int i = 0; i < count; i++) {
//         objects[i]->print();
//       }
//       break;
//     }

//     case 0:
//       break;

//     default:
//       cout << "Invalid choice!\n";
//     }
//   } while (choice != 0);
// }

// // Главная функция обработки меню
// void handleMainMenu() {
//   Ancestor **objects = nullptr;
//   int objectCount = 0;
//   int choice;

//   do {
//     showMainMenu();
//     choice = getNumber("");

//     switch (choice) {
//     case 1:
//       handleAncestorOperations(objects, objectCount);
//       break;

//     case 2:
//       if (objectCount == 0) {
//         cout << "No objects created yet!\n";
//       }
//       cout << "\n=== ALL OBJECTS ===\n";
//       for (int i = 0; i < objectCount; i++) {
//         objects[i]->print();
//       }
//       break;

//     case 0:
//       cout << "Exiting program...\n";
//       break;

//     default:
//       cout << "Invalid choice! Please try again.\n";
//     }
//   } while (choice != 0);

//   // Очистка памяти
//   for (int i = 0; i < objectCount; i++) {
//     delete objects[i];
//   }
//   delete[] objects;
// }

// int main() {
//   handleMainMenu();
//   return 0;
// }

#include <cstring>
#include <iostream>

using namespace std;

int myStrlen(const char *str)
{
    if (str == nullptr) return 0;
    int len = 0;
    for (int ind = 0; str[ind] != '\0'; ind++) len++;
    return len;
}

class Ancestor
{
  private:
    char *humanName = nullptr;

  protected:
    void setName(const char *name)
    {
        delete[] humanName;
        humanName = new char[myStrlen(name) + 1];
        strcpy_s(humanName, myStrlen(name) + 1, name);
    }

  public:
    explicit Ancestor(const char *name) { setName(name); }
    virtual ~Ancestor() { delete[] humanName; }
    virtual void print() const = 0;
    const char* getName() const { return humanName; }
};

class Kid : public Ancestor
{
  public:
    explicit Kid(const char *name) : Ancestor(name) {}
    void print() const override 
    { 
        cout << "Kid - Name: " << getName() << "\n"; 
    }
};

class GrandSon : public Kid
{
  private:
    char *patronymic = nullptr;

  public:
    GrandSon(const char *name, const char *pat) : Kid(name)
    {
        patronymic = new char[myStrlen(pat) + 1];
        strcpy_s(patronymic, myStrlen(pat) + 1, pat);
    }
    ~GrandSon() override { delete[] patronymic; }
    void print() const override 
    { 
        cout << "GrandSon - Name: " << getName() 
             << ", Patronymic: " << patronymic << "\n"; 
    }
};


class AncestorCreator
{
public:
    virtual ~AncestorCreator() = default;
    virtual Ancestor* create() const = 0;
    virtual const char* getTypeName() const = 0;
};


class KidCreator : public AncestorCreator
{
public:
    Ancestor* create() const override
    {
        char name[100];
        cout << "Enter Kid's name: ";
        cin.getline(name, 100);
        return new Kid(name);
    }
    const char* getTypeName() const override { return "Kid"; }
};

class GrandSonCreator : public AncestorCreator
{
public:
    Ancestor* create() const override
    {
        char name[100], patronymic[100];
        cout << "Enter GrandSon's name: ";
        cin.getline(name, 100);
        cout << "Enter GrandSon's patronymic: ";
        cin.getline(patronymic, 100);
        return new GrandSon(name, patronymic);
    }
    const char* getTypeName() const override { return "GrandSon"; }
};


class AncestorCollection
{
private:
    Ancestor** ancestors;
    int capacity;
    int size;

    void resize()
    {
        capacity *= 2;
        Ancestor** newAncestors = new Ancestor*[capacity];
        for (int i = 0; i < size; i++)
        {
            newAncestors[i] = ancestors[i];
        }
        delete[] ancestors;
        ancestors = newAncestors;
    }

public:
    AncestorCollection() : capacity(10), size(0)
    {
        ancestors = new Ancestor*[capacity];
    }

    ~AncestorCollection()
    {
        for (int i = 0; i < size; i++)
        {
            delete ancestors[i];
        }
        delete[] ancestors;
    }

    void add(Ancestor* ancestor)
    {
        if (size >= capacity) resize();
        ancestors[size++] = ancestor;
    }

    void printAll() const
    {
        if (size == 0)
        {
            cout << "No ancestors created yet!\n";
            return;
        }
        
        cout << "\n=== ALL ANCESTORS ===\n";
        for (int i = 0; i < size; i++)
        {
            ancestors[i]->print();
        }
    }

    int getSize() const { return size; }
};


void showMainMenu()
{
    cout << "\n=== FAMILY TREE MENU ===\n";
    cout << "1. Create new ancestor\n";
    cout << "2. Show all ancestors\n";
    cout << "0. Exit\n";
    cout << "Choose option: ";
}

void showCreationMenu(AncestorCreator** creators, int creatorCount)
{
    cout << "\n=== CREATE ANCESTOR ===\n";
    for (int i = 0; i < creatorCount; i++)
    {
        cout << i + 1 << ". Create " << creators[i]->getTypeName() << "\n";
    }
    cout << "0. Back\n";
    cout << "Choose option: ";
}

int getNumber(const char* prompt = "")
{
    if (prompt[0] != '\0') cout << prompt;
    int number;
    cin >> number;
    cin.ignore();
    return number;
}

void handleMainMenu()
{
    
    AncestorCreator* creators[] = {
        new KidCreator(),
        new GrandSonCreator()
    };
    const int creatorCount = 2;
    
    AncestorCollection collection;
    int choice;

    do
    {
        showMainMenu();
        choice = getNumber();

        switch (choice)
        {
            case 1: 
            {
                int createChoice;
                do
                {
                    showCreationMenu(creators, creatorCount);
                    createChoice = getNumber();
                    
                    if (createChoice > 0 && createChoice <= creatorCount)
                    {
                        Ancestor* newAncestor = creators[createChoice - 1]->create();
                        collection.add(newAncestor);
                        cout << creators[createChoice - 1]->getTypeName() 
                             << " created successfully!\n";
                    }
                    else if (createChoice != 0)
                    {
                        cout << "Invalid choice!\n";
                    }
                } while (createChoice != 0);
                break;
            }
                
            case 2: 
                collection.printAll();
                break;
                
            case 0:
                cout << "Exiting program...\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    for (int i = 0; i < creatorCount; i++)
    {
        delete creators[i];
    }
}

int main()
{
    handleMainMenu();
    return 0;
}