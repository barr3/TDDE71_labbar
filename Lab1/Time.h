class Time
{
    public:
        Time();
        Time(unsigned int hour, unsigned int minute, unsigned int second);
        Time(std::string time);
        std::string to_string(std::string format = "24h");
        bool is_am();
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
};

std::stringstream& operator<<(std::stringstream& ss, Time const &rhs);
