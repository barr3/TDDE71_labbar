#include "postfix.h"
#include "token.h"

#include <string>
#include <vector>
#include <stack>
#include <map>
#include <istream>

#include <sstream>
#include <algorithm>
#include <iterator>

// PUBLIC

Postfix::Postfix(std::string const& infix_string) : expr{}
{
  std::istringstream is{infix_string};
  expr = make_postfix(is);
}
    
std::string Postfix::to_string() const
{
  std::ostringstream os;
  std::copy( std::begin(expr), std::end(expr),
             std::ostream_iterator<std::string>{os, " "});
  return os.str();
}

Postfix::operator std::string() const
{
  return to_string();
}

bool Postfix::operator==(std::string const& rhs) const
{
  return to_string() == rhs;
}


// PRIVATE

// right associative operators have input priority > stack priority  
// left associative operators have input priority < stack priority
const Postfix::priority_table Postfix::operator_table {
  // {symbol, input prio, stack prio}
  {"^", {8, 7}},
  {"*", {5, 6}},
  {"/", {5, 6}},
  {"%", {5, 6}},
  {"+", {3, 4}},
  {"-", {3, 4}},
  {"=", {2, 1}}
};

bool Postfix::is_operator(const std::string& token)
{
  // C++20: return operator_table.contains( token );
  return ( operator_table.count( token ) > 0 );
}

Postfix::expression Postfix::make_postfix(std::istream& is, bool match_parenthesis) const
{
  using namespace std::literals; // for string literals ""s
  
  op_stack operator_stack;
  expression postfix;
  Token token;
  int unused_operands{0};

  while (is >> token && token != ")"s )
  {
    if ( is_operator(token) )
    {
      while ( ! operator_stack.empty() && 
              operator_table.at(token).input <=
              operator_table.at(operator_stack.top()).stack )
      {
        postfix.push_back( operator_stack.top() );
        unused_operands -= 1; // uses 2 but creates 1
        operator_stack.pop();
      }
      operator_stack.push(token);
    }
    else if (token == "("s)
    {
      expression parentesis{ make_postfix(is, true) };
      std::copy( std::begin(parentesis), std::end(parentesis), std::back_inserter(postfix) );
      unused_operands += 1; // entire postix is 1 operand
    }
    else
    {
      postfix.push_back( token );
      unused_operands += 1;
    }
  }

  if ( postfix.empty() && match_parenthesis && token == ")"s )
  {
    throw Infix_Error{"Empty parenthesis"};
  }

  if ( match_parenthesis && token != ")"s )
  {
    throw Infix_Error{"Missing ending parenthesis"};
  }
    
  if ( ! match_parenthesis && token == ")"s )
  {
    throw Infix_Error{"Missing starting parenthesis"};
  }
    
  while ( ! operator_stack.empty() )
  {
    postfix.push_back( operator_stack.top() );
    unused_operands -= 1; // uses 2 but creates 1
    operator_stack.pop();
  }

  if ( unused_operands != 1 ) // the last one is the answer
  {
    if ( unused_operands > 1 )
      throw Infix_Error{"Missing operator"};
    else
      throw Infix_Error{"Missing operand"};
  }
    
  return postfix;
}
