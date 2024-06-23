#ifndef RECRUIT_H
#define RECRUIT_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct Recruit
{
    char firstName[50];
    char lastName[50];
    char middleName[50];
    int day, month, year;
    char login[20];
    int pinCode;
    bool isAdult;
    char diseases[5][100]; 
    int diseaseCount;
};

void inputData(Recruit& recruit)
{
    cout << "| Input first name: ";
    cin.ignore();
    cin.getline(recruit.firstName, 50);

    cout << "| Input last name: ";
    cin.getline(recruit.lastName, 50);

    cout << "| Input middle name: ";
    cin.getline(recruit.middleName, 50);

    cout << "| Input your birthday (day month year): ";
    cin >> recruit.day >> recruit.month >> recruit.year;

    int currentYear = 2024;
    recruit.isAdult = (currentYear - recruit.year >= 18 && currentYear - recruit.year < 60);
}

void inputDiseases(Recruit& recruit)
{
    cout << "| How many diseases do you have? (up to 5): ";
    cin >> recruit.diseaseCount;
    cin.ignore();

    for (int i = 0; i < recruit.diseaseCount; ++i)
    {
        cout << "| Input disease #" << i + 1 << ": ";
        cin.getline(recruit.diseases[i], 100);
    }
}

void displayData(const Recruit& recruit)
{
    cout << "| First Name: " << recruit.firstName << endl;
    cout << "| Last Name: " << recruit.lastName << endl;
    cout << "| Middle Name: " << recruit.middleName << endl;
    cout << "| Date of birth: " << recruit.day << "." << recruit.month << "." << recruit.year << endl;
    cout << "| Visit the nearest recruit center: " << (recruit.isAdult ? "Yes" : "No") << endl;

    if (recruit.diseaseCount > 0)
    {
        cout << "| Diseases:                              |" << endl;
        for (int i = 0; i < recruit.diseaseCount; ++i)
        {
            cout << "|- " << recruit.diseases[i] << endl;
        }
    }
    else
    {
        cout << "| No diseases                            |" << endl;
    }
}

bool checkAdmin(const char* login, int pinCode)
{
    return (strcmp(login, "admin007") == 0 && pinCode == 7777);
}

bool checkUserExists(const char* login, int pinCode, ifstream& binFile, Recruit& foundRecruit)
{
    Recruit recruit;
    while (binFile.read((char*)&recruit, sizeof(recruit)))
    {
        if (strcmp(recruit.login, login) == 0 && recruit.pinCode == pinCode)
        {
            foundRecruit = recruit;
            return true;
        }
    }
    return false;
}


void displayRecruitsData() {
    ifstream inFile("admindata.bin", ios::binary);
    if (!inFile) {
        cerr << "Unable to open file." << endl;
        return;
    }

    Recruit recruit;
    int count = 1;
    while (inFile.read(reinterpret_cast<char*>(&recruit), sizeof(recruit))) {
        cout << "| Recruit " << count << " Data:" << endl;
        displayData(recruit);
        cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
        count++;
    }

    inFile.close();
}


#endif
