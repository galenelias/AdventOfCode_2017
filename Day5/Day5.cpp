#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string input;

    std::vector<int> instructions;
    int counter = 0;
    while (std::getline(std::cin, input) && !input.empty())
    {
        instructions.push_back(std::stoi(input));
    }

    int pc = 0;
    int iterations = 0;
    for (;;)
    {
        if (pc >= instructions.size())
            break;
        iterations++;
        int jumpCount = instructions[pc];

        if (instructions[pc] >= 3)
            instructions[pc]--;
        else
            instructions[pc]++;

        pc += jumpCount;
    }

    std::cout << "Exited in " << iterations << std::endl;
}

