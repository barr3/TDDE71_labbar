#ifndef NODE
#define NODE

#include <string>

class Node
{
  public:
    Node() = default;
    Node(Node const&) = delete;
    Node& operator=(Node const&) = delete;
    virtual ~Node() = default;

    virtual double evaluate() const = 0;
    virtual std::string prefix() const = 0;
    virtual std::string infix() const = 0;
    virtual std::string postfix() const = 0;
};

#endif
