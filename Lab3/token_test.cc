#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <iostream>
#include <sstream>

#include "token.h"

using namespace std;

const std::set<std::string> my_operators{
  "+", "+-+", "-", "*", "/", "%", "^", "=", "==", "(", ")", "?", "£", "$", "####"
    };

class Token_Private_Tester
{
public:
  Token_Private_Tester(Token& t) : t{t} {}
  
  bool is_delimeter(int c) const { return t.is_delimeter(c); }
  bool is_separator(int c) const { return t.is_separator(c); }

  bool is_candidate() const { return t.is_candidate(); }

  bool check_candidate(string const& s) { t.token = s; return t.is_candidate(); }

  Token& set(string const& s) { t.token = s; return t; }
  
private:
  Token& t;
};

TEST_CASE("help functions")
{
  Token tok{my_operators};
  Token_Private_Tester t{tok};

  CHECK( t.is_delimeter('+') );
  CHECK( t.is_delimeter('#') );
  CHECK( t.is_delimeter(' ') );
  CHECK_FALSE( t.is_delimeter('.') );
  
  CHECK( t.is_separator(' ') );
  CHECK_FALSE( t.is_separator('0') );
  
  CHECK(       t.check_candidate("+") );
  CHECK(       t.check_candidate("+-") );
  CHECK_FALSE( t.check_candidate("+-+") );
  CHECK_FALSE( t.check_candidate("+-++") );

}

TEST_CASE("classifier functions")
{
  Token tok{my_operators};
  Token_Private_Tester t{tok};
  
  CHECK( t.set("+").is_operator() );
  CHECK_FALSE( t.set("+-").is_operator() );
  CHECK( t.set("+-+").is_operator() );
  CHECK_FALSE( t.set("+-++").is_operator() );
  
  CHECK( t.set("123").is_integer() );
  CHECK( t.set("3.14").is_decimal() );
  CHECK( t.set("x_34").is_identifier() );

  CHECK_FALSE( t.set("123a").is_integer() );
  CHECK_FALSE( t.set("3.14.").is_decimal() );
  CHECK_FALSE( t.set("=x_34").is_identifier() );
}

TEST_CASE("normal input output")
{
  Token t{my_operators};
  istringstream iss{"1+2*34-sfd"};
  ostringstream oss{};
  
  while ( iss >> t )
  {
    oss << t << " ";
  }
  CHECK( oss.str() == "1 + 2 * 34 - sfd ");
}

TEST_CASE("normal input output, default operators")
{
  Token t;
  istringstream iss{"1+2*34-sfd"};
  ostringstream oss{};
  
  while ( iss >> t )
  {
    oss << t << " ";
  }
  CHECK( oss.str() == "1 + 2 * 34 - sfd ");
}

TEST_CASE("multichar operator input output")
{
  Token t{my_operators};
  istringstream iss{"1+-++2===as#####fgh"};
  ostringstream oss{};
  
  while ( iss >> t )
  {
    oss << t << " ";
  }
  CHECK( oss.str() == "1 +-+ + 2 == = as #### #fgh ");
}

int main(int argc, char* argv[] __attribute__((unused)))
{
  Catch::Session session;

  session.run();

   
  Token t{my_operators};
  string s;

  if ( argc <= 1 )
    return 0;
  
  cout << "Manual test mode, press Ctrl-D to exit. "
       << "Please enter lines to split: " << endl;
  while ( getline(cin, s) )
  {
    istringstream iss{s};
    
    while ( iss >> t )
    {
      if ( t.is_operator() )
        cout << "op: '" << t << "', ";
      else if ( t.is_integer() )
        cout << "int: '" << t << "', ";
      else if ( t.is_decimal() )
        cout << "double: '" << t << "', ";
      else if ( t.is_identifier() )
        cout << "var: '" << t << "', ";
      else
        cout << "token: '" << t << "', ";
    }
    cout << endl;
  }
  return 0;
}
