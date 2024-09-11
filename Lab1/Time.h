#include <string>

class Time
{
    public:
        Time();
        Time(unsigned int hour, unsigned int minute, unsigned int second);
        Time(std::string time);
        std::string to_string(std::string format = "24h") const;
        bool is_am() const;
        unsigned int get_hour();
        unsigned int get_minute();
        unsigned int get_second();

        bool operator>(Time const &rhs) const;
        bool operator<(Time const &rhs) const;
        bool operator<=(Time const &rhs) const;
        bool operator>=(Time const &rhs) const;
        bool operator==(Time const &rhs) const;
        bool operator!=(Time const &rhs) const;

    private:
        unsigned int hour;
        unsigned int minute;
        unsigned int second;
        unsigned int calculate_seconds(unsigned int hour, unsigned int minute, unsigned int second) const;
        void throw_if_invalid_time() const;
        void add_num_to_ss(std::stringstream &ss, int num) const;
        std::string to_string_24h() const;
        std::string to_string_12h() const;
};

std::ostream& operator<<(std::ostream& ss, Time const &rhs);
