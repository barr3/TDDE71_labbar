#ifndef LIST
#define LIST

#include <string>

class List
{
public:
        List();
        List(List const &other);
        List(List &&other);
        List& operator=(List const &other);
        ~List();

        void insert_front(int value);
        void push_back(int value);
        void pop_front();
        void pop_back();
        bool is_empty() const;
        std::string to_string() const;

        int front() const;
        int back() const;

        int get(unsigned int index) const;

        void clear();
        unsigned int length() const;

private:
    struct Node 
    { 
        int data;
        Node* next;
    };  

    Node* head;
    Node* tail;

    Node* get_node(unsigned int index) const;
    Node* clone(Node* node);
};

#endif