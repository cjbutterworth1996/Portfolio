#ifndef Stats_H
#define Stats_H
#include <string>
#include "Months.h"
using namespace std;

class Stats
{
public:
    Stats();
    Stats(int mile, int money, int month, int day);
    int get_mile();
    double get_money() const;
    int get_month() const;
    int get_day() const;
    int set_mile(int mile);
    double set_money(double money);
    int set_month(int month);
    int set_day(int day);
    int set_oxen(int oxen);
    int set_food(int food);
    int set_bullets(int bullets);
    int set_wagonParts(int wagonParts);
    int set_aidKits(int aidKits);
    int get_oxen() const;
    int get_food() const;
    int get_bullets() const;
    int get_wagonParts() const;
    int get_aidKits() const;
    void print_stats();
    int get_party() const;
    int set_party(int number);
    string get_next_milestone() const;
    string set_next_milestone();
    int get_distance() const;
    int get_milestoneNumber() const;

private:
    int mile; //Current mile
    double money; //Money
    int month; //Months object array indice
    int day; //Day
    int oxen; //Oxen
    int food; //Food in pounds
    int bullets; //Bullets
    int wagonParts; //Wagon parts
    int aidKits; //First aid kits
    Months months[9]; //Array of Months objects
    int party; //Number of party members still alive
    string milestones[16]; //String array of milestone names
    int milestonesMiles[16]; //array of milestone distances
    int milestone; //array indice of which milestone you are at
};
#endif