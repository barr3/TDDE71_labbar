#ifndef POSTFIX_H
#define POSTFIX_H

#include <string>
#include <vector>
#include <stack>
#include <map>
#include <istream>
#include <stdexcept>

class Infix_Error : public std::logic_error
{
    using std::logic_error::logic_error;
};

// Creates a Postfix from a given infix string. All operands and
// operators are required to be separated by at least one space.
class Postfix
{
public:
  Postfix(std::string const& infix_string);
    
  std::string to_string() const;
  operator std::string() const;
  bool operator==(std::string const& rhs) const;
  
private:
  using op_stack = std::stack<std::string>;
  using expression = std::vector<std::string>;
  
  expression expr;
  
  struct priority
  {
    int input;
    int stack;
  };
  
  using priority_table = std::map<std::string, Postfix::priority>;
 
  static const priority_table operator_table;

  static bool is_operator(const std::string& token);
  
  expression make_postfix(std::istream& is, bool match_parenthesis = false) const;
};

#endif
