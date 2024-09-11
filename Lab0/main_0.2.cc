
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

struct Result {
    std::string name;
    int hours;
    int minutes;
    int seconds;
};

bool operator>(Result lhs, Result rhs);
std::vector<Result> read_file_to_vec(std::ifstream & ifs);
std::string format_number(int num);
void print_results(std::vector<Result> const &results, int line_count);
void sort_results(std::vector<Result> &results);
std::ifstream get_file_from_user();
int get_line_count_from_user(int max_line_count);

int main() 
{
    std::ifstream ifs = get_file_from_user();
    std::vector<Result> r = read_file_to_vec(ifs);

    int line_count = get_line_count_from_user(r.size());   

    sort_results(r);
    print_results(r, line_count);

    return 0;
}

// Allows comparing Result-objects
bool operator>(Result lhs, Result rhs)
{
    int lhs_total_seconds = lhs.hours * 3600 + lhs.minutes * 60 + lhs.seconds;
    int rhs_total_seconds = rhs.hours * 3600 + rhs.minutes * 60 + rhs.seconds;
    return lhs_total_seconds > rhs_total_seconds;
}

std::ifstream get_file_from_user() 
{
    std::string file_name {};
    std::ifstream ifs {};
    while (true)
    {
        std::cout << "Ange filnamn: " << std::flush;
        std::cin >> file_name;
        
        // Checks if the file 'file_name' could be opened
        ifs.open(file_name);
        if (!ifs.fail())
        {
            break;
        }

        std::cout << "FEL: Filen gick inte att öppna!" << std::endl;
    }

    return ifs;
}

int get_line_count_from_user(int max_line_count)
{
    int line_count {};
    while (true)
    {
        std::cout << "Ange antal rader: " << std::flush;
        // Take input and make sure it is valid
        if (!(std::cin >> line_count))
        {
            std::cout << "Inmatningen måste vara ett heltal!" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        else if ((line_count > max_line_count) || (line_count < 0))
        {
            std::cout << "Det finns inte " << line_count << " rader i filen." << std::endl;
        }
        else 
        {
            break;
        }
    }

    return line_count;
}

// Creates a Result object for each line and collects them in a vector
std::vector<Result> read_file_to_vec(std::ifstream & ifs) 
{
    std::string line {};
    std::vector<Result> results {};

    while (std::getline(ifs, line))
    {
        std::istringstream line_ss {line};
        Result temp_result {};
        line_ss >> temp_result.name;
        line_ss >> temp_result.hours;
        line_ss >> temp_result.minutes;
        line_ss >> temp_result.seconds;

        results.push_back(temp_result);
    }

    ifs.close();
    return results;
}

//Adds a leading zero if the number is one-digit
std::string format_number(int num)
{
    std::ostringstream number_string {};
    if(num <10)
    {
        number_string << "0" << num;
    }
    else
    {
        number_string << num;
    }

    return number_string.str();
}

void print_results(std::vector<Result> const &results, int line_count)
{   
    std::cout << "   Namn   |   Tid   " << std::endl;
    std::cout << "====================" << std::endl;
    for (int i = 0; i < line_count; i++)
    {
        std::string hours   = format_number(results[i].hours);
        std::string minutes = format_number(results[i].minutes);
        std::string seconds = format_number(results[i].seconds);

        std::cout << std::setw(9) << std::right << results[i].name << std::flush; 
        std::cout << " | " << hours << ":" << minutes << ":" << seconds << std::endl;
    }
}

void sort_results(std::vector<Result> &results) 
{
    for (unsigned int i = 0; i < results.size() - 1; ++i)
    {
        for (unsigned int j = 0; j < results.size() - i - 1; ++j)
        {
            if (results.at(j) > results.at(j + 1))
            {
                std::swap(results.at(j), results.at(j + 1));
            }
        }
    }
}
