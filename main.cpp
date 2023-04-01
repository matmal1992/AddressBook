#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>

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

struct User
{
    string login{};
    string password{};
    int id{};
};

string getLine()
{
    string imput = "";
    cin.sync();
    getline(cin, imput);
    return imput;
}

void displayUsers(vector <User> users)
{
    cout << "All users: " << endl << endl;
    for(auto c: users)
        cout << "ID: " << c.id << " Login: " << c.login << " Password: " << c.password << endl;
}

void displayContact(const vector <ContactData> contacts, int i)
{
    cout << contacts[i].id << " | " << contacts[i].name << " | " << contacts[i].surname << " | ";
    cout << contacts[i].email << " | " << contacts[i].address << " | " << contacts[i].tel << " | "<< endl;
}

void exportContactsToFile_Edit(vector <ContactData> contacts, int editedId, int i, int userId)
{
    fstream fileContacts{};
    fstream fileTemp{};
    size_t firstBarPos{};
    string line{};
    string idInLineString{};
    int idInLineInt{};

    fileContacts.open("Contacts.txt", ios::in);
    fileTemp.open("TempContacts.txt", ios::out);

    if(fileContacts.good())
    {
        while(getline(fileContacts, line))
        {
            firstBarPos = line.find('|');
            idInLineString = line.substr(0, firstBarPos);
            idInLineInt = atoi(idInLineString.c_str());

            if(idInLineInt == editedId)
            {
                fileTemp << to_string(contacts[i].id) << "|"<< userId << "|" << contacts[i].name << "|" << contacts[i].surname << "|" <<
                contacts[i].email << "|" << contacts[i].address << "|" << contacts[i].tel << "|" << endl;
            }
            else
            {
                fileTemp << line << endl;
            }
        }
    }
    else
    {
        cout << "Something wrong with Contacts.txt." << endl;
        system("pause");
    }
    fileContacts.close();
    fileTemp.close();
    remove("Contacts.txt");
    rename("TempContacts.txt", "Contacts.txt");
}

void exportContactsToFile_Delete(vector <ContactData> contacts, int removedId, int i, int userId)
{
    fstream fileContacts{};
    fstream fileTemp{};
    size_t firstBarPos{};
    string line{};
    string idInLineString{};
    int idInLineInt{};

    fileContacts.open("Contacts.txt", ios::in);
    fileTemp.open("TempContacts.txt", ios::out);

    if(fileContacts.good())
    {
        while(getline(fileContacts, line))
        {
            firstBarPos = line.find('|');
            idInLineString = line.substr(0, firstBarPos);
            idInLineInt = atoi(idInLineString.c_str());

            if(idInLineInt != removedId)
            {
                fileTemp << line << endl;
            }
        }
    }
    else
    {
        cout << "Something wrong with Contacts.txt." << endl;
        system("pause");
    }
    fileContacts.close();
    fileTemp.close();
    remove("Contacts.txt");
    rename("TempContacts.txt", "Contacts.txt");
}

void exportUsersToFile(vector <User> users)
{
    fstream file{};
    size_t i{0};
    file.open("Users.txt", ios::out);

    while(i < users.size())
    {
        file << to_string(users[i].id) << "|" << users[i].login << "|" << users[i].password << "|" << endl;
        i++;
    }
    file.close();
}

int deleteContact(vector <ContactData> &contacts, int numOfContacts, int userId)
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
                    exportContactsToFile_Delete(contacts, removedId, i, userId);
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
    cout << "Enter new name: ";
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

void editContact(vector <ContactData> &contacts, int userId)
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
            exportContactsToFile_Edit(contacts, editedId, i, userId);

            return;
        }
    }
    cout << "You provided invalid ID!" << endl;
}

void exportContactsToFile_Add(vector <ContactData> contacts, int i, int userId)
{
    fstream fileContacts{};
    fstream fileTemp{};
    string line{};
    string idInLineString{};

    fileContacts.open("Contacts.txt", ios::in);
    fileTemp.open("TempContacts.txt", ios::out);

    if(fileContacts.good())
    {
        while(getline(fileContacts, line))
        {
            fileTemp << line << endl;
        }

        fileTemp << to_string(contacts[i].id) << "|"<< userId << "|" << contacts[i].name << "|" << contacts[i].surname << "|" <<
        contacts[i].email << "|" << contacts[i].address << "|" << contacts[i].tel << "|" << endl;
    }
    else
    {
        cout << "Something wrong with Contacts.txt." << endl;
        system("pause");
    }
    fileContacts.close();
    fileTemp.close();
    remove("Contacts.txt");
    rename("TempContacts.txt", "Contacts.txt");
}

