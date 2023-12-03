#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>


struct NumCoord
{
    int number;
    std::vector<std::string> coords;

    NumCoord(int n, std::vector<std::string> c) : number{n}, coords{c} {}
};

struct Gear
{
    std::string coord;
    std::vector<NumCoord> numbers;

    Gear(std::string c, std::vector<NumCoord> n) : coord{c}, numbers{n} {}

};


// DEBUGGING

void OutputMap(std::map <int, std::vector<std::string>> map)
{
    for(std::map<int, std::vector<std::string>>::const_iterator it = map.begin();
    it != map.end(); ++it)
    {
        std::cout << it->first << " : ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            std::cout << *it2 << "  ";
        std::cout << std::endl;
    }
}

void OutputSet(std::set <std::string>& set)
{
    for (auto& str : set)
    {
        std::cout << str << std::endl;
    }
}

void ShowSumCoords(std::vector<std::string>& data, std::set<std::string>& characterCoords,
    std::set<std::string>& sumCoords)
{
    int i{0}, j{0};
    std::string coord;

    for(std::string& datum : data)
    {
        i=0;
        for(char& character : datum)
        {
            coord = std::to_string(i) + "," + std::to_string(j);
            if (characterCoords.count(coord)) std::cout << character;
            else if (sumCoords.count(coord)) std::cout << "X";
            else std::cout << character;
            i++;
        }
        std::cout << std::endl;
        j++;
    }
}


// PART ONE

void GetData(std::vector<std::string>& data)
{
    std::ifstream DataFile("Data.txt");
    std::string line;

    while (getline(DataFile, line))
    {
        data.push_back(line);
    }
    DataFile.close();
}

void GetCharacterCoords(std::vector<std::string>& data,
    std::set<std::string>& characterCoords)
{
    int i{0}, j{0};

    for (std::string& datum : data)
    {
        i = 0;
        for (char& character : datum)
        {
            if (character != '.' && !isdigit(character)) //special
                characterCoords.insert(std::to_string(i) + ',' + std::to_string(j));

            i++;
        }
        j++;
    }
}

void GetSurroundingCoords(std::set<std::string>& characterCoords,
    std::set<std::string>& surroundingCoords)
{
    std::string number{""}, surroundingCoord;
    int numericalCoord[2];

    for (auto& characterCoord : characterCoords)
    {
        for (auto& character : characterCoord)
        {
            if (isdigit(character)) number += character;
            else
            {
                numericalCoord[0] = stoi(number);
                number = "";
            }
        }
        numericalCoord[1] = stoi(number);
        number = "";

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                surroundingCoord = std::to_string(numericalCoord[0] + i) + "," + std::to_string(numericalCoord[1] + j);
                surroundingCoords.insert(surroundingCoord);
            }
        }
    }
}

void AppendToNumCoords(std::vector<NumCoord>& numberCoords,
    std::string& currentNumber, std::vector<std::string>& currentCoords)
{
    if (currentCoords.size() != 0)
    {
        numberCoords.push_back(NumCoord(stoi(currentNumber), currentCoords));
        currentNumber = "";
        currentCoords.clear();
    }
}

void GetNumberCoords(std::vector<std::string>& data,
    std::vector<NumCoord>& numberCoords)
{
    std::string currentNumber{""};
    std::vector<std::string> currentCoords;
    char character;
    int i{0}, j{0};

    for (auto& row : data)
    {
        i = 0;
        for (auto& character : row)
        {
            if (isdigit(character))
            {
                currentNumber += character;
                currentCoords.push_back(std::to_string(i) + "," + std::to_string(j));
            }
            else
            {
                AppendToNumCoords(numberCoords, currentNumber, currentCoords);
            }
            i++;
        }
        AppendToNumCoords(numberCoords, currentNumber, currentCoords);
        j++;
    }
}

void SumNumbers(std::set<std::string>& sumCoords,
    std::vector<NumCoord>& numberCoords)
{
    std::vector<std::string> currentCoordsList;
    int sum{0}, blocks, i{0};

    for (auto& it : numberCoords)
    {
        for (auto& it2 : it.coords)
        {
            if (sumCoords.count(it2))
            {
                sum += it.number;
                break;
            }
        }
    }

    std::cout << "Part One: " << sum << std::endl;
}

void PartOne()
{
    std::vector<std::string> data;
    std::set<std::string> characterCoords;
    std::set<std::string> sumCoords;
    std::vector<NumCoord> numberCoords;

    GetData(data);
    GetCharacterCoords(data, characterCoords);
    GetSurroundingCoords(characterCoords, sumCoords);
    GetNumberCoords(data, numberCoords);
    SumNumbers(sumCoords, numberCoords);
}


// PART TWO

void AddNewGear(int& i, int& j, std::vector<Gear>& gearCoords)
{
    std::string newCoords = std::to_string(i) + ',' + std::to_string(j);
    std::vector<NumCoord> newVector;
    Gear newGear(newCoords, newVector);
    gearCoords.push_back(newGear);
}

void GetGearCoords(std::vector<std::string>& data,
    std::vector<Gear>& gearCoords)
{
    int i{0}, j{0};

    for (std::string& datum : data)
    {
        i = 0;
        for (char& character : datum)
        {
            if (character == '*')
                AddNewGear(i, j, gearCoords);

            i++;
        }
        j++;
    }
}

void CheckForNumberCoord(std::string surroundingCoord,
    std::vector<NumCoord>& numberCoords, Gear& gearCoord)
{
    for (auto& numberCoord : numberCoords)
    {
        for (auto& coord : numberCoord.coords)
        {
            if (coord == surroundingCoord)
            {
                gearCoord.numbers.push_back(numberCoord);
                break;
            }
        }
    }
}

void CheckSurroundingCoords(std::vector<NumCoord>& numberCoords,
    std::vector<Gear>& gearCoords)
{
    std::string number{""}, surroundingCoord;
    int numericalCoord[2];

    for (auto& gearCoord : gearCoords)
    {
        for (auto& character : gearCoord.coord)
        {
            if (isdigit(character)) number += character;
            else
            {
                numericalCoord[0] = stoi(number);
                number = "";
            }
        }
        numericalCoord[1] = stoi(number);
        number = "";

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                surroundingCoord = std::to_string(numericalCoord[0] + i) + "," + std::to_string(numericalCoord[1] + j);
                CheckForNumberCoord(surroundingCoord, numberCoords, gearCoord);
            }
        }
    }
}

void AddGearRatios(std::vector<Gear>& gearCoords)
{
    int ratio{1}, sum{0};
    std::set<int> numsToAdd;

    for (auto& gearCoord : gearCoords)
    {
        for (auto& number : gearCoord.numbers)
        {
            numsToAdd.insert(number.number);
        }

        if (numsToAdd.size() == 2)
        {
            for (auto& number : numsToAdd)
            {
                ratio *= number;
            }
                sum += ratio;
                ratio = 1;
        }

        numsToAdd.clear();
    }

    std::cout << "Part Two: " << sum << std::endl;
}

void PartTwo()
{
    std::vector<std::string> data;
    std::vector<Gear> gearCoords;
    std::vector<NumCoord> numberCoords;

    GetData(data);
    GetGearCoords(data, gearCoords);
    GetNumberCoords(data, numberCoords);
    CheckSurroundingCoords(numberCoords, gearCoords);
    AddGearRatios(gearCoords);
}


int main()
{
    PartOne();
    PartTwo();

    // OutputMap(numberCoords);
    // OutputSet(characterCoords);
    // OutputSet(sumCoords);
    // ShowSumCoords(data, characterCoords, sumCoords);

    return 0;
}