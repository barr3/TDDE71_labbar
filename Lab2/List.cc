#include "List.h"
#include <sstream>

List::List()
    : head{nullptr}, tail{nullptr}
{
}

// Copy constructor
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

// Move constructor
List::List(List &&other)
    : head{other.head}, tail{other.tail}
{
    other.head = nullptr;
    other.tail = nullptr;
}

// Copy assignment operator
List& List::operator=(List const &other)
{
    List temp { other };
    std::swap(temp.head, head);
    std::swap(temp.tail, tail);
    return *this;
}

// Move assignment operator
List& List::operator=(List &&other)
{
    std::swap(other.head, head);
    std::swap(other.tail, tail);
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
    if (is_empty()) 
    {
        tail = new_head;
    }

    head = new_head;
}

void List::push_back(int value)
{
    Node* new_tail { new Node { value, nullptr } };
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
    unsigned int len { length() };
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

void List::sort()
{
    if (is_empty() || head == tail) return;
    head = merge_sort(head);
}



void List::clear()
{
    while (!is_empty())
    {
        pop_front();
    }
    
}

int List::get(unsigned int index) const 
{
    if (is_empty())
    {
        throw std::logic_error("Cannot get values from empty list");
    }
    return get_node(index)->data;
}

int List::front() const
{
    if (is_empty())
    {
        throw std::logic_error("Cannot get front value of empty list");
    }
    return head->data;    
}

int List::back() const
{
    if (is_empty())
    {
        throw std::logic_error("Cannot get back value of empty list");
    }
    return tail->data;    
}

unsigned int List::length() const
{
    Node* current { head };
    int len { 0 };
    while (current != nullptr)
    {
        current = current->next;
        len++;
    }

    return len;
}

bool List::is_empty() const
{
    return head == nullptr;
}

std::string List::to_string() const
{
    std::stringstream ss { };
    Node* current { head };
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

List::Node* List::merge_sort(Node* node)
{
    if (!node || !node->next) return node;

    Node* middle {get_middle(node)};
    Node* second_half {middle->next};
    middle->next = nullptr;

    Node* left {merge_sort(node)};
    Node* right {merge_sort(second_half)};

    return merge_lists(left, right);
}

List::Node* List::get_middle(Node* node)
{
    Node* slow {node};
    Node* fast {node->next};

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

List::Node* List::merge_lists(Node* left, Node* right)
{
    if (!left) return right;
    if (!right) return left;

    if (left->data < right->data)
    {
        left->next = merge_lists(left->next, right);
        return left;
    }
    else 
    {
        right->next = merge_lists(left, right->next);
        return right;
    }
}