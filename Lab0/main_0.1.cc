#include <iostream>
#include <string>
#include <iomanip>

int main() {
    int int_number {};
    float float_number {};
    std::string string_text {};
    char character {};

    // 1
    std::cout << "Skriv in ett heltal: " << std::flush;
    std::cin >> int_number;
    std::cout << "Du skrev in talet: " << int_number << '\n' << std::endl;
    std::cin.ignore(1000, '\n');

    //2
    std::cout << "Skriv in fem decimaltal: " << std::flush;
    std::cin >> float_number;
    std::cout << "Du skrev in talen: " << float_number << " ";
    std::cin >> float_number;
    std::cout << float_number << " ";
    std::cin >> float_number;
    std::cout << float_number << " ";
    std::cin >> float_number;
    std::cout << float_number << " ";
    std::cin >> float_number;
    std::cout << float_number << '\n' << std::endl;
    std::cin.ignore(1000, '\n');

    std::cout << std::setprecision(4) << std::fixed << std::flush;
    
    // 3
    std::cout << "Skriv in ett heltal och ett flyttal: " << std::flush;
    std::cin >> int_number;
    std::cin >> float_number;
    std::cout << "Du skrev in heltalet:";
    std::cout << std::setw(11) << int_number << std::endl;
    std::cout << "Du skrev in flyttalet:";
    std::cout << std::setw(10) << float_number << '\n' << std::endl;
    std::cin.ignore(1000, '\n');

    // 4
    std::cout << "Skriv in ett flyttal och ett heltal: " << std::flush;
    std::cin >> float_number;
    std::cin >> int_number;
    std::cout << "Du skrev in heltalet:";
    std::cout << std::setw(11) << std::setfill('-')  << int_number << std::endl;
    std::cout << "Du skrev in flyttalet:";
    std::cout << std::setw(10) << std::setfill('-') << float_number << '\n' << std::endl;
    std::cin.ignore(1000, '\n');
  
    //5 
    std::cout << "Skriv in ett tecken: " << std::flush;
    std::cin >> character;
    std::cout << "Du skrev in tecknet: " << character << '\n' << std::endl;
    std::cin.ignore(1000, '\n');

    //6 
    std::cout << "Skriv in ett ord: " << std::flush;
    std::cin >> string_text;
    std::cout << "Du skrev in ordet: " << string_text << '\n' << std::endl;
    std::cin.ignore(1000, '\n');

    //7
    std::cout << "Skriv in ett heltal och ett ord: " << std::flush;
    std::cin >> int_number;
    std::cin >> string_text;
    std::cout << "Du skrev in talet |" << int_number <<"| och ordet |" << string_text << "|." << '\n' << std::endl;
    std::cin.ignore(1000, '\n');

    //8
    std::cout << "Skriv in ett tecken och ett ord: " << std::flush;
    std::cin >> character;
    std::cin >> string_text;
    std::cout << "Du skrev in \"" << string_text <<"\" och \'" << character << "\'." << '\n' << std::endl;
    std::cin.ignore(1000, '\n');

    //9
    std::cout << "Skriv in en rad text: " << std::flush;
    std::getline(std::cin, string_text);
    std::cout << "Du skrev in: " << string_text << '\n' << std::endl;

    //10
    std::cout << "Skriv in en till rad text: " << std::flush;
    std::getline(std::cin, string_text);
    std::cout << "Du skrev in: " << string_text << '\n' << std::endl;

    //11
    std::cout << "Skriv in tre ord: " << std::flush;
    std::cin >> string_text;
    std::cout << "Du skrev in: \"" << string_text << "\", \"";
    std::cin >> string_text;
    std::cout << string_text << "\" och \"";
    std::cin >> string_text;
    std::cout << string_text << "\"" << std::endl;
    std::cin.ignore(1000, '\n');

    return 0;
}

