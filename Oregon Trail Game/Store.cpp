#include "Store.h"
#include <string>
#include <iostream>
#include "Stats.h"

using namespace std;

Store::Store()
{
    multiplier = 1; //This gets multiplied by a constant int with a value of 1.2 * storeNumber
    storeNumber = 1;
}

double Store::set_multiplier(double value) //sets multiplier for prices
{
    multiplier = value;
    return multiplier;
}

double Store::get_multiplier() const //returns multiplier for prices
{
    return multiplier;
}

int Store::set_storeNumber(int value) //sets store number (how many you've passed so far)
{
    storeNumber = value;
    return storeNumber;
}

int Store::get_storeNumber() const //returns store number (how many you've passed so far)
{
    return storeNumber;
}