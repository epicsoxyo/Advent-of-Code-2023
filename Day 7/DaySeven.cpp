#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

enum HandTypes
{
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind
};

void OutputData(std::vector<std::pair<std::string, int>>& hands)
{
    for(auto& hand : hands)
    {
        std::cout << hand.first << " " << hand.second << std::endl;
    }
    std::cout << std::endl;
}

void GetData(std::vector<std::pair<std::string, int>>& hands)
{
    std::fstream DataFile("Data.txt");
    std::string line, hand, bet;
    bool isHand;

    while(getline(DataFile, line))
    {
        if (line.length() > 0)
        {
            isHand = true;
            for(char& character : line)
            {
                if(character == ' ') isHand = false;
                else if(isHand) hand += character;
                else if(isdigit(character)) bet += character;
            }
            if (bet.length() > 0) hands.emplace_back(hand, stoi(bet));
            hand = "";
            bet = "";
        }
    }
}

int GetHandType(std::string hand)
{
    std::map<char, int> count;
    int jokers{0};

    for (int i = 0; hand[i]; i++) 
    {
        if (count.find(hand[i]) == count.end()) 
            count.insert(std::make_pair(hand[i], 1));
        else
            count[hand[i]]++;
    }

    if (count.find('J') != count.end())
    {
        if(count['J'] == 5) return FiveOfAKind;
        jokers = count['J'];
        count.erase('J');
    }

    std::pair<char, int> maxValue{'.', 0}, secondMaxValue{'.', 0};

    for(auto& item : count)
    {
        if(item.second > maxValue.second)
        {
            secondMaxValue = maxValue;
            maxValue = item;
        }
        else if(item.second > secondMaxValue.second)
        {
            secondMaxValue = item;
        }
    }

    maxValue.second += jokers;

    switch (maxValue.second)
    {
        case 5: return FiveOfAKind;
        case 4: return FourOfAKind;
        case 3: switch (secondMaxValue.second)
        {
            case 2: return FullHouse;
            default: return ThreeOfAKind;
        }
        case 2: switch (secondMaxValue.second)
        {
            case 2: return TwoPair;
            default: return OnePair;
        }
        default: return HighCard;
    }
}

int ConvertCardToInt(char& card)
{
    switch(card)
    {
        case 'A': return 14;
        case 'K': return 13;
        case 'Q': return 12;
        case 'J': return 1;
        case 'T': return 10;
        default: return card - '0';
    }
}

bool CompareHands(std::pair<std::string, int>& hand1, std::pair<std::string, int>& hand2)
{
    int handType1{GetHandType(hand1.first)}, handType2{GetHandType(hand2.first)};

    if (handType1 != handType2) return handType1 < handType2;

    int card1, card2;

    for (int i = 0; i < 5; i++)
    {
        card1 = ConvertCardToInt(hand1.first[i]);
        card2 = ConvertCardToInt(hand2.first[i]);

        if(card1 != card2) return card1 < card2;
    }

    return false;
}

void CalculateScore(std::vector<std::pair<std::string, int>>& hands)
{
    int total{0}, rank{0};

    for(auto& hand : hands)
    {
        rank++;
        total += rank * hand.second;
    }

    std::cout << "Part One: " << total << std::endl;
}

int main()
{
    std::vector<std::pair<std::string, int>> hands;
    GetData(hands);
    // OutputData(hands);
    std::sort(hands.begin(), hands.end(), CompareHands);
    // OutputData(hands);
    CalculateScore(hands);
}