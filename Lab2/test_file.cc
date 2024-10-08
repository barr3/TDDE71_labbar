#include <sstream>
#include "catch.hpp"
#include "List.h"
#include <limits>
#include <cmath>
#include <iostream>

using namespace std;

TEST_CASE("List")
{
    SECTION("Push back and get")
    {
        List l1 { };
        l1.push_back(1);
        l1.push_back(2);

        CHECK(l1.get(0) == 1);
        CHECK(l1.get(1) == 2);
        CHECK_THROWS(l1.get(2));

        List l2 { };
        CHECK_THROWS(l2.get(0));
    }

    SECTION("Front") {
        List l { };
        l.push_back(1);
        l.push_back(2);

        CHECK(l.front() == 1);
    }

    SECTION("Back") {
        List l { };
        l.push_back(1);
        l.push_back(2);

        CHECK(l.back() == 2);
    }

    SECTION("To string")
    {
        List l1 { };
        l1.push_back(1);
        l1.push_back(2);

        CHECK(l1.to_string() == "[1, 2]");

        List l2 { };

        CHECK(l2.to_string() == "[]");
    }

    SECTION("Insert front")
    {
        List l { };
        l.insert_front(1);
        l.insert_front(2);
        l.insert_front(3);
        
        CHECK(l.to_string() == "[3, 2, 1]");
    }

    SECTION("Pop front")
    {
        List l1 { };
        l1.push_back(1);
        l1.push_back(2);
        l1.push_back(3);

        CHECK(l1.to_string() == "[1, 2, 3]");

        l1.pop_front();
        
        CHECK(l1.to_string() == "[2, 3]");

        List l2 { };

        CHECK_THROWS(l2.pop_front());
    }

    SECTION("Pop back")
    {
        List l1 { };
        l1.push_back(1);
        l1.push_back(2);
        l1.push_back(3);

        CHECK(l1.to_string() == "[1, 2, 3]");

        l1.pop_back();

        CHECK(l1.to_string() == "[1, 2]");

        List l2 { };

        CHECK_THROWS(l2.pop_back());
    }

    SECTION("Duplicate values")
    {
        List l { };
        l.push_back(1);
        l.push_back(1);
        
        CHECK(l.to_string() == "[1, 1]");
    }


    SECTION("Mixed insertion/deletion")
    {
        List l { };
        l.push_back(1);
        l.insert_front(2);
        l.pop_back();
        l.insert_front(3);
        l.push_back(4);
        l.push_back(5);
        l.pop_front();
        l.pop_front();
        l.insert_front(6);

        CHECK(l.to_string() == "[6, 4, 5]");
    }

    SECTION("Length")
    {
        List l1 { };
        l1.push_back(1);
        l1.push_back(2);
        l1.push_back(3);
        
        CHECK(l1.length() == 3);

        List l2 { };
        l2.push_back(1);
        l2.push_back(2);
        l2.push_back(3);
        l2.push_back(3);
        l2.push_back(3);
        l2.push_back(3);
        
        CHECK(l2.length() == 6);

        List l3 { };

        CHECK(l3.length() == 0);
    }

    SECTION("Is empty")
    {
        List l1 { };

        CHECK(l1.is_empty());    

        List l2 { };
        l2.push_back(1);

        CHECK_FALSE(l2.is_empty());    
    }

    SECTION("Clear")
    {
        List l { };
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);

        CHECK(l.to_string() == "[1, 2, 3]");

        l.clear();

        CHECK(l.to_string() == "[]");

        List l2 { };
        CHECK(l.to_string() == "[]");

        l.clear();

        CHECK(l.to_string() == "[]");
    }

    SECTION("Sort")
    {
        List l1 { };
        l1.push_back(4);
        l1.push_back(1);
        l1.push_back(-100);
        l1.push_back(-3);
        l1.push_back(1415);
        l1.push_back(11);
        l1.push_back(3);

        CHECK(l1.to_string() == "[4, 1, -100, -3, 1415, 11, 3]");

        l1.sort();

        CHECK(l1.to_string() == "[-100, -3, 1, 3, 4, 11, 1415]");

        List l2 { };

        CHECK(l2.to_string() == "[]");

        l2.sort();

        CHECK(l2.to_string() == "[]");
    }

    SECTION("Copy constructor")
    {
        List l1 { };
        l1.push_back(1);
        l1.push_back(2);

        List l2 { l1 };

        CHECK(l1.to_string() == "[1, 2]");
        CHECK(l2.to_string() == "[1, 2]");

        l1.pop_back();

        CHECK(l1.to_string() == "[1]");
        CHECK(l2.to_string() == "[1, 2]");
    }

    SECTION("Move constructor")
    {
        List l1 { };
        l1.push_back(1);
        l1.push_back(2);

        List l2 { std::move(l1) };
        
        CHECK(l1.to_string() == "[]");
        CHECK(l2.to_string() == "[1, 2]");
    }

    SECTION("Copy assignment operator")
    {
        List l1 { };
        l1.push_back(1);
        l1.push_back(2);

        List l2 = l1;

        CHECK(l1.to_string() == "[1, 2]");
        CHECK(l2.to_string() == "[1, 2]");

        l1.pop_back();

        CHECK(l1.to_string() == "[1]");
        CHECK(l2.to_string() == "[1, 2]");
    }

    SECTION("Copy assignment operator")
    {
        List l1 { };
        l1.push_back(1);
        l1.push_back(2);

        List l2 = std::move(l1);
        
        CHECK(l1.to_string() == "[]");
        CHECK(l2.to_string() == "[1, 2]");
    }

    SECTION("Constant lists")
    {
        List l1 { };
        l1.push_back(1);
        l1.push_back(2);

        const List l2 { l1 };
        CHECK(l2.to_string() == l1.to_string());
    }
}
