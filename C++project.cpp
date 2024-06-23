#include <iostream>
#include "recruit.h"
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

void displayMainMenu()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "|  Welcome to the Recruitment Center!    |" << endl;
    cout << "| 1. Log in                              |" << endl;
    cout << "| 2. Exit                                |" << endl;
    cout << "| Enter your choice: ";
}

void displayRecruitMenu(Recruit& recruit) {
    int choice;
    cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "| 1. Log in to another profile           |" << endl;
    cout << "| 2. Exit                                |" << endl;
    cout << "| 3. Edit info                           |" << endl;
    cout << "| 4. Save to txt                         |" << endl;
    cout << "|Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        cin.ignore(); 
        cout << "|Logging in to another profile...        |" << endl;
        return;
    }
    case 2:
        cout << "|Exiting...                              |" << endl;
        exit(0);
    case 3: {
        int editChoice;
        cout << "| Select the field you want to edit:" << endl;
        cout << "| 1. First Name" << endl;
        cout << "| 2. Last Name" << endl;
        cout << "| 3. Middle Name" << endl;
        cout << "| 4. Date of Birth" << endl;
        cout << "| 5. Pin Code" << endl;
        cout << "| Enter your choice: ";
        cin >> editChoice;

        switch (editChoice) {
        case 1:
            cout << "| Enter new first name: ";
            cin.ignore();
            cin.getline(recruit.firstName, 50);
            break;
        case 2:
            cout << "| Enter new last name: ";
            cin.ignore();
            cin.getline(recruit.lastName, 50);
            break;
        case 3:
            cout << "| Enter new middle name: ";
            cin.ignore();
            cin.getline(recruit.middleName, 50);
            break;
        case 4:
            cout << "| Enter new date of birth (day month year): ";
            cin >> recruit.day >> recruit.month >> recruit.year;
            break;
        case 5:
            cout << "| Enter new pin code: ";
            cin >> recruit.pinCode;
            break;
        default:
            cout << "| Invalid choice." << endl;
            break;
        }

        
        ofstream outFile("recruits.bin", ios::binary);
        if (!outFile) {
            cerr << "Unable to open file." << endl;
            return;
        }
        outFile.write((char*)&recruit, sizeof(recruit)); 
        outFile.close(); 
        cout << "| Data saved                             |" << endl;
        break;
    }
    case 4: {
        ofstream textFile("my_data.txt");
        if (!textFile) {
            cerr << "Unable to open file." << endl;
            return;
        }
        textFile << "First Name: " << recruit.firstName << endl;
        textFile << "Last Name: " << recruit.lastName << endl;
        textFile << "Middle Name: " << recruit.middleName << endl;
        textFile << "Date of Birth: " << recruit.day << "." << recruit.month << "." << recruit.year << endl;
        textFile << "Pin Code: " << recruit.pinCode << endl;
        textFile.close();

        cout << "| Data saved to my_data.txt.             |" << endl;
        break;
    }
    default:
        cout << "| Invalid choice. Exiting...             |" << endl;
        exit(0);
    }
}

