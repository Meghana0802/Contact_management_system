#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class contact
{
public:
    string name, phone, address, email;
    bool operator==(const contact &other) const
    {
        return (name == other.name && phone == other.phone && address == other.address && email == other.email);
    }
    contact()
    {
        name = "";
        phone = "";
        address = "";
        email = "";
    }
    contact(const string &name, const string &phone, const string &address, const string &email)
        : name(name), phone(phone), address(address), email(email) {}
    string toString() const
    {
        return name + "," + phone + "," + address + "," + email;
    }
    static contact fromString(const string &data)
    {
        size_t comma1 = data.find(",");
        size_t comma2 = data.find(",", comma1 + 1);
        size_t comma3 = data.find(",", comma2 + 1);
        string name = data.substr(0, comma1);
        string phone_num = data.substr(comma1 + 1, comma2 - comma1 - 1);
        string address = data.substr(comma2 + 1, comma3 - comma2 - 1);
        string email = data.substr(comma3 + 1);
        return contact(name, phone_num, address, email);
    }
    void save_contact(const string &newName, const string &newNumber, const string &newAddress, const string &newEmail)
    {
        name = newName;
        phone = newNumber;
        address = newAddress;
        email = newEmail;
    }
};

class contactManager
{
private:
    vector<contact> contacts;
    string file;

public:
    contactManager(const string &filename) : file(filename) {}
    void add_contact(const contact &cont)
    {
        contacts.push_back(cont);
        cout << "The contact is added succesfully" << endl;
    }
    void delete_contact(const contact &cont)
    {
        auto it = find_if(contacts.begin(), contacts.end(), [&cont](const contact &c)
                          { return c.name == cont.name; });
        if (it != contacts.end())
        {
            contacts.erase(it);
            cout << "Contact is removed successfully" << endl;
        }
        else
        {
            cout << "The contact is not found" << endl;
        }
    }
    void display_all_contacts()
    {
        if (contacts.empty())
        {
            cout << "No contacts found" << endl;
        }
        else
        {
            cout << "******************************"
                 << "CONTACTS"
                 << "******************************" << endl;
            for (const contact &cont : contacts)
            {
                cout << "Name: " << cont.name << endl;
                cout << "Phone number: " << cont.phone << endl;
                cout << "Address: " << cont.address << endl;
                cout << "Email: " << cont.email << endl;
                cout << endl;
            }
        }
    }
    void save_to_file()
    {
        ofstream file("contacts.dat");
        if (file.is_open())
        {
            for (contact &cont : contacts)
            {
                file << cont.toString() << endl;
            }
            cout << "Contact is successfully saved to the file" << endl;
        }
        else
        {
            cout << "Unable to open the file" << endl;
        }
    }
    void load_from_file()
    {
        ifstream file("contacts.dat");
        if (file.is_open())
        {
            string line;
            contacts.clear();
            while (getline(file, line))
            {
                contact cont = contact::fromString(line);
                contacts.push_back(cont);
            }
            cout << "Contacts are loaded from the file" << endl;
        }
        else
        {
            cout << "Unable to open the file" << endl;
        }
    }
    void edit_contact(const string& name)
{
    bool found = false;
    for (contact& cont : contacts)
    {
        if (cont.name == name)
        {
            string newName, newNumber, newAddress, newEmail;
            cout<<"Press enter to get the prompts for editing contact info"<<endl;
            cin.ignore();
            cout << "Enter new name: ";
            getline(cin, newName);
            cout << "Enter new phone number: ";
            getline(cin, newNumber);
            cout << "Enter new address: ";
            getline(cin, newAddress);
            cout << "Enter new email: ";
            getline(cin, newEmail);
            cont.save_contact(newName,newNumber,newAddress,newEmail);
            cout << "Contact edited successfully." << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Contact not found." << endl;
    }
}

};

int main()
{
    string fileName = "contacts.txt";
    contactManager CM(fileName);
    cout << "========== Contact Management System ==========" << endl;
    cout << "1. Add Contact" << endl;
    cout << "2. Delete Contact" << endl;
    cout << "3. Edit Contact" << endl;
    cout << "4. Save Contacts to File" << endl;
    cout << "5. Load Contacts from File" << endl;
    cout << "6. Display All Contacts" << endl;
    cout << "0. Exit" << endl;
    int choice;
    do
    {
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {
            string name, phone, address, email;
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter phone number: ";
            getline(cin, phone);
            cout << "Enter address: ";
            getline(cin, address);
            cout << "Enter email: ";
            getline(cin, email);

            CM.add_contact(contact(name, phone, address, email));
            break;
        }
        case 2:
        {
            string name;
            cout << "Enter name to delete contact: ";
            getline(cin, name);

            CM.delete_contact(contact(name, "", "", ""));
            break;
        }
        case 3:
        {
            string name;
            cout << "Enter name to edit contact: ";
            getline(cin, name);
            CM.edit_contact(name);
            break;
        }
        case 4:
            CM.save_to_file();
            break;
        case 5:
            CM.load_from_file();
            break;
        case 6:
            CM.display_all_contacts();
            break;
        case 0:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}