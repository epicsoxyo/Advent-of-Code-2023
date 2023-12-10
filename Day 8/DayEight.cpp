#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


void GetData(std::string& instructions, std::map<std::string, std::pair<std::string, std::string>>& nodes)
{
    std::fstream DataFile("Data.txt");
    std::string line, node, left, right;

    getline(DataFile, instructions);
    getline(DataFile, line); // skip blank line

    while(getline(DataFile, line))
    {
        node = line.substr(0, 3);
        left = line.substr(7, 3);
        right = line.substr(12, 3);

        nodes.insert({node, std::make_pair(left, right)});
    }    

}

void TraversePath(std::string& instructions, std::map<std::string, std::pair<std::string, std::string>>& nodes)
{
    std::string currentNode{"AAA"};
    char currentInstruction;
    int numOfInstructions{instructions.length()}, instructionIndex{0}, totalInstructions{0};

    while(currentNode != "ZZZ")
    {
        currentInstruction = instructions[instructionIndex];

        if(currentInstruction == 'L') currentNode = nodes[currentNode].first;
        else currentNode = nodes[currentNode].second;

        instructionIndex++;
        if (instructionIndex == numOfInstructions) instructionIndex -= numOfInstructions;

        totalInstructions++;
    }
    std::cout << "Part One: " << totalInstructions << std::endl;
}

void PartOne()
{
    std::string instructions, startingNode{"AAA"};
    std::map<std::string, std::pair<std::string, std::string>> nodes;

    GetData(instructions, nodes);
    TraversePath(instructions, nodes);
}


void GetStartingNodes(std::map<std::string, std::pair<std::string, std::string>>& nodes,
    std::vector<std::string>& startingNodes)
{
    for(auto& node : nodes)
    {
        if(node.first[2] == 'A') startingNodes.push_back(node.first);
    }
}

long long TraversePath(std::string& startingNode, std::string& instructions,
    std::map<std::string, std::pair<std::string, std::string>>& nodes)
{
    std::string currentNode{startingNode};
    char currentInstruction;
    int numOfInstructions{instructions.length()}, instructionIndex{0}, totalInstructions{0};

    while(currentNode[2] != 'Z')
    {
        currentInstruction = instructions[instructionIndex];

        if(currentInstruction == 'L') currentNode = nodes[currentNode].first;
        else currentNode = nodes[currentNode].second;

        instructionIndex++;
        if (instructionIndex == numOfInstructions) instructionIndex -= numOfInstructions;

        totalInstructions++;
    }

    return totalInstructions;
}

void TraverseAllPaths(std::string& instructions, std::map<std::string, std::pair<std::string, std::string>>& nodes,
    std::vector<std::string>& startingNodes)
{
    std::vector<long long> nodePathLengths;

    std::cout << "Node path lengths:" << std::endl;
    for(std::string& node : startingNodes)
        std::cout << TraversePath(node, instructions, nodes) << std::endl;
    std::cout << "Now go calculate the LCM and Bob's yer uncle" << std::endl;
}

void PartTwo()
{
    std::string instructions;
    std::map<std::string, std::pair<std::string, std::string>> nodes;
    std::vector<std::string> startingNodes;

    GetData(instructions, nodes);
    GetStartingNodes(nodes, startingNodes);
    TraverseAllPaths(instructions, nodes, startingNodes);
}


int main()
{
    // PartOne();
    PartTwo();

    return 0;
}