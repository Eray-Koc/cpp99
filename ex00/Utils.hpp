#include <string>
#include <vector>
#include <sstream>
class Utils
{
    public:
        static std::string trimSpaces(std::string& s);
        static bool isAllDigit(std::string s);
        static std::vector<std::string> split(const std::string& str, char delimiter);
};
