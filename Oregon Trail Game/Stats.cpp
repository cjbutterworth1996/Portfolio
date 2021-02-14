#include "Stats.h"
#include "Months.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Stats::Stats() //Only month and days can be chosen by the player
{
    mile = 0;
    money = 1600;
    month = 3;
    day = 28;
    oxen = 0;
    food = 0;
    bullets = 0;
    wagonParts = 0;
    aidKits = 0;
    party = 5;
    milestone = 0;

    ifstream monthsFile;
    ifstream milestonesFile;
    const int NUM_MONTHS = 9;
    const int NUM_MILESTONES = 16;
    string line;
    int temp;
    
    monthsFile.open("months.txt"); //fills out array of month objects
    if (monthsFile.fail())
    {
        cout << "Something went wrong. Please check that \"months.txt\" is in the game directory." << endl;
    }
    
    for (int i = 0; i < NUM_MONTHS; i++)
    {
        getline(monthsFile, line);
        months[i].set_month(line);
        getline(monthsFile, line);
        temp = stoi(line);
        months[i].set_days(temp);
    }

    monthsFile.close();

    milestonesFile.open("milestones.txt"); 
    if (milestonesFile.fail())
    {
        cout << "Something went wrong. Please check that \"milestones.txt\" is in the game directory." << endl;
    }

    for (int i = 0; i < NUM_MILESTONES; i++) //fills out milestones array and distance to milestones array
    {
        getline(milestonesFile, line);
        milestones[i] = line;
        getline(milestonesFile, line);
        temp = stoi(line);
        milestonesMiles[i] = temp;
    }
}

int Stats::set_mile(int miles) //Sets current mile
{
    mile = miles;
    return mile;
}

double Stats::set_money(double moneys) //Sets money
{
    money = moneys;
    return money;
}

int Stats::set_month(int months) //Sets indice for months object array
{
    month = months;
    return month;
}

int Stats::set_day(int days) //Sets day
{
    day = days;
    return day;
}

int Stats::set_oxen(int oxens) //Sets oxen
{
    oxen = oxens;
    return oxen;
}

int Stats::set_food(int foods) //Sets pounds of food
{
    food = foods;
    return food;
}

int Stats::set_bullets(int bullets1) //Sets bullets
{
    bullets = bullets1;
    return bullets;
}

int Stats::set_wagonParts(int parts) //Sets wagon parts
{
    wagonParts = parts;
    return wagonParts;
}

int Stats::set_aidKits(int kits) //Sets first aid kits
{
    aidKits = kits;
    return aidKits;
}

int Stats::get_mile() //Returns current mile
{
    return mile;
}

double Stats::get_money() const //Returns money
{
    return money;
}

int Stats::get_month() const //Returns indice for months object array
{
    return month;
}

int Stats::get_day() const //Returns day
{
    return day;
}

int Stats::get_oxen() const //Returns oxen
{
    return oxen;
}

int Stats::get_food() const //Returns pounds of food
{
    return food;
}

int Stats::get_bullets() const //Returns bullets
{
    return bullets;
}

int Stats::get_wagonParts() const //Returns wagon parts
{
    return wagonParts;
}

int Stats::get_aidKits() const //Returns first aid kits
{
    return aidKits;
}

int Stats::get_party() const //Returns number of people still in party (alive)
{
    return party;
}

int Stats::set_party(int number) //Sets number of people still in party (alive)
{
    party = number;
    return party;
}

void Stats::print_stats() // Prints stats at the beginning of each turn
{
    cout << "=======================================================================" << endl;
    cout << "Monday " << endl;
    cout << day << " " << months[month - 3].get_month() << endl; //Uses an array of Months objects
    cout << "Total mileage is: " << mile << endl;
    cout << "Next milestone is: " << get_next_milestone() << endl;
    cout << " in " << get_distance() - get_mile() << " miles" << endl;
    cout << "Total money remaining: $" << money << endl;
    cout << "Oxen: " << "     " << "Food: (lbs)" << "     " << "Bullets: " << "     " << "Wagon parts: " << "     " << "First aid kits: " << endl;
    cout << oxen << "          " << food << "          " << bullets << "             " << wagonParts << "                 " << aidKits << endl;
    cout << "=======================================================================" << endl;
}

string Stats::get_next_milestone() const //Returns name of next milestone
{
    return milestones[milestone];
}

string Stats::set_next_milestone() //Goes to the next milestone
{
    milestone++;
    return milestones[milestone];
}

int Stats::get_distance() const //Returns distance to next milestone
{
    return milestonesMiles[milestone];
}

int Stats:: get_milestoneNumber() const //Returns milestone array indice number. Mainly for determining forts
{
    return milestone;
}