#include "List.h"
#include <iostream>
#include <sstream>

List::List() : head{nullptr}, tail{nullptr}
{
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
    int len {length()};
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

    for (int i { 0 }; i < length(); i++)
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
    for (int i { 0 }; i < index; i++)
    {
        if (current == nullptr)
        {
            throw std::logic_error("index out of range");
        }
        current = current->next;
    }

    return current;
}
