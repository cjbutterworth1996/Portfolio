#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User
{
public:
    User();
    User(string username, int ratings[], int numRatings);
    string getUsername() const;
    void setUsername(string);
    int getRatingAt(int);
    bool setRatingAt(int, int);
    int getNumRatings() const;
    void setNumRatings(int);
    int getSize() const;

private:
    string username;
    static const int size = 50;
    int ratings[50];
    int numRatings;
};
#endif