#ifndef MONTHS_H
#define MONTHS_H
#include <string>
using namespace std;

class Months
{
public:
    Months();
    Months(string name, int days);
    string set_month(string name);
    int set_days(int days);
    int get_days() const;
    string get_month() const;

private:
    int days; //Days in month
    string name; //Name of month
    
};
#endif