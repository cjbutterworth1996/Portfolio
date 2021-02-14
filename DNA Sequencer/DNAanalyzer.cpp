// CS1300-210 Fall 2020
// Author: Collin Butterworth
// Recitation: 210 - Steven Wilmes & Alexis Acevedo
// Project 1 - Problem #4-7

#include <iostream>
#include <string>
using namespace std;

/*
 * This function determines similarity score for gene sequences
 * Paramaters: user inputted string
 * Return: double number for match percentage
*/

double calcSimScore(string sequence1, string sequence2)
{
    char char1;
    char char2;
    int count = 0;
    double simScore = 0;
    double length1 = sequence1.length();
    double length2 = sequence2.length();
    
    if (length1 != length2 || length1 == 0)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < sequence1.length(); i++)
        {
            char1 = sequence1[i];
            char2 = sequence2[i];

            if (char1 != char2)
            {
                count++;
            }
        }
    }  

    simScore = (length1 - count) / length1;
    // count represents hamming distance

    return simScore;
}

/*
 * This function determines the highest similarity score found in a genome
 * Paramaters: user inputted string
 * Return: double number for best similarity score
*/

double findBestSimScore (string genome, string sequence)
{
    double bestScore = 0;
    double matchCheck = 0;
    string substring1;
    
    if (genome.length() < sequence.length())
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < genome.length(); i++)
        {
            substring1 = genome.substr(i, sequence.length());
            matchCheck = calcSimScore(substring1, sequence);
            if (matchCheck > bestScore)
            {
                bestScore = matchCheck;
            }
        }
    }

    return bestScore;
}

/*
 * This function determines the best match for a sequence out of three genomes
 * Paramaters: user inputted strings for three genomes and one sequence
 * Return: nothing
*/

void findMatchedGenome(string genome1, string genome2, string genome3, string sequence)
{
    double bestMatch = 0;
    double score1 = 0;
    double score2 = 0;
    double score3 = 0;
    string output1;
    string output2;
    string output3;
    
    if (genome1.length() == 0 || genome2.length() == 0 || genome3.length() == 0 || sequence.length() == 0)
    {
        cout << "Genomes or sequence is empty." << endl;
    }
    else
    {
        if (genome1.length() != genome2.length() || genome2.length() != genome3.length())
        {
            cout << "Lengths of genomes are different." << endl;
        }
        else
        {
            score1 = findBestSimScore(genome1, sequence); 
            score2 = findBestSimScore(genome2, sequence);
            score3 = findBestSimScore(genome3, sequence);
            bestMatch = score1;
            output1 = "Genome 1 is the best match.";
            
            if (score2 > bestMatch)
            {
                bestMatch = score2;
                output2 = "Genome 2 is the best match.";
            }
            if (score2 == bestMatch)
            {
                output2 = "Genome 2 is the best match.";
            }
            if (score3 > bestMatch)
            {
                bestMatch = score3;
                output3 = "Genome 3 is the best match.";
            }
            if (score3 == bestMatch)
            {
                output3 = "Genome 3 is the best match.";
            }
        }
        
        if (bestMatch == score1)
        {
            cout << output1 << endl;
        }
        if (bestMatch == score2)
        {
            cout << output2 << endl;
        }
        if (bestMatch == score3)
        {
            cout << output3 << endl;
        }
    } 
}

int main()
{
    string sequence1;
    string sequence2;
    string genome1;
    string genome2;
    string genome3;
    int menuOption = -1;

    while (menuOption != 4)
    {
        cout << "Select a numerical option:" << endl;
        cout << "=== menu ===" << endl;
        cout << "1. Find similarity score" << endl;
        cout << "2. Find the best similarity score" << endl;
        cout << "3. Analyze the genome sequences" << endl;
        cout << "4. Quit" << endl;
        cin >> menuOption;

        if (menuOption == 1)
        {
            cout << "Enter sequence 1: " << endl;
            cin >> sequence1;
            cout << "Enter sequence 2: " << endl;
            cin >> sequence2;
            cout << "Similarity score: " << calcSimScore(sequence1, sequence2) << endl;
        }
        else if (menuOption == 2)
        {
            cout << "Enter genome: " << endl;
            cin >> genome1;
            cout << "Enter sequence: " << endl;
            cin >> sequence1;
            cout << "Best similarity score: " << findBestSimScore(genome1, sequence1) << endl;
        }
        else if (menuOption == 3)
        {
            cout << "Enter genome 1: " << endl;
            cin >> genome1;
            cout << "Enter genome 2: " << endl;
            cin >> genome2;
            cout << "Enter genome 3: " << endl;
            cin >> genome3;
            cout << "Enter sequence: " << endl;
            cin >> sequence1;
            findMatchedGenome(genome1, genome2, genome3, sequence1);
        }
        else if (menuOption == 4)
        {
            cout << "Good bye!" << endl;
            return 0;
        }
        else if (menuOption < 1 || menuOption > 4)
        {
            cout << "Invalid option." << endl;
        }
    }

    return 0;
}