string getLastLine()
{
    string filename = "Contacts.txt";
    ifstream fin;
    fin.open(filename);
    int i{};
    char ch{};
    string lastLine{};

    if(fin.is_open())
    {
        fin.seekg(-3,ios_base::end);
        i = fin.tellg();

        for(i; i > 0; i--)
        {
            fin.get(ch);
            fin.seekg(i);

            if(ch == '\n')
            {
                fin.seekg(2, ios_base::cur);
                break;
            }
        }
    }

    getline(fin,lastLine);
    cout << lastLine << '\n';

    fin.close();
    return lastLine;
}

int getIdForNewContact()
{
    fstream fileContacts{};
    size_t firstBarPos{};
    string idInLineString{};
    int idInLineInt{};

    string lastLine = getLastLine();

    firstBarPos = lastLine.find('|');
    idInLineString = lastLine.substr(0, firstBarPos);
    idInLineInt = atoi(idInLineString.c_str());

    cout << "New Id: " << idInLineInt + 1 << endl;
    system("pause");

    return idInLineInt + 1;
}

int addContact(vector <ContactData> &contacts, int numOfContacts, int userId)
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
    newContact.id = getIdForNewContact();

    cout << "New ID: " << newContact.id << endl;
    system("pause");

    contacts.push_back(newContact);
    cout << "New contact has been added." << endl;
    exportContactsToFile_Add(contacts, numOfContacts, userId);
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

void displayUserContacts(const vector <ContactData> contacts)
{
    if(contacts.empty())
        cout << "There are no contacts in your book!." << endl;
    else
    {
        for(size_t i = 0; i < contacts.size(); i++)
            displayContact(contacts, i);
    }
}

ContactData extractContactFromLine(string line, int userId)
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
                j = i+1;
                break;
            case 3:
                word = line.substr(j, i - j);
                j = i+1;
                newContact.name = word;
                break;
            case 4:
                word = line.substr(j, i - j);
                j = i+1;
                newContact.surname = word;
                break;
            case 5:
                word = line.substr(j, i - j);
                j = i+1;
                newContact.email = word;
                break;
            case 6:
                word = line.substr(j, i - j);
                j = i+1;
                newContact.address = word;
                break;
            case 7:
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

int importUserContactsFromFile(vector <ContactData> &contacts, int userId)
{
    ContactData newContact{};
    string line{};
    fstream file{};
    int numOfContacts{0};
    int idInLineInt{};
    string idInLineString{};
    size_t firstBarPos{}, secondBarPos{}, difference{};

    file.open("Contacts.txt", ios::in);

    if(file.good())
    {
        while(getline(file, line))
        {
            firstBarPos = line.find('|');
            secondBarPos = line.find('|', firstBarPos + 1);
            difference = secondBarPos - firstBarPos;
            idInLineString = line.substr(firstBarPos + 1, difference - 1);
            idInLineInt = atoi(idInLineString.c_str());

            if(idInLineInt == userId)
            {
                newContact = extractContactFromLine(line, userId);
                numOfContacts++;
                contacts.push_back(newContact);
            }
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

User extractUserFromLine(string line)
{
    User newUser{};
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
                newUser.id = atoi(word.c_str());
                break;
            case 2:
                word = line.substr(j, i - j);
                j = i+1;
                newUser.login = word;
                break;
            case 3:
                word = line.substr(j, i - j);
                j = i+1;
                newUser.password = word;
                counter = 0;
                break;
            }
        }
    }
    return newUser;
}

void importUsersFromFile(vector <User> &users)
{
    User newUser{};
    string line{};
    int lineNum{0};
    fstream file{};
    int numOfUsers{0};

    file.open("Users.txt", ios::in);

    if(file.good())
    {
        while(getline(file, line))
        {
            lineNum++;
            newUser = extractUserFromLine(line);
            numOfUsers++;
            users.push_back(newUser);
        }
    }
    else
        cout << "There is no file to import data. Your user's base is empty now." << endl << endl;

    file.close();
}

