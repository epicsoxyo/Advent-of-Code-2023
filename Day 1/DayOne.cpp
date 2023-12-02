#include <iostream>
#include <string>
#include <fstream>

void SwitchCharacter(std::string& dataString, std::string numberWord, char replacement)
{
    if(dataString.find(numberWord) != std::string::npos)
    {
        dataString[dataString.find(numberWord) + 1] = replacement;
    }
}

void FilterString(std::string& dataString)
{
    for (int i = 0; i < dataString.length(); i++)
    {
        SwitchCharacter(dataString, "one", '1');
        SwitchCharacter(dataString, "two", '2');
        SwitchCharacter(dataString, "three", '3');
        SwitchCharacter(dataString, "four", '4');
        SwitchCharacter(dataString, "five", '5');
        SwitchCharacter(dataString, "six", '6');
        SwitchCharacter(dataString, "seven", '7');
        SwitchCharacter(dataString, "eight", '8');
        SwitchCharacter(dataString, "nine", '9');
    }
}

char GetFirstInt(std::string&dataString)
{
    for(int i = 0; i <= dataString.length(); i++)
    {
        if (isdigit(dataString[i])) return dataString[i];
    }
    return '\0';
}

char GetLastInt(std::string& dataString)
{
    for (int i = dataString.length(); i >= 0; i--)
    {
        if (isdigit(dataString[i])) return dataString[i];
    }
    return '\0';
}

int main()
{
    std::string calibrationValue;
    std::ifstream DataFile("Data.txt");

    char firstInt, lastInt;
    std::string newString, completeInt;
    completeInt.resize(2);
    int total{0};

    while (getline(DataFile, calibrationValue))
    {
        FilterString(calibrationValue);
    
        firstInt = GetFirstInt(calibrationValue);

        if (!isblank(firstInt))
        {
            lastInt = GetLastInt(calibrationValue);
        
            completeInt[0] = firstInt;
            completeInt[1] = lastInt;
        
            total += stoi(completeInt);
        }

    }

    std::cout << total;

    DataFile.close();

    return 0;
}