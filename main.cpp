#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

struct ContactData
{
    string name{};
    string surname{};
    string email{};
    string address{};
    string tel{};
    int id{};
};

string getLine()
{
    string imput = "";
    cin.sync();
    getline(cin, imput);
    return imput;
}

void displayContact(const vector <ContactData> contacts, int i)
{
    cout << contacts[i].id << " | " << contacts[i].name << " | " << contacts[i].surname << " | ";
    cout << contacts[i].email << " | " << contacts[i].address << " | " << contacts[i].tel << " | "<< endl;
}

int deleteContact(vector <ContactData> &contacts, int numOfContacts)
{
    int removedId{};
    char choice{};
    cout << "Enter ID of a contact to delete: ";
    cin >> removedId;

    for(size_t i = 0; i < contacts.size(); i++)
    {
        if(contacts[i].id == removedId)
        {
            cout << contacts[i].name << " " << contacts[i].surname << " will be removed from your contacts. Do you want to continue? (y/n): ";
            cin >> choice;

            while(choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')
            {
                if(choice == 'Y' || choice == 'y')
                {
                    contacts.erase(contacts.begin() + i);
                    cout << "Contact has been removed from your book." << endl;
                    return numOfContacts - 1;
                }
                else if(choice == 'N' || choice == 'n')
                {
                    return numOfContacts;
                }
                else
                {
                    cout << "Incorrect choice!" << endl;
                    Sleep(1000);
                }
            }
        }
    }
    cout << "You provided invalid ID!" << endl;
    return numOfContacts;
}

bool validateAddedData(vector <ContactData> contacts, string data)
{
    for(size_t i = 0; i < contacts.size(); i++)
    {
        if(contacts[i].email == data)
        {
            cout << "Such email address already exists!" << endl;
            Sleep(1500);
            return false;
        }
        else if(contacts[i].address == data)
        {
            cout << "Such address already exists!" << endl;
            Sleep(1500);
            return false;
        }
        else if(contacts[i].tel == data)
        {
            cout << "Such phone number already exists!" << endl;
            Sleep(1500);
            return false;
        }
    }
    return true;
}

void changeName(vector <ContactData> &contacts, int i)
{
    string newName{};
    cout << "Enter new surname: ";
    cin.sync();
    newName = getLine();

    contacts[i].name = newName;
    cout << "Name has been changed." << endl;
}

void changeSurname(vector <ContactData> &contacts, int i)
{
    string newSurname{};
    cout << "Enter new surname: ";
    cin.sync();
    newSurname = getLine();

    contacts[i].surname = newSurname;
    cout << "Surname has been changed." << endl;
}

void changeEmail(vector <ContactData> &contacts, int i)
{
    bool dataValid{};
    string newEmail{};
    cout << "Enter new email: ";
    cin.sync();
    newEmail = getLine();
    dataValid = validateAddedData(contacts, newEmail);

    if(!dataValid){return;}
    else
    {
        contacts[i].email = newEmail;
        cout << "Email has been changed." << endl;
    }
}

void changeAddress(vector <ContactData> &contacts, int i)
{
    bool dataValid{};
    string newAddress{};
    cout << "Enter new address: ";
    cin.sync();
    newAddress = getLine();
    dataValid = validateAddedData(contacts, newAddress);

    if(!dataValid){return;}
    else
    {
        contacts[i].address = newAddress;
        cout << "Address has been changed." << endl;
    }
}

void changeTel(vector <ContactData> &contacts, int i)
{
    bool dataValid{};
    string newTel{};
    cout << "Enter new phone number: ";
    cin.sync();
    newTel = getLine();
    dataValid = validateAddedData(contacts, newTel);

    if(!dataValid){return;}
    else
    {
        contacts[i].tel = newTel;
        cout << "Phone number has been changed." << endl;
    }
}

void executeEdition(vector <ContactData> &contacts, int i)
{
    char choice{};

    cout << "What exactly would you like to change?" << endl;
    cout << "1. Name" << endl;
    cout << "2. Surname" << endl;
    cout << "3. Email" << endl;
    cout << "4. Address" << endl;
    cout << "5. Tel" << endl;
    cout << "6. Go to the main menu." << endl << endl;
    cout << "Select number: ";
    cin >> choice;

    switch(choice)
    {
    case '1':
        changeName(contacts, i);
        break;
    case '2':
        changeSurname(contacts, i);
        break;
    case '3':
        changeEmail(contacts, i);
        break;
    case '4':
        changeAddress(contacts, i);
        break;
    case '5':
        changeTel(contacts, i);
        break;
    case '6':
        return;
    default:
        cout << "Wrong choice!" << endl;
        return;
    }
}

void editContact(vector <ContactData> &contacts)
{
    int editedId{};
    cout << "Enter ID of a contact to edit: ";
    cin >> editedId;

    for(size_t i = 0; i < contacts.size(); i++)
    {
        if(contacts[i].id == editedId)
        {
            cout << "Your choice:" << endl;
            displayContact(contacts, i);
            executeEdition(contacts, i);
            return;
        }
    }
    cout << "You provided invalid ID!" << endl;
}

int addContact(vector <ContactData> &contacts, int numOfContacts)
{
    string name{}, surname{}, email{}, address{}, tel{}, buf{};

    cout << "Insert name: ";
    name = getLine();

    cout << "Insert surname: ";
    surname = getLine();

    cout << "Insert email: ";
    email = getLine();
    if(!validateAddedData(contacts, email))
        return numOfContacts;

    cout << "Insert address: ";
    address = getLine();
    if(!validateAddedData(contacts, address))
        return numOfContacts;

    cout << "Insert phone number: ";
    tel = getLine();
    if(!validateAddedData(contacts, tel))
        return numOfContacts;

    ContactData newContact{};
    newContact.name = name;
    newContact.surname = surname;
    newContact.email = email;
    newContact.address = address;
    newContact.tel = tel;
    newContact.id = numOfContacts + 1;

    contacts.push_back(newContact);
    cout << "New contact has been added." << endl;
    Sleep(1000);
    return numOfContacts + 1;
}

void findByName(const vector <ContactData> contacts)
{
    string searchedName{};
    bool resultOfSearching = false;

    cout << "Enter searched name: ";
    cin >> searchedName;

    for(size_t i = 0; i < contacts.size(); i++)
    {
        if(contacts[i].name == searchedName)
        {
            resultOfSearching = true;
            displayContact(contacts, i);
        }
    }
    if(!resultOfSearching)
        cout << "There is no contact with such name!" << endl;
}

void findBySurname(const vector <ContactData> contacts)
{
    string searchedSurname{};
    bool resultOfSearching = false;

    cout << "Enter searched surname: ";
    cin >> searchedSurname;

    for(size_t i = 0; i < contacts.size(); i++)
    {
        if(contacts[i].surname == searchedSurname)
        {
            resultOfSearching = true;
            displayContact(contacts, i);
        }
    }
    if(!resultOfSearching)
        cout << "There is no contact with such surname!" << endl;
}

void displayAllContacts(const vector <ContactData> contacts)
{
    if(contacts.empty())
        cout << "There are no contacts in your book!." << endl;
    else
    {
        for(size_t i = 0; i < contacts.size(); i++)
            displayContact(contacts, i);
    }
}

ContactData extractContactFromLine(string line)
{
    ContactData newContact{};
    int counter{0};
    string word{};

    for (size_t i = 0, j = 0; i < line.length(); i++)
    {
        if (line[i] == '|')
        {
            counter++;

            switch(counter)
            {
            case 1:
                word = line.substr(j, i - j);
                j = i+1;
                newContact.id = atoi(word.c_str());
                break;
            case 2:
                word = line.substr(j, i - j);
                j = i+1;
                newContact.name = word;
                break;
            case 3:
                word = line.substr(j, i - j);
                j = i+1;
                newContact.surname = word;
                break;
            case 4:
                word = line.substr(j, i - j);
                j = i+1;
                newContact.email = word;
                break;
            case 5:
                word = line.substr(j, i - j);
                j = i+1;
                newContact.address = word;
                break;
            case 6:
                word = line.substr(j, i - j);
                j = i+1;
                newContact.tel = word;
                counter = 0;
                break;
            }
        }
    }
    return newContact;
}

int importContactsFromFile(vector <ContactData> &contacts)
{
    ContactData newContact{};
    string line{};
    int lineNum{0};
    fstream file{};
    int numOfContacts{0};

    file.open("save.txt", ios::in);

    if(file.good())
    {
        while(getline(file, line))
        {
            lineNum++;
            newContact = extractContactFromLine(line);
            numOfContacts++;
            contacts.push_back(newContact);
        }
    }
    else
    {
        cout << "There is no file to import data. Your book is empty now." << endl;
        system("pause");
    }
    file.close();
    return numOfContacts;
}

void exportContactsToFile(vector <ContactData> contacts)
{
    fstream file{};
    size_t i{0};
    file.open("save.txt", ios::out);

    while(i < contacts.size())
    {
        file << to_string(contacts[i].id) << "|" << contacts[i].name << "|" << contacts[i].surname << "|" <<
        contacts[i].email << "|" << contacts[i].address << "|" << contacts[i].tel << endl;

        i++;
    }
    file.close();
}

void exitProgram(vector <ContactData> contacts)
{
    char exitChoice{};
    cout << "Do you want to save changes? (y/n) ";
    cin >> exitChoice;
    if(exitChoice == 'Y' || exitChoice == 'y')
    {
        exportContactsToFile(contacts);
        exit(0);
    }
    else if(exitChoice == 'N' || exitChoice == 'n')
    {
        exit(0);
    }
    else
    {
        cout << "Incorrect choice!" << endl;
        Sleep(1000);
    }
}

int main()
{
    vector <ContactData> contacts{};
    int numOfContacts{0};
    char choice{};

    numOfContacts = importContactsFromFile(contacts);

    while(true)
    {
        cout << "1. Add new contact." << endl;
        cout << "2. Find by name." << endl;
        cout << "3. Find by surname." << endl;
        cout << "4. Display all contacts." << endl;
        cout << "5. Delete a contact." << endl;
        cout << "6. Edit a contact." << endl;
        cout << "9. Close the program." << endl << endl;

        cout << "Your choice: ";
        cin >> choice;

        switch(choice)
        {
        case '1':
            numOfContacts = addContact(contacts, numOfContacts);
            break;
        case '2':
            findByName(contacts);
            system("pause");
            break;
        case '3':
            findBySurname(contacts);
            system("pause");
            break;
        case '4':
            displayAllContacts(contacts);
            system("pause");
            break;
        case '5':
            numOfContacts = deleteContact(contacts, numOfContacts);
            system("pause");
            break;
        case '6':
            editContact(contacts);
            system("pause");
            break;
        case '9':
            exitProgram(contacts);
            exit(0);
        default:
            cout << "Incorrect choice" << endl;
            Sleep(1000);
        }
        system("cls");
    }
    return 0;
}
