#include "Utils.hpp"

std::string Utils::trimSpaces(std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && std::isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}

bool Utils::isAllDigit(std::string s)
{
    for (size_t i = 0; i < s.size(); i++)
    {
        if (!std::isdigit(s[i]))
            return false;
    }
    return true;
}

std::vector<std::string> Utils::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}