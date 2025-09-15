#include "MutantStack.hpp"

#define PLUS 1
#define MULTIPLY 2
#define DIVISION 3
#define MINUS 4


std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}



bool isValidArgument(std::string s)
{
    if (s.length() > 1 || (!std::isdigit(s[0]) && s[0] != '+' && s[0] != '-' && s[0] != '/' && s[0] != '*'))
        return (false);
    return (true);
} 

void processNums(std::stack<int>& nums, int op)
{
    int a = nums.top();
    nums.pop();
    int b = nums.top();
    nums.pop();
    int result;

    if (op == PLUS)
        result = b + a;
    else if (op == MULTIPLY)
        result = b * a;
    else if (op == DIVISION)
    {
        if (a == 0)
        {
            std::cerr << "Error: Division by zero" << std::endl;
            exit(1);
        }
        result = b / a;
    }
    else if (op == MINUS)
        result = b - a;

    nums.push(result);
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Please try: ./<program_name> '<argument_in_quotes>'" << std::endl;
        return (1);
    }

    std::stack<std::string> allData;
    std::stack<int> nums;
    std::vector<std::string> args = split(av[1], ' ');
    int i = args.size();
    if (i < 3)
    {
        std::cerr << "Unsufficient amount of arguments" << std::endl;
        return (1);
    }
    while (0 <= --i)
    {
        if (!isValidArgument(args[i]))
        {
            std::cerr << "Invalid Argument(s)" << std::endl;
            return (1);
        }
        allData.push(args[i]);
    }
    while (!allData.empty())
    {
        if (std::isdigit(allData.top()[0]))
        {
            nums.push(std::atoi(allData.top().c_str()));
        }
        else if (nums.size() < 2)
        {
            std::cerr << "Not enough numbers" << std::endl;
            return (1);
        }
        else
        {
            if (allData.top()[0] == '+')
                processNums(nums, PLUS);
            else if (allData.top()[0] == '*')
                processNums(nums, MULTIPLY);
            else if (allData.top()[0] == '/')
                processNums(nums, DIVISION);
            else if (allData.top()[0] == '-')
                processNums(nums, MINUS);
            else
            {
                std::cerr << "Invalid Operator" << std::endl;
                return (1);
            }
        }
        allData.pop();
    }
    std::cout << nums.top() << std::endl;
    return (0);
}