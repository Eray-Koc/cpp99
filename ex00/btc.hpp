#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <iomanip>
#include "Utils.hpp"

class NotEnoughArgumentException : public std::exception
{
public:
    virtual const char *what() const throw()
    {
        return "Wrong way to make things work, try: ./btc <your_file>";
    }
};

class InvalidFileException : public std::exception
{
public:
    virtual const char *what() const throw()
    {
        return "No such a file";
    }
};

class InvalidFileContentException : public std::exception
{
public:
    virtual const char *what() const throw()
    {
        return "Invalid file content";
    }
};

class DateTime
{

    public:
        std::string year;
        std::string month;
        std::string day;
  
        std::string printOut(void) const
        {
            std::ostringstream oss;
            oss << this->year << "-" << this->month << "-" << this->day;
            return oss.str();
        }
        void valueVerifier()
        {
            if (!Utils::isAllDigit(this->day) || !Utils::isAllDigit(this->month) || !Utils::isAllDigit(this->year) || this->year.length() != 4 || this->day.length() != 2 || this->month.length() != 2)
                throw InvalidFileContentException();

            int year_int = std::atoi(this->year.c_str());
            int month_int = std::atoi(this->month.c_str());
            int day_int = std::atoi(this->day.c_str());
            if (day_int < 1 || day_int > 31 || year_int < 1 || month_int < 1 || month_int > 12)
                throw InvalidFileContentException();

            if (month_int < 8 && month_int % 2 != 0 && day_int > 31)
                throw InvalidFileContentException();
            if (month_int > 7 && month_int % 2 == 0 && day_int > 31)
                throw InvalidFileContentException();
            if (month_int == 2)
            {
                if (year_int % 4 != 0 && day_int > 28)
                    throw InvalidFileContentException();
                else if (year_int % 4 == 0 && day_int > 29)
                    throw InvalidFileContentException();
            }
            if ((month_int == 4 || month_int == 6 || month_int == 9 || month_int == 11) && day_int > 30)
                throw InvalidFileContentException();
        }

        void valueVerifierButSafe()
        {
            bool fail = false;

            if (!Utils::isAllDigit(this->day) || !Utils::isAllDigit(this->month) || !Utils::isAllDigit(this->year) || this->year.length() != 4 || this->day.length() != 2 || this->month.length() != 2)
            {
                this->year = "0000";
                return;
            }

            int year_int = std::atoi(this->year.c_str());
            int month_int = std::atoi(this->month.c_str());
            int day_int = std::atoi(this->day.c_str());
            if (day_int < 1 || day_int > 31 || year_int < 1 || month_int < 1 || month_int > 12)
                fail = true;

            if (month_int < 8 && month_int % 2 != 0 && day_int > 31)
                fail = true;
            if (month_int > 7 && month_int % 2 == 0 && day_int > 31)
                fail = true;
            if (month_int == 2)
            {
                if (year_int % 4 != 0 && day_int > 28)
                    fail = true;
                else if (year_int % 4 == 0 && day_int > 29)
                    fail = true;
            }
            if ((month_int == 4 || month_int == 6 || month_int == 9 || month_int == 11) && day_int > 30)
                fail = true;
            if (fail)
                this->year = "0000";
        }

        bool operator<(const DateTime& other) const {
            if (year < other.year) return true;
            if (year > other.year) return false;

            if (month < other.month) return true;
            if (month > other.month) return false;

            if (day < other.day) return true;
            if (day > other.day) return false;

            return false;
        }

        bool operator!=(const DateTime& other) const {
            if (year == other.year && day == other.day && month == other.month)
                return false;
            return true;
        }


        DateTime(std::string _year, std::string _month, std::string _day, bool isCsv = true) : year(_year), month(_month), day(_day)
        {
            if (isCsv)
                valueVerifier();
            else
                valueVerifierButSafe();
        }
        ~DateTime() {}
};  

std::ostream &operator<<(std::ostream &o, const DateTime &d)
{
    o << d.printOut();
    return o;
}
