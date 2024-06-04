#include <iostream>
#include <string>

using namespace std;

class Contact {
private:
    string* fullName; // динамічна пам'ять для ПІБ
    string homePhone;
    string workPhone;
    string mobilePhone;
    string additionalInfo;

public:
    // Конструктор за замовчуванням
    Contact() : fullName(new string), homePhone(), workPhone(), mobilePhone(), additionalInfo() {}

    // Конструктор з параметрами
    Contact(const string& name, const string& home, const string& work, const string& mobile, const string& addInfo)
        : fullName(new string(name)), homePhone(home), workPhone(work), mobilePhone(mobile), additionalInfo(addInfo) {}

    // Деструктор
    ~Contact() {
        delete fullName;
    }

    // Функція для введення даних
    void input() {
        cout << "Введіть ПІБ: ";
        getline(cin, *fullName);
        cout << "Введіть домашній телефон: ";
        getline(cin, homePhone);
        cout << "Введіть робочий телефон: ";
        getline(cin, workPhone);
        cout << "Введіть мобільний телефон: ";
        getline(cin, mobilePhone);
        cout << "Введіть додаткову інформацію: ";
        getline(cin, additionalInfo);
    }

    // Функція для виведення даних
    void print() const {
        cout << "ПІБ: " << *fullName << endl;
        cout << "Домашній телефон: " << homePhone << endl;
        cout << "Робочий телефон: " << workPhone << endl;
        cout << "Мобільний телефон: " << mobilePhone << endl;
        cout << "Додаткова інформація: " << additionalInfo << endl;
    }

    // Функція для пошуку абонента за ПІБ
    bool search(const string& name) const {
        return *fullName == name;
    }

    // Функція для зміни даних абонента
    void edit() {
        string newName;
        cout << "Введіть нове ПІБ: ";
        getline(cin, newName);
        *fullName = newName;
        cout << "Введіть новий домашній телефон: ";
        getline(cin, homePhone);
        cout << "Введіть новий робочий телефон: ";
        getline(cin, workPhone);
        cout << "Введіть новий мобільний телефон: ";
        getline(cin, mobilePhone);
        cout << "Введіть нову додаткову інформацію: ";
        getline(cin, additionalInfo);
    }

    // Функція для збереження даних абонента в файл
    void saveToFile(ofstream& file) const {
        file << *fullName << endl;
        file << homePhone << endl;
        file << workPhone << endl;
        file << mobilePhone << endl;
        file << additionalInfo << endl;
    }

    // Функція для завантаження даних абонента з файлу
    void loadFromFile(ifstream& file) {
        getline(file, *fullName);
        getline(file, homePhone);
        getline(file, workPhone);
        getline(file, mobilePhone);
        getline(file, additionalInfo);
    }
};

int main() {
    // Створюємо об'єкт класу "Телефонна книга"
    Contact phoneBook[100];
    int numContacts = 0;

    // Меню програми
    while (true) {
        cout << "1. Додати нового абонента" << endl;
        cout << "2. Видалити абонента" << endl;
        cout << "3. Показати всіх абонентів" << endl;
        cout << "4. Зберегти дані в файл" << endl;
        cout << "5. Завантажити дані з файлу" << endl;
        cout << "6. Вихід" << endl;
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            phoneBook[numContacts].input();
            numContacts++;
            break;
        }
        case 2: {
            string name;
            cout << "Введіть ПІБ абонента для видалення: ";
            getline(cin, name);
            for (int i = 0; i < numContacts; i++) {
                if (phoneBook[i].search(name)) {
                    for (int j = i; j < numContacts - 1; j++) {
                        phoneBook[j] = phoneBook[j + 1];
                    }
                    numContacts--;
                    break;
                }
            }
            break;
        }
        case 3: {
            for (int i = 0; i < numContacts; i++) {
                phoneBook[i].print();
                cout << endl;
            }
            break;
        }
        case 4: {
            ofstream file("phonebook.txt");
            for (int i = 0; i < numContacts; i++) {
                phoneBook[i].saveToFile(file);
            }
            file.close();
            break;
        }
        case 5: {
            ifstream file("phonebook.txt");
            numContacts = 0;
            while (file) {
                phoneBook[numContacts].loadFromFile(file);
                numContacts++;
            }
            file.close();
            break;
        }
        case 6: {
            return 0;
        }
        default: {
            cout << "Неправильний вибір" << endl;
            break;
        }
        }
    }

    return 0;
}