void editRecruit(Recruit& recruit) {
    ifstream inFile("admindata.bin", ios::binary);
    if (!inFile) {
        cerr << "Unable to open file." << endl;
        return;
    }

    vector<Recruit> recruits;
    Recruit tempRecruit;

    while (inFile.read(reinterpret_cast<char*>(&tempRecruit), sizeof(tempRecruit))) {
        recruits.push_back(tempRecruit);
    }

    inFile.close();

    cout << "| Choose the recruit to edit:" << endl;
    for (size_t i = 0; i < recruits.size(); ++i) {
        cout << "| " << i + 1 << ". " << recruits[i].firstName << " " << recruits[i].lastName << endl;
    }

    int choice;
    cout << "| Enter the number of the recruit to edit: ";
    cin >> choice;

    if (choice < 1 || choice > recruits.size()) {
        cout << "| Invalid choice." << endl;
        return;
    }

    Recruit& chosenRecruit = recruits[choice - 1];
    int editChoice;
    cout << "| Select the field you want to edit for " << chosenRecruit.firstName << " " << chosenRecruit.lastName << ":" << endl;
    cout << "| 1. First Name" << endl;
    cout << "| 2. Last Name" << endl;
    cout << "| 3. Middle Name" << endl;
    cout << "| 4. Date of Birth" << endl;
    cout << "| 5. Pin Code" << endl;
    cout << "| Enter your choice: ";
    cin >> editChoice;

    switch (editChoice) {
    case 1:
        cout << "| Enter new first name: ";
        cin.ignore();
        cin.getline(chosenRecruit.firstName, 50);
        break;
    case 2:
        cout << "| Enter new last name: ";
        cin.ignore();
        cin.getline(chosenRecruit.lastName, 50);
        break;
    case 3:
        cout << "| Enter new middle name: ";
        cin.ignore();
        cin.getline(chosenRecruit.middleName, 50);
        break;
    case 4:
        cout << "| Enter new date of birth (day month year): ";
        cin >> chosenRecruit.day >> chosenRecruit.month >> chosenRecruit.year;
        break;
    case 5:
        cout << "| Enter new pin code: ";
        cin >> chosenRecruit.pinCode;
        break;
    default:
        cout << "| Invalid choice." << endl;
        return;
    }

    ofstream outFile("admindata.bin", ios::binary);
    if (!outFile) {
        cerr << "Unable to open file." << endl;
        return;
    }

    for (size_t i = 0; i < recruits.size(); ++i) {
        outFile.write(reinterpret_cast<char*>(&recruits[i]), sizeof(recruits[i]));
    }

    outFile.close();
    cout << "| Data saved." << endl;
}
void deleteRecruitByNumber(int number) {
    ifstream inFile("admindata.bin", ios::binary);
    if (!inFile) {
        cerr << "Unable to open file." << endl;
        return;
    }

    vector<Recruit> recruits;
    Recruit tempRecruit;

    while (inFile.read(reinterpret_cast<char*>(&tempRecruit), sizeof(tempRecruit))) {
        recruits.push_back(tempRecruit);
    }

    inFile.close();

    if (number < 1 || number > recruits.size()) {
        cout << "| Invalid recruit number." << endl;
        return;
    }

    recruits.erase(recruits.begin() + number - 1);

    ofstream outFile("admindata.bin", ios::binary);
    if (!outFile) {
        cerr << "Unable to open file." << endl;
        return;
    }

    for (size_t i = 0; i < recruits.size(); ++i) {
        outFile.write(reinterpret_cast<char*>(&recruits[i]), sizeof(recruits[i]));
    }

    outFile.close();
    cout << "| Recruit number " << number << " deleted." << endl;
}
bool compareByDateOfBirth(const Recruit& a, const Recruit& b) {
    if (a.year != b.year)
        return a.year < b.year;
    if (a.month != b.month)
        return a.month < b.month;
    return a.day < b.day;
}
void sortRecruitsByDateOfBirth() {
    ifstream inFile("admindata.bin", ios::binary);
    if (!inFile) {
        cerr << "Unable to open file." << endl;
        return;
    }

    vector<Recruit> recruits;
    Recruit tempRecruit;

    while (inFile.read(reinterpret_cast<char*>(&tempRecruit), sizeof(tempRecruit))) {
        recruits.push_back(tempRecruit);
    }

    inFile.close();


    sort(recruits.begin(), recruits.end(), compareByDateOfBirth);


    cout << "Recruits sorted by date of birth:" << endl;
    for (const auto& recruit : recruits) {
        displayData(recruit);
        cout << "----------------------------------------" << endl;
    }
}
void displayAdminMenu()
{
    int choice;
    cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "| 1. Log in to another profile           |" << endl;
    cout << "| 2. Exit                                |" << endl;
    cout << "| 3. Add new recruit                     |" << endl;
    cout << "| 4. Edit recruit                        |" << endl;
    cout << "| 5. Delete recruit                      |" << endl;
    cout << "| 6. Sort recruits by date of birth      |" << endl;
    cout << "| Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        cin.ignore();

        cout << "| Logging in to another profile...       |" << endl;
        return;
    }
    case 2:

        cout << "| Exiting...                             |" << endl;
        exit(0);
    case 3:
    {
        cout << "| Adding new recruit...                  |" << endl;
        Recruit newRecruit;
        inputData(newRecruit);
        inputDiseases(newRecruit);
        ofstream outFile("recruits.bin", ios::binary | ios::app);
        outFile.write((char*)&newRecruit, sizeof(newRecruit));
        cout << "| New recruit added and data saved       |" << endl;
        outFile.close();
        break;
    }
    case 4:
        Recruit dummyRecruit;
        editRecruit(dummyRecruit);
        break;
    case 5:
    {
        int recruitNumberToDelete;
        cout << "| Enter the number of the recruit to delete: ";
        cin >> recruitNumberToDelete;
        deleteRecruitByNumber(recruitNumberToDelete);
        break;
    }
    case 6:

        sortRecruitsByDateOfBirth();
        break;
    default:
        cout << "| Invalid choice. Exiting...             |" << endl;
        exit(0);
    }
}


void displayAllRecruits()
{
    ifstream binFile("admindata.bin", ios::binary);
    if (!binFile) {
        cerr << "Unable to open recruits file." << endl;
        return;
    }

    Recruit recruit;
    while (binFile.read((char*)&recruit, sizeof(recruit))) {
        displayData(recruit);
        cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
    }

    binFile.close();
}


int main()
{
    while (true) {
        displayMainMenu();
        int mainChoice;
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: {
            Recruit recruit;
            ifstream binFile("admindata.bin", ios::binary);

            cout << "| Input Login: ";
            cin.ignore();
            cin.getline(recruit.login, 20);

            cout << "| Input Pin Code: ";
            cin >> recruit.pinCode;
            cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;

            if (checkAdmin(recruit.login, recruit.pinCode))
            {
                cout << "| Admin login successful!                |" << endl;

                cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;

                cout << "| Admin Data:                            |" << endl;
                displayRecruitsData();
                displayAdminMenu();
            }
            else
            {
                Recruit foundRecruit;
                bool isNewUser = true;

                if (binFile.is_open())
                {
                    if (checkUserExists(recruit.login, recruit.pinCode, binFile, foundRecruit))
                    {
                        isNewUser = false;
                    }
                    binFile.close();
                }

                if (isNewUser)
                {
                    cout << "| User does not exist. Input data.|" << endl;
                    inputData(recruit);
                    inputDiseases(recruit);

                    ofstream outFile("admindata.bin", ios::binary | ios::app);
                    outFile.write((char*)&recruit, sizeof(recruit));

                    cout << "| Data saved                             |" << endl;
                    outFile.close();
                }
                else
                {
                    cout << "| User already exists!                   |" << endl;
                    cout << "| User Data:                             |" << endl;
                    displayData(foundRecruit);
                    displayRecruitMenu(foundRecruit);

                }
            }
            break;
        }
        case 2:
            cout << "| Exiting...                             |" << endl;
            exit(0);
        default:

            cout << "| Invalid choice. Exiting...             |" << endl;
            exit(0);
        }
    }

    return 0;
}
