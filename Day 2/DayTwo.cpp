#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include<array>

// cubes : [R, G, B]
enum Colour{R, G, B};

std::vector<std::string> GetSubstrings(std::string& str)
{
    std::vector<std::string> substrings{};
    int pos = 0;

    std::string substring{""};

    str = str.erase(0, str.find(":") + 1);

    for (int i = str.size(); i > 0; i--)
    {
        if ((str[i] == 'r') && (str[i - 1] == 'g'))
            continue;

        if((str[i] == 'r') || (str[i] == 'g') || (str[i] == 'b') || isdigit(str[i]))
            substring = str[i] + substring;
        else if(str[i] == ';')
        {
            substrings.push_back(substring);
            substring = "";
        }
    }
    substrings.push_back(substring);

    return substrings;
}

std::array<int, 3> ParseSubstring(std::string str)
{
    std::array<int, 3> totalCubes = {0, 0, 0};
    int index{0};
    std::string number{""}, emptystring{""};
    
    for (int i = str.length(); i >= 0; i--)
    {
        if (isdigit(str[i]))
        {
            number = str[i] + number;
        }
        else
        {
            if (number.compare(emptystring) != 0) totalCubes[index] += stoi(number);
            number = "";

            switch(str[i])
            {
                case 'r': index = 0; break;
                case 'g': index = 1; break;
                case 'b': index = 2; break;
                default: break;
            }
        }
    }
    if (number.compare(emptystring) != 0) totalCubes[index] += stoi(number);

    return totalCubes;
}

std::array<int, 3> GetMaximumCubes(std::string& dataString)
{
    std::vector<std::string> reveals{GetSubstrings(dataString)};
    std::array<int, 3> maxCubes = {0, 0, 0}; // R, G, B
    std::array<int, 3> currentCubes = {0, 0, 0};
    int pos{0};

    std::vector<std::string>::iterator it{reveals.begin()};
    for (it; it < reveals.end(); it++)
    {
        currentCubes = ParseSubstring(*it);
        for (int i = 0; i < 3; i++)
        {
            if(currentCubes[i] > maxCubes[i]) maxCubes[i] = currentCubes[i];
        }
    }

    return maxCubes;
}

bool IsValidGame(std::string& game)
{
    std::array<int, 3> maxCubes{GetMaximumCubes(game)};
    if((maxCubes[0] > 12) || (maxCubes[1] > 13) || (maxCubes[2] > 14)) return false;
    return true;
}

void PartOne()
{
    std::string game;
    std::ifstream DataFile("Data.txt");
    std::array<int, 3> cubes;
    int index{0}, total{0};

    while(getline(DataFile, game))
    {
        index++;
        if(IsValidGame(game)) total += index;
    }

    std::cout << "Sum of total valid games: " << total << std::endl;

    DataFile.close();
}

int GetPower(std::string& game)
{
    int power{1};
    std::array<int, 3> cubes{GetMaximumCubes(game)};
    for (int i = 0; i < 3; i ++) power *= cubes[i];
    return power;
}

void PartTwo()
{
    std::string game;
    std::ifstream DataFile("Data.txt");
    int total{0};

    while(getline(DataFile, game))
    {
        total += GetPower(game);
    }

    std::cout << "Sum of powers: " << total << std::endl;

    DataFile.close();
}

int main()
{
    PartOne();
    PartTwo();
    return 0;
}
