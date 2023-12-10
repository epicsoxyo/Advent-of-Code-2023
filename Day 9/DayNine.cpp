#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>


// TESTING

void OutputData(std::vector<std::vector<std::int64_t>>& data)
{
    for(std::vector<std::int64_t>& line : data)
    {
        for(std::int64_t num : line) std::cout << num << " ";
        std::cout << std::endl;
    }
}


// PART ONE

void OutputLine(std::vector<std::int64_t>& line)
{
    for(std::int64_t& num : line)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

std::vector<std::int64_t> ParseLine(std::string& line)
{
    std::vector<std::int64_t> parsedLine;
    std::string currentNum{""};

    for(char& character : line)
    {
        if(isdigit(character) || (character == '-')) currentNum += character;
        else if(currentNum != "")
        {
            parsedLine.push_back(stoi(currentNum));
            currentNum = "";
        }
    }
    if(currentNum != "") parsedLine.push_back(stoi(currentNum));

    return parsedLine;
}

void GetData(std::vector<std::vector<std::int64_t>>& data)
{
    std::fstream DataFile("Data.txt");
    std::string line;

    while(getline(DataFile, line))
    {
        if(line != "") data.push_back(ParseLine(line));
    }
}

void ExtrapolateFurther(std::vector<std::vector<std::int64_t>>& implicitSequences,
    std::vector<std::int64_t>& currentSequence)
{
    currentSequence.clear();

    for(int i = 0; i < (implicitSequences.back()).size() - 1; i++)
    {
        currentSequence.push_back
        (
            implicitSequences.back()[i+1] - implicitSequences.back()[i]
        );
    }

    implicitSequences.push_back(currentSequence);
}

std::int64_t ExtrapolateValue(std::vector<std::int64_t>& sequence)
{
    std::vector<std::vector<std::int64_t>> implicitSequences;
    std::vector<std::int64_t> currentSequence;

    implicitSequences.push_back(sequence);

    ExtrapolateFurther(implicitSequences, currentSequence);

    bool isZero{false};

    while(!isZero)
    {
        isZero = true;
        for(std::int64_t& n : currentSequence)
        {
            if(n != 0)
            {
                isZero = false;
                break;
            }
        }

        if(!isZero) ExtrapolateFurther(implicitSequences, currentSequence);
    }

    std::int64_t extrapolatedVal{0};

    for(auto& implicitSequence : implicitSequences)
    {
        extrapolatedVal += implicitSequence.back();
    }

    return extrapolatedVal;
}

void SumExtrapolatedValues(std::vector<std::vector<std::int64_t>>& data)
{
    std::int64_t total{0};

    for(auto& sequence : data)
    {
        total += ExtrapolateValue(sequence);
    }

    std::cout << "Part One: " << total;
}

void PartOne()
{
    std::vector<std::vector<std::int64_t>> data;

    GetData(data);
    SumExtrapolatedValues(data);
}


// PART TWO

void ExtrapolateBackFurther(std::vector<std::vector<std::int64_t>>& implicitSequences,
    std::vector<std::int64_t>& currentSequence)
{
    currentSequence.clear();

    for(int i = 0; i < (implicitSequences.back()).size() - 1; i++)
    {
        currentSequence.push_back
        (
            implicitSequences.back()[i] - implicitSequences.back()[i+1]
        );
    }

    implicitSequences.push_back(currentSequence);
}

std::int64_t ExtrapolateBackValue(std::vector<std::int64_t>& sequence)
{
    std::vector<std::vector<std::int64_t>> implicitSequences;
    std::vector<std::int64_t> currentSequence;

    implicitSequences.push_back(sequence);

    ExtrapolateBackFurther(implicitSequences, currentSequence);

    bool isZero{false};

    while(!isZero)
    {
        isZero = true;
        for(std::int64_t& n : currentSequence)
        {
            if(n != 0)
            {
                isZero = false;
                break;
            }
        }

        if(!isZero) ExtrapolateBackFurther(implicitSequences, currentSequence);
    }

    std::int64_t extrapolatedVal{0};

    for(auto& implicitSequence : implicitSequences)
    {
        extrapolatedVal += implicitSequence[0];
    }

    return extrapolatedVal;
}


void SumBackExtrapolatedValues(std::vector<std::vector<std::int64_t>>& data)
{
    std::int64_t total{0};

    for(auto& sequence : data)
    {
        total += ExtrapolateBackValue(sequence);
    }

    std::cout << "Part Two: " << total;
}

void PartTwo()
{
    std::vector<std::vector<std::int64_t>> data;

    GetData(data);
    SumBackExtrapolatedValues(data);
}


// MAIN

int main()
{
    // PartOne();
    PartTwo();

    return 0;
}