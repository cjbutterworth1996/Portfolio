#include "User.h"
#include <string>
using namespace std;

User::User()
{
    username = "";
    numRatings = 0;

    for (int i = 0; i < size; i++)
    {
        ratings[i] = 0;
    }
}

User::User(string username1, int ratings1[], int numRatings1)
{
    username = username1;
    numRatings = numRatings1;

    if (numRatings > 50)
    {
        numRatings = 50;
    }

    for (int i = 0; i < size; i++)
    {
        ratings[i] = ratings1[i];
    }
}

string User::getUsername() const
{
    return username;
}

void User::setUsername(string username1)
{
    username = username1;
}

int User::getRatingAt(int index)
{
    if (index >= size || index < 0)
    {
        return -1;
    }
    else
    {
        return ratings[index];
    }
}

bool User::setRatingAt(int index, int value)
{
    if (index >= size || index < 0)
    {
        return false;
    }
    if (value > 5 || value < 0)
    {
        return false;
    }

    ratings[index] = value;
    return true;
}

int User::getNumRatings() const
{
    return numRatings;
}

void User::setNumRatings(int i)
{
    numRatings = i;
}

int User::getSize() const
{
    return size;
}