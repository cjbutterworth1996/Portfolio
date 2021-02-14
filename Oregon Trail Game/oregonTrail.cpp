#include <iostream>
#include <string>
#include "NPC.h"
#include "Stats.h"
#include "Months.h"
#include "Store.h"
#include <fstream>
#include <cmath>

using namespace std;

double rounding(double price, double multiplier) //This function rounds numbers to 2 decimal places, to ensure store prices and money doesn't display with more than 2 decimal places
{
    price = price * multiplier;
    price = ceil(price * 100.0) / 100.0;
    return price;
}

int main()
{
    string playerName; //temp holder for user name
    string name; //temp holder for NPC names
    string names[5]; //temp array for NPC names
    char choice; //for initial choice of starting at default date or not
    int month = 0; //temp value for months
    int day = 0; //temp value for days
    ifstream storeFile; //store info
    string line; //temp value for reading files
    int option = 0; //temp value for choices
    Months months[9]; //array of month objects
    const int NUM_MONTHS = 9; //number of playable months
    ifstream monthsFile; //for filling months array
    int temp = 0; //temp value
    int purchase = 0; //temp value for store
    Stats stats; //initializing stats
    double bill; //keeps track of money spent per store session
    Store store; //initializing store
    double price = 0; //temp value for store price
    double purchaseFood = 0; //temp value for purchasing food
    int rest = 0; //determines how long you rest
    bool atFort = false; //determines if you are at a fort
    int miles = 0; //temp value for calculating miles traveled
    int option2 = 0; //temp value for choices
    double multiplier = 1; //temp values for store prices getting higher
    const int FOOD_PER_DAY = 3; //lbs. per person per day
    const int TRAVEL_TIME = 14; //days per travel period
    bool rabbit = false; //determines if you find a rabbit
    bool fox = false; //determines if you find a fox
    bool deer = false; //determines if you find a deer
    bool bear = false; //determines if you find a bear
    bool moose = false; //determines if you find a moose
    int option3 = 0; //temp value for choices
    int guess = 0; //temp value for minigames
    int guess2 = 0; //temp value for minigames
    int guess3 = 0; //temp value for minigames
    const int MAX_FOOD = 1000; //maximum amount of food
    int temp2 = 0; //temp value
    int temp3 = 0; //temp value
    int temp4 = 0; //temp value
    int temp5 = 0; //temp value
    NPC party[5]; //array of party members
    ifstream ailmentsFile; //file containing possible ailments
    string ailments[6]; //array of possible ailments
    const int NUM_AILMENTS = 6; // number of possible ailments
    int weight = 0; //weighted chance of dying from ailments
    bool used = false; //first aid kit used or not
    const int PARTY_ARR_SIZE = 5; // size of party array
    int option4 = 0; //temp value for choices
    ofstream statsFile; //file where ending stats get written to
    bool atStart = true; //determines if you have left the starting town yet
    bool atLandmark = false; //determines if you're at a landmark or not
    int turn = 1; //lets you know which turn you're on
    double dubtemp = 0; //temp value
    bool hunt = false; //determines if you hunted that day or not
    const double STORE_MULTIPLIER = 0.25; //Percentage price increase per store

    ailmentsFile.open("Ailments.txt"); //Fills ailments array
    if (ailmentsFile.fail())
    {
        cout << "Something went wrong. Please check that \"Ailments.txt\" is in the game directory." << endl;
        return 0;
    }
    for (int i = 0; i < NUM_AILMENTS; i++)
    {
        getline(ailmentsFile, line);
        ailments[i] = line;
    }
    ailmentsFile.close();

    monthsFile.open("months.txt"); //Fills months array
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

    cout << "Welcome to the Oregon Trail! In this game, the point is to make it to your destination, Oregon City before the end date of November 30th, 1847.\n";
    cout << "You and your family of five will traverse a total of 2040 miles to get there from your starting point in Independence, Missouri. Good luck!" << endl;

    cout << "Please enter your name: " << endl;
    getline(cin, playerName);
    NPC player(playerName, 100, "none");

    cout << "Enter the names of your family members: " << endl;
    for (int i = 0; i < 4; i++)
    {
        getline(cin, name);
        names[i] = name;
    }
    NPC fam1 (names[0], 100, "none");
    NPC fam2 (names[1], 100, "none");
    NPC fam3 (names[2], 100, "none");
    NPC fam4 (names[3], 100, "none");
    NPC wagon; //Wagon is considered an NPC because the only functionality it has is health. Its name is Connor.
    party[0] = player; //Filling out party array to determine who is alive (used later)
    party[1] = fam1;
    party[2] = fam2;
    party[3] = fam3;
    party[4] = fam4;

    cout << "Would you like to start on the default date of 03/28/1847? (y/n)" << endl; //Choice of when to start
    cin >> choice; //if user inputs something other than 'y' or 'n', it defaults to 'y'
    if (choice == 'n')
    {
        cout << "Please choose starting month. (3 - 5)" << endl;
        while(month < 3 || month > 5) //Using while loops like this prevents user from inputting something random
        {
            cin.clear(); //This
            cin.ignore();//and this prevents users from entering infinite loops due to pressing something other than what is expected
            cin >> month;
        }
        if (month == 5) //If you choose May, you have to start on the 1st
        {
            day = 1;
        }
        else if (month == 3)
        {
            cout << "Please choose starting day. (1-31)" << endl;
            while (day < 1 || day > 31)
            {
                cin.clear();
                cin.ignore();
                cin >> day;
            }
        }
        else if (month == 4)
        {
            cout << "Please choose starting day. (1-30)" << endl;
            while (day < 1 || day > 30)
            {
                cin.clear();
                cin.ignore();
                cin >> day;
            }
        }

        stats.set_month(month); //Updating stats with user's choices
        stats.set_day(day);
    }
    else
    {
        Stats stats();
    }
    
    storeFile.open("store_info.txt");
    if (storeFile.fail())
    {
        cout << "Something went wrong. Please make sure \"store_info.txt\" is in the main game folder." << endl; //makes sure the file is present
        return 0;
    }
    while (getline(storeFile, line)) //prints the content of the file
    {
        if (line != "")
        {
            for (int i = 0; i < line.length(); i++)
            {
                cout << line[i];
            }
            cout << endl;
        }
    }
    storeFile.close();

    while (option != 6) //Store loop
    {
        stats.print_stats();

        cout << "1. Oxen" << endl;
        cout << "2. Food" << endl;
        cout << "3. Bullets" << endl;
        cout << "4. Wagon parts" << endl;
        cout << "5. Medical aid kits" << endl;
        cout << "6. Leave" << endl;

        cin.clear();
        cin.ignore();
        cin >> option;
        if (stats.get_oxen() < 6 && option != 1) //Prevents user from accidentally starting without Oxen.
        {
            cout << "You must purchase at least $100 worth of oxen before purchasing anything else!" << endl;
            option = 1;
        }
        if (option == 1)
        {
            price = 40.0;
            price = rounding(price, store.get_multiplier()); //Prevents 3 digit decimal prices
            cout << "How many yokes of oxen would you like to purchase?" << endl;
            cin >> purchase;
            if (purchase * price > stats.get_money()) //Prevents using more money than user has
            {
                cout << "You don't have enough money to do that." << endl;
            }
            else
            {
                if (stats.get_oxen() >= 10) //Prevents user from having more than 10 oxen
                {
                    cout << "You already have the maximum amount of oxen!" << endl;
                }
                else
                {
                    if ((purchase * 2) + stats.get_oxen() > 10) //Prevents user from having more than 10 oxen
                    {
                        cout << "You can only have 10 oxen at one time!" << endl;
                    }
                    else
                    {
                        cout << "You purchased " << purchase * 2 << " oxen!" << endl;
                        stats.set_oxen(stats.get_oxen() + (purchase * 2));
                        cout << "You now have " << stats.get_oxen() << " oxen!" << endl;
                        bill += (purchase * price);
                        stats.set_money(stats.get_money() - (price * purchase));
                        cout << "Your bill is: " << bill << endl;
                    }
                }  
            } 
        }
        if (option == 2)
        {
            price = 0.50;
            price = rounding(price, store.get_multiplier()); //Prevents 3 digit decimals in prices
            cout << "How many pounds of food would you like to purchase?" << endl;
            cin >> purchaseFood;
            if (purchaseFood * price > stats.get_money())
            {
                cout << "You don't have enough money to do that." << endl; //Prevents using more money than user has
            }
            else
            {
                if (purchaseFood + stats.get_food() > MAX_FOOD)
                {
                    cout << "Your wagon can only carry 1000 lbs. of food!" << endl; //Prevents user from having more than 1000lbs. of food
                }
                else
                {
                    cout << "You purchased " << purchaseFood << " lbs. of food!" << endl;
                    stats.set_food(stats.get_food() + purchaseFood);
                    cout << "You now have " << stats.get_food() << " lbs. of food!" << endl;
                    bill += (purchaseFood * price);
                    stats.set_money(stats.get_money() - (purchaseFood * price));
                    cout << "Your bill is: " << bill << endl;        
                }
            }
        }
        if (option == 3)
        {
            price = 2.0;
            price = rounding(price, store.get_multiplier()); //Prevents 3 digit decimals in prices
            cout << "How many boxes of bullets would you like to purchase?" << endl;
            cin >> purchase;
            if (purchase * price > stats.get_money())
            {
                cout << "You don't have enough money to do that." << endl; //Prevents using more money than user has
            }
            else
            {
                cout << "You purchased " << purchase * 20 << " bullets!" << endl;
                stats.set_bullets(stats.get_bullets() + (purchase * 20));
                cout << "You now have " << stats.get_bullets() << " bullets!" << endl;
                bill += (purchase * price);
                cout << "Your bill is: " << bill << endl;
                stats.set_money(stats.get_money() - (purchase * price));
            }
        }
        if (option == 4)
        {
            price = 20.0;
            price = rounding(price, store.get_multiplier()); //Prevents 3 digit decimals in prices
            cout << "How many wagon parts would you like to purchase?" << endl;
            cin >> purchase;
            if (purchase * price > stats.get_money())
            {
                cout << "You don't have enough money to do that." << endl; //Prevents using more money than user has
            }
            else
            {
                cout << "You purchased " << purchase << " wagon parts!" << endl;
                stats.set_wagonParts(stats.get_wagonParts() + purchase);
                cout << "You now have " << stats.get_wagonParts() << " wagon parts!" << endl;
                bill += (purchase * price);
                cout << "Your bill is: " << bill << endl;
                stats.set_money(stats.get_money() - (purchase * price));
            }
        }
        if (option == 5)
        {
            price = 25.0;
            price = rounding(price, store.get_multiplier()); //Prevents 3 digit decimals in prices
            cout << "How many first aid kits would you like to purchase?" << endl;
            cin >> purchase;
            if (purchase * price > stats.get_money()) //Prevents using more money than user has
            {
                cout << "You don't have enough money to do that." << endl;
            }
            else
            {
                cout << "You purchased " << purchase << " first aid kits!" << endl;
                stats.set_aidKits(stats.get_aidKits() + purchase);
                cout << "You now have " << stats.get_aidKits() << " first aid kits!" << endl;
                bill += (purchase * price);
                cout << "Your bill is: " << bill << endl;
                stats.set_money(stats.get_money() - (purchase * price));
            }
        }
        if (option == 6)
        {
            cout << "Okay, partner, well I hope those supplies do you well out there on the Trail! Good luck!" << endl;
        }
    }

    option = 0;

    while (stats.get_mile() < 2040) //Main gameplay loop
    {
        hunt = false; //Resets hunting check to see if you hunted today
        option2 = 0; //resets option2 to prevent auto looping
        option = 0; //resets option to prevent auto looping
        stats.print_stats(); //prints the stats

        cout << "What would you like to do today?" << endl;
        cout << "1. Stop to rest" << endl;
        cout << "2. Continue on the trail" << endl;
        cout << "3. Hunt" << endl;
        cout << "4. Quit" << endl;

        cin.clear();
        cin.ignore();
        cin >> option;
        if (atStart == true) //If you are at the starting town and try to do anything but leave, this forces you to leave.
        {
            if (option == 1 || option == 3)
            {
                cout << "You must leave town first." << endl;
                option = 2;
            }
        }

        if (stats.get_oxen() <= 0) //Failure condition for 0 oxen
        {
            cout << "Your last oxen has died. You hike for another 10 days before dying of heat exhaustion. Bummer." << endl;
            statsFile.open("results.txt");
            statsFile << "Leader: " << player.get_name() << endl;
            statsFile << "Miles travelled: " << stats.get_mile() << endl;
            statsFile << "Food remaining: " << stats.get_food() << endl;
            statsFile << "Cash remaining: " << stats.get_money() << endl;
            statsFile.close();
            return 0;
        }
        if (stats.get_food() <= 0) //Failure condition for 0 food
        {
            cout << "You ran out of food and died of starvation. Bummer." << endl;
            statsFile.open("results.txt");
            statsFile << "Leader: " << player.get_name() << endl;
            statsFile << "Miles travelled: "<< stats.get_mile() << endl;
            statsFile << "Food remaining: " << stats.get_food() << endl;
            statsFile << "Cash remaining: " << stats.get_money() << endl;
            statsFile.close();
            return 0;
        }
        if (player.get_health() == 0) //Failure condition for ailments
        {
            cout << "You died of " << player.get_condition() << ". Bummer." << endl;
            statsFile.open("results.txt");
            statsFile << "Leader: " << player.get_name() << endl;
            statsFile << "Miles travelled: " << stats.get_mile() << endl;
            statsFile << "Food remaining: " << stats.get_food() << endl;
            statsFile << "Cash remaining: " << stats.get_money() << endl;
            statsFile.close();
            return 0;
        }
        if (wagon.get_health() == 0 && stats.get_wagonParts() == 0) //Failure condition for wagon breaking down
        {
            cout << "Your wagon broke down and you have no wagon parts to fix it with. You hike for another 10 days before dying of thirst. Bummer." << endl;
            statsFile.open("results.txt");
            statsFile << "Leader: " << player.get_name() << endl;
            statsFile << "Miles travelled: " << stats.get_mile() << endl;
            statsFile << "Food remaining: " << stats.get_food() << endl;
            statsFile << "Cash remaining: " << stats.get_money() << endl;
            statsFile.close();
            return 0;
        }
        if (months[stats.get_month() - 3].get_month() == "November" && stats.get_day() == 30) //Failure condition for time limit
        {
            cout << "You failed to reach Oregon City before winter. You and your family freeze to death due to your gross incompetence." << endl;
            statsFile.open("results.txt");
            statsFile << "Leader: " << player.get_name() << endl;
            statsFile << "Miles travelled: " << stats.get_mile() << endl;
            statsFile << "Food remaining: " << stats.get_food() << endl;
            statsFile << "Cash remaining: " << stats.get_money() << endl;
            statsFile.close();
            return 0;
        }

        if (option == 1) //Resting
        {
            rest = rand() % 3 + 1; //Determines how long you rest
            switch (rest)
            {
                case 1:
                    cout << "You rest 1 day." << endl;
                    day = stats.get_day();
                    if (day + 1 > months[stats.get_month() - 3].get_days())
                    {
                        day = 1;
                        stats.set_month(stats.get_month() + 1);
                    }
                    else
                    {
                        day++;
                    }
                    stats.set_day(day);
                    stats.set_food(stats.get_food() - (FOOD_PER_DAY * rest * stats.get_party()));
                    break;
                case 2:
                    cout << "You rest 2 days." << endl;
                    day = stats.get_day();
                    for (int i = 0; i < 2; i++)
                    {
                        if (day + 1 > months[stats.get_month() - 3].get_days())
                        {
                            day = 1;
                            stats.set_month(stats.get_month() + 1);
                        }
                        else
                        {
                            day++;
                        }
                        stats.set_day(day);
                    }
                    stats.set_food(stats.get_food() - (FOOD_PER_DAY * rest * stats.get_party()));
                    break;
                case 3:
                    cout << "You rest 3 days." << endl;
                    day = stats.get_day();
                    for (int i = 0; i < 3; i++)
                    {
                        if (day + 1 > months[stats.get_month() - 3].get_days())
                        {
                            day = 1;
                            stats.set_month(stats.get_month() + 1);
                        }
                        else
                        {
                            day++;
                        }
                        stats.set_day(day);
                    }
                    stats.set_food(stats.get_food() - (FOOD_PER_DAY * rest * stats.get_party()));
                    break;
            }
        }
        if (option == 2) //Continuing on the trail
        {
            atStart = false;
            if (stats.get_oxen() < 4) //These statements determine how many miles you travel in a two-week period based on how many oxen you have
            {
                miles = rand() % 19 + 70; // 19 is the range, 70 is the base. (70 - 88)
            }
            else if (stats.get_oxen() >= 4 && stats.get_oxen() < 6) 
            {
                miles = rand() % 18 + 88; // (88 - 105)
            }
            else if (stats.get_oxen() >=6 && stats.get_oxen() < 8)
            {
                miles = rand() % 19 + 113; // (105 - 123)
            }
            else if (stats.get_oxen() >= 8)
            {
                miles = rand() % 18 + 123; // (123 - 140)
            }

            if (stats.get_mile() + miles >= stats.get_distance()) //Determines if player gets stopped at a landmark
            {
                option = 0; //Resets option to prevent auto-looping
                atLandmark = true;
                if(atFort == true) //Different text for if you rest at a fort
                {
                    cout << "You are still at " << stats.get_next_milestone() << "." << endl;
                }
                else //Flavor text for landmarks
                {
                    cout << " You were prepared to go " << miles << " miles, but you arrived at " << stats.get_next_milestone() << "." << endl;
                }
                stats.set_mile(stats.get_distance());
                day = stats.get_day();
                for (int i = 0; i < TRAVEL_TIME; i++) //This loop determines if the month needs to get changed and prevents days from going over the amount of days in that month
                    {
                        if (day + 1 > months[stats.get_month() - 3].get_days())
                        {
                            day = 1;
                            stats.set_month(stats.get_month() + 1);
                        }
                        else
                        {
                            day++;
                        }
                        stats.set_day(day);
                    }
                stats.set_food(stats.get_food() - (FOOD_PER_DAY * TRAVEL_TIME * stats.get_party()));
                if (stats.get_milestoneNumber() == 2 || stats.get_milestoneNumber() == 4 || stats.get_milestoneNumber() == 7 || stats.get_milestoneNumber() == 10 || stats.get_milestoneNumber() == 12 || stats.get_milestoneNumber() == 14)
                {
                    store.set_multiplier(multiplier + STORE_MULTIPLIER);
                    while (option2 != 3)
                    {
                        cout << "What do you want to do?" << endl;
                        cout << "1. Visit the store" << endl;
                        cout << "2. Rest" << endl;
                        cout << "3. Continue on the trail" << endl;

                        cin.clear();
                        cin.ignore();
                        cin >> option2;
                        if(atFort == true)
                        {
                            cout << "You are still at " << stats.get_next_milestone() << "." << endl;
                            stats.print_stats();
                        }
                        if (option2 == 1)
                        {
                            bill = 0;
                            while (option != 6) //Apart from price increases, this section is a repeat of the first store, just at a fort instead
                            {
                                stats.print_stats();

                                cout << "1. Oxen" << endl;
                                cout << "2. Food" << endl;
                                cout << "3. Bullets" << endl;
                                cout << "4. Wagon parts" << endl;
                                cout << "5. Medical aid kits" << endl;
                                cout << "6. Leave" << endl;

                                cin.clear();
                                cin.ignore();
                                cin >> option;
                                if (option == 1)
                                {
                                    price = 40.0;
                                    price = rounding(price, store.get_multiplier()); //Rounds prices to 2 decimal places and includes new store multiplier
                                    cout << "How many yokes of oxen would you like to purchase?" << endl;
                                    cin >> purchase;
                                    if (purchase * price > stats.get_money())
                                    {
                                        cout << "You don't have enough money to do that." << endl;
                                    }
                                    else
                                    {
                                        if (stats.get_oxen() >= 10)
                                        {
                                            cout << "You already have the maximum amount of oxen!" << endl;
                                        }
                                        else
                                        {
                                            if ((purchase * 2) + stats.get_oxen() > 10)
                                            {
                                                cout << "You can only have 10 oxen at one time!" << endl;
                                            }
                                            else
                                            {
                                                cout << "You purchased " << purchase * 2 << " oxen!" << endl;
                                                stats.set_oxen(stats.get_oxen() + (purchase * 2));
                                                cout << "You now have " << stats.get_oxen() << " oxen!" << endl;
                                                bill += (purchase * price);
                                                stats.set_money(stats.get_money() - (price * purchase));
                                                cout << "Your bill is: " << bill << endl;
                                            }
                                        }  
                                    } 
                                }
                                if (option == 2)
                                {
                                    price = 0.50;
                                    price = rounding(price, store.get_multiplier());
                                    cout << "How many pounds of food would you like to purchase?" << endl;
                                    cin >> purchaseFood;
                                    if (purchaseFood * price > stats.get_money())
                                    {
                                        cout << "You don't have enough money to do that." << endl;
                                    }
                                    else
                                    {
                                        if (purchaseFood + stats.get_food() > MAX_FOOD)
                                        {
                                            cout << "Your wagon can only carry 1000 lbs. of food!" << endl;
                                        }
                                        else
                                        {
                                            cout << "You purchased " << purchaseFood << " lbs. of food!" << endl;
                                            stats.set_food(stats.get_food() + purchaseFood);
                                            cout << "You now have " << stats.get_food() << " lbs. of food!" << endl;
                                            bill += (purchaseFood * price);
                                            stats.set_money(stats.get_money() - (purchaseFood * price));
                                            cout << "Your bill is: " << bill << endl; 
                                        }    
                                    }
                                }
                                if (option == 3)
                                {
                                    price = 2.0;
                                    price = rounding(price, store.get_multiplier());
                                    cout << "How many boxes of bullets would you like to purchase?" << endl;
                                    cin >> purchase;
                                    if (purchase * price > stats.get_money())
                                    {
                                        cout << "You don't have enough money to do that." << endl;
                                    }
                                    else
                                    {
                                        cout << "You purchased " << purchase * 20 << " bullets!" << endl;
                                        stats.set_bullets(stats.get_bullets() + (purchase * 20));
                                        cout << "You now have " << stats.get_bullets() << " bullets!" << endl;
                                        bill += (purchase * price);
                                        cout << "Your bill is: " << bill << endl;
                                        stats.set_money(stats.get_money() - (purchase * price));
                                    }
                                }
                                if (option == 4)
                                {
                                    price = 20.0;
                                    price = rounding(price, store.get_multiplier());
                                    cout << "How many wagon parts would you like to purchase?" << endl;
                                    cin >> purchase;
                                    if (purchase * price > stats.get_money())
                                    {
                                        cout << "You don't have enough money to do that." << endl;
                                    }
                                    else
                                    {
                                        cout << "You purchased " << purchase << " wagon parts!" << endl;
                                        stats.set_wagonParts(stats.get_wagonParts() + purchase);
                                        cout << "You now have " << stats.get_wagonParts() << " wagon parts!" << endl;
                                        bill += (purchase * price);
                                        cout << "Your bill is: " << bill << endl;
                                        stats.set_money(stats.get_money() - (purchase * price));
                                    }
                                }
                                if (option == 5)
                                {
                                    price = 25.0;
                                    price = rounding(price, store.get_multiplier());
                                    cout << "How many first aid kits would you like to purchase?" << endl;
                                    cin >> purchase;
                                    if (purchase * price > stats.get_money())
                                    {
                                        cout << "You don't have enough money to do that." << endl;
                                    }
                                    else
                                    {
                                        cout << "You purchased " << purchase << " first aid kits!" << endl;
                                        stats.set_aidKits(stats.get_aidKits() + purchase);
                                        cout << "You now have " << stats.get_aidKits() << " first aid kits!" << endl;
                                        bill += (purchase * price);
                                        cout << "Your bill is: " << bill << endl;
                                        stats.set_money(stats.get_money() - (purchase * price));
                                    }
                                }
                                if (option == 6)
                                {
                                    cout << "Okay, partner, well I hope those supplies do you well out there on the Trail! Good luck!" << endl;
                                }
                            }
                            option = 0;
                        }
                        if (option2 == 2) //resting at a fort allows you to visit the store as many times as you want until you leave
                        {
                            atFort = true;
                            rest = rand() % 3 + 1;
                            switch (rest)
                            {
                                case 1:
                                    cout << "You rest 1 day." << endl;
                                    day = stats.get_day();
                                    if (day + 1 > months[stats.get_month() - 3].get_days())
                                    {
                                        day = 1;
                                        stats.set_month(stats.get_month() + 1);
                                    }
                                    else
                                    {
                                        day++;
                                    }
                                    stats.set_day(day);
                                    stats.set_food(stats.get_food() - (FOOD_PER_DAY * rest * stats.get_party()));
                                    break;
                                case 2:
                                    cout << "You rest 2 days." << endl;
                                    day = stats.get_day();
                                    for (int i = 0; i < 2; i++)
                                    {
                                        if (day + 1 > months[stats.get_month() - 3].get_days())
                                        {
                                            day = 1;
                                            stats.set_month(stats.get_month() + 1);
                                        }
                                        else
                                        {
                                            day++;
                                        }
                                        stats.set_day(day);
                                    }
                                    stats.set_food(stats.get_food() - (FOOD_PER_DAY * rest * stats.get_party()));
                                    break;
                                case 3:
                                    cout << "You rest 3 days." << endl;
                                    day = stats.get_day();
                                    for (int i = 0; i < 3; i++)
                                    {
                                        if (day + 1 > months[stats.get_month() - 3].get_days())
                                        {
                                            day = 1;
                                            stats.set_month(stats.get_month() + 1);
                                        }
                                        else
                                        {
                                            day++;
                                        }
                                        stats.set_day(day);
                                    }
                                    stats.set_food(stats.get_food() - (FOOD_PER_DAY * rest * stats.get_party()));
                                    break;
                            }
                        }
                        if (option2 == 3) //Leaves the fort
                        {
                            if (stats.get_oxen() < 4)
                            {
                                miles = rand() % 19 + 70; // 19 is the range, 70 is the base. (70 - 88)
                            }
                            else if (stats.get_oxen() >= 4 && stats.get_oxen() < 6) 
                            {
                                miles = rand() % 18 + 88; // (88 - 105)
                            }
                            else if (stats.get_oxen() >=6 && stats.get_oxen() < 8)
                            {
                                miles = rand() % 19 + 113; // (105 - 123)
                            }
                            else if (stats.get_oxen() >= 8)
                            {
                                miles = rand() % 18 + 123; // (123 - 140)
                            }
                            atFort = false;
                            for (int i = 0; i < TRAVEL_TIME; i++)
                            {
                                if (day + 1 > months[stats.get_month() - 3].get_days())
                                {
                                    day = 1;
                                    stats.set_month(stats.get_month() + 1);
                                }
                                else
                                {
                                    day++;
                                }
                                stats.set_day(day);
                            }
                            stats.set_food(stats.get_food() - (FOOD_PER_DAY * TRAVEL_TIME * stats.get_party()));
                            stats.set_mile(stats.get_mile() + miles);
                            stats.set_next_milestone();
                            atLandmark = false;
                        }
                    }
                }
                else //Non-store landmark
                {
                    //Non-store landmarks function the same as anywhere else on the trail, so this just updates what the next milestone is and how far it is
                    stats.set_next_milestone();
                    atLandmark = false;
                }
            }
            else // not landmark
            {
                for (int i = 0; i < TRAVEL_TIME; i++)
                {
                    if (day + 1 > months[stats.get_month() - 3].get_days())
                    {
                        day = 1;
                        stats.set_month(stats.get_month() + 1);
                    }
                    else
                    {
                        day++;
                    }
                    stats.set_day(day);
                }
                stats.set_food(stats.get_food() - (FOOD_PER_DAY * TRAVEL_TIME * stats.get_party()));
                stats.set_mile(stats.get_mile() + miles);
            }
        }
        else if (option == 3) // hunting
        {
            hunt = true; //flags that you hunted today
            day = stats.get_day();
            if (day + 1 > months[stats.get_month() - 3].get_days())
            {
                day = 1;
                stats.set_month(stats.get_month() + 1);
            }
            else
            {
                day++;
            }
            stats.set_day(day);

            temp = rand() % 100; //Determines chance of seeing a rabbit
            if (temp <= 50)
            {
                rabbit = true;
            }
            temp = rand() % 100; //Determines chance of seeing a fox
            if (temp <= 25)
            {
                fox = true;
            }
            temp = rand() % 100; //Determines chance of seeing a deer
            if (temp <= 15)
            {
                deer = true;
            }
            temp = rand() % 100; //Determines chance of seeing a bear
            if (temp <= 7)
            {
                bear = true;
            }
            temp = rand() % 100; //Determines chance of seeing a moose
            if (temp <= 5)
            {
                moose = true;
            }

            cout << "On your hunting trip, you find: " << endl;
            if (rabbit == false && fox == false && deer == false && bear == false && moose == false)
            {
                cout << "absolutely nothing. Cursing the gods, you head back to the camp." << endl;
            }
            if (rabbit == true)
            {
                cout << "A rabbit! Do you want to hunt it?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cin.clear();
                cin.ignore();
                cin >> option3;
                if (option3 == 1)
                {
                    if (stats.get_bullets() < 10)
                    {
                        stats.set_bullets(0);
                        cout << "The hunt was unsuccessful. You have " << stats.get_bullets() << " bullets left." << endl;
                    }
                    else
                    {
                        temp = rand() % 10 + 1;
                        cout << "Pick 3 numbers between 1 and 10;" << endl; //Insanely unfair "guess what I'm thinking game" that makes this game extremely hard to beat
                        cin.clear();
                        cin.ignore();
                        cin >> guess; //User enters 3 numbers between 1 and 10. If they guess right, they get the food
                        cin >> guess2;
                        cin >> guess3;
                        if (guess == temp || guess2 == temp || guess3 == temp)
                        {
                            cout << "Success! You gained 5lbs of food!" << endl;
                            stats.set_bullets(stats.get_bullets() - 10);
                            stats.set_food(stats.get_food() + 5);
                        }
                        else
                        {
                            cout << "Wow, you seriously need to work on your aim. Better luck next time." << endl;
                            stats.set_bullets(stats.get_bullets() - 10);
                        } 
                    }
                }
            }
            if (fox == true)
            {
                cout << "A fox! Do you want to hunt it?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cin.clear();
                cin.ignore();
                cin >> option3;
                if (option3 == 1)
                {
                    if (stats.get_bullets() < 10)
                    {
                        stats.set_bullets(0);
                        cout << "The hunt was unsuccessful. You have " << stats.get_bullets() << " bullets left." << endl;
                    }
                    else
                    {
                        temp = rand() % 10 + 1;
                        cout << "Pick 3 numbers between 1 and 10;" << endl;
                        cin.clear();
                        cin.ignore();
                        cin >> guess;
                        cin >> guess2;
                        cin >> guess3;
                        if (guess == temp || guess2 == temp || guess3 == temp)
                        {
                            cout << "Success! You gained 10lbs of food!" << endl;
                            stats.set_bullets(stats.get_bullets() - 8);
                            stats.set_food(stats.get_food() + 10);
                        }
                        else
                        {
                            cout << "Success! If success means hitting absolutely nothing and looking like a fool. Better luck next time." << endl;
                            stats.set_bullets(stats.get_bullets() - 8);
                        }
                    }
                }
            }
            if (deer == true)
            {
                cout << "A deer! Do you want to hunt it?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cin.clear();
                cin.ignore();
                cin >> option3;
                if (option3 == 1)
                {
                    if (stats.get_bullets() < 10)
                    {
                        stats.set_bullets(0);
                        cout << "The hunt was unsuccessful. You have " << stats.get_bullets() << " bullets left." << endl;
                    }
                    else
                    {
                        temp = rand() % 10 + 1;
                        cout << "Pick 3 numbers between 1 and 10;" << endl;
                        cin.clear();
                        cin.ignore();
                        cin >> guess;
                        cin >> guess2;
                        cin >> guess3;
                        if (guess == temp || guess2 == temp || guess3 == temp)
                        {
                            cout << "Success! You gained 60lbs of food!" << endl;
                            stats.set_bullets(stats.get_bullets() - 5);
                            stats.set_food(stats.get_food() + 60);
                        }
                        else
                        {
                            cout << "HOW did you miss that? Like, seriously, HOW? Well, better luck next time I guess." << endl;
                            stats.set_bullets(stats.get_bullets() - 5);
                        }
                    }
                }
            }
            if (bear == true)
            {
                cout << "A bear! Do you want to hunt it?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cin.clear();
                cin.ignore();
                cin >> option3;
                if (option3 == 1)
                {
                    if (stats.get_bullets() < 10)
                    {
                        stats.set_bullets(0);
                        cout << "The hunt was unsuccessful. You have " << stats.get_bullets() << " bullets left." << endl;
                    }
                    else
                    {
                        temp = rand() % 10 + 1;
                        cout << "Pick 3 numbers between 1 and 10;" << endl;
                        cin.clear();
                        cin.ignore();
                        cin >> guess;
                        cin >> guess2;
                        cin >> guess3;
                        if (guess == temp || guess2 == temp || guess3 == temp)
                        {
                            cout << "Success! You gained 200lbs of food!" << endl;
                            stats.set_bullets(stats.get_bullets() - 10);
                            stats.set_food(stats.get_food() + 200);
                        }
                        else
                        {
                            cout << "I'm surprised you're not dead right now, honestly. That was pathetic. Better luck next time." << endl;
                            stats.set_bullets(stats.get_bullets() - 10);
                        }
                    }
                }
            }
            if (moose == true)
            {
                cout << "A moose! Do you want to hunt it?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cin.clear();
                cin.ignore();
                cin >> option3;
                if (option3 == 1)
                {
                    if (stats.get_bullets() < 10)
                    {
                        stats.set_bullets(0);
                        cout << "The hunt was unsuccessful. You have " << stats.get_bullets() << " bullets left." << endl;
                    }
                    else
                    {
                        temp = rand() % 10 + 1;
                        cout << "Pick 3 numbers between 1 and 10;" << endl;
                        cin.clear();
                        cin.ignore();
                        cin >> guess;
                        cin >> guess2;
                        cin >> guess3;
                        if (stats.get_bullets() < 12)
                        {
                            stats.set_bullets(0);
                            cout << "The hunt was unsuccessful. You have " << stats.get_bullets() << " bullets left." << endl;
                        }
                        else
                        {
                            if (guess == temp || guess2 == temp || guess3 == temp)
                            {
                                cout << "Success! You gained 500lbs of food!" << endl; //If you don't manage to hunt at least a few moose or bears on your travels, there's basically zero chance of you winning
                                stats.set_bullets(stats.get_bullets() - 12);
                                stats.set_food(stats.get_food() + 500);
                            }
                            else
                            {
                                cout << "You must be the worst shot West of the Atlantic. That was pitiful. Better luck next time." << endl;
                                stats.set_bullets(stats.get_bullets() - 12);
                            }
                        }
                    }
                }
            }
            cout << "After a long day of hunting, it's time to chow down on some grub." << endl; //Pointless eating choice. I'm sure this had more functionality in the original game
            cout << "How would you like to eat?" << endl;
            option3 = 0;
            while (option3 < 1 || option3 > 3)
            {
                cout << "1. Poorly: (2lbs / person)" << endl; //Has no negative side effects, so you always want to choose this.
                cout << "2. Moderately: (3lbs / person)" << endl; //Pointless waste of food
                cout << "3. Well: (5lbs / person)" << endl; //Pointless waste of food
                cin.clear();
                cin.ignore();
                cin >> option3;
                if (option3 == 1)
                {
                    cout << "You decide to starve everyone." << endl;
                    stats.set_food(stats.get_food() - (stats.get_party() * 2));
                }
                if (option3 == 2)
                {
                    cout << "You decide it's best to save your food. Everyone gets their regular portions." << endl;
                    stats.set_food(stats.get_food() - (stats.get_party() * 3));
                }
                if (option3 == 3)
                {
                    cout << "You decide to have a small feast. Everyone liked that." << endl;
                    stats.set_food(stats.get_food() - (stats.get_party() * 5));
                }
            }
            if (stats.get_food() > 1000) //If you somehow manage to hunt enough to completely stock your wagon (yeah right), you have to leave any excess behind
            {
                cout << "Despite a wildly successful day of hunting, your wagon can only carry 1000 lbs of food." << endl;
                if (stats.get_party() > 1)
                {
                    cout << "After much internal debate over leaving one of your family members instead, you begrudgingly leave the rest of the food behind." << endl;
                }
                else
                {
                    cout << "You begrudgingly leave the rest of the food behind." << endl;
                }
                stats.set_food(1000);
            }
        }
        if (option == 4) //Quit option with some flavor text
        {
            cout << "You become increasingly apathetic and eventually refuse to do anything." << endl;
            cout << "You and your family die of starvation because of your nihilism." << endl;
            cout << "Hope it was worth it." << endl;
            statsFile.open("results.txt"); //Prints results to results.txt file
            statsFile << "Leader: " << player.get_name() << endl;
            statsFile << "Miles travelled: 2040" << endl;
            statsFile << "Food remaining: " << stats.get_food() << endl;
            statsFile << "Cash remaining: " << stats.get_money() << endl;
            statsFile.close();
            return 0;
        }
        //Misfortunes
        temp = rand() % 100;
        if (temp > 40) //40% chance of running into misfortunes
        {
            cout << "Through some miracle, you somehow manage to make it another 2 weeks without someone getting sick or some such nonsense." << endl;
        }
        else if (temp <= 40 && atLandmark == false && hunt == false)
        {
            temp2 = rand() % 100;
            cout << "temp2 is : " << temp2 << endl;
            if (temp2 <= 33) //30% chance of someone getting sick
            {
                option3 = 0;
                temp3 = rand() % stats.get_party(); //Determines who gets sick. If they are dead, this has no effect.
                if (temp3 == 0)
                {
                    temp4 = rand() % 6; //Determines which ailment they get
                    party[0].set_condition(ailments[temp4]);
                    if (stats.get_aidKits() > 0)
                    {
                        stats.set_aidKits(stats.get_aidKits() - 1);
                        weight = 50; //% chance of survival
                        used = true; //This checks if you used a first aid kit
                    }
                }
                if (temp3 == 1 && party[1].get_health() == 100)
                {
                    temp = rand() % 6;
                    party[1].set_condition(ailments[temp4]);
                    if (stats.get_aidKits() > 0)
                    {
                        stats.set_aidKits(stats.get_aidKits() - 1);
                        weight = 50;
                        used = true;
                    }
                }
                if (temp3 == 2 && party[2].get_health() == 100)
                {
                    temp = rand() % 6;
                    party[2].set_condition(ailments[temp4]);
                    if (stats.get_aidKits() > 0)
                    {
                        stats.set_aidKits(stats.get_aidKits() - 1);
                        weight = 50;
                        used = true;
                    }
                }
                if (temp3 == 3 && party[3].get_health() == 100)
                {
                    temp = rand() % 6;
                    party[3].set_condition(ailments[temp4]);
                    if (stats.get_aidKits() > 0)
                    {
                        stats.set_aidKits(stats.get_aidKits() - 1);
                        weight = 50;
                        used = true;
                    }
                }
                if (temp3 == 4 && party[4].get_health() == 100)
                {
                    temp = rand() % 6;
                    party[4].set_condition(ailments[temp4]);
                    if (stats.get_aidKits() > 0)
                    {
                        stats.set_aidKits(stats.get_aidKits() - 1);
                        weight = 50;
                        used = true;
                    }
                }
                if (used == false) //If you had no first aid kits available
                {
                    option3 = 0;
                    while (option3 < 1 || option3 > 2)
                    {
                        cout << " " << party[temp3].get_name() << " has come down with a case of " << party[temp3].get_condition() << "!" << endl;
                        cout << "What would you like to do?" << endl;
                        cout << "1. Rest" << endl;
                        cout << "2. Press on" << endl;
                        cin.clear();
                        cin.ignore();
                        cin >> option3;
                        if (option3 == 1)
                        {
                            weight = 30; //70% chance of survival
                        }
                        if (option3 == 2)
                        {
                            weight = 70; //30% chance of survival
                        }
                    }
                }
                for (int i = 0; i < PARTY_ARR_SIZE; i++)
                {
                    if (party[i].get_condition() != "none") //Determines who is sick
                    {
                        temp5 = rand() % 100 + 1;
                        if (weight == 50) //These if statements determine whether the party member survives or not. This one is for if you gave them medicine
                        {
                            if (temp5 <= 50) //50% chance of survival
                            {
                                cout << party[i].get_name() << "survived thanks to the medicine." << endl;
                                party[i].set_condition("none");
                            }
                            else if (temp5 > 50)
                            {
                                cout << party[i].get_name() << "died of " << party[i].get_condition() << " despite the medicine." << endl;
                                stats.set_party(stats.get_party() - 1);
                                party[i].set_health(0);
                                party[i].set_condition("none");
                            }
                        }
                        else if (weight == 30) //If you rested
                        {
                            if (temp5 <= 70) //70% chance of survival
                            {
                                cout << "Against your best judgment, you begrudgingly relent and rest for 3 days, grumbling the whole time." << endl;
                                cout << party[i].get_name() << "survived, due to the rest you took. Well, I suppose that was worth it..." << endl;
                                party[i].set_condition("none");
                                day = stats.get_day();
                                for (int i = 0; i < 3; i++)
                                {
                                    if (day + 1 > months[stats.get_month() - 3].get_days())
                                    {
                                        day = 1;
                                        stats.set_month(stats.get_month() + 1);
                                    }
                                    else
                                    {
                                        day++;
                                    }
                                    stats.set_day(day);
                                }
                                stats.set_food(stats.get_food() - (FOOD_PER_DAY * rest * stats.get_party()));
                            }
                            else if (temp5 > 70)
                            {
                                cout << "Against your best judgment, you begrudgingly relent and rest for 3 days, grumbling the whole time." << endl;
                                cout << "Despite all of that, " << party[i].get_name() << " died anyways. What a colossal waste of time." << endl;
                                party[i].set_condition("none");
                                party[i].set_health(0);
                                day = stats.get_day();
                                for (int i = 0; i < 3; i++)
                                {
                                    if (day + 1 > months[stats.get_month() - 3].get_days())
                                    {
                                        day = 1;
                                        stats.set_month(stats.get_month() + 1);
                                    }
                                    else
                                    {
                                        day++;
                                    }
                                    stats.set_day(day);
                                }
                                stats.set_food(stats.get_food() - (FOOD_PER_DAY * rest * stats.get_party()));
                                stats.set_party(stats.get_party() - 1);
                            }
                        }
                        else if (weight == 70) //If you pressed on
                        {
                            if (temp5 > 70) //30% chance of survival
                            {
                                cout << "You don't have time for this." << endl;
                                cout << party[i].get_name() << "survived somehow." << endl;
                                party[i].set_condition("none");
                            } 
                            else if (temp5 <= 70)
                            {
                                cout << "You don't have time for this." << endl;
                                cout << "Unsurprisingly, your wanton lack of compassion causes " << party[i].get_name() << " to die a horrible, painful death on the trail." << endl;
                                party[i].set_condition("none");
                                party[i].set_health(0);
                                stats.set_party(stats.get_party() - 1);
                            }
                        }
                    }
                }
            }
            else if (temp2 > 33 && temp2 <= 66) //33% chance of oxen dying
            {
                cout << "One of your oxen died. Drat." << endl;
                stats.set_oxen(stats.get_oxen() - 1);
            }
            else if (temp2 > 66) //33% chance of wagon breaking down. If you have wagon parts, they get used automatically
            {
                cout << "Daydreaming about being rid of your family's incessant whining, you hit a rock and your wagon breaks. Drat." << endl;
                if (stats.get_wagonParts() > 0)
                {
                    cout << "You use some wagon parts to fix it after some fruitless cursing of the gods." << endl;
                    stats.set_wagonParts(stats.get_wagonParts() - 1);
                }
                else if (stats.get_wagonParts() <= 0) //This will cause a failure condition, but it won't trigger immediately
                {
                    cout << "You don't have any more wagon parts. Uh oh." << endl;
                    wagon.set_health(0);
                }
            }
        } // End of misfortunes
        temp = rand() % 50 + 5;
        temp2 = rand() % 100 + 1;
        if (temp2 <= temp && atLandmark == false && hunt == false) //Riders section
        {
            cout << "You spot some riders ahead! They don't look hostile, but you aren't taking any chances." << endl; //Just my spin on the rider scenario, nothing changes except the flavor text
            cout << "Your family looks at you nervously as you grit your teeth, unholster your gun and decide what to do." << endl;
            option3 = 0;
            while (option3 < 1 || option3 > 3)
            {
                cout << "1. Run" << endl;
                cout << "2. Attack" << endl;
                cout << "3. Surrender" << endl;
                cin.clear();
                cin.ignore();
                cin >> option3;
                
                if (option3 == 1)
                {
                    cout << "Despite the riders not showing the slightest interest in you, you hightail it out of there." << endl;
                    cout << "In your deranged flight from perceived danger, an oxen breaks a leg, you lose 10 lbs. of food, and the wagon breaks an axle." << endl; //Probably the worst option
                    stats.set_oxen(stats.get_oxen() - 1);
                    stats.set_food(stats.get_food() - 10);
                    if (stats.get_wagonParts() > 0)
                    {
                        stats.set_wagonParts(stats.get_wagonParts() - 1);
                    }
                    else
                    {
                        wagon.set_health(0);
                    }
                }
                else if (option3 == 2)
                {
                    cout << "Being the deranged lunatic that you are, you decide to shoot first, ask questions later." << endl; //If you're like me, and you just spend all your money on bullets in the beginning, this is easily the best choice
                    cout << "The riders, realizing that some madman is trying to kill them, take cover and return fire." << endl;
                    temp3 = rand() % 10 + 1;
                    cout << "Pick 3 numbers between 1 and 10" << endl;
                    guess = 0;
                    guess2 = 0;
                    guess3 = 0;
                    cin.clear();
                    cin.ignore();
                    cin >> guess;
                    cin >> guess2;
                    cin >> guess3;
                    if (guess == temp3 || guess2 == temp3 || guess3 == temp3)
                    {
                        cout << "Congratulations, you scared them off." << endl;
                        cout << "Looting their supplies, you get 50 lbs. of food and 50 bullets" << endl;
                        stats.set_bullets(stats.get_bullets() + 50);
                        if (stats.get_food() + 50 > 1000)
                        {
                            stats.set_food(1000);
                        }
                        else
                        {
                            stats.set_food(stats.get_food() + 50);
                        }
                    }
                    else
                    {
                        cout << "After a harrowing battle, and several minutes of bartering for your life, the riders decide to let you go." << endl;
                        cout << "You give them a quarter of your cash reserves" << endl;
                        stats.set_bullets(stats.get_bullets() - 50);
                        stats.set_money(stats.get_money() - (stats.get_money() * 0.25));
                        dubtemp = rounding(stats.get_money(), 1);
                        stats.set_money(dubtemp);
                    } 
                }
                else if (option3 == 3) //Same as option 2, but you save 50 bullets. Pointless because 50 bullets is pretty cheap.
                {
                    cout << "It turns out they WERE hostile, and you end up surrendering before they open fire." << endl;
                    cout << "The riders take a quarter of your cash reserves and let you go on your way." << endl;
                    stats.set_money(stats.get_money() - (stats.get_money() * 0.25));
                    dubtemp = rounding(stats.get_money(), 1);
                    stats.set_money(dubtemp);
                }
            }
        }
        turn++; //This bar just separates turns to make the interface a bit easier to read
        cout << "========================================================================================================================================================" << endl;
        cout << "                                                                                                                                                        " << endl;
        cout << "                                                                                                                                                        " << endl;
        cout << "                                                                     "<< "Turn: " << turn << "                                                                         " << endl;
        cout << "                                                                                                                                                        " << endl;
        cout << "                                                                                                                                                        " << endl;
        cout << "========================================================================================================================================================" << endl;

    }
    cout << "Congratulations! You successfully made it Oregon City!" << endl; //This will literally never happen due to how hard this game is, but good luck.
    cout << "Within weeks, you realize what a colossal waste of time it was coming here." << endl;
    statsFile.open("results.txt"); //Writes end stats to results.txt
    statsFile << "Leader: " << player.get_name() << endl;
    statsFile << "Miles travelled: 2040" << endl;
    statsFile << "Food remaining: " << stats.get_food() << endl;
    statsFile << "Cash remaining: " << stats.get_money() << endl;
    statsFile.close();

    return 0;
}