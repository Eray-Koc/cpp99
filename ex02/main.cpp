
#include <iostream>
#include <vector>
#include <ctime>
#include "PMergeMe.hpp"

bool isAllDigit(std::string s)
{
    for (size_t i = 0; i < s.size(); i++)
    {
        if (!std::isdigit(s[i]))
            return false;
    }
    return true;
}



int main(int ac, char **av)  
{
    if (ac < 2)
    {
        std::cerr << "Unsufficient argument amount\n";
        return (1);
    }
    std::vector<int> vec;
    std::deque<int> deq;
    for (int i = 1; i < ac; i++)
    {
        if (!isAllDigit(av[i]))
        {
            std::cerr << " Invalid Argument(s)\n";
            return (1);
        }
        int val = std::atoi(av[i]);
        vec.push_back(val);
        deq.push_back(val);
    }
    std::cout << "Before: "; PMergeME::printContainer(vec);
    std::clock_t startVec = std::clock();
    PMergeME::splitContainer(vec, 0, vec.size() - 1);
    std::clock_t endVec = std::clock();
    std::cout << "After:  "; PMergeME::printContainer(vec);
    double elapsedVec = 1000000.0 * (endVec - startVec) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << elapsedVec << " us" << std::endl;

    std::clock_t startDeq = std::clock();
    PMergeME::splitContainer(deq, 0, deq.size() - 1);
    std::clock_t endDeq = std::clock();
    double elapsedDeq = 1000000.0 * (endDeq - startDeq) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque  : " << elapsedDeq << " us" << std::endl;
    return 0;
}