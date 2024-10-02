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

    SECTION("Pop front")
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

    SECTION("Pop back")
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

    SECTION("Clear/Length/Empty")
    {
        List l { };
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);

        CHECK(l.to_string() == "[1, 2, 3]");
        CHECK(l.length() == 3);
        CHECK_FALSE(l.is_empty());
        l.clear();
        CHECK(l.to_string() == "[]");
        CHECK(l.length() == 0);
        CHECK(l.is_empty());
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
        List l2 { l1 };
        List l3 { };
        List l4 { l3 };

        CHECK(l1.to_string() == l2.to_string());
        CHECK(l3.to_string() == l4.to_string());
        l3 = l1;
        CHECK(l1.to_string() == l3.to_string());
    }

    SECTION("Sort")
    {
        List l1 { };
        l1.push_back(5);
        l1.push_back(4);
        l1.push_back(3);
        l1.push_back(2);
        l1.push_back(1);
        List l2 { };
        l2.push_back(30);
        l2.push_back(12);
        l2.push_back(-4);
        l2.push_back(4);
        l2.push_back(73);
        l2.push_back(8765432);
        List l3 { };

        CHECK(l1.to_string() == "[5, 4, 3, 2, 1]");
        l1.sort();
        CHECK(l1.to_string() == "[1, 2, 3, 4, 5]");

        CHECK(l2.to_string() == "[30, 12, -4, 4, 73, 8765432]");
        l2.sort();
        CHECK(l2.to_string() == "[-4, 4, 12, 30, 73, 8765432]");
        
        CHECK(l3.to_string() == "[]");
        l3.sort();
        CHECK(l3.to_string() == "[]");
    }

    SECTION("Double values")
    {
        List l {};
        l.push_back(1);
        l.push_back(1);

        CHECK(l.to_string() == "[1, 1]");
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
