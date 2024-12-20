#include "Expression.h"
#include "Operands.h"
#include "Operators.h"
#include <cmath> // abs
#include <iostream>
#include <limits>
#include <memory>

#include "catch.hpp"

TEST_CASE("Operand real")
{
    Operand* pi{ new Real{ 3.14 } };

    CHECK(pi->evaluate() == 3.14);
    CHECK(pi->postfix() == "3.140");
}

TEST_CASE("Addition")
{
    Node* pi = new Real{ 3.14 };
    Node* e = new Real{ 2.72 };
    Node* pluslr = new Addition{ pi, e };
    Node* plusrl = new Addition{ e, pi };

    CHECK(pluslr->evaluate() == 5.86);
    CHECK(plusrl->evaluate() == 5.86);
    CHECK(pluslr->postfix() == "3.140 2.720 +");
    CHECK(plusrl->postfix() == "2.720 3.140 +");
}

bool compare_equal(double a, double b)
{
    return std::abs(a - b) <= std::numeric_limits<double>::epsilon();
}

TEST_CASE("Test case ignoring rounding errors")
{
    Node* a = new Real{ 0.01 };
    Node* b = new Real{ 0.09 };
    Node* plus = new Addition{ a, b };

    // CHECK( plus->evaluate() == 0.1 ); // Rounding error!!
    CHECK(compare_equal(plus->evaluate(), 0.1));
}

TEST_CASE("Operand integer")
{
    Operand* i = new Integer{ 7 };

    CHECK(i->evaluate() == 7);
    CHECK(i->postfix() == "7");
}

TEST_CASE("Subtraction")
{
    Node* a = new Integer{ 10 };
    Node* b = new Integer{ 9 };
    Node* c = new Real{ 5.0 };

    Node* s1 = new Subtraction{ a, b };
    Node* s2 = new Subtraction{ b, a };
    Node* s3 = new Subtraction{ a, c };

    CHECK(s1->evaluate() == 1);
    CHECK(s2->evaluate() == -1);
    CHECK(s3->evaluate() == 5.0);
    CHECK(s1->prefix() == "- 10 9");
    CHECK(s1->infix() == "( 10 - 9 )");
    CHECK(s1->postfix() == "10 9 -");
}

TEST_CASE("Multiplication")
{
    Node* a = new Real{ 2.0 };
    Node* b = new Real{ 5.0 };
    Node* c = new Real{ 0.0 };
    Node* d = new Integer{ 10 };
    Node* e = new Integer{ 0 };

    Node* m1 = new Multiplication{ a, b };
    Node* m2 = new Multiplication{ a, c };
    Node* m3 = new Multiplication{ a, d };
    Node* m4 = new Multiplication{ d, c };
    Node* m5 = new Multiplication{ d, e };

    CHECK(m1->evaluate() == 10.0);
    CHECK(m2->evaluate() == 0.0);
    CHECK(m3->evaluate() == 20.0);
    CHECK(m4->evaluate() == 0.0);
    CHECK(m5->evaluate() == 0.0);
    CHECK(m1->prefix() == "* 2.000 5.000");
    CHECK(m1->infix() == "( 2.000 * 5.000 )");
    CHECK(m1->postfix() == "2.000 5.000 *");
}

TEST_CASE("Division")
{
    Node* a = new Integer{ 10 };
    Node* b = new Real{ 2.0 };
    Node* c = new Integer{ 0 };
    Node* d = new Integer{ 5 };
    Node* e = new Integer{ 2 };

    Node* d1 = new Division{ a, b };
    Node* d2 = new Division{ a, c };
    Node* d3 = new Division{ d, e };

    CHECK(d1->evaluate() == 5.0);
    CHECK_THROWS(d2->evaluate());
    CHECK(d3->evaluate() == 2.5);
    CHECK(d1->prefix() == "/ 10 2.000");
    CHECK(d1->infix() == "( 10 / 2.000 )");
    CHECK(d1->postfix() == "10 2.000 /");
}