void exitProgram(vector <ContactData> contacts)
{
    char exitChoice{};
    cout << "Do you want to save changes? (y/n) ";
    cin >> exitChoice;
    if(exitChoice == 'Y' || exitChoice == 'y')
    {
        //exportContactsToFile(contacts);
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

void changeUserPassword(vector <User> &users, int userId)
{
    string oldPassword{}, newPassword{};

    cout << "Insert your old password: ";
    cin >> oldPassword;
    for(size_t i = 0; i < users.size(); i++)
    {
        if(users[i].id == userId)
        {
            if(users[i].password == oldPassword)
            {
                cout << "Insert your new password: ";
                cin >> newPassword;

                users[i].password = newPassword;
                exportUsersToFile(users);

                cout << "Your password has been changed." << endl;
                Sleep(1000);
            }
            else
            {
                cout << "You provided incorrect password!" << endl;
                Sleep(1000);
            }
        }
    }
}

void registerUser(vector <User> &users)
{
    User user{};
    string login{}, password{};
    bool validLogin = true;

    cout << "Insert login: ";
    cin >> login;

    for(auto c: users)
    {
        if(login == c.login)
        {
            cout << "Such login already exists!" << endl;
            Sleep(1000);
            validLogin = false;
        }
    }

    if(validLogin)
    {
        cout << "Insert password: ";
        cin >> password;

        user.login = login;
        user.password = password;
        user.id = users.size() + 1;
        users.push_back(user);

        cout << "User '" << login << "' has been added." << endl;
        exportUsersToFile(users);
        Sleep(1000);
    }
}

int signIn(vector <User> &users)
{
    User user{};
    string login{}, password{};
    int actualId = 0;
    bool validLogin = false;

    cout << "Insert login: ";
    cin >> login;

    for(auto c: users)
    {
        if(login == c.login)
        {
            cout << "Insert password: ";
            cin >> password;
            if(password == c.password)
            {
                actualId = c.id;
                cout << "Successful login" << endl << endl;
            }
            else
            {
                cout << "Incorrect password!" << endl;
                Sleep(1000);
                return 0;
            }
            validLogin = true;
        }
    }

    if(!validLogin)
    {
        cout << "There is no such login in our base!" << endl;
        Sleep(1000);
    }

    return actualId;
}

void userAddressBook(vector <User> &users, int &userId)
{
    vector <ContactData> contacts{};
    int numOfContacts{0}; //refactor numofcontacts
    char choice{};

    numOfContacts = importUserContactsFromFile(contacts, userId);

    while(choice != '8')
    {
        //greet an user
        cout << "1. Add new contact." << endl;
        cout << "2. Find by name." << endl;
        cout << "3. Find by surname." << endl;
        cout << "4. Display all contacts." << endl;
        cout << "5. Delete a contact." << endl;
        cout << "6. Edit a contact." << endl;
        cout << "7. Change password." << endl;
        cout << "8. Log out." << endl;

        cout << "Your choice: ";
        cin >> choice;

        switch(choice)
        {
        case '1':
            numOfContacts = addContact(contacts, numOfContacts, userId);
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
            displayUserContacts(contacts);
            system("pause");
            break;
        case '5':
            numOfContacts = deleteContact(contacts, numOfContacts, userId);
            system("pause");
            break;
        case '6':
            editContact(contacts, userId);
            system("pause");
            break;
        case '7':
            changeUserPassword(users, userId);
            break;
        case '8':
            userId = 0;
            break;
        default:
            cout << "Incorrect choice" << endl;
            Sleep(1000);
        }
        system("cls");
    }
}

int main()
{
    vector <User> users{};
    char choice{};
    int actualId{};

    importUsersFromFile(users);

    while(true)
    {
        cout << ">>> MAIN MENU <<<" << endl;
        cout << "--------------------------" << endl;
        cout << "1. Sign in" << endl;
        cout << "2. Sign up" << endl;
        cout << "3. Close the program" << endl;
        cout << "4. Display users" << endl;
        cout << "--------------------------" << endl;
        cout << "Your choice: ";
        cin >> choice;

        switch(choice)
        {
        case '1':
            actualId = signIn(users);
            if(actualId != 0)
            {
                userAddressBook(users, actualId);
            }
            //system("pause");
            break;
        case '2':
            registerUser(users);
            break;
        case '3':
            //some saving
            //exitProgram(contacts);
            exit(0);
            break;
        case '4':
            displayUsers(users);
            system("pause");
            break;
        default:
            cout << "Incorrect choice" << endl;
            Sleep(1000);
        }
        system("cls");
    }

    return 0;
}
