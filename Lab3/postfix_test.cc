#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <iostream>
#include <sstream>

#include "postfix.h"

using namespace std;

TEST_CASE("infix to postfix conversion")
{
  CHECK( Postfix{"1"} == "1 ");

  CHECK( Postfix{"1 + 2"} == "1 2 + ");
  
  CHECK( Postfix{"1 + 2 + 3"} == "1 2 + 3 + ");
  CHECK( Postfix{"1 + 2 * 3"} == "1 2 3 * + ");
  CHECK( Postfix{"1 * 2 + 3"} == "1 2 * 3 + ");
  CHECK( Postfix{"1 ^ 2 ^ 3"} == "1 2 3 ^ ^ ");
  CHECK( Postfix{"1 - 2 - 3"} == "1 2 - 3 - ");
  CHECK( Postfix{"1 - 2 + 3"} == "1 2 - 3 + ");

  CHECK( Postfix{"1 / 2 - 3 * 4"} == "1 2 / 3 4 * - ");
  
  CHECK( Postfix{"( ( 0 ) )"} == "0 ");
  
  CHECK( Postfix{"( 1 ^ 2 ) ^ 3"} == "1 2 ^ 3 ^ ");
  CHECK( Postfix{"1 ^ ( 2 ^ 3 )"} == "1 2 3 ^ ^ ");
  CHECK( Postfix{"( 1 ^ ( 2 ^ 3 ) )"} == "1 2 3 ^ ^ ");
  CHECK( Postfix{"( ( 1 ^ ( 2 ) ^ 3 ) )"} == "1 2 3 ^ ^ ");

  CHECK( Postfix{"1 + 2 * 3 - 4 * 5 + 6 / 7 - 8"} == "1 2 3 * + 4 5 * - 6 7 / + 8 - ");
  CHECK( Postfix{"( 1 + 2 ) * 3 - ( 4 * 5 + 6 ) / 7 - 8"} == "1 2 + 3 * 4 5 * 6 + 7 / - 8 - ");

//  CHECK( Postfix{"(1+2)*3-(4*5+6)/7-8"} == "1 2 + 3 * 4 5 * 6 + 7 / - 8 - ");
}

TEST_CASE("infix to postfix conversion problems")
{
  // Missing operands (empty infix)
  CHECK_THROWS( Postfix("") );
  
  // Missing operands (empty paranthesis)
  CHECK_THROWS( Postfix("( )") );
  
  // Missing operands
  CHECK_THROWS( Postfix("1 +") );
  CHECK_THROWS( Postfix("+ 2") );

  // Missing operator
  CHECK_THROWS( Postfix("1 1 - 1") );
  
  // Missing parenthesis
  CHECK_THROWS( Postfix("( ) + 2") );
  CHECK_THROWS( Postfix("( + 2") );
  CHECK_THROWS( Postfix("1 + 2 )") );
}

int main()
{
  Catch::Session session;

  session.run();
  
  return 0;
}
