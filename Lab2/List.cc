#include "List.h"
#include <iostream>
#include <sstream>

List::List()
    : head{nullptr}, tail{nullptr}
{
}

List::List(List const &other)
    : head{clone(other.head)}, tail{nullptr}
{
    unsigned int len {length()};

    if (len != 0)
    {
        tail = get_node(len - 1);
        tail->next = nullptr;
    }
}

List::List(List &&other)
    : head{other.head}, tail{other.tail}
{
    other.head = nullptr;
    other.tail = nullptr;
}

List& List::operator=(List const &other)
{
    List temp {other};
    std::swap(temp.head, head);
    std::swap(temp.tail, tail);
    return *this;
}

List::~List()
{
    while(not is_empty())
    {
        pop_front();
    }
}

void List::insert_front(int value)
{
    Node* new_head { new Node {value, head} };
    // new_head->next = head;
    // new_head->data = value;
    if (is_empty()) 
    {
        tail = new_head;
    }

    head = new_head;
}

void List::push_back(int value)
{
    Node* new_tail { new Node {value, nullptr}};
    // new_tail->next = nullptr;
    // new_tail->data = value;
    if (is_empty())
    {
        tail = new_tail;        
        head = new_tail;
    }
    else
    {
        tail->next = new_tail;
        tail = new_tail;
    }
}

void List::pop_front()
{
    if (!is_empty())
    {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

void List::pop_back()
{
    unsigned int len {length()};
    if (len > 1)
    {
        Node* previous = get_node(len-2);
        delete tail;
        tail = previous;
        tail->next = nullptr;
    }
    else if (len == 1)
    {
        delete tail;
        tail = nullptr;
        head = nullptr;
    }
}

bool List::is_empty() const
{
    return head == nullptr;
}

std::string List::to_string() const
{
    std::stringstream ss {};
    Node* current {head};
    ss << "[";

    for (unsigned int i { 0 }; i < length(); i++)
    {
        ss << current->data;
        if (i < length() - 1)
        {
            ss << ", ";
        }
        current = current->next;
    }
    ss << "]";

    return ss.str();
}

int List::front() const
{
    if (!is_empty())
    {
        return head->data;    
    }
    else
    {
        throw std::logic_error("Cannot get value from empty list");
    }
    
}

int List::back() const
{
    if (!is_empty())
    {
        return tail->data;    
    }
    else
    {
        throw std::logic_error("Cannot get value from empty list");
    }
    
}

int List::get(unsigned int index) const 
{
    // Node* current { head };
    // for (int i { 0 }; i < index; i++)
    // {
    //     current = current->next;
    // }

    // return current->data;

    return get_node(index)->data;
}

void List::clear()
{
    while (!is_empty())
    {
        pop_front();
    }
    
}

unsigned int List::length() const
{
    Node* current { head };
    int length {0};
    while (current != nullptr)
    {
        current = current->next;
        length++;
    }

    return length;
}

List::Node* List::get_node(unsigned int index) const 
{
    Node* current { head };
    for (unsigned int i { 0 }; i < index; i++)
    {
        if (current == nullptr)
        {
            throw std::logic_error("index out of range");
        }
        current = current->next;
    }

    return current;
}

List::Node* List::clone(List::Node* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    return new Node{node->data, clone(node->next)};
}
