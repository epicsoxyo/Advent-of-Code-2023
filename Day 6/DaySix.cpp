#include <iostream>
#include <fstream>
#include <vector>
#include <string>


// TESTING

void OutputData(std::vector<int>& times, std::vector<int>& records)
{
    std::cout << "Times:   ";
    for (int& time : times) std::cout << time << " ";
    std::cout << std::endl;
    
    std::cout << "Records: ";
    for (int& time : records) std::cout << time << " ";
    std::cout << std::endl;
}


// PART ONE

std::vector<int> ParseAsInts(std::string& str)
{
    std::string currentInt{""};
    std::vector<int> parsedString;

    for (char& character : str)
    {
        if (isdigit(character)) currentInt += character;
        else if (currentInt != "")
        {
            parsedString.push_back(stoll(currentInt));
            currentInt = "";
        }
    }
    if (currentInt != "") parsedString.push_back(stoll(currentInt));

    return parsedString;
}

void GetData(std::vector<int>& times, std::vector<int>& records)
{
    std::ifstream DataFile("Data.txt");
    std::string line;

    getline(DataFile, line);
    times = ParseAsInts(line);

    getline(DataFile, line);
    records = ParseAsInts(line);

    DataFile.close();
}

void SumPossible(std::vector<int>& times, std::vector<int>& records)
{
    int distanceMoved, waysToWin, total{1};

    for (int i = 0; i < times.size(); i++)
    {
        waysToWin = 0;

        for (int buttonHeld = 0; buttonHeld <= times[i]; buttonHeld++)
        {
            distanceMoved = buttonHeld * (times[i] - buttonHeld);

            if (distanceMoved > records[i]) waysToWin++;
        }

        if (waysToWin > 0) total *= waysToWin;
    }

    std::cout << "Part One: " << total << std::endl;
}

void PartOne()
{
    std::vector<int> times, records;

    GetData(times, records);
    OutputData(times, records);
    SumPossible(times, records);
}


// PART TWO

long long ParseAsInt(std::string& str)
{
    std::string currentInt{""};

    for (char& character : str)
    {
        if (isdigit(character)) currentInt += character;
    }

    return stoll(currentInt);
}

void GetData(long long& time, long long& record)
{
    std::ifstream DataFile("Data.txt");
    std::string line;

    getline(DataFile, line);
    time = ParseAsInt(line);

    getline(DataFile, line);
    record = ParseAsInt(line);

    DataFile.close();
}

void SumPossible(long long& time, long long& record)
{
    long long distanceMoved, waysToWin{0};

    for (int buttonHeld = 0; buttonHeld <= time; buttonHeld++)
    {
        distanceMoved = buttonHeld * (time - buttonHeld);

        if (distanceMoved > record) waysToWin++;
    }

    std::cout << "Part Two: " << waysToWin << std::endl;
}

void PartTwo()
{
    long long time, record;

    GetData(time, record);
    SumPossible(time, record);

}


// MAIN

int main()
{
    PartOne();
    std::cout << std::endl;
    PartTwo();
}