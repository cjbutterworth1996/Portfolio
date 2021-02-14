#include "User.h"
#include <string>
#include <iostream>
using namespace std;

/* 
// This function adds a User object to a User object array
// Inputs: string of username, an array of User objects, int number of book ratings, int number of User objects stored in the array, int number size of User object array
// Returns: int number of User objects stored in the array
*/

int addUser(string userName, User users[], int numRatings, int numUsersStored, int usersArrSize)
{
    if (numUsersStored >= usersArrSize) //Makes sure the array isn't already full
    {
        return -2;
    }
    for (int i = 0; i < numUsersStored; i++) //Makes sure the username isn't already taken
    {
        if (users[i].getUsername() == userName)
        {
            return -1;
        }
    }
    if (userName == "") //Makes sure the username isn't empty
    {
        return -1;
    }

    users[numUsersStored].setUsername(userName);
    users[numUsersStored].setNumRatings(0);
    numUsersStored++;
    
    return numUsersStored;
}

int main()
{
    string userName;
    User users[100];
    int numRatings = 0;
    int numUsersStored = 0;
    int usersArrSize = 100;
    int function;

    cout << "Enter username: " << endl;
    getline(cin, userName);
    function = addUser(userName, users, numRatings, numUsersStored, usersArrSize);
    if (function == -2)
    {
        cout << "User database is full. Please contact administrator." << endl;
    }
    if (function == -1)
    {
        cout << "Username is already taken or you entered and invalid username. Please try again." << endl;
    }

    cout << users[0].getUsername() << endl;
    cout << users[0].getNumRatings() << endl;

    return 0;
}