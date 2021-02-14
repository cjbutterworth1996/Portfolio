#include "User.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
    int ratings[50];
    const int SIZE = 50;

    for (int i = 0; i < SIZE; i++)
    {
       ratings[i] = 0;
    }

    User user1;
    User user2("Collin", ratings, 3);

    cout << "User 1: " << user1.getUsername() << " " << user1.getNumRatings() << endl;
    for (int i = 0; i < user1.getNumRatings(); i++)
    {
        cout << user1.getRatingAt(i) << endl;
    }
    cout << "User 2: " << user2.getUsername() << " " << user2.getNumRatings() << endl;
    for (int i = 0; i < user2.getNumRatings(); i++)
    {
        cout << user2.getRatingAt(i) << endl;
    }

    cout << "Size: " << user1.getSize() << endl;

    user1.setUsername("Butterworth");
    user1.setRatingAt(3, 5);
    user1.setNumRatings(4);

    cout << user1.getUsername() << endl;
    cout << user1.getRatingAt(3) << endl;
    cout << user1.getNumRatings() << endl;

    return 0;
}