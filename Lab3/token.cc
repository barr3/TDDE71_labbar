#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include <algorithm>
#include <cctype>

#include "token.h"

using namespace std;

// Public

set<string> const Token::default_operators{
  "+", "-", "*", "/", "%", "^", "=", "(", ")", "?", "£", "$"
    };

string const Token::default_separators{" \t\n\r"};

Token::Token(set<string> const& ops, string const& sep)
  : operators{ops}, separators{sep}, token{}
{
}

istream& operator>>(istream& iss, Token& t)
{
  return t.next(iss);
}

ostream& operator<<(ostream& oss, Token const& t)
{
  return oss << t.token;
}

bool Token::is_operator() const
{
  return operators.count( token ) == 1;
}

bool Token::is_integer() const
{
  return all_of(token.begin(), token.end(), ::isdigit);
}

bool Token::is_decimal() const
{
  bool valid_chars = all_of(token.begin(), token.end(), [](char c)->bool
                            {
                              return c == '.' || isdigit(c);
                            });
  bool one_dot = count(token.begin(), token.end(), '.') == 1;
  return valid_chars && one_dot;
}

bool Token::is_identifier() const
{
  return all_of(token.begin(), token.end(), [](char c)->bool
                {
                  return c == '_' || isalnum(c);
                });
}

// Private

bool Token::is_separator(int c) const
{
  return ( separators.find(c) != string::npos );
}

bool Token::is_delimeter(int c) const
{
  if ( c == -1 ) // Traits::eof()
    return true;
  
  if ( is_separator( c ) )
    return true;
  
  auto b{ operators.begin() };
  auto e{ operators.end() };
  
  for ( ; b != e; ++b )
  {
    if ( b->at(0) == c )
      return true;
  }
  return false;
}

bool Token::is_candidate() const
{
  auto b{ operators.begin() };
  auto e{ operators.end() };

  for ( ; b != e; ++b )
  {
    if ( b->find( token ) == 0 && *b != token )
      return true;
  }
  return false;
}

void Token::append(int c)
{
  token.push_back( static_cast<char>(c) );
}

void Token::ignore_separators(istream& iss)
{
  auto c{ iss.peek() };

  while ( c != -1 ) // Traits::eof()
  {
    if ( ! is_separator( c ) )
      return;
    
    iss.get();
    c = iss.peek();
  }
}

istream& Token::next(istream& iss)
{
  token.clear();

  ignore_separators( iss );
  
  auto c{ iss.peek() };

  bool prev_is_op{false};
  
  while ( c != -1 ) // Traits::eof()
  {
    append( c );

    bool is_op{ is_operator() };
    bool is_can{ is_candidate() };
    bool is_del{ is_delimeter(c) };
    
    if ( is_op && ! is_can )
    {
      iss.get();
      return iss;
    }

    if ( prev_is_op && ! is_op && ! is_can )
    {
      token.pop_back();
      return iss;
    }
    
    if ( is_del && ! is_can )
    {
      token.pop_back();
      return iss;
    }

    prev_is_op = is_op;
    iss.get();
    c = iss.peek();
  }
  
  return iss;
}
