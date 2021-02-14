#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

struct wordRecord {
    string word;
    int count;
};

bool isIgnoreWord (string word, string ignoreWords[])
{
    bool inArray = false;
    for (int i = 0; i < 50; i++)
    {
        if (ignoreWords[i] == word)
        {
            inArray = true;
            return inArray;
        }
    }

    return inArray;
}

int getTotalNumberNonIgnoreWords (wordRecord distinctWords[], int length)
{
    int total = 0;
    for (int i = 0; i < length; i++)
    {
        total += distinctWords[i].count;
    }

    return total;
}

void reverse(wordRecord array[], int array_size)
{
    int end = array_size - 1;
    int halfway = array_size / 2;
    wordRecord temp;
    for (int i = 0; i < halfway; i++)
    {
        temp = array[i];
        array[i] = array[end - i];
        array[end - i] = temp;
    }
}

void sortArray (wordRecord distinctWords[], int length)
{
    int i;
    int spotCount;
    int j; 
    wordRecord spot; 
    for (i = 1; i < length; i++)
    {
        spot = distinctWords[i];
        spotCount = distinctWords[i].count;
        j = i - 1;
        
        while (j >= 0 && distinctWords[j].count > spotCount)
        {
            distinctWords[j + 1] = distinctWords[j];
            j = j - 1;
        }
        distinctWords[j + 1] = spot;
    }
    reverse(distinctWords, length);
}

void printTenFromN (wordRecord distinctWords[], int N, int totalNumWords)
{
    float probability;
    float temp1;
    float temp2 = totalNumWords;
    cout << setprecision(5) << fixed;
    
    for (int i = 0; i < 10; i++)
    {
        temp1 = distinctWords[i + N].count;
        
        probability = temp1 / temp2;
        cout << probability << " - " << distinctWords[i + N].word << endl;
    }
}

int splitSpace(string line, char delim, string array[], int size)
{
    int start = 0;
    int increment = 0;
    int count = 0;
    int index;
    int index2;
    string temp;
    int check1;
    int check2;
    
    index = line.find_first_of(' ');

    if (line.length() == 0)
    {
        return 0;
    }

    if (line.find_first_of(' ') == -1)
    {
        array[0] = line;
        count = 1;
        return 0;
    }

    if (index != 0)
    {
        array[0] = line.substr(0, index);
        start = line.find_first_not_of(' ', index);
        increment++;
        count++;
    }
    else
    {
        index = line.find_first_not_of(' ');
        start = index;
    }

    for (int i = start; i < line.length(); i += start)
    {
        index = line.find_first_of(' ', start);
        if (index != - 1)
        {
            array[0 + increment] = line.substr(start, index - start);
            count++;
            increment++;
        }
        index2 = line.find_first_not_of(' ', index);
        if (index2 != - 1)
        {
            start = index2;
        }
    }
    
    check1 = line.find_last_of(' ');
    if (check1 != - 1)
    {
        check1 += 1;
        temp = line.substr(check1, line.length() - 1);
        if (temp[0] >= 33 && temp[0] <= 126)
        {
            array[0 + increment] = temp;
            count++;
        }
    }

    return count;
}

void getIgnoreWords (const char *ignoreWordFileName, string ignoreWords[])
{
    ifstream words;
    words.open(ignoreWordFileName);
    string line;
    int i = 0;
    char delim = ' ';
    int size = 50;
    string temp[50];

    while (words >> line)
    {
        ignoreWords[i] = line;
        i++;
    }
}

void sortAlph (wordRecord arr[], int totalUniqueWords)
{
    wordRecord temp;
    int spot;

    for (int i = 0; i < totalUniqueWords; i++)
    {
        if (arr[i].count == arr[i+1].count)
        {
            spot = i;
            while (arr[i].word > arr[i+1].word)
            {
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                i++;
            }
            i = spot;
        }
    }
}

int main(int argc, char *argv[])
{
    int startIndex = stoi(argv[1]);
    ifstream ignoreFile;
    ifstream wordsFile;
    string wordsFileName;
    const char * fileName;
    string ignore[50];
    int size = 100;
    wordRecord *arr;
    arr = new wordRecord[size];
    string line;
    string tempArr[50];
    int splitCount;
    char delim = ' ';
    string word;
    bool check;
    int numUniqueWords = 0;
    bool counted = false;
    int totalUniqueCount = 0;
    int totalCount = 0;
    int doubled = 0;

    if (argc != 4)
    {
        cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
        return 0;
    }

    fileName = argv[3];

    getIgnoreWords(fileName, ignore);
    ignoreFile.close();
    
    wordsFileName = argv[2];
    wordsFile.open(wordsFileName);

    while (wordsFile >> word)
    {
        counted = false;
        check = isIgnoreWord(word, ignore);
        if (numUniqueWords == 0 && check == false)
        {
            arr[0].word = word;
            arr[0].count = 1;
            numUniqueWords++;
            totalCount++;
            check = true;
        }
        if (check == true)
        {
            totalCount++;
        }
        if (check == false)
        {
            for (int j = 0; j < numUniqueWords; j++)
            {
                if (arr[j].word == word)
                {
                    arr[j].count++;
                    totalCount++;
                    counted = true;
                }
            }
        }
        if (counted == false && check == false)
        {
            if (numUniqueWords == size)
            {
                int newSize = size * 2;
                wordRecord *newArray = new wordRecord[newSize];
                for (int j = 0; j < size; j++)
                {
                    newArray[j] = arr[j];
                }
                delete [] arr;
                size = newSize;
                arr = newArray;
                doubled++;
            }
            arr[numUniqueWords].word = word;
            arr[numUniqueWords].count = 1;
            numUniqueWords++;
            totalCount++;
        }      
    }

    totalUniqueCount = getTotalNumberNonIgnoreWords(arr, numUniqueWords);
    sortArray(arr, numUniqueWords);
    sortAlph(arr, numUniqueWords);

    cout << "Array doubled: " << doubled << endl;
    cout << "Distinct non-common words: " << numUniqueWords << endl;
    cout << "Total non-common words: " << totalUniqueCount << endl;
    cout << "Probability of next 10 words from rank " << startIndex << endl;
    cout << "---------------------------------------" << endl;
    printTenFromN(arr, startIndex, totalUniqueCount);

    return 0;
}