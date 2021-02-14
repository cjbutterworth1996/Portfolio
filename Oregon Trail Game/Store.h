#ifndef Store_H
#define Store_H
#include <string>
using namespace std;

class Store
{
public:
    Store();
    double set_multiplier(double value);
    double get_multiplier() const;
    int get_storeNumber() const;
    int set_storeNumber(int value);

private:
    double multiplier; //Multiplier for increasing prices
    int storeNumber; //Keeps track of how many stores you've passed so far
};
#endif