TEST_CASE("Exponentiation")
{
    Node* a = new Real{ 2 };
    Node* b = new Real{ 2 };
    Node* c = new Real{ 0 };
    Node* d = new Real{ -3 };
    Node* e = new Real{ 0.0001 };
    Node* f = new Real{ 2.453 };
    Node* g = new Integer{ 10 };
    Node* h = new Integer{ 2 };

    Node* exp = new Exponentiation{ a, b };
    Node* exp_2 = new Exponentiation{ c, d };
    Node* exp_3 = new Exponentiation{ d, f };
    Node* exp_4 = new Exponentiation{ e, d };
    Node* exp_5 = new Exponentiation{ g, h };
    Node* exp_6 = new Exponentiation{ g, a };

    CHECK(exp->evaluate() == 4);
    CHECK_THROWS(exp_2->evaluate());
    CHECK_THROWS(exp_3->evaluate());
    CHECK_NOTHROW(exp_4->evaluate());
    CHECK(exp_5->evaluate() == 100);
    CHECK(exp_6->evaluate() == 100);
    CHECK(exp->prefix() == "^ 2.000 2.000");
    CHECK(exp->infix() == "( 2.000 ^ 2.000 )");
    CHECK(exp->postfix() == "2.000 2.000 ^");
}

TEST_CASE("conversion to string")
{
    Node* a =
      new Addition{ new Subtraction{ new Real{ 1.0 }, new Integer{ 1 } },
                    new Multiplication{ new Integer{ 2 }, new Integer{ 5 } } };
    Node* b =
      new Exponentiation{ new Addition{ new Integer{ 2 }, new Real{ 23.0 } },
                          new Real{ 0.5 } };

    SECTION("prefix")
    {
        CHECK(a->prefix() == "+ - 1.000 1 * 2 5");
        CHECK(b->prefix() == "^ + 2 23.000 0.500");
    }
    SECTION("infix")
    {
        CHECK(a->infix() == "( ( 1.000 - 1 ) + ( 2 * 5 ) )");
        CHECK(b->infix() == "( ( 2 + 23.000 ) ^ 0.500 )");
    }
    SECTION("postfix")
    {
        CHECK(a->postfix() == "1.000 1 - 2 5 * +");
        CHECK(b->postfix() == "2 23.000 + 0.500 ^");
    }
}

TEST_CASE("Expression evaluation")
{
    Expression e1{ "3 + 4" };
    Expression e2{ "( 2 + 23.000 ) ^ 0.500" };
    Expression e3{ "3 - 4" };
    Expression e4{ "3 * 4" };
    Expression e5{ "18 / 3" };
    Expression e6{ "10.0 / 20" };
    Expression e7{ "( 4 * (20 - 16) ) ^ 2" };

    CHECK(e1.evaluate() == 7);
    CHECK(e2.evaluate() == 5.0);
    CHECK(e3.evaluate() == -1);
    CHECK(e4.evaluate() == 12);
    CHECK(e5.evaluate() == 6);
    CHECK(e6.evaluate() == 0.5);
    CHECK(e7.evaluate() == 256);
}

TEST_CASE("Expression errors")
{
    CHECK_THROWS(Expression{ "3 +" }); // Missing operand
    CHECK_THROWS(Expression{ "4 3" }); // Missing operator
    CHECK_THROWS(Expression{ "" });    // Empty expression
}

TEST_CASE("Expression massignment operator")
{
    Expression e1{ "1 + 1" };
    Expression e2 = std::move(e1);

    // e1.evaluate(); // Segmentation violation because e1 was moved
    CHECK(e2.evaluate() == 2);
}

TEST_CASE("Expression move constructor")
{
    Expression e1{ "1 + 1" };
    Expression e2{ std::move(e1) };

    // e1.evaluate(); // Segmentation violation because e1 was moved
    CHECK(e2.evaluate() == 2);
}

#if 0 // Flytta ned denna rad för att aktivera nästa TEST_CASE

#endif
