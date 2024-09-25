#include <sstream>
#include "catch.hpp"
#include "List.h"
#include <limits>
#include <cmath>
#include <iostream>

using namespace std;

TEST_CASE("Insert and get")
{
    SECTION("Push back")
    {
        List l1 { };
        l1.push_back(1);
        l1.push_back(2);
        l1.push_back(3);
        l1.push_back(4);
        CHECK(l1.get(0) == 1);
        CHECK(l1.get(1) == 2);
        CHECK(l1.get(2) == 3);
        CHECK(l1.get(3) == 4);

        CHECK_THROWS(l1.get(1999)); 
        CHECK_THROWS(l1.get(-1));
    }

    SECTION("Insert front")
    {
        List l1 { };
        l1.insert_front(1);
        l1.insert_front(2);
        l1.insert_front(3);
        l1.insert_front(4);
        CHECK(l1.get(0) == 4);
        CHECK(l1.get(1) == 3);
        CHECK(l1.get(2) == 2);
        CHECK(l1.get(3) == 1);
    }

    SECTION("Insert and push")
    {
        List l1 { };
        l1.insert_front(1);
        l1.push_back(2);
        l1.insert_front(3);
        l1.push_back(4);
        CHECK(l1.get(0) == 3);
        CHECK(l1.get(1) == 1);
        CHECK(l1.get(2) == 2);
        CHECK(l1.get(3) == 4);
    }

    SECTION("POP front")
    {
        List l1 { };
        l1.insert_front(1);
        l1.insert_front(2);
        l1.insert_front(3);
        l1.insert_front(4);

        l1.pop_front();
        CHECK(l1.get(0) == 3);
        CHECK(l1.get(1) == 2);
        CHECK(l1.get(2) == 1);
    }

    SECTION("POP back")
    {
        List l1 { };
        l1.push_back(1);
        l1.push_back(2);
        l1.push_back(3);
        l1.push_back(4);

        l1.pop_back();
        CHECK(l1.get(0) == 1);
        CHECK(l1.get(1) == 2);
        CHECK(l1.get(2) == 3);


    }

    SECTION("To string")
    {
        List l1 { };
        List l2 { };
        List l3 { };
        l1.push_back(1);
        l1.push_back(2);
        l1.push_back(3);
        l1.push_back(4);
        l2.push_back(5);

        CHECK(l1.to_string() == "[1, 2, 3, 4]");
        //CHECK(l1to_string() == "[1, 2, 3]");

        CHECK(l2.to_string() == "[5]");
        CHECK(l3.to_string() == "[]");

    }

    SECTION("Front and back")
    {
        List l1 { };
        List l2 { };
        List l3 { };
        l1.push_back(1);
        l1.push_back(2);
        l1.push_back(3);
        l1.push_back(4);
        l3.push_back(8);
        
        CHECK(l1.front() == 1);
        CHECK(l1.back() == 4);
        CHECK_THROWS(l2.front());
        CHECK(l3.front() == 8);
        CHECK(l3.back() == 8);
        CHECK(l3.front() == l3.back());
    }

    SECTION("Special constructors")
    {
        List l1 {};
        l1.push_back(1);
        List l2 {l1};
        List l3 {};
        List l4 {l3};

        CHECK(l1.to_string() == l2.to_string());
        CHECK(l3.to_string() == l4.to_string());
        l3 = l1;
        CHECK(l1.to_string() == l3.to_string());
    }

}
