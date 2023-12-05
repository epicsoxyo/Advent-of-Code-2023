/*
    THIS IS NOT AN EFFICIENT SOLUTION IN THE SLIGHTEST. 
    I just had other things to do today so I figured I'd rather spend < 20 minutes
    on my solution + let it run in the background than spend a few hours looking
    into better ways of doing it.

    This took exactly one hour to run on my specced-out gaming PC,
    but it got the correct answer first try. You have been warned.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


// TESTING

void OutputData(std::vector<long long>& seeds, std::vector<std::vector<std::vector<long long>>>& rawData)
{
    std::cout << "Seeds: ";

    for (long long& seed : seeds)
        std::cout << seed << " ";

    std::cout << "\n\n" << std::endl;
    std::cout << "Maps: \n" << std::endl;

    for(std::vector<std::vector<long long>>& map : rawData)
    {
        for (std::vector<long long>& row : map)
        {
            for (long long num : row)
                std::cout << num << " ";
            
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}


// PART ONE

std::vector<long long> ParseAsInts(std::string& str)
{
    std::string currentInt{""};
    std::vector<long long> parsedString;

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

void GetData(std::vector<long long>& seeds, std::vector<std::vector<std::vector<long long>>>& rawData)
{
    std::ifstream DataFile("Data.txt");
    std::string line;
    std::vector<std::vector<long long>> currentMap;

    getline(DataFile, line);
    seeds = ParseAsInts(line);

    while (getline(DataFile, line))
    {
        if (isdigit(line[0])) currentMap.push_back(ParseAsInts(line));
        else if (currentMap.size() > 0)
        {
            rawData.push_back(currentMap);
            currentMap.clear();
        }
    }
    if (currentMap.size() > 0) rawData.push_back(currentMap);

    DataFile.close();
}

long long MapValue(long long& currentSeedVal, std::vector<std::vector<long long>>& map)
{
    long long num, mappedNum, range;

    for (std::vector<long long>& row : map)
    {
        mappedNum = row[0];
        num = row[1];
        range = row[2];

        if (currentSeedVal >= num && currentSeedVal < num + range)
            return currentSeedVal + (mappedNum - num);
    }

    return currentSeedVal;
}

void PartOne(std::vector<long long>& seeds, std::vector<std::vector<std::vector<long long>>>& rawData)
{
    long long currentSeedVal{seeds[0]}, minSeedLoc{-1};

    for (long long& seed : seeds)
    {
        currentSeedVal = seed;

        for (std::vector<std::vector<long long>>& map : rawData)
            currentSeedVal = MapValue(currentSeedVal, map);

        if (minSeedLoc > currentSeedVal || minSeedLoc < 0) minSeedLoc = currentSeedVal;
    }

    std::cout << "Minimum Location (Part 1): " << minSeedLoc << std::endl;
}

void PartTwo(std::vector<long long>& seeds, std::vector<std::vector<std::vector<long long>>>& rawData)
{
    long long currentSeedVal{seeds[0]}, minSeedLoc{-1}, startingNum;
    bool isRange{false};

    for (long long& num : seeds)
    {
        if (!isRange)
        {
            startingNum = num;
            std::cout << "On seed: " << startingNum << std::endl;
            isRange = true;
        }
        else
        {
            for (int i = 0; i < num; i++)
            {
                currentSeedVal = startingNum + i;

                for (std::vector<std::vector<long long>>& map : rawData)
                    currentSeedVal = MapValue(currentSeedVal, map);

                if (minSeedLoc > currentSeedVal || minSeedLoc < 0)
                {
                    minSeedLoc = currentSeedVal;
                    std::cout << "- Found new minimum: " << minSeedLoc << std::endl;
                }
            }
            isRange = false;
        }
    }

    std::cout << "Minimum Location (Part 2): " << minSeedLoc << std::endl;
}

int main()
{
    std::vector<long long> seeds;
    std::vector<std::vector<std::vector<long long>>> rawData;

    GetData(seeds, rawData);
    PartOne(seeds, rawData);
    PartTwo(seeds, rawData);

}