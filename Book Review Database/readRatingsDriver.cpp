#include "User.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/*
 * This function splits strings into indices in an array
 * Paramaters: user inputted string, character separator, non-user inputted string array, and user inputted integer size of string array
 * Return: integer number of splits
*/

int split(string split, char separator, string array[], int size)
{
    int position1 = 0; // start of substring
    int position2 = 0; // number of spaces for substring
    int j = 0; // array position
    int count = 1; // count number of splits, set to 1 because if no splits, the entire string gets set to the first array indice

    if (split.length() == 0)
    {
        return 0; // this ensures that the user is not trying to split a 1 character string
    }
    
    for (int i = 0; i < split.length() - 1; i++)
    {
        if (split[i] == separator)
        {
            position2 = i;
            array[j] = split.substr(position1, position2 - position1);
            position1 = position2 + 1;
            j++;
            count++;
        }
    }

    array[j] = split.substr(position1, split.length() - 1);

    if (position1 == 0)
    {
        array[j] = split;
    }
    if (count > size)
    {
        return -1;
    }

    return count;
}

/* 
// This function reads from a file to fill ratings for User objects
// Inputs: string of file name, User object array, int number of User objects stored in array, int number size of array, int number of max columns (i.e. max ratings)
// Returns: int number of User objects in array
*/

int readRatings(string filename, User users[], int numUsersStored, int usersArrSize, int maxCol)
{
    ifstream in_file;
    string line;
    string temp[50000];
    const char SEPARATOR = ',';
    string tempUsername;
    int tempRatings[50];
    int tempRate;
    int row = numUsersStored;

    in_file.open(filename);
    if (numUsersStored >= usersArrSize) //Makes sure the User array isn't already full
    {
        return -2;
    }
    if (in_file.fail()) //Makes sure the file opened properly
    {
        return -1;
    }

    if (maxCol < 0 || maxCol > 50)
    {
        maxCol = 50;
    }

    while (getline(in_file, line) && numUsersStored < usersArrSize)
    {
        if (line != "") //Makes sure the line isn't empty
        {
            split(line, SEPARATOR, temp, maxCol);
            tempUsername = temp[0];
            users[numUsersStored].setUsername(tempUsername);
            int count = 1;

            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == SEPARATOR)
                {
                    line = line.substr(i + 1, line.length() - i); //This gets rid of the username
                    break;
                }
            }

            split(line, SEPARATOR, temp, maxCol);

            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == SEPARATOR)
                {
                    count++;
                }
            }

            if (count > 50)
            {
                count = 50;
            }

            users[numUsersStored].setNumRatings(count);

            for (int i = 0; i < count; i++)
            {
                tempRate = stoi(temp[i]);
                users[numUsersStored].setRatingAt(i, tempRate);
            }

            numUsersStored++;
        }
    }

    return numUsersStored;
}

int main()
{
    string filename;
    User users[100];
    int numUsersStored = 0;
    int usersArrSize;
    int maxCol;

    cout << "Enter file name: " << endl;
    getline(cin, filename);
    cout << "Enter number of users stored: " << endl;
    cin >> numUsersStored;
    cout << "Enter the size of users array: " << endl;
    cin >> usersArrSize;
    cout << "Enter max number of columns: " << endl;
    cin >> maxCol;

    cout << readRatings(filename, users, numUsersStored, usersArrSize, maxCol) << endl;

    return 0;
}