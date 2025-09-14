#include <stack>
#include <vector>
#include <iostream>
#include <sstream>

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
    int result = 0;

    if (op == PLUS)
    {
        while (!nums.empty())
        {
            result += nums.top();
            nums.pop();
        }
    }
    else if (op == MULTIPLY)
    {
        result = 1;
        while (!nums.empty())
        {
            result *= nums.top();
            nums.pop();
        }
    }
    else if (op == DIVISION)
    {
        
    }
    nums.push(result);

}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Please try: ./<program_name> '<argument_in_quotes>'" << std::endl;
        return (1);
    }

    std::stack<std::string> s;
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
        s.push(args[i]);
    }
    while (!s.empty())
    {
        if (std::isdigit(s.top()[0]))
        {
            nums.push(std::atoi(s.top().c_str()));
        }
        else
        {

        }
        if (nums.size() == 2)
        {

        }
        s.pop();
    }
    return (0);
}