#include "Book.h"
#include "User.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/* 
// This function converts a string to all lowercase in order for case insensitive identification
// Inputs: string to convert
// Returns: converted to lowercase string
*/

string toLower(string username)
{
    for (int i = 0; i < username.length(); i++)
    {
        if (username[i] >= 65 && username[i] <= 90)
        username[i] = username[i] + 32;
    }

    return username;
}

/* 
// This function returns a specfic user's rating of a specific book
// Inputs: string of username, string of title, array of User objects, array of Book objects, int number of Users in array, int number of Books in array
// Returns: int number rating of specified user's rating of specified book
*/

int getRating(string username, string title, User users[], Book books[], int numUsers, int numBooks)
{
    username = toLower(username);
    string tempName;
    title = toLower(title);

    for (int i = 0; i < numUsers; i++)
    {
        tempName = users[i].getUsername();
        tempName = toLower(tempName);
        users[i].setUsername(tempName);
    }

    for (int i = 0; i < numBooks; i++)
    {
        tempName = books[i].getTitle();
        tempName = toLower(tempName);
        books[i].setTitle(tempName);
    }

    for (int i = 0; i < numUsers; i++)
    {
        if (users[i].getUsername() == username)
        {
            for (int j = 0; j < numBooks; j++)
            {
                if (books[j].getTitle() == title)
                {
                    return users[i].getRatingAt(j);
                }
            }
        }
    }
    
    return -3;
}

int main()
{
    string username;
    string title;
    User users[100];
    Book books[10000];
    int numUsers = 100; // Just for testing purposes.
    int numBooks = 50; // Just for testing purposes.

    cout << "Enter username: " << endl;
    getline(cin, username);
    cout << "Enter a book title: " << endl;
    getline(cin, title);

    cout << username << "'s rating for " << title << " is " << getRating(username, title, users, books, numUsers, numBooks) << endl;
}