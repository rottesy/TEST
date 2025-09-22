#include <cstring>
#include <iostream>

using namespace std;

inline constexpr const int kMaxInt = 2147483647;
inline constexpr const int kMinInt = -2147483648;

int myStrlen(const char *str)
{
    if (str == nullptr)
    {
        return 0;
    }
    int len = 0;

    for (int ind = 0; str[ind] != '\0'; ind++)
    {
        len++;
    }

    return len;
}

class Ancestor
{
  private:
    char *humanName = nullptr;

  protected:
    [[nodiscard]] const char *getName() const { return humanName; }

  public:
    explicit Ancestor(const char *name)
    {
        humanName = new char[myStrlen(name) + 1];
        strcpy_s(humanName, myStrlen(name) + 1, name);
    }
    virtual ~Ancestor() { delete[] humanName; }
    virtual void print() const = 0;
};

class Kid : public Ancestor
{
  public:
    explicit Kid(const char *name) : Ancestor(name) {}
    void print() const override { cout << "Kid: " << getName() << "\n"; }
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
    void print() const override { cout << "GrandSon: " << getName() << " " << patronymic << "\n"; }
};

int getNumber(const char *msg)
{
    int num = 0;

    std::cout << msg;

    while (true)
    {
        if (std::cin.peek() == '\n' || std::cin.peek() == ' ' || std::cin.fail())
        {
            std::cin.clear();
            while (std::cin.get() != '\n' && !std::cin.eof())
                ;
            std::cout << "\nError, invalid input. Please try again: ";
            continue;
        }
        if ((std::cin >> num).good() && std::cin.get() == '\n' && (kMinInt <= num) && (num <= kMaxInt))
        {
            return num;
        }
    }
}

class FamilyProgram
{
  private:
    Ancestor **familyMemebrs = nullptr;
    int size = 0;
    int capacity = 0;

    void expandMembers()
    {
        if (size < 0)
        {
            size = 0;
        }
        if (size + 1 >= capacity)
        {
            capacity = (capacity == 0) ? 2 : capacity * 2;
            auto **newMembers = new Ancestor *[capacity];
            for (int i = 0; i < size; i++)
            {
                newMembers[i] = familyMemebrs[i];
            }
            delete[] familyMemebrs;
            familyMemebrs = newMembers;
        }
        size++;
    }

    void addMember()
    {
        expandMembers();

        cout << "\n=== ADD FAMILY MEMBER ===" << "\n";
        cout << "1. Add Kid" << "\n";
        cout << "2. Add GrandSon" << "\n";

        int opt = getNumber("Choose type: ");

        auto *name = new char[100];
        cout << "Enter name: ";
        cin.getline(name, 100);

        if (myStrlen(name) == 0)
        {
            cout << "Error: Name cannot be empty!" << "\n";
            size--;
            return;
        }

        switch (opt)
        {
            case 1:
                familyMemebrs[size - 1] = new Kid(name);
                delete[] name;
                break;

            case 2:
            {
                auto *patronymic = new char[100];
                cout << "Enter patronymic: ";
                cin.getline(patronymic, 100);

                familyMemebrs[size - 1] = new GrandSon(name, patronymic);
                delete[] name;
                delete[] patronymic;
                break;
            }

            default:
                delete[] name;
                size--;
                cout << "Error: Invalid option!" << "\n";
                break;
        }
    }

  public:
    FamilyProgram() = default;
    ~FamilyProgram() { clear(); }

    void addFamilyMember() { addMember(); }

    void showAllMembers() const
    {
        if (size == 0)
        {
            cout << "No family members!" << "\n";
            return;
        }
        cout << "\n=== FAMILY MEMBERS ===" << "\n";
        for (int i = 0; i < size; i++)
        {
            cout << i + 1 << ". ";
            familyMemebrs[i]->print();
        }
    }

    void clear()
    {
        for (int i = 0; i < size; i++)
        {
            delete familyMemebrs[i];
        }
        delete[] familyMemebrs;
        familyMemebrs = nullptr;
        size = capacity = 0;
    }

    void run()
    {

        while (true)
        {
            cout << "\n=== FAMILY TREE ===" << "\n";
            cout << "1. Add member" << "\n";
            cout << "2. Show members" << "\n";
            cout << "3. Exit" << "\n";

            int opt = getNumber("Choose option: ");

            switch (opt)
            {
                case 1:
                    addFamilyMember();
                    break;
                case 2:
                    showAllMembers();
                    break;
                case 3:
                    cout << "Goodbye!" << "\n";
                    return;
                default:
                    cout << "Error: Invalid menu option!" << "\n";
                    break;
            }
        }
    }
};

int main()
{
    FamilyProgram program;
    program.run();
    return 0;
}