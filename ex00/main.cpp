#include "btc.hpp"

#define USER_INPUT  0
#define CSV_FILE 1


bool isValidNum(std::string fValue)
{
    int i = 0;
    const char *f = fValue.c_str();
    if (f[0] == '.' || f[0] == '-')
        return false;
    if (f[i] == '+')
        i++;
    while (f[i])
    {
        if (!std::isdigit(f[i]) && f[i] != '.')
            return false;
        i++;
    }
    return true;
}


std::string trimSpaces(std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && std::isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}

void parseLine(std::string line, std::map<DateTime, float>& keyVal, std::map<DateTime, float> csv)
{
    if (std::count(line.begin(), line.end(), '|') != 1) 
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    std::vector<std::string> tokens = Utils::split(line, '|');
    if (tokens.size() != 2)
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    std::string date = Utils::trimSpaces(tokens[0]);
    std::string val = Utils::trimSpaces(tokens[1]);

    if (std::count(date.begin(), date.end(), '-') != 2)
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    std::vector<std::string> datTimeValues = Utils::split(date, '-');
    if (datTimeValues.size() != 3)
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    DateTime d(datTimeValues[0], datTimeValues[1], datTimeValues[2], false);
    if (d.year == "0000")
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    if (std::atof(val.c_str()) <= 0)
    {

        std::cerr << "Error: not a positive number. " << std::endl;
        return;
    }
    if (std::atof(val.c_str()) > 1000)
    {

        std::cerr << "Error: value can't be bigger than 1000. " << std::endl;
        return;
    }
    std::stringstream ss(val);
    int a;
    ss >> a;
    if (ss.fail())
    {
        std::cerr << "Error: too large number." << std::endl;
        return;
    }
    if (isValidNum(val))
        keyVal[d] = std::atof(val.c_str());
    else
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    std::map<DateTime, float>::const_iterator it = csv.lower_bound(d);
    std::map<DateTime, float>::const_iterator key_val_it = keyVal.lower_bound(d);
    if (it == csv.end() || it->first != d) 
        {
            if (it == csv.begin()) 
            {
                std::cerr << "Error: no data before => " << date << std::endl;
                return;
            }
            --it;
        }

        float result = key_val_it->second * it->second;

        std::cout << d << " => " << key_val_it->second << " = " << result << std::endl;
}


std::map<DateTime, float> openFileAndStartReading(std::string userInputFile, std::map<DateTime, float> csv)
{
    std::map<DateTime, float> keyVal;
    std::ifstream file(userInputFile.c_str());
    if (!file.is_open())
        throw InvalidFileException();
    std::string line;
    getline(file, line);
    if (line != "date | value")
        throw InvalidFileContentException();
    while (getline(file, line))
    {
        parseLine(line, keyVal, csv);
    }
    return keyVal;
}


std::map<DateTime, float> parseCsvFile(std::string csvFile)
{
    std::map<DateTime, float> keyVal;
    std::string line;

    std::ifstream file(csvFile.c_str());
    if (!file.is_open())
        throw InvalidFileException();
    getline(file, line);
    if (line != "date,exchange_rate")
        throw InvalidFileContentException();
    while (getline(file, line))
    {
        if (std::count(line.begin(), line.end(), ',') != 1 || std::count(line.begin(), line.end(), '-') != 2)
            throw InvalidFileContentException();
        std::vector<std::string> datePriceValues = Utils::split(line, ',');
        std::string date = Utils::trimSpaces(datePriceValues[0]);
        std::string price = Utils::trimSpaces(datePriceValues[1]);
        if (date.empty() || price.empty())
            throw InvalidFileContentException();
        if (std::count(date.begin(), date.end(), '-') != 2)
            throw InvalidFileContentException();
        std::vector<std::string> dateTimeValues = Utils::split(date, '-');
        DateTime d(dateTimeValues[0], dateTimeValues[1], dateTimeValues[2]);
        if (isValidNum(price))
            keyVal[d] = std::atof(price.c_str());
        else
            throw InvalidFileContentException();
    }
    return keyVal;
}

int main(int ac, char **av)
{

    if (ac != 2)
    {
        std::cerr << "Wrong way to make things work, try: ./<program_name> <input_file>" << std::endl;
        return (1);
    }
    std::map<DateTime, float> csv;
    std::map<DateTime, float> userInputFile;
    try
    {
        csv = parseCsvFile("data.csv");
        // std::map<DateTime, float>::iterator it = csv.begin();
        // while (it != csv.end())
        // {
        //     std::cout << it->first << "  |  ";
        //     std::cout << std::fixed << std::setprecision(2) << it->second << std::endl;
        //     ++it;
        // }
        // return (0);
        openFileAndStartReading(av[1], csv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}