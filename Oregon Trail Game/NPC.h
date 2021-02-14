#ifndef NPC_H
#define NPC_H
#include <string>
using namespace std;

class NPC
{
public:
    NPC();
    NPC(string name, int health, string condition);
    string set_name(string name);
    string set_condition(string condition);
    int set_health(int health);
    string get_name() const;
    int get_health() const;
    string get_condition() const;

private:
    string name; //Name of NPC
    string condition; //Condition (ailment) if any of NPC
    int health; //Health of NPC

};
#endif