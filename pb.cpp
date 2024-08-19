#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_NAME_LENGTH 20
#define MAX_NUMBER_LENGTH 15

class Contact {
public:
    char name[MAX_NAME_LENGTH];
    char number[MAX_NUMBER_LENGTH];

    Contact(const char* name, const char* number) {
        strncpy(this->name, name, MAX_NAME_LENGTH);
        strncpy(this->number, number, MAX_NUMBER_LENGTH);
    }
};

class Phonebook {
private:
    vector<Contact> contacts;

public:
    void addContact();
    void deleteContact();
    void displayContacts() const;
    void searchContact() const;
    void sortContacts();
    void speedDial() const;
    void saveContacts() const;
    void loadContacts();

    Phonebook() {
        loadContacts();
    }

    ~Phonebook() {
        saveContacts();
    }
};

void Phonebook::addContact() {
    char name[MAX_NAME_LENGTH];
    char number[MAX_NUMBER_LENGTH];

    cout << "Enter the name: ";
    cin.ignore();
    cin.getline(name, MAX_NAME_LENGTH);

    cout << "Enter the number: ";
    cin.getline(number, MAX_NUMBER_LENGTH);

    contacts.emplace_back(name, number);
}

void Phonebook::deleteContact() {
    if (contacts.empty()) {
        cout << "No contacts found.\n";
        return;
    }

    char searchName[MAX_NAME_LENGTH];
    cout << "Enter the name to delete: ";
    cin.ignore();
    cin.getline(searchName, MAX_NAME_LENGTH);

    auto it = remove_if(contacts.begin(), contacts.end(), [searchName](const Contact& contact) {
        return strcmp(contact.name, searchName) == 0;
    });

    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        cout << "Contact deleted successfully.\n";
    } else {
        cout << "Contact not found.\n";
    }
}

void Phonebook::displayContacts() const {
    if (contacts.empty()) {
        cout << "\nNo contacts found.\n";
        return;
    }

    cout << "\n--- Contacts ---\n";
    for (const auto& contact : contacts) {
        cout << "\nName: " << contact.name << "\n";
        cout << "Number: " << contact.number << "\n";
        cout << "----------------\n";
    }
}

void Phonebook::searchContact() const {
    if (contacts.empty()) {
        cout << "\nNo contacts found.\n";
        return;
    }

    char searchName[MAX_NAME_LENGTH];
    cout << "\nEnter the name to search: ";
    cin.ignore();
    cin.getline(searchName, MAX_NAME_LENGTH);

    auto it = find_if(contacts.begin(), contacts.end(), [searchName](const Contact& contact) {
        return strcmp(contact.name, searchName) == 0;
    });

    if (it != contacts.end()) {
        cout << "\nContact found:\n";
        cout << "\nName: " << it->name << "\n";
        cout << "Number: " << it->number << "\n";
    } else {
        cout << "\nContact not found.\n";
    }
}

void Phonebook::sortContacts() {
    if (contacts.empty()) {
        cout << "\nNo contacts found.\n";
        return;
    }

    sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return strcmp(a.name, b.name) < 0;
    });

    cout << "\nContacts sorted successfully.\n";
}

void Phonebook::speedDial() const {
    if (contacts.empty()) {
        cout << "\nNo contacts found.\n";
        return;
    }

    int speedDialIndex;
    cout << "\nEnter the speed dial index (1-N): ";
    cin >> speedDialIndex;

    if (speedDialIndex > 0 && speedDialIndex <= contacts.size()) {
        const auto& contact = contacts[speedDialIndex - 1];
        cout << "\nSpeed dialing " << contact.name << " - " << contact.number << "\n";
    } else {
        cout << "\nInvalid speed dial index.\n";
    }
}

void Phonebook::saveContacts() const {
    ofstream file("phonebook.txt");
    if (!file) {
        cout << "\nError opening the file.\n";
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.name << "," << contact.number << "\n";
    }

    file.close();
}

void Phonebook::loadContacts() {
    ifstream file("phonebook.txt");
    if (!file) {
        cout << "No phonebook file found.\n";
        return;
    }

    char line[MAX_NAME_LENGTH + MAX_NUMBER_LENGTH + 2];

    while (file.getline(line, sizeof(line))) {
        char* name = strtok(line, ",");
        char* number = strtok(nullptr, "\n");

        contacts.emplace_back(name, number);
    }

    file.close();
}

int main() {
    Phonebook phonebook;
    int choice;

    do {
        cout << "\n--- Phonebook Menu ---\n";
        cout << "1. Add Contact\n";
        cout << "2. Delete Contact\n";
        cout << "3. Display Contacts\n";
        cout << "4. Search Contact\n";
        cout << "5. Sort Contacts\n";
        cout << "6. Speed Dial\n";
        cout << "7. Quit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                phonebook.addContact();
                break;
            case 2:
                phonebook.deleteContact();
                break;
            case 3:
                phonebook.displayContacts();
                break;
            case 4:
                phonebook.searchContact();
                break;
            case 5:
                phonebook.sortContacts();
                break;
            case 6:
                phonebook.speedDial();
                break;
            case 7:
                cout << "\nPhonebook saved successfully.\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                break;
        }
    } while (choice != 7);

    return 0;
}
