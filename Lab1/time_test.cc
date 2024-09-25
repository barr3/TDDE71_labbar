#include <sstream>
#include "catch.hpp"
#include "Time.h"
#include <limits>
#include <cmath>

using namespace std;


bool compare_equal(double a, double b)
{
   return std::abs(a - b) <= 0.001;
}

TEST_CASE("Constructors and getters")
{
   SECTION("Default")
   {
      Time empty{};
      CHECK(empty.get_hour() == 0);
      CHECK(empty.get_minute() == 0);
      CHECK(empty.get_second() == 0);
   }
   /* ----- REMOVE THIS COMMENT WHEN PREVIOUS TEST PASSES ----- */

   SECTION("Integer")
   {
      Time t0{0, 0, 0};
      Time t1{12, 30, 30};
      Time t2{23, 59, 59};

      CHECK_THROWS(Time{13, 35, 60});
      CHECK_THROWS(Time{13, 60, 35});
      CHECK_THROWS(Time{24, 35, 35});

      CHECK(t0.get_hour() == 0);
      CHECK(t0.get_minute() == 0);
      CHECK(t0.get_second() == 0);
      CHECK(t1.get_hour() == 12);
      CHECK(t1.get_minute() == 30);
      CHECK(t1.get_second() == 30);
      CHECK(t2.get_hour() == 23);
      CHECK(t2.get_minute() == 59);
      CHECK(t2.get_second() == 59);
   }

   SECTION("String")
   {
      Time t0{"00:00:00"};
      Time t1{"12:30:30"};
      Time t2{"23:59:59"};

      CHECK_THROWS(Time{"13:35:60"});
      CHECK_THROWS(Time{"13:60:35"});
      CHECK_THROWS(Time{"24:35:35"});

      CHECK(t0.get_hour() == 0);
      CHECK(t0.get_minute() == 0);
      CHECK(t0.get_second() == 0);
      CHECK(t1.get_hour() == 12);
      CHECK(t1.get_minute() == 30);
      CHECK(t1.get_second() == 30);
      CHECK(t2.get_hour() == 23);
      CHECK(t2.get_minute() == 59);
      CHECK(t2.get_second() == 59);
   }
}
TEST_CASE("is_am")
{
   Time t0{"05:00:00"};
   Time t1{"14:00:00"};
   CHECK(t0.is_am());
   CHECK_FALSE(t1.is_am());
}

TEST_CASE("to_string")
{
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};
   SECTION("24 hour format no argument")
   {
      CHECK(t0.to_string() == "00:00:00");
      CHECK(t1.to_string() == "11:59:59");
      CHECK(t2.to_string() == "12:00:00");
      CHECK(t3.to_string() == "13:00:00");
      CHECK(t4.to_string() == "23:59:59");
      // Fill with more tests!
   }

   SECTION("24 hour format with argument")
   {
      CHECK(t0.to_string("24h") == "00:00:00");
      CHECK(t1.to_string("24h") == "11:59:59");
      CHECK(t2.to_string("24h") == "12:00:00");
      CHECK(t3.to_string("24h") == "13:00:00");
      CHECK(t4.to_string("24h") == "23:59:59");
      // Fill with more tests!
   }

   SECTION("12 hour format")
   {
      CHECK(t0.to_string("12h") == "12:00:00am");
      CHECK(t1.to_string("12h") == "11:59:59am");
      CHECK(t2.to_string("12h") == "12:00:00pm");
      CHECK(t3.to_string("12h") == "01:00:00pm");
      CHECK(t4.to_string("12h") == "11:59:59pm");
   }
}

TEST_CASE("operators")
{
   Time t0{11, 5, 39};
   Time t1{11, 5, 40};
   Time t2{11, 5, 40};
   Time t3{12, 0, 0};

   SECTION("Comparisons")
   {
      CHECK(t0 < t1);
      CHECK_FALSE(t0 > t1);
      CHECK(t1 == t2);
      CHECK(t1 != t3);
      CHECK(t1 >= t2);
      CHECK(t3 >= t2);
      CHECK(t0 != t3);
   }

   SECTION("Stream")
   {
      std::stringstream oss{};
      oss << t0;
      CHECK(oss.str() == t0.to_string());
   }
}

TEST_CASE("Milliseconds")
{
   Time t0{};
   Time t1{12, 0, 0, 0};
   Time t2{12, 0, 0};
   Time t3{13, 43, 23, 300};
   Time t4{4, 45, 23, 32};
   Time t5{4, 45, 23, 4};
   Time t6{4, 45, 24, 4};

   SECTION("to_string")
   {
      CHECK_THROWS(Time {"1:b"});
      CHECK_THROWS(Time {"1:1899:49.111"});
      CHECK_THROWS(Time {"12:a:1"});
      CHECK_THROWS(Time {"12b2:1:1.1"});
      CHECK_THROWS(Time {"12:1:1:41"});
      CHECK(t0.to_string() == "00:00:00");
      CHECK(t1.to_string() == "12:00:00");
      CHECK(t2.to_string() == "12:00:00");
      CHECK(t3.to_string() == "13:43:23.300");
      CHECK(t3.to_string("12h") == "01:43:23.300pm");
      CHECK(t4.to_string() == "04:45:23.032");
      CHECK(t5.to_string() == "04:45:23.004");

      CHECK(t4.get_millisecond() == 32);
      CHECK(t3.get_millisecond() == 300);
   }

   SECTION("operator-")
   {
      CHECK( compare_equal(t4-t5, 0.028));
      CHECK( compare_equal(t5-t4, -0.028));
      CHECK(t6-t5 == 1);
   }
}

TEST_CASE("Increment operator")
{
   SECTION("Postfix increment")
   {

      Time t0 {12,0, 0};
      Time t1 {23, 59, 59};
      Time t2 {7,4,59};
      Time t3 {9, 59, 23};
      Time t4 {4, 5, 6, 300};
      Time t5 {2, 4, 59, 300};

      CHECK( t0++.to_string() == "12:00:00");
      CHECK( t0.to_string() == "12:00:01");
      CHECK( t1++.to_string() == "23:59:59");
      CHECK( t1.to_string() == "00:00:00");
      CHECK( t2++.to_string() == "07:04:59");
      CHECK( t2.to_string() == "07:05:00");
      CHECK( t3++.to_string() == "09:59:23");
      CHECK( t3.to_string() == "09:59:24");
      CHECK( t4++.to_string() == "04:05:06.300");
      CHECK( t4.to_string() == "04:05:07.300");
      CHECK( t5++.to_string() == "02:04:59.300");
      CHECK( t5.to_string() == "02:05:00.300");
      CHECK( t2 - (t2++) == 1.0);

   }

   SECTION("Postfix increment")
   {

      Time t0 {12,0, 0};
      Time t1 {23, 59, 59};
      Time t2 {7,4,59};
      Time t3 {9, 59, 23};
      Time t4 {4, 5, 6, 300};
      Time t5 {2, 4, 59, 300};

      CHECK( (++t0).to_string() == "12:00:01");
      CHECK( (++t1).to_string() == "00:00:00");
      CHECK( (++t2).to_string() == "07:05:00");
      CHECK( (++t3).to_string() == "09:59:24");
      CHECK( (++t4).to_string() == "04:05:07.300");
      CHECK( (++t5).to_string() == "02:05:00.300");
      CHECK( t2 - (++t2) == 0);

   }
   
}

// Fill with more tests of other functions and operators!
