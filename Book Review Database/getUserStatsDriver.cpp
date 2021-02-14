#include "User.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

/* 
// This function prints a specfic user's average rating
// Inputs: string of username, array of User objects, int number of Users in array, int number of Books in array
// Returns: abstract integer based on what the function accomplished
*/

int getUserStats(string username, User users[], int numUsersStored, int numBooksStored)
{
    double count = 0;
    double avgTotal = 0;
    double temp;
    double avg;

    for (int i = 0; i < numUsersStored; i++)
    {
        if (users[i].getUsername() == username)
        {
            for (int j = 0; j < numBooksStored; j++)
            {
                if (users[i].getRatingAt(j) != 0)
                {
                    count++;
                    temp = users[i].getRatingAt(j);
                    avgTotal += temp;
                }
            }

            if (count > 0) //Prevents dividing by 0
            {
                avg = avgTotal / count;
            }

            if (count == 0)
            {
                cout << username << " has not rated any books." << endl;
                return 0;
            }
            else
            {
                cout << username << " rated " << fixed << setprecision(0) << count << " books" << endl;
                cout << username << "'s average rating was " << fixed << setprecision(2) << avg << endl;
                return 1;
            }

            count = 0;
            avgTotal = 0;
        }
    }

    cout << username << " does not exist." << endl;
    return -3; 
}

int main()
{
    string username;
    User users[100];
    int numUsersStored = 3; //For testing purposes.
    int numBooksStored = 3; //For testing purposes.

    users[0].setUsername("User1");
    users[0].setNumRatings(3);
    users[0].setRatingAt(0,0);
    users[0].setRatingAt(1,0);
    users[0].setRatingAt(2,0);
    users[1].setUsername("User2");
    users[1].setNumRatings(3);
    users[1].setRatingAt(0,4);
    users[1].setRatingAt(1,1);
    users[1].setRatingAt(2,2);
    users[2].setUsername("User3");
    users[2].setNumRatings(3);
    users[2].setRatingAt(0,5);
    users[2].setRatingAt(1,5);
    users[2].setRatingAt(2,4);
    
    getUserStats("User1", users, numUsersStored, numBooksStored);
    getUserStats("User2", users, numUsersStored, numBooksStored);
    getUserStats("User3", users, numUsersStored, numBooksStored);

    return 0;
}