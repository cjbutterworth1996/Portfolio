#include "Months.h"
#include <string>
using namespace std;

Months::Months()
{
    name = "temp";
    days = 0;
}

Months::Months(string name1, int days1) //Name of month and days in said month
{
    name = name1;
    days = days1;
}

string Months::set_month(string name1) //Changes the name of the month
{
    name = name1;
    return name;
}

int Months::set_days(int days1) //Changes how many days in said month
{
    days = days1;
    return days;
}

string Months::get_month() const //Returns name of month
{
    return name;
}

int Months::get_days() const //Returns days in month
{
    return days;
}