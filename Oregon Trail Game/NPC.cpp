#include "NPC.h"
#include <string>
using namespace std;

NPC::NPC() //Default constructor for testing purposes only
{
    name = "Connor";
    health = 100;
    condition = "none";
}

NPC::NPC(string name1, int health1, string condition1) //Main constructor for NPCS. Includes name, health, and condition.
{
    name = name1;
    health = health1;
    condition = condition1;
}

string NPC::set_name(string name1) //Changes name of NPC
{
    name = name1;
    return name;
}
int NPC::set_health(int health1) //Changes health of NPC
{
    health = health1;
    return health;
}
string NPC::set_condition(string condition1) //Changes condition (ailment) of NPC
{
    condition = condition1;
    return condition;
}

string NPC::get_name() const //Returns name of NPC
{
    return name;
}

int NPC::get_health() const //Returns health of NPC
{
    return health;
}

string NPC::get_condition() const //Returns condition of NPC
{
    return condition;
}