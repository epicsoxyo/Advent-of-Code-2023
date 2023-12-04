#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <set>

bool usingTestData{true};

// TESTING

void OutputData(std::vector<std::string>& data)
{
    for (std::string& datum : data)
    {
        std::cout << datum << std::endl;
    }

    std::cout << std::endl;
}

void OutputData(std::vector<std::array<int, 35>>& data)
{
    std::cout << "Nums:\n";
    for (std::array<int, 35>& row : data)
    {
        for (int& num : row)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}


// MAIN

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

void ParseData(std::vector<std::string>& data,
    std::vector<std::array<int, 35>>& nums)
{
    std::string currentNum;
    std::array<int, 35> currentArray;
    int i{0};

    for (auto& datum : data)
    {
        datum.erase(0, datum.find(":"));

        for (auto& character : datum)
        {
            if (isdigit(character)) currentNum += character;
            else if (currentNum != "")
            {
                currentArray[i] = stoi(currentNum);
                currentNum = "";
                i++;
            }
        }

        currentArray[i] = stoi(currentNum);
        nums.push_back(currentArray);

        currentNum = "";
        i = 0;
    }
}

int IntPow(int a, int b)
{
  int i = 1;
  for (int j = 1; j <= b; j++)  i *= a;
  return i;
}

void PartOne(std::vector<std::array<int, 35>>& nums)
{
    std::set<int> myNums;
    std::array<int, 10> winningNums;
    int points{0}, numberOfWinningNums;

    for (std::array<int, 35>& num : nums)
    {
        numberOfWinningNums = 0;
        myNums.clear();

        for (int i = 0; i < 10; i++)
            winningNums[i] = num[i];
        for (int i = 10; i < 35; i++)
            myNums.insert(num[i]);
        
        for (int& winningNum : winningNums)
            if (myNums.count(winningNum)) numberOfWinningNums += 1;


        if (numberOfWinningNums > 0) points += IntPow(2, numberOfWinningNums - 1);
    }

    std::cout << "Score: " << points << std::endl;

}

void PartTwo(std::vector<std::array<int, 35>>& nums)
{
    std::set<int> myNums;
    std::array<int, 10> winningNums;
    std::array<int, 214> copies;
    int pos{0}, numberOfWinningNums;

    copies.fill(1);

    for (std::array<int, 35>& num : nums)
    {
        numberOfWinningNums = 0;
        myNums.clear();

        for (int i = 0; i < 10; i++)
            winningNums[i] = num[i];
        for (int i = 10; i < 35; i++)
            myNums.insert(num[i]);
        
        for (int& winningNum : winningNums)
            if (myNums.count(winningNum)) numberOfWinningNums += 1;

        for (int i = pos + 1; i <= pos + numberOfWinningNums; i++)
            copies[i] += copies[pos];

        pos++;
    }

    int scratchcards{0};

    for (auto& copy : copies) scratchcards += copy;

    std::cout << "Scratchcards: " << scratchcards << std::endl; 
}

int main()
{
    std::vector<std::string> data;
    std::vector<std::array<int, 35>> nums;

    GetData(data);
    // OutputData(data);
    ParseData(data, nums);
    // OutputData(nums);
    PartTwo(nums);

}